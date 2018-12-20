// Create_Entity.cpp: implementation of the Create_Entity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Create_Entity.h"

#include <cassert>
#include <string>
#include <sstream>
#include <ctype.h>

#include "../object/Global.h"

#include "Point.h"
#include "Scene_d.h"
#include "Rect.h"
#include "Database.h"
#include "Paint_Entity.h"
#include "Painter.h"
#include "myalgorithm.h"
#include "Layer.h"
#include "Normal.h"
#include "Cad_Command.h"
#include "Blue_Frame_Tools.h"

#include "../include/getrace.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml
{

static int s_count;
static void trace_new()
{
	++s_count;
	//TRACE_OUT("\nnew Cmd(Create_Entity), count : %d\n", s_count);
}
static void trace_del()
{
	--s_count;
	//TRACE_OUT("\ndel Cmd(Create_Entity), count : %d\n", s_count);
}


LPCTSTR Create_Entity::OUTSIDE_BLUE_FRAME_  = "outside_blue_frame.";

int Create_Entity::pick_rect_edge_length(RECT_SIZE rcsz) const
{
	switch(rcsz){
		case DRAG_RC:
			return 5;
			break;
		case STRECH_RC:
			return 3;
			break;
		default:
			return 5;
			break;
	}
}
Create_Entity::Create_Entity(Scene& scene)
:scene_(scene)
,step_(0)
,first_(true)
,group_ents_(NULL)
,needundo_(true) 
,steel_(0)
//,undoed_(false)
,cadcmdflag_(CAD_NULL)
,cad_(NULL)
,work_state_(WORK_IDLE)
,ortho_(true)
,iscopy_(false)
//,cad_iter_(-1)
,create_text_(false)
,blue_frame_(false)
,type_(EDIT)
,type_temp_(EDIT)
,copynum_(0)
//,scn_(NULL)
MCT_INIT2("Create_Entity")
{
//	TRACE_OUT("\n####Create_Entity::Create_Entity()\n");
	trace_new();
  myclass_ = "Create_Entity";
	//scn_ = &scene_;
//	TRACE_OUT("####scene_ptr:%d\n",&scene_);
	//TRACE_OUT("####scn_ptr:%d\n",scn_);
	//TRACE_OUT("####scn_ptr&:%d\n",&scn_);
}

void Create_Entity::copy(const Create_Entity& s, Create_Entity& d)const
{
  d.mouse_screen_ = s.mouse_screen_;
  d.mouse_move_ = s.mouse_move_;
  d.mouse_snap_ = s.mouse_snap_;
  d.steel_ = s.steel_;
	d.blue_frame_ = s.blue_frame_;

	d.myclass_ = s.myclass_;
}

Create_Entity::~Create_Entity()
{
	trace_del();
	//TRACE_OUT("Create_Entity::~Create_Entity()\n");
	dlhml::destory(bk_);
}
Point Create_Entity::screen2world(const Point& cpt)
{
	Point pt(cpt);
#ifndef USE_IMAGE
	scene_.screen_to_world_point(pt);
#endif
  pt.z=0;
	return pt;
}
void Create_Entity::get_ortho_point(const Point& base,Point& pt)
{
  if(!scene_.ortho())
    return;
  if(fabs(pt.x-base.x) < fabs(pt.y-base.y))
    pt.x = base.x;
  else
    pt.y = base.y;

  pt.z=0;
}
void Create_Entity::rect_from_center_pt(Rect& rc,const Point& center,Float halfEdgeLen)
{
  rc.xmin(center.x - halfEdgeLen);
  rc.xmax(center.x + halfEdgeLen);
  rc.ymin(center.y - halfEdgeLen);
  rc.ymax(center.y + halfEdgeLen);
}
bool Create_Entity::get_snap_point(Point& pt, bool xor)
{
  Float halfedge = pick_rect_edge_length() * scene_.screen_to_world().value(0,0);
  Rect rc;
  rect_from_center_pt(rc,pt,halfedge);
  Snap* snap = scene_.get_snap_flag();
  //bool  draw_c=false;
  bool b = scene_.database()->snap_entity(scene_.paint_snap_,
                                          pt,
                                          rc,
                                          *snap,
                                          begin_);


  if(xor){
    Painter* painter = scene_.get_painter();
    Paint_Entity paint(scene_,*painter);
    scene_.paint_snap_.paint_snap(paint,pt,halfedge);
  }

//  return b||snap->anypoint();
  pt.z=0;
  return b;
}
  //  if(draw_c){
  //    Line ln(c_,c_);
  //    ln.selected(true);
  //    ln.color(RGB(255,0,255));
  //    ln.draw(get_paint());
  //    draw_c = false;
  //  }
void Create_Entity::mouse_move(UINT nFlags, const Point& pt)
{
  mouse_screen_ = pt;
  Point lpt = screen2world(pt);
  lpt.z=0;
  if(MK_MBUTTON == nFlags){
  //scene_.set_move(move_point_.x-lpt.x,move_point_.y-lpt.y,move_point_.z-lpt.z);
    scene_.set_move(move_point_.x-lpt.x,move_point_.y-lpt.y,0);
    scene_.invalidate();
  }
  char ch[20];
  ::sprintf(ch,"%.4f,%.4f",lpt.x,lpt.y);
  scene_.coord_info_to_status(ch);



	//TRACE_OUT("Create_Entity::mouse_move:\n");
	//TRACE_OUT("mouse_move_:\t%f\t,%f\n",mouse_move_.x, mouse_move_.y);
  mouse_move_ = lpt;

  adjust_point(lpt,false);
	//TRACE_OUT("adjust_point:\t%f\t,%f\n",lpt.x, lpt.y);
  if(cad_){
    lpt = cad_->key_cammand(begin_,lpt);
		//TRACE_OUT("cad_->(lpt):\t%f\t,%f\n",lpt.x, lpt.y);
  }
  //lpt.z=0;
  mouse_snap_ = lpt;
	//TRACE_OUT("mouse_snap_:\t%f\t,%f\n",mouse_snap_.x, mouse_snap_.y);

	move_button(nFlags,lpt);
}
void Create_Entity::move_button(UINT nFlags, const Point& pt)
{
	mouse_move_p(nFlags,pt);
}
void Create_Entity::left_button_down(UINT nFlags, const Point& pt) 
{
	Point lpt = screen2world(pt);
//  if(!adjust_){
//    left_button_down_p(nFlags,lpt);
//    return;
//  }

// 	TRACE_OUT("\n####\nCreate_Entity::left_button_down:\n");
// 	TRACE_OUT("lpt:\t%f\t,%f\n",lpt.x, lpt.y);
// 	TRACE_OUT("mouse_snap_:\t%f\t,%f\n",mouse_snap_.x, mouse_snap_.y);
  lpt=mouse_snap_;
  lpt.z=0;
  if(!adjust_point(lpt)){
    return;
  }
  //lpt.z=0;
	left_button(nFlags, lpt);
  //set(lpt);
} 

//  if(create_text_){
//    if(!adjust_blue_frame(lpt)){
//      return;
//    }
//    left_button_down_p(nFlags,lpt);
//    return;
//  }

void Create_Entity::left_button(UINT nFlags, const Point& pt)
{
  if(!adjust_blue_frame(pt)){
    return;
  }
  //lpre_ = left_;
	//left_ = pt   ;
	//set_left(pt);
  left_button_down_p(nFlags,pt);

	////记录上次左键按下的点
	scene_.pre_left(pt);
}

void Create_Entity::left_button_up(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  //lpt.z=0;
	//get_snap_point(lpt);
  left_button_up_p(nFlags,lpt);
}
void Create_Entity::left_button_dblclk(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  lpt=mouse_snap_;
  lpt.z=0;
  left_button_dblclk_p(nFlags,lpt);
}
void Create_Entity::right_button_down(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  right_button_down_p(nFlags,lpt);
}
void Create_Entity::right_button_up(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  right_button_up_p(nFlags,lpt);
  //  lin shi zhe me yong.
  //on_ok();
}
void Create_Entity::right_button_dblclk(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  right_button_dblclk_p(nFlags,lpt);
}
void Create_Entity::middle_button_down(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  //lpt.z=0;
  move_point_ = lpt;
  middle_button_down_p(nFlags,lpt);
}
void Create_Entity::middle_button_up(UINT nFlags, const Point& pt)
{
  Point lpt = screen2world(pt);
  middle_button_up_p(nFlags,lpt);
}

void Create_Entity::move_scene(const Entity * e, double scale)
{
	if(!e) return;
	move_scene(e->box2d()*scale);
}
void Create_Entity::move_scene(const std::vector<Entity*>& es, double scale)
{
	Rect rc;
	dlhml::box2d<Entity>(es, rc);
	move_scene(rc);
}

void Create_Entity::move_scene(const Rect& rc)
{
	Rect rect = rc;
	if(rect.xmin() == rect.xmax()){
		rect.xmin(rect.xmin()-100);
		rect.xmax(rect.xmax()+100);
	}
	if(rect.ymin() == rect.ymax()){
		rect.ymin(rect.ymin()-100);
		rect.ymax(rect.ymax()+100);
	}


  //移动
  Point mino;
  mino.setdata(rect.xmin(),rect.ymin(),0.0);
  scene_.set_move(-mino.x,-mino.y,-mino.z);
  //缩放
  Rect client_rc;
  client_rc = scene_.client_rect();
  Point lpt;
  lpt.setdata(client_rc.width(),client_rc.height(),0.0);
  Float scale = 1.0;
  Float scaley = (rect.ymax()-rect.ymin())/lpt.y;
  Float scalyx = (rect.xmax()-rect.xmin())/lpt.x;
  if(scaley < scalyx){
    scale = scalyx;///0.9;
  }
  else{
    scale = scaley;///0.9;
  }
  scale = 1.01*scale/scene_.get_current_scale();
  scene_.set_scale(scale,scale,scale);
  //移动
  Point srco;
  srco.setdata((rect.xmax()+rect.xmin())/2.0,(rect.ymax()+rect.ymin())/2.0,0.0);
  Point desto;
  Point c(client_rc.width()/2.0,client_rc.height()/2.0);
  desto = scene_.get_current_center(c);
  scene_.set_move(srco.x-desto.x,srco.y-desto.y,srco.z-desto.z);
  scene_.invalidate();
	
}

void Create_Entity::middle_button_dblclk(UINT nFlags, const Point& pt)
{
  Rect rect;
  scene_.database()->all_entity_rect(rect);

  if(rect==Rect()){
    rect.xmin(-10);
    rect.ymin(-10);
    rect.xmax(100);
    rect.ymax(100);
  }
  
	move_scene(rect);
  
  Point spt = screen2world(pt);
  middle_button_dblclk_p(nFlags,spt);
}

static bool can_zoom_out(Scene& sn)
{
  const Float zoom_max = 1000000;
  RECT src;
  sn.screen_rc(src);
  Rect rc(src);
  sn.screen_to_world_rect(rc);
  if(fabs(rc.xmax()-rc.xmin()) >= zoom_max){
    return false;
  }
  if(fabs(rc.ymax()-rc.ymin()) >= zoom_max){
    return false;
  }
  return true;
}

static bool can_zoom_in(Scene& sn)
{
  const Float zoom_min = 10;
  RECT src;
  sn.screen_rc(src);
  Rect rc(src);
  sn.screen_to_world_rect(rc);
  if(fabs(rc.xmax()-rc.xmin()) <= zoom_min){
    return false;
  }
  if(fabs(rc.ymax()-rc.ymin()) <= zoom_min){
    return false;
  }
  return true;
}

void Create_Entity::mouse_wheel(UINT nFlags, short zDelta, const Point& pt)
{
  Float wheel_scale = scene_.wheel_speed();
  if(wheel_scale <= 0){
    wheel_scale = 1.5;
  }

  Point lpt = screen2world(pt);
  lpt.z=0;
  if(step_==SEL_S||step_==SEL_E){
    get_snap_point(lpt,false);
    lpt.z=0;
  }
  Float srcx = -lpt.x;
  Float srcy = -lpt.y;
  Float srcz = -lpt.z;
  //Float srcz = -lpt.z;
  scene_.set_move(srcx,srcy,srcz);
  Float scale = 1.0;
  if(zDelta < 0){
    scale = wheel_scale;
  }else{
    scale = 1/wheel_scale;
  }
  
  if(scale > 1 && !can_zoom_out(scene_)){
    scale = 1;
  }
  if(scale < 1 && !can_zoom_in(scene_)){
    scale = 1;
  }

  scene_.set_scale(scale,scale,scale);
  scene_.set_move(-srcx,-srcy,-srcz);
  scene_.invalidate();
  mouse_wheel_p(nFlags,zDelta,lpt);
}


/////////////////////////////////////////////////////////
static LPCTSTR BLANK_CHAR = " \t";

static bool is_empty(const std::string& txt)
{
	std::stringstream ss(txt);
	std::string str;
	ss >> str;
	return str.empty();
}

static bool is_at(const std::string& txt)
{
	std::stringstream ss(txt);
	std::string str;
	ss >> str;
	if(str.empty()){
		return false;
	}
  return (str[0] == '@') ;
}

static bool is_float(const std::string& str)
{
	int i=0;
	for(; i<str.size(); ++i){
		if(!isdigit(str[i]) && str[i] != '.' && str[i] != '-'){
			return false;
		}
	}
	return true;
}


////@141.4<1,1
////@141.4<45
////141.4<1,1
////141.4<45
static bool get_len(const std::string& txt, Float& len)
{
	int at_pos = txt.find('@');
	int sp_pos = txt.find('<');
	if( (sp_pos==std::string::npos) || (at_pos >= sp_pos) ){
		return false;
	}
	if(at_pos==std::string::npos){
		at_pos = -1;
	}

	std::string lentxt = txt.substr(at_pos+1, sp_pos-at_pos-1);
	std::string lenstr = dlhml::std_str(lentxt, BLANK_CHAR);

	if(lenstr.empty()){
		return false;
	}
	if(!is_float(lenstr)){
		return false;
	}
	len = atof(lenstr.c_str());
	
	return true;
}

////100,100
static bool str_2_pt(const std::string& str, Point& pt)
{
	std::vector<std::string> subs;
	dlhml::parse(subs, str, ",");

	if(subs.size() < 2){
		return false;
	}
	std::string x = dlhml::std_str(subs[0], BLANK_CHAR);
	std::string y = dlhml::std_str(subs[1], BLANK_CHAR);

	if(!is_float(x) || !is_float(y)){
		return false;
	}
	pt.x = atof(x.c_str());
	pt.y = atof(y.c_str());

	return true;
}

////@100,100
static bool get_pt(const std::string& txt, Point& nor)
{
	int sp_pos = txt.find('@');
	if( (sp_pos==std::string::npos) || (sp_pos+1==std::string::npos) ){
		return false;
	}
	std::string nortxt = txt.substr(sp_pos+1);
	std::string norstr = dlhml::std_str(nortxt, BLANK_CHAR);
	
	if(norstr.empty()){
		return false;
	}
  if(!str_2_pt(norstr, nor)){
		return false;
	}
	
	return true;
}


////@141.4<1,1
static bool get_nor(const std::string& txt, Normal& nor)
{
	int sp_pos = txt.find('<');
	if( (sp_pos==std::string::npos) || (sp_pos+1==std::string::npos) ){
		return false;
	}
	std::string nortxt = txt.substr(sp_pos+1);
	std::string norstr = dlhml::std_str(nortxt, BLANK_CHAR);

	if(norstr.empty()){
		return false;
	}
	Point pt;
  if(!str_2_pt(norstr, pt)){
		return false;
	}
	nor.set_data(pt);

	return true;
}

////@141.4<45
static bool get_degree(const std::string& txt, Float& degree)
{
	int sp_pos = txt.find('<');
	if( (sp_pos==std::string::npos) || (sp_pos+1==std::string::npos) ){
		return false;
	}
	std::string degtxt = txt.substr(sp_pos+1);
	std::string degstr = dlhml::std_str(degtxt, BLANK_CHAR);

	if(degstr.empty()){
		return false;
	}
	if(!is_float(degstr)){
		return false;
	}
	degree = atof(degstr.c_str());

	return true;
}

////@141.4<1,1
////141.4<1,1
static bool len_normal(const Point& begin, 
											 const Point& mouse, 
											 const std::string& txt, 
											 Point& pt)
{
// 	if(!is_at(txt)){
// 		return false;
// 	}
	Float len = 0;
	if(!get_len(txt, len)){
		return false;
	}
	Normal nor;
	if(!get_nor(txt, nor)){
		return false;
	}
	pt = begin.polarTo(len, nor);

	return true;
}

////@141.4<45  
////141.4<45  
static bool len_degree(const Point& begin, 
											 const Point& mouse, 
											 const std::string& txt, 
											 Point& pt)
{
// 	if(!is_at(txt)){
// 		return false;
// 	}
	Float len = 0;
	if(!get_len(txt, len)){
		return false;
	}
	Float deg;
	if(!get_degree(txt, deg)){
		return false;
	}
	Normal nor;
	dlhml::degree_2_normal2d(deg, nor);
	pt = begin.polarTo(len, nor);
	
	return true;
}

////@100,100
static bool normal_pt(const Point& begin, 
											const Point& mouse, 
											const std::string& txt, 
											Point& pt)
{
	if(!is_at(txt)){
		return false;
	}
	Point nor;
	if(!get_pt(txt, nor)){
		return false;
	}
	pt = begin + nor;

	return true;
}

////2100,3100
static bool real_pt(const Point& begin, 
										const Point& mouse, 
										const std::string& txt, 
										Point& pt)
{
	std::string str = dlhml::std_str(txt, BLANK_CHAR);
	if(!str_2_pt(str, pt)){
		return false;
	}

	return true;
}

////@100
////100
static bool len_pt(const Point& begin, 
									 const Point& mouse, 
									 const std::string& txt, 
									 Point& pt)
{
	std::string str = dlhml::std_str(txt, BLANK_CHAR);
	if(str[0] == '@'){
		str.erase(str.begin());
	}
	if(!is_float(str)){
		return false;
	}
	Float  len = atof(str.c_str());
	Normal nor;
	nor.set_data(begin, mouse);
	nor.set_unit();
	pt = begin.polarTo(len, nor);

	return true;
}

static bool cmdln(const Point& begin, const Point& mouse, std::string txt, Point& pt)
{
	if(len_normal(begin, mouse, txt, pt)){
		return true;
	}
	if(len_degree(begin, mouse, txt, pt)){
		return true;
	}
	if(normal_pt(begin, mouse, txt, pt)){
		return true;
	}
	if(real_pt(begin, mouse, txt, pt)){
		return true;
	}
	if(len_pt(begin, mouse, txt, pt)){
		return true;
	}

	return false;
}

Point Create_Entity::get_rotate_temp_end(Float val)
{
	Point pt;
	Float len = 100;
	Normal tnor, enor;
	dlhml::degree_2_normal2d(0  , tnor);
	dlhml::degree_2_normal2d(val, enor);
	temp_ = begin_.polarTo(len, tnor);
	pt    = begin_.polarTo(len, enor);
	return pt;
}

Point Create_Entity::get_rotate_end(Float val)
{
	Point pt;
	Float len = begin_.distanceto2d(temp_);
	Normal tnor, enor;
	Float  tdeg=0, edeg=0;
	tnor.set_data(begin_, temp_);
	dlhml::normal2d_2_degree(tnor, tdeg);
	edeg = tdeg + val;
	dlhml::degree_2_normal2d(edeg, enor);
	pt = begin_.polarTo(len, enor);
	return pt;
}

static bool get_rotate_degree(Float sdeg, std::string txt, Float& edeg)
{
	std::string str = dlhml::std_str(txt, BLANK_CHAR);
	bool at_pos = false;
	if(str[0] == '@'){
		str.erase(str.begin());
		at_pos = true;
	}
	if(!is_float(str)){
		return false;
	}
	Float  val = atof(str.c_str());
	if(at_pos){
		edeg = sdeg + val;
	}else{
		edeg = val;
	}
	dlhml::std_degree(edeg);
	
	return true;
}

bool Create_Entity::get_rotate_pt(Point& temp, Point& end, std::string cmdtxt)const
{
	Float len = 100;
	Float tdeg=0, edeg=0;
	Normal tnor, enor;
	dlhml::degree_2_normal2d(tdeg, tnor);
	if(!get_rotate_degree(tdeg, cmdtxt, edeg)){
		return false;
	}
	dlhml::degree_2_normal2d(edeg, enor);
	temp = begin_.polarTo(len, tnor);
	end  = begin_.polarTo(len, enor);

	return true;
}
bool Create_Entity::get_rotate_pt(Point& end, std::string cmdtxt)const
{
	Float len = begin_.distanceto2d(temp_);
	Normal tnor, enor;
	Float  tdeg=0, edeg=0;
	tnor.set_data(begin_, temp_);
	dlhml::normal2d_2_degree(tnor, tdeg);
	if(!get_rotate_degree(tdeg, cmdtxt, edeg)){
		return false;
	}
	dlhml::degree_2_normal2d(edeg, enor);
	end = begin_.polarTo(len, enor);

	return true;
}


Point Create_Entity::get_scale_end(Float val)
{
	Point pt;
	Float len = val * 100;
	pt = begin_;
	pt.x += len;
	return pt;
}

void Create_Entity::cmdin()
{
	Point pt;
	bool iskeypt = false;
	Float val = 0;
	char buf[512];
	int len = get_commmand_line_string(buf);
	buf[len] = '\0';
	std::string cmdtxt = buf;
	if(cmdtxt.empty()){
		return;
	}
	

	if(cad_ && type_ == COPY && step_ == DRAGS && get_command_line_length(val)){
		cad_->count(val);
		iskeypt = false;
	}
	else if(cad_ && cad_->cadtype()==ROTACMD && step_ == DRAGT && 
																get_rotate_pt(temp_, pt, cmdtxt)){
		//pt = get_rotate_temp_end(val);
		step_ = DRAGE;
		iskeypt = true;
	}
	else if(cad_ && cad_->cadtype()==ROTACMD && step_ == DRAGE && 
																get_rotate_pt(pt, cmdtxt)){
		//pt = get_rotate_end(val);
		//step_ = DRAGE;
		iskeypt = true;
	}
	else if(cad_ && cad_->cadtype()==SCALECMD && step_ == DRAGE && get_command_line_length(val)){
		pt = get_scale_end(val);
		//step_ = DRAGE;
		iskeypt = true;
	}
	else{
		if(!cmdln(scene_.pre_left(), mouse_snap_, cmdtxt, pt)){
			command_line_output("\ninput error, again please.");
			return;
		}
		if(cad_){ 
			cad_->key_cammand(begin_, pt);
		}
		iskeypt = true;
	}
	
	if(iskeypt){
		move_button(NULL, pt);
		left_button(NULL, pt);
	}
	scene_.info_to_command_line("",true);
	scene_.invalidate();
}

void Create_Entity::key_down(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  vk_.set_data(nChar,nRepCnt,nFlags);
  key_down_p(nChar,nRepCnt,nFlags);

	return;

	if(vk_.enter()){
		Point pt;
		bool iskeypt = false;
		Float val = 0;
		char buf[512];
		int len = get_commmand_line_string(buf);
		buf[len] = '\0';
		std::string cmdtxt = buf;

		if(cad_ && step_ == DRAGS && type_ == COPY && get_command_line_length(val)){
			cad_->count(val);
			iskeypt = false;
		}else{
			if(!cmdln(scene_.pre_left(), mouse_snap_, cmdtxt, pt)){
				command_line_output("\ninput error, again please.");
				return;
			}
			if(cad_){ 
				cad_->key_cammand(begin_, pt);
			}
			iskeypt = true;
		}

		if(iskeypt){
			move_button(NULL, pt);
			left_button(NULL, pt);
		}
		scene_.info_to_command_line("",true);
		scene_.invalidate();
	}
}

// void Create_Entity::key_down(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
//   vk_.set_data(nChar,nRepCnt,nFlags);
//   key_down_p(nChar,nRepCnt,nFlags);
// //  if(create_text_){
// //    return;
// //  }
// 
// 	if(vk_.enter()){
// 		double val = 0;
// 		Point pt;
// 		int  num = 0;
// 		bool iskeypt = false;
// 
// 		if(get_command_line_point(pt)){
// 			iskeypt = true;
// 			if(cad_){
// 				pt = cad_->key_cammand(begin_,pt);
// 			}
// 			TRACE_OUT("Create_Entity::key_down()-get_command_line_point\n");
// 		}
// 		else if(get_command_line_length(val)){
// 			iskeypt = true;
// 			if(cad_){
// 				if(step_ == DRAGS && type_ == COPY){
// 					cad_->count(val);
// 					iskeypt = false;
// 				}else{
// 					pt = cad_->key_cammand(begin_,mouse_snap_,val);
// 				}
// 			}else{
// 				Normal nor;
// 				nor.set_data(begin_, mouse_snap_);
// 				pt = begin_.polarTo(val, nor);
// 			}
// 			TRACE_OUT("Create_Entity::key_down()-get_command_line_length\n");
// 		}
// 		if(iskeypt){
// 			move_button(NULL, pt);
// 			left_button(NULL, pt);
// 		}
// 		scene_.info_to_command_line("",true);
// 		//on_enter();
// 		scene_.invalidate();
// 	}
// }


// Entity* Create_Entity::get_move_src()
// {
//   if(undoed_){
//     if(cad_iter_<0 || cad_iter_>= bk_.size()){
//       return NULL;
//     }
//     return bk_[cad_iter_];
//   }
//   else{
//     if(cad_iter_<0 || cad_iter_>= xor_.size()){
//       return NULL;
//     }
//     return xor_[cad_iter_];
//   }
// }
// Entity* Create_Entity::get_copy_src()
// {
//   if(!iscopy_){
//     return NULL;
//   }
//   if(undoed_){
//     if(cad_iter_<0 || cad_iter_>= bk_.size()){
//       return NULL;
//     }
//     return bk_[cad_iter_];
//   }
//   else{
//     if(cad_iter_<0 || cad_iter_>= xor_.size()){
//       return NULL;
//     }
//     return xor_[cad_iter_];
//   }
// }


//**********************************************************************
bool Create_Entity::is_there(const std::vector<Entity*>& es, MY_CLASS mc)
{
  int i=0;
  for(i=0; i<es.size(); i++){
    if(!es[i]){
      continue;
    }
    if(es[i]->myclass() == mc){
      return true;
    }
  }
  return false;
}


void Create_Entity::set_first_draw()
{
	first_ = true;
  refresh();
}
void Create_Entity::xor_draw()
{
	Painter* painter = scene_.get_painter();
	Paint_Entity paint(scene_,*painter);
	if(!first_){
		xor_draw_p(paint);
	}
	first_ = false;
}
bool Create_Entity::get_command_line_point(Point& pt) const
{
	return scene_.get_command_line_point(pt);
}
bool Create_Entity::get_command_line_length(Float& val) const
{
	return scene_.get_command_line_length(val);
}
int Create_Entity::get_commmand_line_string(LPTSTR str) const
{
	return scene_.get_commmand_line_string(str);
}



void Create_Entity::command_line_output(LPCTSTR txt,bool up)
{
  scene_.info_to_command_line(txt, up);
}
void Create_Entity::command_line_output(double d,bool up)
{
  const int pt_format_buf_size = 128;
	char buf[pt_format_buf_size];
	int len = sprintf(buf, "%.6f\0", d);
	scene_.info_to_command_line(buf,up);
}
void Create_Entity::command_line_output(const Point& pt,bool up)
{
  const int pt_format_buf_size = 128;
	char buf[pt_format_buf_size];
	int len = sprintf(buf, "%.0f, %.0f\0", pt.x, pt.y);
	scene_.info_to_command_line(buf,up);
}

//  兰框指针 group_ents_
void Create_Entity::select_blue_frame(const Point& pt)
{
  bool blue = scene_.database()->select_group(group_ents_,pt);
  if(group_ents_ == NULL){
		return;
  }
	int count = group_ents_->entity_count();
  if(!blue){
    group_ents_ = NULL;
  }
}
void Create_Entity::select_blue_frame(const Entity& ent)
{
  bool blue = scene_.database()->select_group(group_ents_, ent);
 	if(group_ents_ == NULL){
		return;
 	}
  if(!blue){
    group_ents_ = NULL;
  }
}
void Create_Entity::select_blue_frame(const Entity_ID& id)
{
  bool blue = scene_.database()->select_group(group_ents_, id);
  if(group_ents_ == NULL){
		return;
  }
  if(!blue){
    group_ents_ = NULL;
  }
}

bool Create_Entity::is_in_blue_frame(const Point& pt)
{
  if(group_ents_ == NULL){
	  return false;
  }
  return group_ents_->isin(pt); 
}

//void Create_Entity::adjust(bool b)
//{
//  adjust_=b;
//}
//bool Create_Entity::adjust()const
//{
//  return adjust_;
//}

bool Create_Entity::adjust_blue_frame(const Point& pt, bool cmd)
{
	return true;

	if(blue_frame_){
		return true;
	}

  if(step_==SEL_S || step_==SEL_E || step_==DRAGS || step_==DRAGE || step_==EDITE){
    return true;
  }

  if(step_ == 0 || INSER_BLOCK){
    select_blue_frame(pt);
    if(!group_ents_){
      if(cmd){
        scene_.info_to_command_line("the point is outside any blue frame.",true);
      }
			return false;
    }
  }
  else{
    if(!group_ents_){
      return true;
    }
    if(!is_in_blue_frame(pt)){
      if(cmd){
        scene_.info_to_command_line("the point is outside the bule frame.",true);
      }
      return false;
    }
  }
  return true;
}

bool Create_Entity::adjust_point(Point& pt, bool cmd)
{
	//TRACE_OUT("Create_Entity::adjust_point:\n");
	if(blue_frame_){
		return true;
	}
	
  if(step_==SEL_S || step_==SEL_E){
    return true;
  }

  if(step_ >= STEP_ZERO && step_ < STEP_SNAP){
    bool snap = get_snap_point(pt);
    pt.z=0;
    bool anypt= scene_.get_snap_flag()->anypoint();
    if(step_ < STEP_ANYP && step_ > STEP_ZERO && ortho_ && step_!=DRAGS && step_!=SEL_S ){//&& !snap
      if(!cad_ || cad_->is_ortho()){
        get_ortho_point(begin_, pt);
      }
      pt.z=0;
    }
    if(snap || anypt){
      return true;
    }
  }
  else if(step_ >= STEP_SNAP){
    get_snap_point(pt);
    pt.z=0;
    return true;
  }
  else if(step_ < STEP_ZERO){
    return true;
  }

  if(cmd){
    scene_.info_to_command_line("Snap a point, please.",true);
  }
  return false;
}

bool Create_Entity::key_input_pt(Point& pt)
{
  if(vk_.enter()){
    if(get_command_line_point(pt)){
      scene_.info_to_command_line("",true);
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}
bool Create_Entity::key_input_length(Point& pt, Point prept)
{
  Float length(0.0);
  if(vk_.enter()){
    if(get_command_line_length(length)){
      if(step_ == 0){
        return false;
      }
			get_ortho_point(prept,mouse_snap_);
			Normal nor;
			nor.set_data(prept,mouse_snap_);
			pt = prept.polarTo(length,nor);
      scene_.info_to_command_line("",true);
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

Paint_Entity Create_Entity::get_paint()
{
  Painter* painter = scene_.get_painter();
  Paint_Entity paint(scene_, *painter);
  return paint;
}
double Create_Entity::get_len_screen(RECT_SIZE rcsz)
{
	return pick_rect_edge_length(rcsz) * scene_.screen_to_world().value(0,0);
}
void Create_Entity::get_rect(const Point& pt, Rect& myrc, RECT_SIZE rcsz)
{
	double len = get_len_screen(rcsz);
	myrc.xmin(pt.x-len);
	myrc.xmax(pt.x+len);
	myrc.ymin(pt.y-len);
	myrc.ymax(pt.y+len);
}

static void insert_gpentities_to_db(Database& db, Group_Ents * gp)
{
  Entity_ID id;
	int i=0;
	for(i=0; i<gp->entity_count(); ++i){
		gp->getat(i)->post2db(db, id);
	}
}

//**************************************************************

static void remove_gp_from_db(Database& db, Group_Ents * gp)
{
	Entity_ID id;
	int i=0;
	for(i=0; i<gp->entity_count(); ++i){
		id = gp->getat(i)->entity_id();
		db.remove_entity(id);
	}
}

 
bool Create_Entity::if_lock(Entity* ent)
{
	Layer* layer = NULL;
	bool if_have = scene_.database()->get_layer(layer,ent->layer_name());
	if(if_have && layer != NULL){
		if(layer->lock()){
			return true;
    }
	}
	return false;	
}

Entity* Create_Entity::id_2_entity(const Entity_ID& id)const
{
  Entity* ent = NULL;
  scene_.database()->entity_from_id(ent, id);
  return ent;
//  scene_.database()->entity_from_id(ent, id);
//  return ent;
}

//  Create_Entity * Create_Entity::clone()
//  {
//    Create_Entity* ce = cloneme();
//    return ce;
//  }
//  Create_Entity * Create_Entity::cloneme()
//  {
//    Create_Entity* ce = new Create_Entity;
//    copyme(ce);
//    return ce;
//  }
//  void Create_Entity::copyme(Create_Entity* ce)
//  {
//    ce->mouse_screen_ = mouse_screen_;
//    ce->mouse_move_   = mouse_move_  ;
//    ce->mouse_snap_   = mouse_snap_  ;
//    ce->steel_        = steel_       ;
//  }
//
void Create_Entity::refresh()
{
  draw(xor_);
  on_draw();
  scene_.paint_snap_.ondraw();  
  //get_snap_point(mouse_move_);
  //adjust_point(mouse_move_);
  //mouse_move(NULL,mouse_move_);
  mouse_move(NULL,mouse_screen_);
}

void Create_Entity::on_draw()
{
  //  Paint_Entity paint = get_paint();
  //  int i=0;
  //  for(i=0; i<xor_.size(); i++){
  //    xor_[i]->draw(paint);
  //  }
  //  draw(xor_);
  //  paint_snap_.ondraw();  
  //  get_snap_point(mouse_snap_);
    //get_snap_point(mouse_move_);
  //#ifdef _DEBUG
  //  command_line_output("on_draw");
  //#endif
}

void Create_Entity::xor(const std::vector<Entity*>& xor)
{
	//NOOK??
  dlhml::push_back<Entity>(xor, xor_);
}

const std::vector<Entity*>& Create_Entity::xor()const
{
  return xor_;
}


// void Create_Entity::clear_xor()
// {
// 	select(xor_, false);
// 	xor_.clear();
// }

void Create_Entity::xor_draw(const std::vector<Entity*> e, bool xor)
{
  Paint_Entity paint = get_paint();
  int i=0;
  for(i=0; i<xor_.size(); i++){
    if(xor){
      xor_[i]->xor_draw(paint);
    }
    else{
      xor_[i]->draw(paint);
    }
  }
}
void Create_Entity::draw(const std::vector<Entity*> e)
{
  xor_draw(e, false);
}

void Create_Entity::close()
{
  closeme();
}
//void Create_Entity::close()
//{
// 	if(undoed_){
// 		destory(bk_);
// 		bk_.clear();
// 	}
// 	else{
// 		destory(db_);
// 		db_.clear();
// 	}
//  closeme();
//}


//undo-redo************************************************** 
void Create_Entity::execute()
{
//	TRACE_OUT("Create_Entity::execute()\n");
	switch(type_){
		case ADD:
		case COPY:
		case MULTICOPY:
			insert_to_db();
			break;
		case DEL:
			remove_from_db();
			break;
		case EDIT:
		case PROP:
			swap_db_con();
			break;
		case ADD_DEL:
			swap_db_ptr();
			break;
	}
	
// 	undoed_ = false;
//   int i=0;
//   for(i=0; i<db_.size(); i++){
//     if(!db_[i]){
//       continue;
//     }
//     remove_from_db(db_[i]);
//   }
//   for(i=0; i<bk_.size(); i++){
//     if(!bk_[i]){
//       continue;
//     }
//     cad_iter_=i;
//     insert_to_db(bk_[i]);
//   }
//   cad_iter_=-1;
  if(is_there(db_,LINE_DIM_BLOCK) || is_there(bk_,LINE_DIM_BLOCK)){
    Blue_Frame_Tools bft(scene_,group_ents_);
    bft.reset_show_4pt_start();
  }
  scene_.invalidate();
}

void Create_Entity::unexecute()
{
//	TRACE_OUT("Create_Entity::unexecute()\n");
	switch(type_){
		case ADD:
		case COPY:
		case MULTICOPY:
			remove_from_db();
			break;
		case DEL:
			insert_to_db();
			break;
		case EDIT:
		case PROP:
			swap_db_con();
			break;
		case ADD_DEL:
			swap_db_ptr();
			break;
	}
	////undo redo 不虚了
	////增加bk（new）通知，和交换内容（*it）通知
	////EDIT，需要保证交换双方数量相等（不等的用其他方式处理，暂无）

// 	undoed_ = true;
//   int i=0;
//   for(i=0; i<bk_.size(); i++){
//     if(!bk_[i]){
//       continue;
//     }
//     remove_from_db(bk_[i]);
//   }
//   for(i=0; i<db_.size(); i++){
//     if(!db_[i]){
//       continue;
//     }
//     cad_iter_=i;
//     insert_to_db(db_[i]);
//   }
//   cad_iter_=-1;
  if(is_there(db_,LINE_DIM_BLOCK) || is_there(bk_,LINE_DIM_BLOCK)){
    Blue_Frame_Tools bft(scene_,group_ents_);
    bft.reset_show_4pt_start();
  }
  scene_.invalidate();
}

void Create_Entity::insert_to_db()
{
//	TRACE_OUT("\n####\nCreate_Entity::insert_to_db()\n");
	/////阵列复制时，复制一行一列，等于没复制
	// 	if(bk_.empty()){
	// 		return;
	// 	}
	////增加命令，db_内应没有对象
	assert(db_.empty() &&	"Create_Entity::insert_to_db()");
	std::swap(db_, bk_);
	assert(bk_.empty() &&	"Create_Entity::insert_to_db()");
	insert_to_db(db_);
}

void Create_Entity::remove_from_db()
{
	assert(bk_.empty() && "Create_Entity::remove_from_db()");
	remove_from_db(db_);
	std::swap(db_, bk_);
	assert(db_.empty() && "Create_Entity::remove_from_db()");
}

void Create_Entity::swap_db_ptr()
{
  int i=0;
  for(i=0; i<db_.size(); i++){
    if(!db_[i]){
      continue;
    }
    remove_from_db(db_[i]);
  }
  for(i=0; i<bk_.size(); i++){
    if(!bk_[i]){
      continue;
    }
    //cad_iter_=i;
    insert_to_db(bk_[i]);
  }
	std::swap(db_, bk_);
}

void Create_Entity::swap_db_con()
{
//	TRACE_OUT("Create_Entity::swap_db_con(dbs, bks)\n");
	assert(db_.size()==bk_.size() && "Create_Entity::swap_db()");
	int i=0;
	for(i=0; i<db_.size(); ++i){
		Entity * db = db_[i];
		Entity * bk = bk_[i];
		bk_[i]->selected(db_[i]->selected());
//		TRACE_OUT("Before...\n", (int)(db));
//		TRACE_OUT("db entity ptr == %d\t", (int)(db));
//		TRACE_OUT("db's color == %d\n", db->color_index());
//		TRACE_OUT("bk entity ptr == %d\t", (int)(bk));
//		TRACE_OUT("bk's color == %d\n", bk->color_index());
		dlhml::swap(db_[i], bk_[i]);
		if(type_ == PROP){
			swap_db_con_p(db_[i], bk_[i]);
		}
//		TRACE_OUT("After...\n", (int)(db));
//		TRACE_OUT("db entity ptr == %d\t", (int)(db));
//		TRACE_OUT("db's color == %d\n", db->color_index());
//		TRACE_OUT("bk entity ptr == %d\t", (int)(bk));
//		TRACE_OUT("bk's color == %d\n", bk->color_index());
	}

}

void Create_Entity::copy_bk(const Entity * db, std::vector<Entity*>& bk)
{
//	TRACE_OUT("Create_Entity::copy_bk(db, <>bk)\n");
//	TRACE_OUT("Before copy_bk: bk.size == %d\n", bk.size());
	assert(db && "Create_Entity::copy_bk(db, bk)");
	assert(!bk.empty() && "Create_Entity::copy_bk(db, bk)");
	copy_bk_p(db, bk);
}

void Create_Entity::copy_bk(std::vector<Entity*>& db, std::vector<Entity*>& bk)
{
	int db_size = db.size();
	int bk_size = bk.size();
	assert(bk_size % db_size == 0 && "Create_Entity::copy_bk()");
	copy_bk_p(db, bk);
}

void Create_Entity::insert_to_db(const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); ++i){
		insert_to_db(es[i]);
	}
}

void Create_Entity::remove_from_db(const std::vector<Entity*>& es)
{
	int i=0;
	for(i=0; i<es.size(); ++i){
		remove_from_db(es[i]);
	}
}

void Create_Entity::insert_to_db(Entity* entity)
{
	Database& db = *(scene_.database());
	
  Entity_ID id;
  if(entity->layer_name() ==""){
    entity->layer_name(layer_manual_dim);
  }
  entity->post2db(db, id);
	
	////兰框与其他实体区别对待
	if(entity->isa(MY_RUNTIME_CLASS(Group_Ents))){
		Group_Ents * gp = static_cast<Group_Ents*>(entity);
		insert_gpentities_to_db(db, gp);
	}
	else{
		if(group_ents_){
			group_ents_->push_back(entity);
		}
		insert_to_db_p(entity);
	}
	
  //return id;
}

void Create_Entity::remove_from_db(Entity* entity)
{
	Database& db = *(scene_.database());
	
	if(entity->isa(MY_RUNTIME_CLASS(Group_Ents))){
		Group_Ents * gp = static_cast<Group_Ents*>(entity);
		remove_gp_from_db(db, gp);
	}
	else{
		if(group_ents_){
			group_ents_->erase(entity);
		}
	}
  Entity_ID id = entity->entity_id();
  scene_.database()->remove_entity(id);
	
  remove_from_db_p(entity);
}

void Create_Entity::trace_seled_pt(const std::vector<Entity*>& es)const
{
#ifdef  _DEBUG
	int i=0;
	for(; i<es.size(); ++i){
		std::vector<Point> pts;
		es[i]->getstrech(pts);
		int k=0;
		for(; k<pts.size(); ++k){
			bool sel = pts[k].selected();
//			TRACE_OUT("\n#### The %d entity's the %d pt's highlight state is %d\n", i, k, sel);
		}
	}
#endif//_DEBUG
}

void Create_Entity::set_strech_pt(const std::vector<Entity*>& es)
{
	if(!cad_ || cad_->cadtype() != STRECHCMD){
		return;
	}

	strech_pt_.clear();
	int i=0;
	for(; i<es.size(); ++i){
		std::vector<Point> pts;
		es[i]->getstrech(pts);
		std::vector<bool> sel;
		int k=0;
		for(; k<pts.size(); ++k){
			bool itsel = pts[k].selected();
			sel.push_back(itsel);
		}
		strech_pt_.push_back(std::make_pair(i, sel));
	}
}
void Create_Entity::get_strech_pt(std::vector<Entity*>& es)const
{
	if(!cad_ || cad_->cadtype() != STRECHCMD){
		return;
	}

	assert(es.size() == strech_pt_.size() && "Create_Entity::get_strech_pt(), must be ==");
	int i=0;
	for(; i<es.size(); ++i){
		std::vector<Point> pts;
		es[i]->getstrech(pts);
		int aaa = pts.size();
		int bbb = strech_pt_[i].second.size();
		assert(pts.size() == strech_pt_[i].second.size() && "Create_Entity::get_strech_pt(), must be ==");
		int k=0;
		for(; k<pts.size(); ++k){
			pts[k].selected(strech_pt_[i].second[k]);
		}
		es[i]->setstrech(pts);
	}
}


void Create_Entity::copy_flag(bool b)
{
	if(type_ == COPY || type_ == MULTICOPY){
		return;
	}

	if(b){
		iscopy_ = true;
		if(type_ == EDIT){
			type_temp_ = type_;
			type_ = ADD;
		}
	}
	else{
		iscopy_ = false;
		if(type_temp_ == EDIT){
				type_ = EDIT;
		}
	}
}

}//namespace
