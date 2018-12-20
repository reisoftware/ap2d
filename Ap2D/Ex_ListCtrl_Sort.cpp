
#include "stdafx.h"
#include "Ex_ListCtrl_Sort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(HeaderCtrl_Sort, CHeaderCtrl)

HeaderCtrl_Sort::HeaderCtrl_Sort()
MCT_INIT1("HeaderCtrl_Sort")
{
	ascending_ = true;
}

HeaderCtrl_Sort::~HeaderCtrl_Sort()
{
}


BEGIN_MESSAGE_MAP(HeaderCtrl_Sort, CHeaderCtrl)
	//{{AFX_MSG_MAP(HeaderCtrl_Sort)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HeaderCtrl_Sort message handlers
void HeaderCtrl_Sort::set_sort_arrow(const int column,const bool ascending)
{
	column_ = column;
	ascending_ = ascending;

	// change the item to owner drawn.
	HD_ITEM hditem;

	hditem.mask = HDI_FORMAT;
	VERIFY( GetItem( column, &hditem ) );
	hditem.fmt |= HDF_OWNERDRAW;
	VERIFY( SetItem( column, &hditem ) );

	// invalidate the header control so it gets redrawn
	Invalidate();
}

void HeaderCtrl_Sort::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDC dc;
	VERIFY( dc.Attach( lpDrawItemStruct->hDC ) );

	// save the device context.
	const int iSavedDC = dc.SaveDC();

	// get the column rect.
	CRect rc( lpDrawItemStruct->rcItem );

	// set the clipping region to limit drawing within the column.
	CRgn rgn;
	VERIFY( rgn.CreateRectRgnIndirect( &rc ) );
	(void)dc.SelectObject( &rgn );
	VERIFY( rgn.DeleteObject() );

	// draw the background,
	CBrush brush( GetSysColor( COLOR_3DFACE ) );
	dc.FillRect( rc, &brush );

	// get the column text and format.
	TCHAR szText[ 256 ];
	HD_ITEM hditem;

	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = szText;
	hditem.cchTextMax = 255;

	VERIFY( GetItem( lpDrawItemStruct->itemID, &hditem ) );

	// determine the format for drawing the column label.
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;

	if( hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if( hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;

	// adjust the rect if the mouse button is pressed on it.
	if( lpDrawItemStruct->itemState == ODS_SELECTED )
	{
		rc.left++;
		rc.top += 2;
		rc.right++;
	}

	CRect rcIcon( lpDrawItemStruct->rcItem );
	const int iOffset = ( rcIcon.bottom - rcIcon.top ) / 4;

	// adjust the rect further if the sort arrow is to be displayed.
	if( lpDrawItemStruct->itemID == (UINT)column_ )
		rc.right -= 3 * iOffset;

	rc.left += iOffset;
	rc.right -= iOffset;

	// draw the column label.
	if( rc.left < rc.right )
		(void)dc.DrawText( szText, -1, rc, uFormat );

	// draw the sort arrow.
	if( lpDrawItemStruct->itemID == (UINT)column_ )
	{
		// set up the pens to use for drawing the arrow.
		CPen penLight( PS_SOLID, 1, GetSysColor( COLOR_3DHILIGHT ) );
		CPen penShadow( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW ) );
		CPen* pOldPen = dc.SelectObject( &penLight );

		if( ascending_ )
		{
			// draw the arrow pointing upwards.
			dc.MoveTo( rcIcon.right - 2 * iOffset, iOffset);
			dc.LineTo( rcIcon.right - iOffset, rcIcon.bottom - iOffset - 1 );
			dc.LineTo( rcIcon.right - 3 * iOffset - 2, rcIcon.bottom - iOffset - 1 );
			(void)dc.SelectObject( &penShadow );
			dc.MoveTo( rcIcon.right - 3 * iOffset - 1, rcIcon.bottom - iOffset - 1 );
			dc.LineTo( rcIcon.right - 2 * iOffset, iOffset - 1);		
		}
		else
		{
			// draw the arrow pointing downwards.
			dc.MoveTo( rcIcon.right - iOffset - 1, iOffset );
			dc.LineTo( rcIcon.right - 2 * iOffset - 1, rcIcon.bottom - iOffset );
			(void)dc.SelectObject( &penShadow );
			dc.MoveTo( rcIcon.right - 2 * iOffset - 2, rcIcon.bottom - iOffset );
			dc.LineTo( rcIcon.right - 3 * iOffset - 1, iOffset );
			dc.LineTo( rcIcon.right - iOffset - 1, iOffset );		
		}

		// restore the pen.
		(void)dc.SelectObject( pOldPen );
	}

	// restore the previous device context.
	VERIFY( dc.RestoreDC( iSavedDC ) );

	// detach the device context before returning.
	(void)dc.Detach();
}

