
#include "stdafx.h"
#include "Line_Type.h"
#include "iolua.h"
#include "../afc/counter.h"

namespace dlhml{


LPCTSTR lt_continue()
{
  return "Continuous";
}
LPCTSTR lt_dot()
{
  return "dot";
}
LPCTSTR lt_center()
{
  return "center";
}


Line_Type::Line_Type()
MCT_INIT1("Line_Type")
{
  name_ = 0;
  string_copy(name_,"Continuous");

	strcpy(Name,"");
	strcpy(DescriptiveText,"");

}
Line_Type::Line_Type(const Line_Type& rhs)
	MCT_INIT1("Line_Type")
{
  name_=0;
  string_copy(name_,rhs.name_);
  style_ = rhs.style_;

	//
	strcpy(Name,rhs.Name);
	StandardFlags = rhs.StandardFlags;
	strcpy(DescriptiveText,rhs.DescriptiveText);
	ElementsNumber = rhs.ElementsNumber;
	for(int i=0;i<LINE_ELEM_MAX_NUM;i++){
		Elements[i] = rhs.Elements[i];
	}
	PatternLength = rhs.PatternLength;

}
Line_Type& Line_Type::operator =(const Line_Type& rhs)
{
  if(this == &rhs)
    return *this;
  string_copy(name_,rhs.name_);
  style_ = rhs.style_;
 
	strcpy(Name,rhs.Name);
	StandardFlags = rhs.StandardFlags;
	strcpy(DescriptiveText,rhs.DescriptiveText);
	ElementsNumber = rhs.ElementsNumber;
	for(int i=0;i<LINE_ELEM_MAX_NUM;i++){
		Elements[i] = rhs.Elements[i];
	}
	PatternLength = rhs.PatternLength;

	return *this;
}
Line_Type::~Line_Type()
{
  string_delete(name_);
}
bool Line_Type::close()
{
  delete this;
  return true;
}
Line_Type* Line_Type::create_me()
{
  return new Line_Type;
}

// void Line_Type::lua_load(iLua_File &fin)
// {
// 
// }
// 
// void Line_Type::lua_save(oLua_File &fout)const
// {
// 	fout.save_value("name_", name_);
// 	fout.save_array("style_", style_.begin(), style_.end());
// }

HPEN Line_Type::get_pen(DWORD* style,int num,COLORREF col)const
{
  //bet
  //增加选中状态
  int line_width = 3;
  LOGBRUSH lb;
  //lb.lbStyle = BS_SOLID;
  lb.lbStyle = *style;
  lb.lbColor = col;
  //ter
  if(0 == strcmp(name_,"Continuous")){
    return ::CreatePen(PS_SOLID,line_width,col);
  }
  //BET
  else if(0 == strcmp(name_,"dot")){
    return ::CreatePen(PS_DOT,line_width,col);
  }
  else if(0 == strcmp(name_,"center")){
    return ::CreatePen(PS_DASHDOT,line_width,col);
  }
  else if(0 == strcmp(name_,"hash")){
    return ::CreatePen(PS_SOLID,line_width,col);
  }
  //TER
  else{
    LOGBRUSH lb;
    lb.lbStyle = BS_SOLID;
    lb.lbColor = col;
    return ::ExtCreatePen(PS_COSMETIC|PS_USERSTYLE,line_width,&lb,style_.size(),style_.begin());
  }
  
  //liming
  //	LOGBRUSH lb;
  //	lb.lbStyle = BS_SOLID;
  //	lb.lbColor = col;
  //	return ::ExtCreatePen(PS_COSMETIC|PS_USERSTYLE,1,&lb,num,style);
  //liming
}
void Line_Type::set_style(DWORD* style,int num)
{
  style_.assign(style,style+num);
}
HPEN Line_Type::get_pen(COLORREF col, bool sel) const
{
  //bet
  //增加选中状态
  int line_width = sel ? 3 : 1;
  if(sel){
    if(0 == strcmp(name_,"Continuous")){
      return ::CreatePen(PS_SOLID,line_width,col);
    }
    else if(0 == strcmp(name_,"center")){
      LOGBRUSH lb;
      lb.lbStyle = BS_SOLID;
      lb.lbColor = col;
      return ::ExtCreatePen(PS_GEOMETRIC|
        PS_DASHDOT|
        PS_ENDCAP_SQUARE|
        PS_JOIN_MITER,
        line_width,
        &lb,
        0,
        NULL);
    }
    else if(0 == strcmp(name_,"dot")){
      LOGBRUSH lb;
      lb.lbStyle = BS_SOLID;
      lb.lbColor = col;
      return ::ExtCreatePen(PS_GEOMETRIC|
        PS_DOT|
        PS_ENDCAP_SQUARE|
        PS_JOIN_MITER,
        line_width,
        &lb,
        0,
        NULL);
    }
    else if(0 == strcmp(name_,"dash")){
      return ::CreatePen(PS_DASH,1,col);
    }
    else{
      return ::CreatePen(PS_SOLID,line_width,col);
    }
  }
  //ter
  
  ////没有选中
  //liming
  else{
    //    if(col==RGB(255,255,255)){
    //      int aaa=100;
    //    }
    if(0 == strcmp(name_,"Continuous")){
      return ::CreatePen(PS_SOLID,line_width,col);
    }
    //BET
    else if(0 == strcmp(name_,"dot")){
      return ::CreatePen(PS_DOT,line_width,col);
    }
    else if(0 == strcmp(name_,"center")){
      return ::CreatePen(PS_DASHDOT,line_width,col);
    }
    else if(0 == strcmp(name_,"dash")){
      return ::CreatePen(PS_DASH,line_width,col);
    }
    //TER
    else{
      //BET
      return ::CreatePen(PS_SOLID,line_width,col);
      //liming
      //		  LOGBRUSH lb;
      //		  lb.lbStyle = BS_SOLID;
      //		  lb.lbColor = col;
      //		  return ::ExtCreatePen(PS_COSMETIC|PS_USERSTYLE,
      //                            line_width,
      //                            &lb,
      //                            style_.size(),
      //                            style_.begin());
      //TER
    }
  }
  //liming
}
void Line_Type::save_lua(std::ofstream &out,char *name,int tab_num)
{

}
void Line_Type::open_lua(lua_State *l,char *name)
{

}





}

