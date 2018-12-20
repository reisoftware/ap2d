
#include "stdafx.h"
#include "Ln_Dim.h"
#include "Global.h"

#include <algorithm>
#include <functional>


#include "Database.h"
#include "Entity_Snap_Implement.h"
#include "File.h"
#include "Edit_Entity.h"
#include "DrawEntity.h"
#include "Matrix_d.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Dimension_Style.h"
#include "Normal.h"
#include "Text.h"
#include "Circle.h"
#include <cassert>
#include "Visitor.h"

#include "getrace.h"
#include "encode.h"


namespace dlhml{
MY_IMPLEMENT_DYNCREATE(Ln_Dim,Dimension)
Ln_Dim::Ln_Dim()
MCT_INIT1("Ln_Dim")
{
  dim_mode_= PILEUP_DIM ;
  dim_rota_= ORTHO_DIM ;
	show0_  = true       ;
  end_show_ = true;
	dim_line_radian_ = 0;
	dim_text2_ = "";
	text2_rotation_ = 0.0;
	align_point2_ = Text::left_bottom;
	dim_text3_ = "";
	text3_rotation_ = 0.0;
	align_point3_ = Text::left_bottom;

		user_content_ = false;

  
}
Ln_Dim::Ln_Dim(const Ln_Dim& rhs)
:Dimension(rhs)
MCT_INIT2("Ln_Dim")
{
  dim_mode_=rhs.dim_mode_;
  dim_rota_=rhs.dim_rota_;
	show0_  =rhs.show0_  ;
  end_show_ = rhs.end_show_;
	dim_line_radian_ = rhs.dim_line_radian_;
	(dim_text2_ = rhs.dim_text2_);
	text2_rotation_ = rhs.text2_rotation_;
	text2_position_ = rhs.text2_position_;
	align_point2_ = rhs.align_point2_;
	(dim_text3_ = rhs.dim_text3_);

	text3_rotation_ = rhs.text3_rotation_;
	text3_position_ = rhs.text3_position_;
	align_point3_ = rhs.align_point3_;
  //data point
  opt_=rhs.opt_;
	spt_=rhs.spt_;
	ept_=rhs.ept_;
	odm_=rhs.odm_;
	edm_=rhs.edm_;

  txt2_change_=rhs.txt2_change_;
  txt2_record_=rhs.txt2_record_;
	user_content_ = rhs.user_content_;
}
Ln_Dim& Ln_Dim::operator=(const Ln_Dim& rhs)
{
	Dimension::operator =(rhs);
	if(this == &rhs)
		return *this;
  dim_mode_=rhs.dim_mode_;
  dim_rota_=rhs.dim_rota_;
	show0_  =rhs.show0_  ;
  end_show_ = rhs.end_show_;
	dim_line_radian_ = rhs.dim_line_radian_;
	(dim_text2_ = rhs.dim_text2_);
	text2_rotation_ = rhs.text2_rotation_;
	text2_position_ = rhs.text2_position_;
	align_point2_ = rhs.align_point2_;
	(dim_text3_=rhs.dim_text3_);
	text3_rotation_ = rhs.text3_rotation_;
	text3_position_ = rhs.text3_position_;
	align_point3_ = rhs.align_point3_;
  //data point
  opt_=rhs.opt_;
	spt_=rhs.spt_;
	ept_=rhs.ept_;
	odm_=rhs.odm_;
	edm_=rhs.edm_;

  txt2_change_=rhs.txt2_change_;
  txt2_record_=rhs.txt2_record_;
	user_content_ = rhs.user_content_;
	return *this;
}

Ln_Dim::~Ln_Dim()
{
}

Float Ln_Dim::dim_line_radian() const
{
  return dim_line_radian_;
}
void Ln_Dim::dim_line_degree(Float a)
{
  //double rad = degree_2_radian(deg);
  dim_line_radian_ = degree_2_radian(a);
  show_change(true);
}
Float Ln_Dim::dim_line_degree() const
{
  return radian_2_degree(dim_line_radian_);
}
    

bool Ln_Dim::visit(Visitor& v)
{
  show_change(true);
	return v.Visit_Ln_Dim(*this);
}
//void Ln_Dim::text3_normal(const Normal& nor)
//{
//	text3_rotation_ = nor.angle_x_axis_two_pi();
//  show_change(true);
//}
void Ln_Dim::loadme(File& in)
{
  Dimension::load_me(in);
	in  >> dim_mode_
      >> dim_rota_
      >> show0_
      >> dim_line_radian_ 
      >> dim_text2_ 
      >> text2_rotation_ 
      >> dim_text3_ 
      >> text3_rotation_;
	int TextAlignFlag;
	in >> TextAlignFlag;
	align_point2_ = (Text::AlignPt)TextAlignFlag;
	in >> TextAlignFlag;
	align_point3_ = (Text::AlignPt)TextAlignFlag;
	text2_position_.load(in);
	text3_position_.load(in);
  //data point
	opt_.load(in);
	spt_.load(in);
	ept_.load(in);
	odm_.load(in);
	edm_.load(in);
  show_change(true);
}
void Ln_Dim::saveme(const File& out) const
{
	save_me(out);
	out << dim_mode_
      << dim_rota_
      << show0_
      << dim_line_radian_ 
      << dim_text2_ 
      << text2_rotation_ 
      << dim_text3_ 
      << text3_rotation_;
	int TextAlignFlag = align_point2_;
	out << TextAlignFlag;
	TextAlignFlag = align_point3_;
	out << TextAlignFlag;
	text2_position_.save(out);
	text3_position_.save(out);
  //data point
  opt_.save(out);
	spt_.save(out);
	ept_.save(out);
	odm_.save(out);
	edm_.save(out);
}

void Ln_Dim::save_luame(std::ofstream &out,int tab_num)
{
	Dimension::save_luame(out,tab_num);
	
	lua::int_save(out,"dim_mode_",dim_mode_,tab_num);
	lua::int_save(out,"dim_rota_",dim_rota_,tab_num);
	lua::bool_save(out,"show0_",show0_,tab_num);
	lua::bool_save(out,"end_show_",end_show_,tab_num);

	lua::float_save(out,"dim_line_radian_",dim_line_radian_,tab_num);

	lua::string_save(out,"dim_text2_",dim_text2_,tab_num);
	lua::float_save(out,"text2_rotation_",text2_rotation_,tab_num);

	lua::string_save(out,"dim_text3_",dim_text3_,tab_num);	
	lua::float_save(out,"text3_rotation_",text3_rotation_,tab_num);

	int TextAlignFlag = align_point2_;
	lua::int_save(out,"align_point2_",TextAlignFlag,tab_num);
	TextAlignFlag = align_point3_;
	lua::int_save(out,"align_point3_",TextAlignFlag,tab_num);
	text2_position_.save_lua(out,"text2_position_",tab_num);
	text3_position_.save_lua(out,"text3_position_",tab_num);
	opt_.save_lua(out,"opt_",tab_num);
	spt_.save_lua(out,"spt_",tab_num);
	ept_.save_lua(out,"ept_",tab_num);
	odm_.save_lua(out,"odm_",tab_num);
	edm_.save_lua(out,"edm_",tab_num);
}
static Text::AlignPt get_align_kind(int v)
{
	if(v == 1)
		return Text::AlignPt::left_top;
	else if(v == 2)
		return Text::AlignPt::left_center;
	else if(v == 3)
		return Text::AlignPt::left_bottom;
	else if(v == 4)
		return Text::AlignPt::center_top;
	else if(v == 5)
		return Text::AlignPt::center_center;
	else if(v == 6)
		return Text::AlignPt::center_bottom;
	else if(v == 7)
		return Text::AlignPt::right_top;
	else if(v == 8)
		return Text::AlignPt::right_center;
	else if(v == 9)
		return Text::AlignPt::right_bottom;
	else
		return Text::AlignPt::center_center;
}
void Ln_Dim::open_luame(lua_State *l)  
{
	TRACE_OUT("Ln_Dim::open_luame() start\n");
	Dimension::open_luame(l);
	get_value(number,l,dim_mode_,"dim_mode_");
	get_value(number,l,dim_rota_,"dim_rota_");
	get_value(number,l,show0_,"show0_");
	get_value(number,l,end_show_,"end_show_");
	get_value(number,l,dim_line_radian_,"dim_line_radian_");
	std::string temp;
	get_value(string,l,temp,"dim_text2_");
	(dim_text2_ = temp.c_str());
	get_value(number,l,text2_rotation_,"text2_rotation_");

	get_value(string,l,temp,"dim_text3_");
	(dim_text3_ = temp.c_str());
	get_value(number,l,text3_rotation_,"text3_rotation_");

	int val=0;
	get_value(number,l,val,"align_point2_");
	align_point2_ = get_align_kind(val);
	get_value(number,l,val,"align_point3_");
	align_point3_ = get_align_kind(val);
	text2_position_.open_lua(l,"text2_position_");
	text3_position_.open_lua(l,"text3_position_");
	opt_.open_lua(l,"opt_");
	spt_.open_lua(l,"spt_");
	ept_.open_lua(l,"ept_");
	odm_.open_lua(l,"odm_");
	edm_.open_lua(l,"edm_");
	txt_change(true);
	TRACE_OUT("Ln_Dim::open_luame() end\n");

}
void Ln_Dim::get_strme(char *out)
{
	rei_quit();
	rei_add_str(NULL,"kind","LN_DIM");
	get_str_ent();
	get_str_dim();
	////////////////////////////////////////////////////////////
	rei_add_int(NULL,"dim_mode_",dim_mode_);
	rei_add_int(NULL,"dim_rota_",dim_rota_);
	rei_add_int(NULL,"show0_",show0_);
	rei_add_int(NULL,"end_show_",end_show_);
	rei_add_float(NULL,"dim_line_radian_",dim_line_radian_);
	rei_add_str(NULL,"dim_text2_",dim_text2_.c_str());
	rei_add_float(NULL,"text2_rotation_",text2_rotation_);
	rei_add_str(NULL,"dim_text3_",dim_text3_.c_str());
	rei_add_int(NULL,"align_point2_",align_point2_);
	rei_add_int(NULL,"align_point3_",align_point3_);
	text2_position_.get_str_sub("text2_position_");
	text3_position_.get_str_sub("text3_position_");
	opt_.get_str_sub("opt_");
	spt_.get_str_sub("spt_");
	ept_.get_str_sub("ept_");
	odm_.get_str_sub("odm_");

	rei_get_encode(out);
}
void Ln_Dim::set_from_strme(char *in)
{
	rei_init(in);
	set_from_str_ent();
	set_from_str_dim();
	////////////////////////////////////////////////////////////
	dim_mode_ = atoi(rei_get("dim_mode_"));
	dim_rota_ = atoi(rei_get("dim_rota_"));
	show0_ = atoi(rei_get("show0_"));
	end_show_ = atoi(rei_get("end_show_"));
	dim_line_radian_ = atof(rei_get("dim_line_radian_"));
	dim_text2_ = rei_get("dim_text2_");
	text2_rotation_ = atof(rei_get("text2_rotation_"));
	dim_text3_ = rei_get("dim_text3_");
	align_point2_ = (Text::AlignPt)(atoi(rei_get("align_point2_")));
	align_point3_ = (Text::AlignPt)(atoi(rei_get("align_point3_")));
	text2_position_.set_from_str_sub("text2_position_");
	text3_position_.set_from_str_sub("text3_position_");
	
	opt_.set_from_str_sub("opt_");
	spt_.set_from_str_sub("spt_");
	ept_.set_from_str_sub("ept_");
	odm_.set_from_str_sub("odm_");
	rei_quit();
}
void Ln_Dim::get_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	get_str_ent_sub(name);
	get_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_mode_",name);
	rei_add_int(NULL,"dim_mode_",dim_mode_);
	sprintf(s,"%s.dim_rota_",name);
	rei_add_int(NULL,"dim_rota_",dim_rota_);
	sprintf(s,"%s.show0_",name);
	rei_add_int(NULL,"show0_",show0_);
	sprintf(s,"%s.end_show_",name);
	rei_add_int(NULL,"end_show_",end_show_);
	sprintf(s,"%s.dim_line_radian_",name);
	rei_add_float(NULL,"dim_line_radian_",dim_line_radian_);
	sprintf(s,"%s.dim_text2_",name);
	rei_add_str(NULL,"dim_text2_",dim_text2_.c_str());
	sprintf(s,"%s.text2_rotation_",name);
	rei_add_float(NULL,"text2_rotation_",text2_rotation_);
	sprintf(s,"%s.dim_text3_",name);
	rei_add_str(NULL,"dim_text3_",dim_text3_.c_str());
	sprintf(s,"%s.align_point2_",name);
	rei_add_int(NULL,"align_point2_",align_point2_);
	sprintf(s,"%s.align_point3_",name);
	rei_add_int(NULL,"align_point3_",align_point3_);
	sprintf(s,"%s.text2_position_",name);
	text2_position_.get_str_sub("text2_position_");
	sprintf(s,"%s.text3_position_",name);
	text3_position_.get_str_sub("text3_position_");
	sprintf(s,"%s.opt_",name);
	opt_.get_str_sub("opt_");
	sprintf(s,"%s.spt_",name);
	spt_.get_str_sub("spt_");
	sprintf(s,"%s.ept_",name);
	ept_.get_str_sub("ept_");
	sprintf(s,"%s.odm_",name);
	odm_.get_str_sub("odm_");
}
void Ln_Dim::set_from_str_sub(char *name)
{
	char s[MAX_REDIS_STR];
	set_from_str_ent_sub(name);
	set_from_str_dim_sub(name);
	////////////////////////////////////////////////////////////
	sprintf(s,"%s.dim_mode_",name);
	dim_mode_ = atoi(rei_get(s));
	sprintf(s,"%s.dim_rota_",name);
	dim_rota_ = atoi(rei_get(s));
	sprintf(s,"%s.show0_",name);
	show0_ = atoi(rei_get(s));
	sprintf(s,"%s.end_show_",name);
	end_show_ = atoi(rei_get(s));
	sprintf(s,"%s.dim_line_radian_",name);
	dim_line_radian_ = atof(rei_get(s));
	sprintf(s,"%s.dim_text2_",name);
	dim_text2_ = rei_get(s);
	sprintf(s,"%s.text2_rotation_",name);
	text2_rotation_ = atof(rei_get(s));
	sprintf(s,"%s.dim_text3_",name);
	dim_text3_ = rei_get(s);
	sprintf(s,"%s.align_point2_",name);
	align_point2_ = (Text::AlignPt)(atoi(rei_get(s)));
	sprintf(s,"%s.align_point3_",name);
	align_point3_ = (Text::AlignPt)(atoi(rei_get(s)));
	sprintf(s,"%s.text2_position_",name);
	text2_position_.set_from_str_sub(s);
	sprintf(s,"%s.text3_position_",name);
	text3_position_.set_from_str_sub(s);
	
	sprintf(s,"%s.opt_",name);
	opt_.set_from_str_sub(s);
	sprintf(s,"%s.spt_",name);
	spt_.set_from_str_sub(s);
	sprintf(s,"%s.ept_",name);
	ept_.set_from_str_sub(s);
	sprintf(s,"%s.odm_",name);
	odm_.set_from_str_sub(s);
	rei_quit();
	

}