/////////////////////////////////////////////////////////////////////////////
// ListCtrl_Sort

LPCTSTR g_pszSection = _T("ListCtrls");
ListCtrl_Sort::ListCtrl_Sort()
	: m_iNumColumns( 0 )
	, m_iSortColumn( -1 )
	, m_bSortAscending( true )
	MCT_INIT2("ListCtrl_Sort")
{
}


ListCtrl_Sort::~ListCtrl_Sort()
{
}


BEGIN_MESSAGE_MAP(ListCtrl_Sort, CListCtrl)
	//{{AFX_MSG_MAP(ListCtrl_Sort)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ListCtrl_Sort message handlers

void ListCtrl_Sort::PreSubclassWindow()
{
	// the list control must have the report style.

  HWND  hwnd = ::GetDlgItem(m_hWnd,   0);   
  if(hwnd){   
		CWnd*   pHeader = CWnd::FromHandlePermanent(hwnd);   
		if(pHeader){   
			if(!pHeader->IsKindOf(RUNTIME_CLASS(HeaderCtrl_Sort))){   
				pHeader->Detach();   
				m_ctlHeader.SubclassWindow(hwnd);   
			}   
		}else   
			m_ctlHeader.SubclassWindow(hwnd);   
  }   
  CListCtrl::PreSubclassWindow();   
	
/*
	ASSERT( GetStyle() & LVS_REPORT );

	CListCtrl::PreSubclassWindow();
	m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) ;
*/	//加判断时，debug会崩掉，去掉列排序不好用
//	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}


BOOL ListCtrl_Sort::set_headings( UINT id_str )
{
	CString head_str;
	VERIFY( head_str.LoadString( id_str ) );
	return set_headings( head_str );
}

// the heading text is in the format column 1 text,column 1 width;column 2 text,column 3 width;etc.
BOOL ListCtrl_Sort::set_headings( const CString& head_str )
{
	int iStart = 0;
	for( ;; ){
		const int iComma = head_str.Find( _T(','), iStart );

		if( iComma == -1 )
			break;
		const CString strHeading = head_str.Mid( iStart, iComma - iStart );
		iStart = iComma + 1;
		int iSemiColon = head_str.Find( _T(';'), iStart );
		if( iSemiColon == -1 )
			iSemiColon = head_str.GetLength();
		const int iWidth = atoi( head_str.Mid( iStart, iSemiColon - iStart ) );
		iStart = iSemiColon + 1;
		if( InsertColumn( m_iNumColumns++, strHeading, LVCFMT_LEFT, iWidth ) == -1 )
			return FALSE;
	}
	return TRUE;
}


int ListCtrl_Sort::add_item( LPCTSTR contents, ... )
{
//	TRACE_OUT("\n####ListCtrl_Sort::add_item\n");

	const int iIndex = InsertItem( GetItemCount(), contents );

	LPTSTR* arrpsz = new LPTSTR[ m_iNumColumns ];
//	TRACE_OUT("####arrpsz : %d\n", arrpsz);
	arrpsz[ 0 ] = new TCHAR[ lstrlen( contents ) + 1 ];
//	TRACE_OUT("####arrpsz[0] : %d\n", arrpsz[0]);
	(void)lstrcpy( arrpsz[ 0 ], contents );

 	va_list list;
	va_start( list, contents );

	for( int iColumn = 1; iColumn < m_iNumColumns; iColumn++ )
	{
		contents = va_arg( list, LPCTSTR );
		ASSERT_VALID_STRING( contents );
		VERIFY( CListCtrl::SetItem( iIndex, iColumn, LVIF_TEXT, contents, 0, 0, 0, 0 ) );

		arrpsz[ iColumn ] = new TCHAR[ lstrlen( contents ) + 1 ];
//		TRACE_OUT("####arrpsz[%d] : %d\n", iColumn, arrpsz[iColumn]);
		(void)lstrcpy( arrpsz[ iColumn ], contents );
	}

	va_end( list );

	VERIFY( SetTextArray( iIndex, arrpsz ) );

	return iIndex;
}


void ListCtrl_Sort::FreeItemMemory( const int iItem )
{
//	TRACE_OUT("\n####ListCtrl_Sort::FreeItemMemory\n");
	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( iItem ) );
	if(!pid)
		return;
	LPTSTR* arrpsz = pid->arrpsz;

	for( int i = 0; i < m_iNumColumns; i++ )
	{
//		TRACE_OUT("####arrpsz[%d] : %d\n", i, arrpsz[i]);
		delete[] arrpsz[ i ];
	}

//	TRACE_OUT("####arrpsz : %d\n", arrpsz);
	delete[] arrpsz;
	delete pid;

	VERIFY( CListCtrl::SetItemData( iItem, NULL ) );
}


