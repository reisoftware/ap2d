#include "stdafx.h"
#include "list_ctrl.h" 

#include <cassert>


static LVITEM lvGetItemData; 


List_Ctrl::List_Ctrl() 
{ 
  hwnd_=NULL; 
} 

List_Ctrl::~List_Ctrl() 
{ 
  hwnd_=NULL; 
} 

void List_Ctrl::init(HWND hlistctrl) 
{ 
  hwnd_=hlistctrl; 
//  return true; 
} 

void List_Ctrl::init(HWND hdlg, int listctrlid)
{
  assert(::IsWindow(hdlg));
  HWND hlc = ::GetDlgItem(hdlg, listctrlid);
  assert(::IsWindow(hlc));
  hwnd_ = hlc;
}

////////////////////  <<<  style  >>>  ////////////////////
DWORD List_Ctrl::SetExtendedStyle(DWORD dwNewStyle) 
{ 
  assert(::IsWindow(hwnd_)); 
  return (DWORD)::SendMessage(hwnd_,LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwNewStyle); 
}

DWORD List_Ctrl::GetExtendedStyle()
{
  assert(::IsWindow(hwnd_)); 
  return (DWORD)::SendMessage(hwnd_, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
} 

////////////////////  <<<  InsertColumn  >>>  ////////////////////
int List_Ctrl::InsertColumn(int nCol, const LVCOLUMN* pColumn)
{ 
  assert(::IsWindow(hwnd_)); 
  return (int) ::SendMessage(hwnd_, LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn); 
}

int List_Ctrl::InsertColumn(int nCol, int nWidth, LPCTSTR heading) 
{ 
  assert(::IsWindow(hwnd_)); 
  return InsertColumn(nCol, heading, LVCFMT_LEFT, nWidth); 
} 

int List_Ctrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat,
                            int nWidth, int nSubItem)
{
  LVCOLUMN column;
  column.mask = LVCF_TEXT|LVCF_FMT;
  column.pszText = (LPTSTR)lpszColumnHeading;
  column.fmt = nFormat;
  if (nWidth != -1)
  {
    column.mask |= LVCF_WIDTH;
    column.cx = nWidth;
  }
  if (nSubItem != -1)
  {
    column.mask |= LVCF_SUBITEM;
    column.iSubItem = nSubItem;
  }
  return List_Ctrl::InsertColumn(nCol, &column);
}

////////////////////  <<<  InsertItem  >>>  ////////////////////
int List_Ctrl::InsertItem(const LVITEM* pItem)
{ 
  assert(::IsWindow(hwnd_)); 
  return (int) ::SendMessage(hwnd_, LVM_INSERTITEM, 0, (LPARAM)pItem); 
}

int List_Ctrl::InsertItem(LPCSTR lpString) 
{ 
  assert(::IsWindow(hwnd_)); 
  LV_ITEM lv; 
  lv.mask=LVIF_TEXT; 
  lv.cchTextMax=MAX_PATH; 
  lv.iItem=GetItemCount(); 
  lv.iSubItem=0; 
  lv.pszText=const_cast<LPSTR>(lpString); 
  return InsertItem(&lv); 
} 

////////////////////  <<<  SetItem  >>>  ////////////////////
BOOL List_Ctrl::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
                        int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
{
  assert(::IsWindow(hwnd_));
  //ASSERT((GetStyle() & LVS_OWNERDATA)==0);
  LVITEM lvi;
  lvi.mask = nMask;
  lvi.iItem = nItem;
  lvi.iSubItem = nSubItem;
  lvi.stateMask = nStateMask;
  lvi.state = nState;
  lvi.pszText = (LPTSTR) lpszItem;
  lvi.iImage = nImage;
  lvi.lParam = lParam;
  return (BOOL) ::SendMessage(hwnd_, LVM_SETITEM, 0, (LPARAM)&lvi);
}

BOOL List_Ctrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText ) 
{ 
  assert(::IsWindow(hwnd_));
  //assert((GetStyle() & LVS_OWNERDATA)==0);
  LVITEM lvi;
  lvi.iSubItem = nSubItem;
  lvi.pszText = (LPTSTR) lpszText;
  return (BOOL) ::SendMessage(hwnd_, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi);
} 

////////////////////  <<<  Get  >>>  ////////////////////
std::string List_Ctrl::GetItemText(int nItem, int nSubItem)
{
  assert(::IsWindow(hwnd_));
  LVITEM lvi;
  memset(&lvi, 0, sizeof(LVITEM));
  lvi.iSubItem = nSubItem;
  int nLen = 128;
  char buf[128];
  int nRes;
  do
  {
    nLen *= 2;
    lvi.cchTextMax = nLen;
    lvi.pszText = buf;
    nRes  = (int)::SendMessage(hwnd_, LVM_GETITEMTEXT, (WPARAM)nItem,
      (LPARAM)&lvi);
  } while (nRes == nLen-1);

  std::string str = buf;
  return str;
}

int List_Ctrl::GetSelectionMark()
{
  return ::SendMessage(hwnd_, LVM_GETSELECTIONMARK, 0, 0);
}

int List_Ctrl::GetItemCount() 
{ 
  assert(::IsWindow(hwnd_)); 
  return ::SendMessage(hwnd_,LVM_GETITEMCOUNT,0,0);; 
} 

////////////////////  <<<  delete  >>>  ////////////////////
BOOL List_Ctrl::DelteItem(int nItem) 
{ 
  assert(::IsWindow(hwnd_)); 
  return (BOOL)::SendMessage(hwnd_, LVM_DELETEITEM, nItem,0); 
} 

BOOL List_Ctrl::DeleteAllItems()
{
  while(GetItemCount() > 0){
    if(!DelteItem(0)){
      return FALSE;
    }
  }
  return TRUE;
}