void Ln_Dim::edit_propertyme(const Edit_Entity& edit)
{
//	edit.edit_ln_dim(*this);
  show_change(true);
}

//void Ln_Dim::drawme(Draw_Entity& out) const
//{
//	out.draw_ln_dim(*this);
//}
//void Ln_Dim::xor_drawme(Draw_Entity& out) const
//{
//	out.xor_draw_ln_dim(*this);
//}

errorinfo Ln_Dim::postme2db(Database& db,Entity_ID& id)
{
  show_change(true);
	return db.entity_push_back(this,id);
}

void Ln_Dim::transformbyme(const Matrix& mat)
{
// 	REITRACE;
 Dimension::transformbyme(mat);
  text2_rotation_=text_rotation_;
	text2_position_.transformby(mat);

  dlhml::transformby2d_radian(mat, dim_line_radian_);

  text3_rotation_=text_rotation_;
	text3_position_.transformby(mat);
  
  //data point
  opt_.transformby(mat);
	spt_.transformby(mat);
	ept_.transformby(mat);
	odm_.transformby(mat);
	edm_.transformby(mat);
  show_change(true);
}

//BET 2009.09.10
//************************************************************************
//                          matrix's type                                                                        
//************************************************************************
//void Ln_Dim::transformbyme(const Matrix& mat)
//{
// 	REITRACE;
// Dimension::transformbyme(mat);
//  text2_rotation_=text_rotation_;
//	text2_position_.transformby(mat);
//
//  if(mat.mat_type()==ZRAOTA_MAT){
//    dim_line_radian_ += mat.rota_radian();
//    std_radian(dim_line_radian_);
//  }
//
//  text3_rotation_=text_rotation_;
//	text3_position_.transformby(mat);
//  //data point
//  opt_.transformby(mat);
//	spt_.transformby(mat);
//	ept_.transformby(mat);
//	odm_.transformby(mat);
//	edm_.transformby(mat);
//  show_change(true);
//}
//TER