BOOL ListCtrl_Sort::DeleteItem( int iItem )
{
	FreeItemMemory( iItem );
	return CListCtrl::DeleteItem( iItem );
}


BOOL ListCtrl_Sort::DeleteAllItems()
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeItemMemory( iItem );

	return CListCtrl::DeleteAllItems();
}


bool IsNumber( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true;
}


int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	ASSERT_VALID_STRING( pszNumber1 );
	ASSERT_VALID_STRING( pszNumber2 );

	const int iNumber1 = atoi( pszNumber1 );
	const int iNumber2 = atoi( pszNumber2 );

	if( iNumber1 < iNumber2 )
		return -1;
	
	if( iNumber1 > iNumber2 )
		return 1;

	return 0;
}


bool IsDate( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	// format should be 99/99/9999.

	if( lstrlen( pszText ) != 10 )
		return false;

	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& pszText[ 2 ] == _T('/')
		&& _istdigit( pszText[ 3 ] )
		&& _istdigit( pszText[ 4 ] )
		&& pszText[ 5 ] == _T('/')
		&& _istdigit( pszText[ 6 ] )
		&& _istdigit( pszText[ 7 ] )
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}


int DateCompare( const CString& strDate1, const CString& strDate2 )
{
	const int iYear1 = atoi( strDate1.Mid( 6, 4 ) );
	const int iYear2 = atoi( strDate2.Mid( 6, 4 ) );

	if( iYear1 < iYear2 )
		return -1;

	if( iYear1 > iYear2 )
		return 1;

	const int iMonth1 = atoi( strDate1.Mid( 3, 2 ) );
	const int iMonth2 = atoi( strDate2.Mid( 3, 2 ) );

	if( iMonth1 < iMonth2 )
		return -1;

	if( iMonth1 > iMonth2 )
		return 1;

	const int iDay1 = atoi( strDate1.Mid( 0, 2 ) );
	const int iDay2 = atoi( strDate2.Mid( 0, 2 ) );

	if( iDay1 < iDay2 )
		return -1;

	if( iDay1 > iDay2 )
		return 1;

	return 0;
}


int CALLBACK ListCtrl_Sort::CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	ListCtrl_Sort* pListCtrl = reinterpret_cast<ListCtrl_Sort*>( lParamData );
	ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CListCtrl ) ) );

	ItemData* pid1 = reinterpret_cast<ItemData*>( lParam1 );
	ItemData* pid2 = reinterpret_cast<ItemData*>( lParam2 );

	ASSERT( pid1 );
	ASSERT( pid2 );

	LPCTSTR pszText1 = pid1->arrpsz[ pListCtrl->m_iSortColumn ];
	LPCTSTR pszText2 = pid2->arrpsz[ pListCtrl->m_iSortColumn ];

	ASSERT_VALID_STRING( pszText1 );
	ASSERT_VALID_STRING( pszText2 );

	if( IsNumber( pszText1 ) )
		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1, pszText2 ) : NumberCompare( pszText2, pszText1 );
	else if( IsDate( pszText1 ) )
		return pListCtrl->m_bSortAscending ? DateCompare( pszText1, pszText2 ) : DateCompare( pszText2, pszText1 );
	else
		// text.
		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1, pszText2 ) : lstrcmp( pszText2, pszText1 );
}
void ListCtrl_Sort::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	#ifdef _DEBUG
	return;
	#endif
	
	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );

	
	int cursel = GetSelectionMark();
	if(cursel != -1){
		EnsureVisible(cursel,TRUE);
	}	

	*pResult = 0;
}


