#include "StdAfx.h"
#include "xls_excel.h"
#include "xls_tools.h"
#include <comdef.h>
#include <cassert>
#include "../afc/trace.h"

namespace aex{

Excel::Excel()
:start_(true)
{
	afc::Trace at;
	at.trace("Excel::Excel()");
	::CoInitialize(NULL);//COM
	if(!app_.CreateDispatch("Excel.Application")){
    //AfxMessageBox("Office Excel not find.");
    start_ = false;
  }else{
		books_ = app_.GetWorkbooks();
		//COleVariant covOptional2(1l);
		book_ = books_.Add (COleVariant(1l));//covOptional2);
		sheets_ = book_.GetSheets();
		sheet_ = sheets_.GetItem(COleVariant((long)sheets_.GetCount()));
		app_.SetVisible(FALSE);
		app_.SetUserControl(TRUE);
	}
  init();
}

Excel::~Excel()
{
	close();
	::CoUninitialize();//COM
	afc::Trace at;
	at.trace("Excel::~Excel()");
}

bool Excel::is_start()const
{
  return start_;
}

void Excel::add_sheet(LPCTSTR name)
{
  sheet_ = sheets_.Add(vtMissing, _variant_t(sheet_), COleVariant(1l), vtMissing);
  sheet_.SetName(name);
}

void Excel::set_text(const std::vector<afc::xls::Cell>& cells)
{
	int n=cells.size();
	int i=0;
	for(i=0; i<n; ++i){
		set_text(cells[i]);
	}
}

void Excel::add(const afc::xls::Book& xbook)
{
	add(xbook.sheets);
}

void Excel::add(const std::vector<afc::xls::Sheet>& xsheets)
{
	int n=xsheets.size();
	int i=0;
	for(i=0; i<n; ++i){
		add(xsheets[i]);
	}
}

void Excel::add(const afc::xls::Sheet& xsheet)
{
	add_sheet(xsheet.name());
	set_text(xsheet.cells);
	set_border(xsheet.borders);
	set_w(xsheet.ws);
	set_h(xsheet.hs);
}

void Excel::set_text(const afc::xls::Cell& cell)
{
	set_text(cell.pos, cell.content);
	set_text_style(cell.pos, cell.style);
}

void Excel::set_text(const afc::xls::Pos& pos, LPCTSTR content)
{
	set_text(pos.x, pos.y, pos.w, pos.h, content);
}

void Excel::set_text(int x, int y, int w, int h, LPCTSTR content)
{
	std::string pos = aex::xls::get_regular_pos(x, y, w, h);
	set_text(pos.c_str(), content);
}

void Excel::set_border(const std::vector<afc::xls::Pos>& borders)
{
	int n=borders.size();
	int i=0;
	for(i=0; i<n; ++i){
		set_border(borders[i]);
	}
}

void Excel::set_border(const afc::xls::Pos& borders)
{
	afc::string pos = aex::xls::get_regular_pos(borders);
	set_border(pos, TRUE);
}

void Excel::set_w(const std::vector<double>& ws)
{
	int n=ws.size();
	int i=0;
	for(; i<n; ++i){
		set_col_width(i+1, ws[i]);
	}

// 	std::vector<afc::xls::pair>::const_iterator it = ws.begin();
// 	for(; it != ws.end(); it++){
// 		int a = it->first;
// 		double b = it->second;
// 		set_col_width(it->first, it->second);
// 	}
}

void Excel::set_h(const std::vector<double>& hs)
{
	int n=hs.size();
	int i=0;
	for(; i<n; ++i){
		set_row_height(i+1, hs[i]);
	}

// 	std::vector<afc::xls::pair>::const_iterator it = hs.begin();
// 	for(; it != hs.end(); it++){
// 		set_row_height(it->first, it->second);
// 	}
}

//
void Excel::set_text_style(const afc::xls::Pos& pos, const afc::xls::CS& cs)
{
	afc::string posstr = aex::xls::get_regular_pos(pos);
	set_text_style(posstr, cs.font, cs.text_color, cs.size, cs.blod, cs.italic);
	set_range_interior(posstr, cs.back_color);
	set_range_align(posstr, cs.h_align, cs.v_align);
}

//
void Excel::save_as(const afc::xls::Book& xbook)
{
	add(xbook);
	save_as(xbook.name);
}

void Excel::save_as(LPCTSTR file)
{
	//app_.SetDisplayAlerts(FALSE);//取消覆盖提示
	book_.SaveAs(COleVariant(file),vtMissing,vtMissing,vtMissing,
		vtMissing,vtMissing,0,COleVariant((short)TRUE),
		vtMissing,vtMissing,vtMissing);
}



///////////////// << private >> /////////////////
void Excel::init()
{
}

void Excel::close()
{
	COleVariant varTrue(short(1),VT_BOOL);
	COleVariant varFalse(short(0),VT_BOOL);
	//app_.SetAlertBeforeOverwriting(FALSE);
	app_.SetDisplayAlerts(FALSE);
  app_.Quit();    
}

void Excel::set_text(LPCTSTR pos, LPCTSTR content)
{
	assert(aex::xls::is_regular_pos(pos) && "Excel::set_text(), pos isn't regular.");
	ref::Range range = sheet_.GetRange(COleVariant(pos), vtMissing);
	range.Merge(COleVariant((long)0)); 
	range.SetValue(COleVariant(content));
	range.ReleaseDispatch();
}

void Excel::set_text_style(	LPCTSTR pos, 
														LPCTSTR fontname, 
														long color, 
														long size, 
														short is_blod, 
														short is_italic)
{
	ref::Range range = sheet_.GetRange(COleVariant(pos), vtMissing);
	ref::Font font = range.GetFont();
	font.SetName(COleVariant(fontname));
	font.SetSize(COleVariant(size));
	font.SetColorIndex(COleVariant(color));
	font.SetItalic(COleVariant((short)is_italic));
	font.SetBold(COleVariant((short)is_blod));

	range.ReleaseDispatch();
}

void Excel::set_range_interior(LPCTSTR pos, long color)
{
	ref::Range range = sheet_.GetRange(COleVariant(pos), vtMissing);
	ref::Interior inter = range.GetInterior();
	inter.SetColorIndex(COleVariant(color));
}

void Excel::set_range_align(LPCTSTR pos, long h_align, long v_align)
{
	ref::Range range = sheet_.GetRange(COleVariant(pos), vtMissing);
	range.SetHorizontalAlignment(COleVariant(h_align));
	range.SetVerticalAlignment(COleVariant(v_align));
}

void Excel::set_border(LPCTSTR pos, BOOL grid)
{
	ref::Range range = sheet_.GetRange(COleVariant(pos), vtMissing);
// 	Range range = cur_sheet_.GetRange(
// 		COleVariant(NumToPos(rect.top,rect.left))
// 		,COleVariant(NumToPos(rect.bottom,rect.right)));

	ref::Borders borders = range.GetBorders();
	if (grid) {
		borders.SetLineStyle(COleVariant((short)1));
	}
	else {
		ref::Border border;
		border=borders.GetItem(7); 
		border.SetLineStyle(COleVariant((short)1)); 
		border=borders.GetItem(8); 
		border.SetLineStyle(COleVariant((short)1)); 
		border=borders.GetItem(9); 
		border.SetLineStyle(COleVariant((short)1)); 
		border=borders.GetItem(10); 
		border.SetLineStyle(COleVariant((short)1)); 
	}
	borders.ReleaseDispatch();
}

void Excel::set_row_height(long row, float val)
{
	afc::string pos = xls::get_regular_pos(0, row, 1, 1);
	ref::Range range = sheet_.GetRange(COleVariant(pos.c_str()), vtMissing);
	range.SetRowHeight(COleVariant(val));
}

void Excel::set_col_width(long col, float val)
{
	afc::string pos = xls::get_regular_pos(col, 0, 1, 1);
	ref::Range range = sheet_.GetRange(COleVariant(pos.c_str()), vtMissing);
	range.SetColumnWidth(COleVariant(val));
}



}//namespace