void Ln_Dim::drag_startme(const Matrix& mat)
{
	text_position_.transformby(mat);
	//bet
  odm_.transformby(mat);
  //lm
	//edm_.transformby(mat);
  //ter
  show_change(true);
}
void Ln_Dim::drag_endme(const Matrix& mat)
{
	text2_position_.transformby(mat);
	text3_position_.transformby(mat);
	edm_.transformby(mat);
  show_change(true);
}

Entity* Ln_Dim::cloneme() const
{
	return new Ln_Dim(*this);
}

void Ln_Dim::closeme()
{
	delete this;
}

//TEXT2 SET
void Ln_Dim::dim_text2(std::string str)			          
{
  (dim_text2_ = str);
  txt2_change(true);
}
void Ln_Dim::text2_rotation(Float f)		          
{
  text2_rotation_=f;
  txt2_change(true);
}
void Ln_Dim::text2_position(const Point& pos)	  
{
  text2_position_=pos;
  txt2_change(true);
}
void Ln_Dim::text2_normal(const Normal& nor)
{
  text2_rotation_ = nor.angle_x_axis_two_pi();
  txt2_change(true);
}
void Ln_Dim::align_point2(Text::AlignPt align)	  
{
  align_point2_=align;
  txt2_change(true);
}

//DATA
void Ln_Dim::setdata(const Point& opt,
                     const Point& spt,
                     const Point& ept,
                     const Point& stdim,
                     const Point& eddim)
{
  opt_.set2d(opt);
  spt_.set2d(spt);
  ept_.set2d(ept);
  odm_.set2d(stdim);
  edm_.set2d(eddim);
  txt2_change(true);
}
void Ln_Dim::opt(const Point& pt)			
{
  opt_.set2d(pt);
  txt2_change(true);
}
void Ln_Dim::spt(const Point& pt)			
{
  spt_.set2d(pt);
  txt2_change(true);
}
void Ln_Dim::ept(const Point& pt)				
{
  ept_.set2d(pt);
  txt2_change(true);
}
void Ln_Dim::odm(const Point& pt)		
{
  odm_.set2d(pt);
  txt2_change(true);
}