void ListCtrl_Sort::Sort( int iColumn, bool bAscending )
{
	m_iSortColumn = iColumn;
	m_bSortAscending = bAscending;

	// show the appropriate arrow in the header control.
	m_ctlHeader.set_sort_arrow( m_iSortColumn, m_bSortAscending );

	VERIFY( SortItems( CompareFunction, reinterpret_cast<DWORD>( this ) ) );
}


void ListCtrl_Sort::LoadColumnInfo()
{
	// you must call this after setting the column headings.
	ASSERT( m_iNumColumns > 0 );

	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );

	UINT nBytes = 0;
	BYTE* buf = NULL;
	if( AfxGetApp()->GetProfileBinary( g_pszSection, strKey, &buf, &nBytes ) )
	{
		if( nBytes > 0 )
		{
			CMemFile memFile( buf, nBytes );
			CArchive ar( &memFile, CArchive::load );
			m_ctlHeader.Serialize( ar );
			ar.Close();

			m_ctlHeader.Invalidate();
		}

		delete[] buf;
	}
}


void ListCtrl_Sort::SaveColumnInfo()
{
	ASSERT( m_iNumColumns > 0 );

	CString strKey;
	strKey.Format( _T("%d"), GetDlgCtrlID() );

	CMemFile memFile;

	CArchive ar( &memFile, CArchive::store );
	m_ctlHeader.Serialize( ar );
	ar.Close();

	DWORD dwLen = memFile.GetLength();
	BYTE* buf = memFile.Detach();	

	VERIFY( AfxGetApp()->WriteProfileBinary( g_pszSection, strKey, buf, dwLen ) );

	free( buf );
}


void ListCtrl_Sort::OnDestroy() 
{
	for( int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeItemMemory( iItem );

	CListCtrl::OnDestroy();
}


BOOL ListCtrl_Sort::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	if( !CListCtrl::SetItemText( nItem, nSubItem, lpszText ) )
		return FALSE;

	LPTSTR* arrpsz = GetTextArray( nItem );
	LPTSTR pszText = arrpsz[ nSubItem ];
	delete[] pszText;
	pszText = new TCHAR[ lstrlen( lpszText ) + 1 ];
	(void)lstrcpy( pszText, lpszText );
	arrpsz[ nSubItem ] = pszText;

	return TRUE;
}


BOOL ListCtrl_Sort::SetItemData( int nItem, DWORD dwData )
{
	if( nItem >= GetItemCount() )
		return FALSE;

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	pid->dwData = dwData;

	return TRUE;
}


DWORD ListCtrl_Sort::GetItemData( int nItem ) const
{
	ASSERT( nItem < GetItemCount() );

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( nItem ) );
	ASSERT( pid );
	return pid->dwData;
}


BOOL ListCtrl_Sort::SetTextArray( int iItem, LPTSTR* arrpsz )
{
	ASSERT( CListCtrl::GetItemData( iItem ) == NULL );
	ItemData* pid = new ItemData;
	pid->arrpsz = arrpsz;
	return CListCtrl::SetItemData( iItem, reinterpret_cast<DWORD>( pid ) );
}


LPTSTR* ListCtrl_Sort::GetTextArray( int iItem ) const
{
	ASSERT( iItem < GetItemCount() );

	ItemData* pid = reinterpret_cast<ItemData*>( CListCtrl::GetItemData( iItem ) );
	return pid->arrpsz;
}
void ListCtrl_Sort::get_check_items(CStringArray& items,int col)
{
	CString str;
	for(int i=0;i<GetItemCount();i++){
		if(GetCheck(i)){
			str = GetItemText(i,col);
			items.Add(str);
		}
	}		
}


