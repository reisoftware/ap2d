#ifndef _MFCEX_EXCEL_H_
#define _MFCEX_EXCEL_H_

#include "export.h"
#include "excel9.h"
#include <string>
#include <vector>
#include "../afc/rpt.h"

namespace aex{

class AEXAPI Excel
{
public:
  Excel();
	~Excel();
  bool is_start()const;

public:
  void add_sheet(LPCTSTR name);

public:
	void add(const afc::xls::Book& xbook);
	void add(const std::vector<afc::xls::Sheet>& xsheets);
	void add(const afc::xls::Sheet& xsheet);

public:
	void set_text(const std::vector<afc::xls::Cell>& cells);
	void set_text(const afc::xls::Cell& cell);
	void set_border(const std::vector<afc::xls::Pos>& borders);
	void set_border(const afc::xls::Pos& borders);
	void set_w(const std::vector<double>& ws);
	void set_h(const std::vector<double>& hs);

public:
	void set_text(const afc::xls::Pos& pos, LPCTSTR content);
	void set_text(int x, int y, int w, int h, LPCTSTR content);

	void set_text_style(const afc::xls::Pos& pos, const afc::xls::CS& cs);

public:
	void save_as(const afc::xls::Book& xbook);
	void save_as(LPCTSTR file);
	
private:
  void init();
	void close();

private:
	void set_text(LPCTSTR pos, LPCTSTR content);
	void set_text_style(LPCTSTR pos, const char *name, long color, long size,	short is_blod, short is_italic);
	void set_range_interior(LPCTSTR pos, long color);
	void set_range_align(LPCTSTR pos, long h_align, long v_align);
	void set_border(LPCTSTR pos, BOOL grid = TRUE);
	void set_col_width(long col, float val);
	void set_row_height(long row, float val);

private:
	ref::_Worksheet sheet_;
	ref::Sheets sheets_;
	ref::_Workbook book_;
	ref::Workbooks books_;
	ref::_Application app_;

private:
  bool start_;
};

}//namespace

#endif//FILE