void Ln_Dim::edm(const Point& pt)		
{
  edm_.set2d(pt);
  txt2_change(true);
}
void Ln_Dim::ext_line_radian(Float a)
{
  dim_line_radian_ = a-pi/2;
  txt2_change(true);
}
void Ln_Dim::dim_line_radian(Float a)
{
  dim_line_radian_ = a;
  txt2_change(true);
}

//MODE
void Ln_Dim::mode(DIM_MODE m)
{
  txt2_change(true);
  dim_mode_=m;
}
void Ln_Dim::rota(DIM_ROTA m)
{
  txt2_change(true);
  dim_rota_=m;
}

//OPERATOR
void Ln_Dim::re0_dm()
{
  txt2_change(true);
  Line exln, dmln;
  get_e_lines(exln,dmln);
  Point old_dm = exln.perpendicular(edm_);
  edm_ = odm_;
  Point new_dm = exln.perpendicular(edm_);
  edm_ = new_dm;
  
  Point txt_pt;
  if(mode()==PILEUP_DIM){
    txt_pt = text2_position();
    txt_pt = txt_pt + new_dm - old_dm;
    text2_position(txt_pt);
  }
  else if(mode()==CLOSED_DIM){
    txt_pt = text_position();
    txt_pt = txt_pt + new_dm - old_dm;
    text_position(txt_pt);
    
    txt_pt = text2_position();
    txt_pt = txt_pt + new_dm - old_dm;
    text2_position(txt_pt);
  }
//  txt_pt = text3_position();
//  txt_pt = txt_pt + new_dm - old_dm;
//  text3_position(txt_pt);
}
void Ln_Dim::align_dim_lines(const Point& pos)
{
  txt2_change(true);

  Entity_Calculate calc;
  Line oexln,eexln,odmln,edmln;
  get_o_lines(oexln,odmln);
  get_e_lines(eexln,edmln);
  Point new_odm_pt,new_edm_pt;
  calc.line_perpendicular(new_odm_pt,oexln,pos);
  calc.line_perpendicular(new_edm_pt,eexln,pos);

  Point odms,edme;
  calc.line_perpendicular(odms,oexln,odm_);
  calc.line_perpendicular(edme,eexln,edm_);

  Point o_off = new_odm_pt-odms;
  Point e_off = new_edm_pt-edme;
  ////移动标注点及文本
  odm_ += o_off;
  edm_ += e_off;
  text_position_ += o_off;
  text2_position_ += e_off;
  text3_position_ += e_off;
}
void Ln_Dim::align_base(const Point& pos)
{
  txt2_change(true);
  Entity_Calculate calc;
  Line oexln;
  Line sexln;
  Line eexln;
  Line odmln;
  Line sdmln;
  Line edmln;
  get_o_lines(oexln,odmln);
  get_s_lines(sexln,eexln,sdmln);
  get_e_lines(eexln,edmln);
  Point obase;
  Point sbase;
  Point ebase;
  calc.line_perpendicular(obase,oexln,pos);
  opt_=obase;
  calc.line_perpendicular(sbase,sexln,pos);
  spt_=sbase;
  calc.line_perpendicular(ebase,eexln,pos);
  ept_=ebase;
}
void Ln_Dim::offset_dm(const Normal off_nor, Float dis, int flags)
{
  show_change(true);
  Normal nor = off_nor;
  ext_line_normal(nor);
  nor.set_unit();
  
  Point txtpt;
  Line oexln,odmln,eexln,edmln;
  if(mode() == PILEUP_DIM){
    if(flags==1){
      odm_ = odm_.polarTo(dis,nor);
      get_o_lines(oexln, odmln);
      text_position(odmln.middle());
    }
    else if(flags==2){
      edm_ = edm_.polarTo(dis,nor);
      get_e_lines(eexln,edmln);
      text2_position(edmln.middle());
    }
  }
  else if(mode()==CLOSED_DIM){
    if(flags==1){
    }
    else if(flags==2){
      edm_ = edm_.polarTo(dis,nor);
      txtpt= text_position();
      txtpt= txtpt.polarTo(dis,nor);
      text_position(txtpt);
    }
  }
}


