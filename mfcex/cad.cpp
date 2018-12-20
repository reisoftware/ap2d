#include "stdafx.h"
#include "cad.h"
#include <cassert>
#include "../object/Text.h"
#include "../object/Line.h"
#include "../object/Matrix_d.h"
#include "../afc/format.h"
#include "../afc/trace.h"


namespace aex{

Object::Object(const afc::xls::Book& xbook, const dlhml::Point& org)
:xbook_(xbook)
,org_(org)
// ,dis_(dis)
// ,ents_(NULL)
{
}

//////////////////////////////////////////////////////
// static double get_s_sum(const std::vector<afc::xls::pair>& ps)
// {
// 	double sum = 0;
// 	int n=ps.size();
// 	int i=0;
// 	for(; i<n; ++i){
// 		sum += ps[i].second;
// 	}
// 	return sum;
// }

// static double get_dis_sum(const std::vector<afc::xls::pair>& ps, int pid, BOOL LT)
// {
// 	int n = ps.size();
// 	assert(pid >= 1);
// 	int fsum = 0;
// 	double sum = 0;
// 	int flimit = pid- (LT?1:0);
// 	int i=0;
// 	for(; i<n; ++i){
// 		if(ps[i].first <= flimit){
// 			sum += ps[i].second;
// 		}
// 	}
// 	return sum;
// }

static dlhml::Rect get_cell_rect(const std::vector<double>& ws, 
																 const std::vector<double>& hs,
																 const afc::xls::Pos& pos,
																 const dlhml::Point& org)
{
	dlhml::Rect rc;
	rc.xmin(afc::xls::get_size_sum(ws, pos.left()-1) + org.x);
	rc.ymax(-afc::xls::get_size_sum(hs, pos.top()-1) + org.y);
	rc.xmax(afc::xls::get_size_sum(ws, pos.right()) + org.x);
	rc.ymin(-afc::xls::get_size_sum(hs, pos.bottom()) + org.y);
	return rc;
}

static void set_text_rect(dlhml::Text& txt, 
													const dlhml::Rect& rc, 
													int h_align, 
													int v_align)
{
	double xcen = (rc.xmin()+rc.xmax())/2;
	double ycen = (rc.ymin()+rc.ymax())/2;
	//左
	if(h_align == 2){
		//上
		if(v_align == 1){
			txt.position(dlhml::Point(rc.xmin(), rc.ymax()));
			txt.align_point(dlhml::Text::left_top);
		} 
		//下
		else if(v_align == 3){
			txt.position(dlhml::Point(rc.xmin(), rc.ymin()));
			txt.align_point(dlhml::Text::left_bottom);
		} 
		//中
		else{
			txt.position(dlhml::Point(rc.xmin(), ycen));
			txt.align_point(dlhml::Text::left_center);
		} 
	}
	//右
	else if(h_align == 4){
		//上
		if(v_align == 1){
			txt.position(dlhml::Point(rc.xmax(), rc.ymax()));
			txt.align_point(dlhml::Text::right_top);
		} 
		//下
		else if(v_align == 3){
			txt.position(dlhml::Point(rc.xmax(), rc.ymin()));
			txt.align_point(dlhml::Text::right_bottom);
		} 
		//中
		else{
			txt.position(dlhml::Point(rc.xmax(), ycen));
			txt.align_point(dlhml::Text::right_center);
		} 
	}
	//中
	else{
		//上
		if(v_align == 1){
			txt.position(dlhml::Point(xcen, rc.ymax()));
			txt.align_point(dlhml::Text::center_top);
		} 
		//下
		else if(v_align == 3){
			txt.position(dlhml::Point(xcen, rc.ymin()));
			txt.align_point(dlhml::Text::center_bottom);
		} 
		//中
		else{
			txt.position(dlhml::Point(xcen, ycen));
			txt.align_point(dlhml::Text::center_center);
		} 
	}
	
}


//////////////////////////////////////////////////////

void Object::output(std::vector<dlhml::Entity*>& ents, 
										const dlhml::Rect& rect)
{
	dlhml::Entity * ent = NULL;
  dlhml::Point st,ed;
  dlhml::Line ln;
  ln.color_index(7);
  
  st.setdata(rect.xmin(),rect.ymin());
  ed.setdata(rect.xmin(),rect.ymax());
  ln.setdata(st,ed);
  ent = ln.clone();
	ents.push_back(ent);
  
  st.setdata(rect.xmax(),rect.ymax());
  ln.setdata(st,ed);
  ent = ln.clone();
	ents.push_back(ent);
  
  ed.setdata(rect.xmax(),rect.ymin());
  ln.setdata(st,ed);
  ent = ln.clone();
	ents.push_back(ent);
  
  st.setdata(rect.xmin(),rect.ymin());
  ln.setdata(st,ed);
  ent = ln.clone();
	ents.push_back(ent);
}

void Object::output(std::vector<dlhml::Entity*>& ents, 
										const dlhml::Rect& rect,
										const afc::xls::Cell& cell)
{
// 	afc::Trace at;
// 	at.trace("output_rect_text()");
	dlhml::Entity * ent = NULL;
	dlhml::Text txt;
	//txt.fo
	afc::string str = cell.content;
	if(cell.style.precision >0){
// 		at.trace("afc::format()", str);
		if(!str){
			str = "";
		}
		str = afc::format(atof(str), 
											cell.style.precision, 
											cell.style.bit, 
											afc::tobool(cell.style.addends));
	}
// 	at.trace("afc::format()", str);
	txt.text(str.c_str());
	txt.color_index(cell.style.text_color);
	txt.dxf_height(cell.style.size);
	set_text_rect(txt, rect, cell.style.h_align, cell.style.v_align);
	ent = txt.clone();
	ents.push_back(ent);
}


void Object::output(std::vector<dlhml::Entity*>& ents, 
							const afc::xls::Cell& cell,
							const std::vector<double>& ws, 
							const std::vector<double>& hs)
{
	dlhml::Rect rc = get_cell_rect(ws, hs, cell.pos, org_);
	afc::Trace at;
	at.trace("cell.content : ", cell.content);
	at.trace("rc.xmin : ", rc.xmin());
	output(ents, rc);
	at.trace("rc.ymax : ", rc.ymax());
	output(ents, rc, cell);
}


void Object::output(std::vector<dlhml::Entity*>& ents, const afc::xls::Sheet& xsheet)
{
	int n=xsheet.cells.size();
	int i=0;
	for(i=0; i<n; ++i){
		output(ents, xsheet.cells[i], xsheet.ws, xsheet.hs);
	}
}

//////////////////////////////////////////////////////
void Object::output(std::vector<dlhml::Entity*>& ents)
{
	int n=xbook_.sheets.size();
	int i=0;
	for(i=0; i<n; ++i){
		output(ents, xbook_.sheets[i]);
	}
}



namespace obj{
// static void output(std::vector<dlhml::Entity*>& ents, 
// 									 const afc::xls::Pos& xborder,
// 									 const afc::xls::Grid_Size& ws,
// 									 const afc::xls::Grid_Size& hs)
// {
// 	int n=xborder.x;
// 	
// }
// 	
// static void output(std::vector<dlhml::Entity*>& ents, const afc::xls::Sheet& xsheet)
// {
// 	int n=xsheet.borders.size();
// 	int i=0;
// 	for(; i<n; ++i){
// 		output(ents, xsheet.borders[i]);
// 	}
// }
// 
// 
// void output(std::vector<dlhml::Entity*>& ents, 
// 						const afc::xls::Book& xbook,
// 						const dlhml::Point& org,
// 						const dlhml::Normal& dis)
// {
// 	int n=xbook.sheets.size();
// 	int i=0;
// 	for(i=0; i<n; ++i){
// 		output(ents, xbook.sheets[i]);
// 	}
// }

}//namespace
}//namespace