void ListCtrl_Sort::get_check_items(CStringArray& items,std::vector<int>& rows,int col)
{
	CString str;
	for(int i=0;i<GetItemCount();i++){
		if(GetCheck(i)){
			str = GetItemText(i,col);
			items.Add(str);
			rows.push_back(i);
		}
	}		
}
void ListCtrl_Sort::get_items(CStringArray& items,int col)
{
	CString str;
	for(int i=0;i<GetItemCount();i++){
		str = GetItemText(i,col);
		items.Add(str);
	}		

}
void ListCtrl_Sort::get_items(std::vector<std::string>& items,int col)
{
	CString str;
	for(int i=0;i<GetItemCount();i++){
		str = GetItemText(i,col);
		items.push_back(str.GetBuffer(0));
	}		

}
void ListCtrl_Sort::get_rows(std::vector<std::string>& items,int col)
{
	CString str;
	for(int i=0;i<GetItemCount();i++){
		str = GetItemText(i,col);
		items.push_back(str.GetBuffer(0));
	}		

}

BOOL ListCtrl_Sort::find_str(CString str_find,int col)
{
	CStringArray items;
	get_items(items,col);
	for(int i=0;i<items.GetSize();i++){
		if(strcmp(items[i],str_find)==0)
			return TRUE;
	}
	return FALSE;
}
int ListCtrl_Sort::find_pos(CString str_find,int col)
{
	CStringArray items;
	get_items(items,col);
	for(int i=0;i<items.GetSize();i++){
		if(strcmp(items[i],str_find)==0)
			return i;
	}
	return -1;

}
CString ListCtrl_Sort::get_select()
{
	POSITION pos = GetFirstSelectedItemPosition();
	int nItem = GetNextSelectedItem(pos);
	return GetItemText(nItem,0);

}
void ListCtrl_Sort::change(std::string val,int row,int col)
{
	SetItemText(row,col,val.c_str());

}
void ListCtrl_Sort::get_select_rows(std::vector<std::string>& items,int col)
{
	POSITION pos = GetFirstSelectedItemPosition();
	while(pos){
		int nItem = GetNextSelectedItem(pos);
		CString temp =  GetItemText(nItem,col);
		items.push_back(temp.GetBuffer(0));
	}

}
int ListCtrl_Sort::count_col()
{
	CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
	return pHeaderCtrl->GetItemCount();	
}
int ListCtrl_Sort::get_select_row(Vals& vals)
{
	POSITION pos = GetFirstSelectedItemPosition();
	int nItem = GetNextSelectedItem(pos);
	if(nItem == -1)
		return -1;
	Val val;
	CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
	for(int i=0;i<pHeaderCtrl->GetItemCount();i++){
		HDITEM hdi;
		hdi.mask = HDI_TEXT;
		TCHAR  lpBuffer[256];
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = 256;
		pHeaderCtrl->GetItem(i, &hdi);

		val.head = hdi.pszText;
		val.val = GetItemText(nItem,i);
		val.check = FALSE;
		vals.push_back(val);
	}
	return nItem;

}
void ListCtrl_Sort::set_row_val(const Vals& vals,int row)//row=0时，改变当前选中行的值
{
	if(row == -1){
		POSITION pos = GetFirstSelectedItemPosition();
		row = GetNextSelectedItem(pos);
		if(row == -1)
			return ;
	}
	for(int i=0;i<vals.size();i++){
		if(vals[i].check)
			SetItemText(row,i,vals[i].val.c_str());

	}
	//需要循环整个list，有相同的前三项时，把以后的值也改变。

}
void ListCtrl_Sort::set_row_val(const Vals& olds,const Vals& vals)
{
	POSITION pos = GetFirstSelectedItemPosition();
	while(pos){
		int nItem = GetNextSelectedItem(pos);
		for(int j=2;j<vals.size();j++){
			if(vals[j].check)
				SetItemText(nItem,j,vals[j].val.c_str());
		}
	}

/*
	CString one,two,three;
	for(int i=0;i<GetItemCount();i++){
		two = GetItemText(i,1);
		three = GetItemText(i,2);
		if(strcmp(two,olds[1].val.c_str())==0 &&
			strcmp(three,olds[2].val.c_str())==0 ){
				for(int j=0;j<vals.size();j++){
					if(vals[j].check)
						SetItemText(i,j,vals[j].val.c_str());
				}

		}
	}		
*/

}