//TEXT RECORD
void Ln_Dim::txt2_change(bool b)const
{
  Ln_Dim * the = const_cast<Ln_Dim*>(this);
  the->txt2_change_=b;

  txt_change(true);
  show_change(true);
}
void Ln_Dim::txt2_record(const Text& txt)const
{
  Ln_Dim * the = const_cast<Ln_Dim*>(this);
  the->txt2_record_=txt;
  txt2_change(false);
}
bool Ln_Dim::get_text2_show(Text& text) const
{
  if(txt2_change_){
    const Dimension_Style* ds=&dim_style_val_;
    text.set_database(static_current_db_);
    text.align_point(align_point2_);
    text.rotation(text2_rotation_);
    text.setdata(text2_position_,dim_text2_);
    text.color_index(dim_style_val_.text_color());
    ds->get_text(text);

    txt2_record(text);
  }
  else{
    text=txt2_record_;
  }

	return true;
}
bool Ln_Dim::get_text3_show(Text& text) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
//	assert(static_current_db_);
//	assert(dim_style_);
	text.set_database(static_current_db_);
	text.align_point(align_point3_);
	text.rotation(text3_rotation_);
	text.setdata(text3_position_,dim_text3_);
	text.color_index(dim_style_val_.text_color());
  //	Dimension_Style* ds=0;
  //	static_current_db_->get_dimensionstyle(ds,dim_style_);
  //	assert(ds);
	ds->get_text(text);
	return true;

//lm
//	assert(static_current_db_);
//	assert(dim_style_);
//	text.set_database(static_current_db_);
//	text.align_point(align_point3_);
//	text.rotation(text3_rotation_);
//	text.setdata(text3_position_,dim_text3_);
//	text.color_index(dim_style_val_.text_color());
//	Dimension_Style* ds=0;
//	static_current_db_->get_dimensionstyle(ds,dim_style_);
//	assert(ds);
//	ds->get_text(text);
//	return true;
}
bool Ln_Dim::get_text2_frame_show(Text& text, std::vector<Entity*>& es)const
{
  get_text2_show(text);
  dim_style_val_.get_text_frame(text,es);
  return true;
}
bool Ln_Dim::pt_in_range(const Point& pt) const
{
	Line start,end,dim1,dim2;
	get_o_lines(start,dim1);
	get_e_lines(end,dim2);
	Point pp1,pp2;
	Entity_Calculate calc;
	calc.line_perpendicular(pp1,start,pt);
	calc.line_perpendicular(pp2,end,pt);
	Line line(pp1,pp2);
	return calc.point_in_linesegment(pt,line);
}
bool Ln_Dim::get_o_lines(Line& oexln,Line& odmln) const
{
//	if(!start_show_)
//		return false;
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Normal n;
	n.set_x_axis_angle(dim_line_radian_);
	Point pt = odm_.polarTo(100,n);
	Entity_Calculate calc;
	Point pp1;
	Line line(odm_,pt);
	calc.line_perpendicular(pp1,line,opt_);
	Point off1,off2;
	off1 = ds->get_extend_base(opt_,pp1);
	off2 = ds->get_extend_end(opt_,pp1);
	oexln.setdata(off1,off2);
	Text text;
	get_text_show(text);
	Point dimpt = ds->get_dim_length(pp1,n,text);
	odmln.setdata(pp1,dimpt);

  oexln.set2d();
  odmln.set2d();
	return true;
}
bool Ln_Dim::get_s_lines(Line& sexln,Line& eexln,Line& sdmln) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
	Normal n;
	n.set_x_axis_angle(ext_line_radian());
	Point pt = spt_.polarTo(spt_.distanceto(ept_),n);
	Entity_Calculate calc;
	Point pp1;
	Line line(spt_,pt);
	calc.line_perpendicular(pp1,line,edm_);
	pt = ept_.polarTo(spt_.distanceto(ept_),n);
	Point pp2;
	line.setdata(ept_,pt);
	calc.line_perpendicular(pp2,line,edm_);
	sdmln.setdata(pp1,pp2);

	Point off1,off2;
	off1 = ds->get_extend_base(spt_,pp1);
	off2 = ds->get_extend_end(spt_,pp1);
	sexln.setdata(off1,off2);
	off1 = ds->get_extend_base(ept_,pp2);
	off2 = ds->get_extend_end(ept_,pp2);
	eexln.setdata(off1,off2);

  sexln.set2d();
  eexln.set2d();
  sdmln.set2d();
	return true;
}
bool Ln_Dim::get_e_lines(Line& extendline,Line& dimline) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Normal n;
	n.set_x_axis_angle(dim_line_radian_);
	Point pt = edm_.polarTo(100,n);
	Entity_Calculate calc;
	Point pp1;
	Line line(edm_,pt);
	calc.line_perpendicular(pp1,line,ept_);
	Point off1,off2;
	off1 = ds->get_extend_base(ept_,pp1);
	off2 = ds->get_extend_end(ept_,pp1);
	if(strcmp("",dim_text3_.c_str())!=0){
		Text text3;
		get_text3_show(text3);
		Normal nor;
		nor.set_data(ept_,pp1);
		off2 = ds->get_dim_length(off2,nor,text3);
	}
	extendline.setdata(off1,off2);
	n.set_reverse();
	Text text;
	get_text2_show(text);
	Point dimpt = ds->get_dim_length(pp1,n,text);
	dimline.setdata(pp1,dimpt);

  extendline.set2d();
  dimline.set2d();

	return true;
}
void Ln_Dim::get_line(std::vector<Entity*>& es)const
{
  if(dim_mode_==PILEUP_DIM){
    Line * oex = Line::create_me();
    Line * eex = Line::create_me();
    Line * odm = Line::create_me();
    Line * edm = Line::create_me();
    get_o_lines(*oex,*odm);
    get_e_lines(*eex,*edm);
    es.push_back(oex);
    es.push_back(odm);
    es.push_back(eex);
    es.push_back(edm);
  }
  else if(dim_mode_==CLOSED_DIM){
    Line * sex = Line::create_me();
    Line * eex = Line::create_me();
    Line * edm = Line::create_me();
    get_s_lines(*sex,*eex,*edm);
    es.push_back(sex);
    es.push_back(eex);
    es.push_back(edm);
  }
}

