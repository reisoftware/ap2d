#ifndef _EX_LISTCTRL_SORT_H_
#define _EX_LISTCTRL_SORT_H_
//Ex_ListCtrl_Sort.h
#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

#include <vector>
#include "counter.h"

class HeaderCtrl_Sort : public CHeaderCtrl
{
	DECLARE_DYNCREATE(HeaderCtrl_Sort)   
// Construction
public:
	HeaderCtrl_Sort();

public:
	void set_sort_arrow(const int column,const bool ascending);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HeaderCtrl_Sort)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~HeaderCtrl_Sort();

protected:
	int column_;
	BOOL ascending_;

	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	DECLARE_MESSAGE_MAP()
private:
	MCT_DEF
};


struct Val
{
	Val()MCT_INIT1("Val"){}
	std::string head;
	std::string val;
	bool check;
private:
	MCT_DEF
};
typedef std::vector<Val> Vals;




class ListCtrl_Sort : public CListCtrl
{

	struct ItemData

	{
	public:
		ItemData() : arrpsz( NULL ), dwData( NULL )MCT_INIT2("ItemData") {}

		LPTSTR* arrpsz;
		DWORD dwData;

	private:
		// ban copying.
		ItemData( const ItemData& );
		ItemData& operator=( const ItemData& );
	private:
		MCT_DEF
	};

// Construction
public:
	ListCtrl_Sort();

public:
	BOOL set_headings( UINT id_str );
	BOOL set_headings( const CString& head_str );

	int add_item( LPCTSTR contents, ... );
	BOOL DeleteItem( int iItem );
	BOOL DeleteAllItems();
	void LoadColumnInfo();
	void SaveColumnInfo();
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	void Sort( int iColumn, bool bAscending );
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD GetItemData(int nItem) const;

	void get_check_items(CStringArray& items,int col=0);
	void get_items(CStringArray& items,int col=0);
	void get_items(std::vector<std::string>& items,int col=0);
	void get_check_items(CStringArray& items,std::vector<int>& rows,int col=0);
	BOOL find_str(CString str_find,int col=0);
	int find_pos(CString str_find,int col=0);

	CString get_select();
	void change(std::string val,int row =0,int col=0);

	void get_select_rows(std::vector<std::string>& items,int col=0);
	void get_rows(std::vector<std::string>& items,int col=0);
	int get_select_row(Vals& vals);
	int count_col();
	void set_row_val(const Vals& vals,int row=-1);//row=0时，改变当前选中行的值
	void set_row_val(const Vals& olds,const Vals& vals);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListCtrl_Sort)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ListCtrl_Sort();

	// Generated message map functions
protected:
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	void FreeItemMemory( const int iItem );
	BOOL SetTextArray( int iItem, LPTSTR* arrpsz );
	LPTSTR* GetTextArray( int iItem ) const;

	HeaderCtrl_Sort m_ctlHeader;

	int m_iNumColumns;
	int m_iSortColumn;
	bool m_bSortAscending;
	//{{AFX_MSG(ListCtrl_Sort)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()



private:
	MCT_DEF

};

#endif
