#ifndef _AFC_LISTCTRL_H_
#define _AFC_LISTCTRL_H_


#include "windows.h" 
#include <commctrl.h> 
#include <string>


class List_Ctrl 
{ 
public: 
  List_Ctrl(); 
  ~List_Ctrl(); 
  void init(HWND hlistctrl); 
  void init(HWND hdlg, int listctrlid);
  
public:
  DWORD SetExtendedStyle(DWORD dwNewStyle); 
  DWORD GetExtendedStyle();
  
  int InsertColumn(int nCol, const LVCOLUMN* pColumn);
  int InsertColumn(int nCol, int nWidth, LPCTSTR heading); 
  int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1 );
  
  int InsertItem(const LVITEM* pItem);
  int InsertItem(LPCSTR lpString); 

  BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
  BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText ); 

  std::string GetItemText(int nItem, int nSubItem);

  int GetItemCount(); 
  int GetSelectionMark();

  BOOL DelteItem(int nItem); 
  BOOL DeleteAllItems(); 
  


private:
  HWND hwnd_; 

}; 


#endif//FILE