void Ln_Dim::get_show(std::vector<Entity*>& es) const
{
  switch(dim_mode_)
  {
  case PILEUP_DIM:
    get_pileup_show(es);
    break;
  case CLOSED_DIM:
    get_closed_show(es);
    break;
  }
}
void Ln_Dim::get_pileup_show(std::vector<Entity*>& es) const
{
  //0
  if(show0_){
    //line
    Line * oex = Line::create_me();
    Line * odm = Line::create_me();
    get_o_lines(*oex, *odm);
    oex->line_style(line_style());
    odm->line_style(line_style());
    oex->color_index(dim_style_val_.line_color());
    odm->color_index(dim_style_val_.line_color());
    es.push_back((Entity*)oex);
    es.push_back((Entity*)odm);
    //arrow
    std::vector<Line*> olns;
    get_o_arrow_line_show(olns);
    dlhml::push_back<Line>(olns,es);
    //push_o_arrow_line_show(es);
    std::vector<Circle*> ocrs;
    get_o_arrow_circle_show(ocrs);
    dlhml::push_back<Circle>(ocrs,es);
    //push_o_arrow_circle_show(es);

	  //text
    Text * txt1 = Text::create_me();
	  get_text_frame_show(*txt1,es);
    es.push_back(txt1);
  }
  //e
  if(end_show_){
    //line
    Line * eex = Line::create_me();
    Line * edm = Line::create_me();
    get_e_lines(*eex, *edm);
    eex->line_style(line_style());
    edm->line_style(line_style());
    eex->color_index(dim_style_val_.line_color());
    edm->color_index(dim_style_val_.line_color());
    es.push_back((Entity*)eex);
    es.push_back((Entity*)edm);
    //arrow
    std::vector<Line*> elns;
    get_e_arrow_line_show(elns);
    dlhml::push_back<Line>(elns,es);
    //push_e_arrow_line_show(es);
    std::vector<Circle*> ecrs;
    get_e_arrow_circle_show(ecrs);
    dlhml::push_back<Circle>(ecrs,es);
    //push_e_arrow_circle_show(es);
	  //text
    Text * txt2 = Text::create_me();
	  get_text2_frame_show(*txt2,es);
    es.push_back(txt2);
  }
}
void Ln_Dim::get_closed_show(std::vector<Entity*>& es) const
{
  //line
  Line * sex = Line::create_me();
  Line * eex = Line::create_me();
  Line * edm = Line::create_me();
  get_s_lines(*sex, *eex, *edm);
  sex->line_style(line_style());
  eex->line_style(line_style());
  edm->line_style(line_style());
  sex->color_index(dim_style_val_.line_color());
  eex->color_index(dim_style_val_.line_color());
  edm->color_index(dim_style_val_.line_color());
  es.push_back((Entity*)sex);
  es.push_back((Entity*)eex);
  es.push_back((Entity*)edm);
  //arrow
  std::vector<Line*> slns;
  get_s_arrow_line_show(*edm,slns);
  dlhml::push_back<Line>(slns,es);
  //push_s_arrow_line_show(es);
  std::vector<Circle*> scrs;
  get_s_arrow_circle_show(*edm,scrs);
  dlhml::push_back<Circle>(scrs,es);
  //push_s_arrow_circle_show(es);
	//text
  Text * txt1 = Text::create_me();
	get_text_frame_show(*txt1,es);
  es.push_back(txt1);

  Point txt_base_pt = text_position(); 
  Point txt_dm_insc = edm->perpendicular(txt_base_pt);
  if(!edm->is_in_segline(txt_dm_insc)){
    Float st_dis = txt_dm_insc.distanceto2d(edm->start());
    Float ed_dis = txt_dm_insc.distanceto2d(edm->end  ());
    Line * txt_extentd_ln = Line::create_me(); 
    txt_extentd_ln->line_style(line_style());
    txt_extentd_ln->color_index(dim_style_val_.line_color());
    if(LessThen(st_dis,ed_dis)){
      txt_extentd_ln->setdata(txt_dm_insc,edm->start());
    }else{
      txt_extentd_ln->setdata(txt_dm_insc,edm->end  ());
    }
    es.push_back(txt_extentd_ln);
  }
}

bool Ln_Dim::get_dim_lines_show(std::vector<Line*>& lines) const
{
  int i=0;
  Line * ln = Line::create_me();
  switch(dim_mode_)
  {
  case PILEUP_DIM:
	  get_o_lines(*lines[0],*lines[1]);
	  get_e_lines(*lines[2],*lines[3]);
	  for(i=0;i<4;++i){
		  lines[i]->line_style(line_style());
	  }
    break;
  case CLOSED_DIM:
    //NOOK
    break;
  }
	return true;
}

//void Ln_Dim::push_o_arrow_line_show(std::vector<Entity*>& es)const
//{
//  std::vector<Line*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Line::create_me();
//  }
//  int oln_arraw_num = get_o_arrow_line_show(oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_o_arrow_line_show(std::vector<Line*>& lines) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Line oln,dim;
	get_o_lines(oln,dim);
	Normal nor;
	nor.set_data(dim.end(),dim.start());
	ds->get_arrow_line(dim.start(),nor,lines);
	for(int i=0;i<lines.size();++i){
		lines[i]->line_style(line_style());
		//lines[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}
//void Ln_Dim::push_e_arrow_line_show(std::vector<Entity*>& es)const
//{
//  std::vector<Line*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Line::create_me();
//  }
//  int oln_arraw_num = get_e_arrow_line_show(oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_e_arrow_line_show(std::vector<Line*>& lines) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Line eln,dim;
	get_e_lines(eln,dim);
	Normal nor;
	nor.set_data(dim.end(),dim.start());
	ds->get_arrow_line(dim.start(),nor,lines);
	for(int i=0;i<lines.size();++i){
		lines[i]->line_style(line_style());
		//lines[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}
//  获得0点箭头线
//void Ln_Dim::push_o_arrow_circle_show(std::vector<Entity*>& es)const
//{
//  std::vector<Circle*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Circle::create_me();
//  }
//  int oln_arraw_num = get_o_arrow_circle_show(oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_o_arrow_circle_show(std::vector<Circle*>& circles) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Line oln,dim;
	get_o_lines(oln,dim);
	ds->get_arrow_circle(dim.start(),circles);
	for(int i=0;i<circles.size();++i){
		circles[i]->line_style(line_style());
		//circles[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}
//void Ln_Dim::push_e_arrow_circle_show(std::vector<Entity*>& es)const
//{
//  std::vector<Circle*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Circle::create_me();
//  }
//  int oln_arraw_num = get_e_arrow_circle_show(oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_e_arrow_circle_show(std::vector<Circle*>& circles) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Line eln,dim;
	get_e_lines(eln,dim);
	ds->get_arrow_circle(dim.start(),circles);
	for(int i=0;i<circles.size();++i){
		circles[i]->line_style(line_style());
		//circles[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}


//void Ln_Dim::push_s_arrow_line_show(std::vector<Entity*>& es)const
//{
//  Line sex, eex, edm;
//  get_s_lines(sex, eex, edm);
//
//  std::vector<Line*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Line::create_me();
//  }
//  int oln_arraw_num = get_s_arrow_line_show(edm, oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_s_arrow_line_show(const Line& dim,std::vector<Line*>& lines) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	Normal nor;
	nor.set_data(cos(ext_line_radian()+pi/2),sin(ext_line_radian()+pi/2),0);

	ds->get_arrow_line(dim.start(),nor,lines);
	nor.set_data(cos(ext_line_radian()-pi/2),sin(ext_line_radian()-pi/2),0);
	//std::vector<Line*> end;
	//std::copy(lines.begin()+num1,lines.end(),std::back_inserter(end));
  
	ds->get_arrow_line(dim.end(),nor,lines);
	//int num = num1+num2;
	for(int i=0;i<lines.size();++i){
		lines[i]->line_style(line_style());
		//lines[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}
//void Ln_Dim::push_s_arrow_circle_show(std::vector<Entity*>& es)const
//{
//  Line sex, eex, edm;
//  get_s_lines(sex, eex, edm);
//
//  std::vector<Circle*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Circle::create_me();
//  }
//  int oln_arraw_num = get_s_arrow_circle_show(edm, oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//}
int Ln_Dim::get_s_arrow_circle_show(const Line& dim,std::vector<Circle*>& circles) const
{
  //bet
  //2009.06.18
	const Dimension_Style* ds=&dim_style_val_;
  //lm
	//assert(static_current_db_);
	//assert(dim_style_);
	//Dimension_Style* ds=0;
	//static_current_db_->get_dimensionstyle(ds,dim_style_);
	//assert(ds);
  //ter
	ds->get_arrow_circle(dim.start(),circles);
	//std::vector<Circle*> end;
	//std::copy(circles.begin()+num1,circles.end(),std::back_inserter(end));

	ds->get_arrow_circle(dim.end(),circles);
	//int num = num1+num2;
	for(int i=0;i<circles.size();++i){
		circles[i]->line_style(line_style());
		//circles[i]->color_index(dim_style_val_.line_color());
	}
	//return num;
  return 0;
}


bool Ln_Dim::intersectme(const Rect& rect) const
{
	Entity_Calculate calc;
	Line sexln,exln,dmln;
	Text text;
  switch(dim_mode_)
  {
  case PILEUP_DIM:
	  get_o_lines(exln,dmln);
    if(calc.linesegment_insect_rect(exln,rect)){
		  return true;
    }
	  if(calc.linesegment_insect_rect(dmln,rect)){
		  return true;
    }
	  get_e_lines(exln,dmln);
	  if(calc.linesegment_insect_rect(exln,rect)){
		  return true;
    }
	  if(calc.linesegment_insect_rect(dmln,rect)){
		  return true;
    }
	  get_text_show(text);
	  if(text.intersect(rect)){
		  return true;
    }
	  get_text2_show(text);
	  if(text.intersect(rect)){
		  return true;
    }
    break;
  case CLOSED_DIM:
    get_s_lines(sexln,exln,dmln);
	  if(calc.linesegment_insect_rect(sexln,rect)){
		  return true;
    }
	  if(calc.linesegment_insect_rect(exln,rect)){
		  return true;
    }
	  if(calc.linesegment_insect_rect(dmln,rect)){
		  return true;
    }
	  get_text_show(text);
	  if(text.intersect(rect)){
		  return true;
    }
    break;
  }

//	get_text3_show(text);
//	if(text.intersect(rect))
//		return true;
	return false;
}
bool Ln_Dim::envelopme(const Rect& rect) const
{
	Rect rc,rc2,rc3;
	Text text;
	get_text_show(text);
	rc = text.box2d();
	get_text2_show(text);
	rc2 = text.box2d();
	//get_text3_show(text);
	//rc3 = text.box2d();
	return opt_.envelop(rect) && spt_.envelop(rect) && ept_.envelop(rect) 
		&& odm_.envelop(rect) && edm_.envelop(rect)
		&& rc.envelop(rect) && rc2.envelop(rect) /*&& rc3.envelop(rect)*/;
}

Rect Ln_Dim::calc_box2d() const
{
	Rect box;
	dlhml::box2d(box,get_show_record());
//	Entity_Calculate calc;
//  calc.get_ents_rect(box,get_show_record());
	return box;
//  Rect box;
//  std::vector<Entity*> ents;
//  get_show(ents);
//  Entity_Calculate calc;
//  calc.get_ents_rect(box,ents);
//  return box;
}
//Rect Ln_Dim::calc_box2d() const
//{
//	Rect box;
//  std::vector<Entity*> ents;
//  get_show(ents);
////	Line oln,eln,odm,edm;
////	get_o_lines(oln,odm);
////	get_e_lines(eln,edm);
////	ents.push_back(&oln);
////	ents.push_back(&odm);
////	ents.push_back(&eln);
////	ents.push_back(&edm);
////	Text text;
////	get_text_show(text);
////	ents.push_back(&text);
////	Text text2;
////	get_text2_show(text2);
////	ents.push_back(&text2);
////	//Text text3;
////	//get_text3_show(text3);
////	//ents.push_back(&text3);
//	Entity_Calculate calc;
//	calc.get_ents_rect(box,ents);
//	return box;
//}

//bool Ln_Dim::snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const
//{
////NOOK SNAP 2009.07.02
//  return false;
////	Entity_Snap_Implement<Ln_Dim> imp(*this);
////	return ent.snap_intersect_point_imp(pt,imp,rect);
//}
bool Ln_Dim::snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const
{
	return snap.intersect(pt,rect,*this);
}

//  //template<class T> 
//void Ln_Dim::get_entitits_show(std::vector<Entity*>& es,
//  int (Ln_Dim::*show_ptr)(std::vector<Line*>))const
//{
//  std::vector<Line*> oln_arraw;
//  oln_arraw.resize(ARROW_LINE_COUNT);
//  int i=0;
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i] = Line::create_me();
//  }
//  int oln_arraw_num = show_ptr(oln_arraw);
//  for(i=0; i<oln_arraw_num; i++){
//    es.push_back(oln_arraw[i]->clone());
//  }
//  for(i=0; i<oln_arraw.size(); i++){
//    oln_arraw[i]->close();
//  }
//  return; 
//}




void Ln_Dim::setctrl(const std::vector<Point>& pts)
{
//NOOK fatal error C1001: INTERNAL COMPILER ERROR with japanese system.
  if(pts.size() < 3){
    return;
  }
  opt_=pts[0];
  spt_=pts[0];
  ept_=pts[1];
  odm_=pts[2];
  edm_=pts[2];


  ////dim_line_radian_
  if(dim_rota_ == ORTHO_DIM){
    //Rect baserc = baseln.box2d();
    Rect baserc;//= baseln.box2d();
    baserc.xmin(min(opt_.x,ept_.x));
    baserc.xmax(max(opt_.x,ept_.x));
    baserc.ymin(min(opt_.y,ept_.y));
    baserc.ymax(max(opt_.y,ept_.y));


    if(EquFloat(baserc.ymin(),baserc.ymax())){
      dim_line_radian_=h_radian(opt_,ept_);
    }
    else if(EquFloat(baserc.xmin(),baserc.xmax())){
      dim_line_radian_=v_radian(opt_,ept_);
    }
    else if(edm_.envelop(baserc)){
      if(MoreEqu(fabs(opt_.x-ept_.x),fabs(opt_.y-ept_.y))){
        dim_line_radian_ = h_radian(opt_,ept_);
      }
      else{
        dim_line_radian_ = v_radian(opt_,ept_);
      }
    }
   else if(MoreEqu(edm_.x,baserc.xmin())&&LessEqu(edm_.x,baserc.xmax())){
      dim_line_radian_ = h_radian(opt_,ept_);
    }
    else if(MoreEqu(edm_.y,baserc.ymin())&&LessEqu(edm_.y,baserc.ymax())){
      dim_line_radian_ = v_radian(opt_,ept_);
    }
    else{
      dlhml::Line baseln;
			baseln.setdata(opt_,ept_);
      Point mid = baseln.middle();
      Line hln, vln;
      Normal hnor(1,0,0), vnor(0,1,0);
      hln.setdata(mid,hnor);
      vln.setdata(mid,vnor);
      Float hdis = hln.distanceto2d(edm_);
      Float vdis = vln.distanceto2d(edm_);
      if(MoreEqu(hdis,vdis)){
        ////距离水平中线较远
        dim_line_radian_ = h_radian(opt_, ept_);
      }
      else{
        dim_line_radian_ = v_radian(opt_, ept_);
      }
    }

  }


	//2014-10-24 zgb 
  else if(dim_rota_ == ALIGN_DIM){
    Normal nor;
    nor.set_data(opt_,ept_);
    normal2d_2_radian(nor,dim_line_radian_);


  }

  show_change(true);


}
void Ln_Dim::getctrl(std::vector<Point>& pts)const
{
  pts.push_back(opt_);
  pts.push_back(ept_);
  pts.push_back(edm_);
}
int Ln_Dim::pt_count()const
{
  return 3;
}

void Ln_Dim::ext_line_normal(Normal& nor)
{
  show_change(true);
  Line oexln,odmln;
  get_o_lines(oexln, odmln);
  Point st,ed;
  st  = oexln.start();
  ed  = oexln.start();
  ed += nor;
  Point ed_oex = oexln.perpendicular(ed);
  nor.set_data(st,ed_oex);
}


//void Ln_Dim::offset_dm(const Normal off_nor, int flags)
//{
//  Normal nor = off_nor;
//  ext_line_normal(nor);
//
//  Point pt = flags==1 ? odm() : edm();
//	pt += nor;
//	flags==1 ? odm(pt) : edm(pt);
//  pt = flags==1 ? text_position() : mode() ? text_position() :  text2_position();
//	pt += nor;
//	flags==1 ? text_position(pt) : mode() ? text_position() : text2_position(pt);
//}

Float Ln_Dim::ext_line_radian()const
{
  return dim_line_radian_ + dlhml::pi/2;
}


// Rect Ln_Dim::offset_box()    //  干涉后参与偏移部分的外框
// void offset_pp(); //  偏移位置++
// int  offset_floor();  //  起始楼层
// int  span_floor();    //  占用层数
// int  floor_count();   //  楼层数

Float Ln_Dim::get_span_oe() const
{
  Line oexln, eexln, odmln, edmln;
  get_o_lines(oexln, odmln);
  get_e_lines(eexln, edmln);
//   Point pedal_in_odm = PointPedal(eexln.end(), oexln);
// 	double dis = pedal_in_odm.distanceto(eexln.end());
//	geo::Line gln =	dlhml::convert(oexln);
//	geo::Point gpt = dlhml::convert(eexln.end());
// 	Float dis = gln.dis2d(gpt);
	return 0;
}

Float Ln_Dim::get_span_se() const
{
//  Line sexln, eexln, sdmln;
//  get_s_lines(sexln,eexln,sdmln);
//	double dis = sdmln.length();
	return 0;
}

}//namespace
