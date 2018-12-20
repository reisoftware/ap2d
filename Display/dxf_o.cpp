#include "StdAfx.h"
#include "dxf_o.h"
#include <vector>
#include <cassert>
#include "CadLib.h"
#include "../object/Global.h"
#include "../object/Entity.h"
#include "../object/Line.h"
#include "../object/Circle.h"
#include "../object/Line_Type.h"


using namespace std;
#define txt_style_name  "rei"

namespace dlhml{


#define g_lock_layer_name  "LOCK_LAYER"

#define layer_white_hidden "white_hidden"
#define layer_white_center "white_center"
#define layer_white_solid "white_solid"
#define layer_yellow_solid "yellow_solid"
#define layer_shuise_solid "shuise_solid"
#define layer_green_solid "green_solid"
#define layer_red_solid "red_solid"

#define layer_apcad  "apcad"

static OBJHANDLE add_lineType_solid(CDrawing& drawingSave)
{
	LTYPE ltype;
	//  Continuous
	ZeroMemory(&ltype, sizeof(ltype));
	strcpy(ltype.Name, "Continuous");
	strcpy(ltype.DescriptiveText, "Solid line");
	return drawingSave.AddLinetype(&ltype);

}
static OBJHANDLE add_lineType_hidden(CDrawing& drawingSave)
{
	//Hidden
	LTYPE ltype;
	ZeroMemory(&ltype, sizeof(ltype));
	strcpy(ltype.Name, "HIDDEN");
	strcpy(ltype.DescriptiveText, "Hidden __ __ __ __ __ __ __ __ __ __ __ __ __ _");
	ltype.ElementsNumber = 2;
	ltype.PatternLength = 9.5249999999999986;
	ltype.Elements[0] = 6.349999999999997;
	ltype.Elements[1] =-3.174999999999998;
	return drawingSave.AddLinetype(&ltype);

}
static OBJHANDLE add_lineType_center(CDrawing& drawingSave)
{
	//center
	LTYPE ltype;
	ZeroMemory(&ltype, sizeof(ltype));
	strcpy(ltype.Name, "CENTER");
	strcpy(ltype.DescriptiveText, "Center ____ _ ____ _ ____ _ ____ _ ____ _ ____");
	ltype.ElementsNumber = 4;
	ltype.PatternLength = 2.0;
	ltype.Elements[0] = 1.25;
	ltype.Elements[1] = -0.25;
	ltype.Elements[2] = 0.25;
	ltype.Elements[3] = -0.25;
	return drawingSave.AddLinetype(&ltype);
}
static OBJHANDLE add_lineType_DASHDOT2(CDrawing& drawingSave)
{
	//  DASHDOT2
	LTYPE ltype;
	ZeroMemory(&ltype, sizeof(ltype));
	strcpy(ltype.Name, "DASHDOT2");
	strcpy(ltype.DescriptiveText, "Dash dot (.5x) _._._._._._._._._._._._._._._.");
	ltype.ElementsNumber = 4;//73
	ltype.PatternLength = 0.5;//40
	ltype.Elements[0] = 0.25;//49
	ltype.Elements[1] = -0.125;
	ltype.Elements[2] = 0.0;
	ltype.Elements[3] = -0.125;
	return drawingSave.AddLinetype(&ltype);

}

//*****************************************************************
static void add_layer(LPCTSTR lpstr_layerName,OBJHANDLE ltypeObjHandle,int iColorID,CDrawing& drawingSave)
{
	LAYER	layer;
	// Layer1
	ZeroMemory(&layer, sizeof(layer));
	strcpy(layer.Name, lpstr_layerName);
	layer.Color = iColorID;
	layer.LineTypeObjhandle = ltypeObjHandle; // Continuous
	drawingSave.AddLayer(&layer);	
}
static void add_lock_layer(LPCTSTR lpstr_layerName,OBJHANDLE ltypeObjHandle,int iColorID,CDrawing& drawingSave)
{
	//70=4时是锁定
	LAYER	layer;
	// Layer1
	ZeroMemory(&layer, sizeof(layer));
	strcpy(layer.Name, lpstr_layerName);
	layer.Color = iColorID;
	layer.LineTypeObjhandle = ltypeObjHandle; // Continuous
	layer.StandardFlags = '4';
	drawingSave.AddLayer(&layer);	
}
//********************************************************
//句柄临时不保存，但注意用到时如何保存处理
static OBJHANDLE add_txtstyle(dlhml::Text_Style *sty,CDrawing& drawingSave)
{
	//  STYLE table type -------------------------
	STYLE	style;
	ZeroMemory(&style, sizeof(style));
	strcpy(style.Name, sty->na);
	style.StandardFlags = sty->StandardFlags;
	style.TextGenerationFlags = sty->TextGenerationFlags;
	strcpy(style.PrimaryFontFilename, sty->PrimaryFontFilename);
	style.ObliqueAngle = sty->ObliqueAngle;
	style.FixedTextHeight = sty->FixedTextHeight;
	style.WidthFactor = sty->WidthFactor;
	style.LastHeightUsed = sty->LastHeightUsed;
	if(strcmp(style.Name,"") == 0){
		assert("add_txtstyle name = """);
		return 0;
	}
	OBJHANDLE obj;
	obj = drawingSave.AddTextStyle(&style);
	style.Objhandle = obj;
	return obj;
}
static void add_ltype(dlhml::Line_Type *v,CDrawing& drawingSave)
{
	if(strcmp(v->Name," ")==0 || strcmp(v->Name,"")==0)
		return ;
	LTYPE ltype;
	ZeroMemory(&ltype, sizeof(ltype));
	strcpy(ltype.Name, v->Name);
	strcpy(ltype.DescriptiveText, v->DescriptiveText);
	ltype.ElementsNumber = v->ElementsNumber;
	ltype.PatternLength = v->PatternLength;
	
	memcpy(ltype.Elements, v->Elements, sizeof(double)*30);			// Line Elements (Max=30)
	drawingSave.AddLinetype(&ltype);
}
static OBJHANDLE add_txtstyle_standard(CDrawing& drawingSave)
{
	//  STYLE table type -------------------------
	STYLE	style;
	ZeroMemory(&style, sizeof(style));
	strcpy(style.Name, txt_style_name);
	style.StandardFlags = 1;
	style.TextGenerationFlags = 1;
	strcpy(style.PrimaryFontFilename, "MS Mincho");
	style.ObliqueAngle = 0.0;
	style.FixedTextHeight = 0;
	style.WidthFactor = 1.0;
	style.LastHeightUsed = 0;
	if(strcmp(style.Name,"") == 0){
		assert("add_txtstyle name = """);
		return 0;
	}
	OBJHANDLE obj;
	obj = drawingSave.AddTextStyle(&style);
	style.Objhandle = obj;
	return obj;
}

static void init_setting(CDrawing& drawing,Database& db)
{
	//线形
	OBJHANDLE solid_objHand = add_lineType_solid(drawing);
	OBJHANDLE hidden_objHand = add_lineType_hidden(drawing);
	OBJHANDLE center_objHand = add_lineType_center(drawing);

	dlhml::ltype_iterator iter_lt = db.lstyle_begin();
	while (iter_lt != db.lstyle_end()){
		add_ltype(*iter_lt,drawing);
		iter_lt++;
		
	}


	//OBJHANDLE DASHDOT2_objHand = add_lineType_DASHDOT2(drawing);
	//层
	add_layer("APDXF", solid_objHand, 7, drawing);
  add_layer("solid", solid_objHand, 7, drawing);
	add_layer("hidden", hidden_objHand, 7, drawing);
	add_layer("center", center_objHand, 7, drawing);
	//1红色，2黄色，3绿色，4：水色，5蓝色，6品红，7白色，
// 	add_layer(layer_white_hidden.c_str(),hidden_objHand,7,drawing);
// 	add_layer("white_center",center_objHand,7,drawing);
// 	add_layer("white_solid" ,solid_objHand ,7,drawing);
// 	add_layer("yellow_solid",solid_objHand ,2,drawing);
// 	add_layer("shuise_solid",solid_objHand ,4,drawing);
// 	add_layer("green_solid" ,solid_objHand ,3,drawing);
	//设置锁定层
// 	add_lock_layer(g_lock_layer_name.c_str(),solid_objHand,7,drawing);
	//文本样式
	add_txtstyle_standard(drawing);
/*
	dlhml::txt_style_iterator iter = db.text_style_begin();
	while (iter != db.text_style_end()){
		add_txtstyle(*iter,drawing);
		iter++;
		
	}
*/

}

//0 ==== leftbottom
//1 ==== leftcenter
//2 ==== rightbottom
//3 ==== 
//4 ==== center
static int get_text_Attachment_style(dlhml::Text::AlignPt style)
{
  return TJ_LEFT;
// #define	TJ_BOTTOMLEFT	0x0100
// #define	TJ_BOTTOMCENTER	0x0101
// #define	TJ_BOTTOMRIGHT	0x0102
// #define	TJ_MIDDLELEFT	0x0200
// #define	TJ_MIDDLECENTER	0x0201
// #define	TJ_MIDDLERIGHT	0x0202
// #define	TJ_TOPLEFT		0x0300
// #define	TJ_TOPCENTER	0x0301
// #define	TJ_TOPRIGHT		0x0302

// 	int iAttach = 0;
// 	if(style  == dlhml::Text::center_center)
// 		iAttach = 4;
// 	else if(style  == dlhml::Text::left_bottom)
// 		iAttach = 0;
// 	else if(style  == dlhml::Text::left_center)
// 		iAttach = 1;
// 	else if(style  == dlhml::Text::right_bottom)
// 		iAttach = 2;
// 	else
// 		iAttach = 4;
// 
// 	return iAttach;

  int justification = 0;
  switch(style){
  case dlhml::Text::left_top :
    justification = TJ_TOPLEFT;
    break;
  case dlhml::Text::center_top:
    justification = TJ_TOPCENTER;
    break;
  case dlhml::Text::right_top:
    justification = TJ_TOPRIGHT;
    break;
  case dlhml::Text::left_center:
    justification = TJ_MIDDLELEFT;
    break;
  case dlhml::Text::center_center:
    justification = TJ_MIDDLECENTER;
    break;
  case dlhml::Text::right_center:
    justification = TJ_MIDDLERIGHT;
    break;
  case dlhml::Text::left_bottom:
    justification = TJ_BOTTOMLEFT;
    break;
  case dlhml::Text::center_bottom:
    justification = TJ_BOTTOMCENTER;
    break;
  case dlhml::Text::right_bottom:
    justification = TJ_BOTTOMRIGHT;
    break;
  }
  //justification = (int)(style)-1;
  justification = TJ_FIT;
  return justification;

}

//*****************************************************************
//

//*****************************************************************
static LPCTSTR dxf_line_type(LPCTSTR obj_line_type)
{
  if(strcmp(obj_line_type, dlhml::lt_continue()) == 0){
    return "Continuous";
  }
  if(strcmp(obj_line_type, dlhml::lt_dot()) == 0){
    return "HIDDEN";
  }
  if(strcmp(obj_line_type, dlhml::lt_center()) == 0){
    return "CENTER";
  }
  return "Continuous";
}

//*****************************************************************
static void save_attribute(CDrawing& dwg, Entity * e)
{
  assert(e);
  if(!e){
    return;
  }
  if(strcmp(e->group().c_str(),"HiddenFrame") == 0){
    return;
  }
  
  short itcolor = e->color_index();

	//处理线性
  dwg.SetLineType(e->line_style().c_str());
//  LPCTSTR itlt = dxf_line_type(e->line_style());
//  dwg.SetLineType(itlt);
  dwg.SetColor(itcolor);
  dwg.SetLayer("APDXF");
	

}

static void save_line(CDrawing& dwg, Line * ln)
{
  assert(ln);
  save_attribute(dwg, ln);
	dwg.Line(ln->start().x,ln->start().y,ln->end().x,ln->end().y);
}

static void save_circle(CDrawing& dwg, Circle * circle)
{
  assert(circle);
  save_attribute(dwg, circle);
  dwg.Circle(circle->center().x,circle->center().y,circle->radius());
}

static void save_arc(CDrawing& dwg, RArc * arc)
{
  assert(arc);
  save_attribute(dwg, arc);
  dwg.Arc(arc->center().x,arc->center().y,arc->radius(),arc->start_degree2d(),arc->end_degree2d());
}

static void save_text(CDrawing& dwg, Text * txt)
{
  save_attribute(dwg, txt);
//	dwg.SetTextStyle(txt->style_name());
	dwg.SetTextStyle(txt_style_name);

  int iAttach = get_text_Attachment_style(txt->align_point());
  
//   std::vector<dlhml::Point> box;
//   txt->real_txt_pt(box);
  Line ln = txt->dxf_base_line();
  
  dwg.Text(txt->text().c_str(),
    ln.start().x,
    ln.start().y,
    ln.end().x,
    ln.end().y,
    txt->dxf_height(),
    iAttach,
    txt->rotation_degree(),
    txt->width_factor());
}


// static void save_line(CDrawing& dwg, Line * ln)
// {
// 	if(!ln){
// 		return;
// 	}
//   if(strcmp(ln->group(),"HiddenFrame")== 0){
// 		return;
//   }
// 
// 	dwg.SetColor(ln->color_index());
// 	////此时层不是一般概念上的层，它是颜色和线性的标示
// 	string group = get_layer_name(ln->color_index(),ln->line_style());
// 	dwg.SetLayer(group.c_str());  
// 
// 	if(strcmp(ln->line_style(),"dot") == 0)
// 		dwg.SetLineType("HIDDEN");
// 	else if(strcmp(ln->line_style(),"center") == 0)
// 		dwg.SetLineType("CENTER");
// 	else
// 		dwg.SetLineType("Continuous");
// 
//   
// 
// 	set_lock_layer_name();  
// 
// 	dwg.Line(ln->start().x,ln->start().y,ln->end().x,ln->end().y);
// }

// static void save_circle(CDrawing& dwg, Circle * circle)
// {
//   if(!circle){
//     return;
//   }
//   
//   if(strcmp(circle->group(),"HiddenFrame")== 0)
//     return;
//   
//   dwg.SetColor(circle->color_index());
//   //此时层不是一般概念上的层，它是颜色和线性的标示
//   string group = get_layer_name(circle->color_index(),circle->line_style());
//   dwg.SetLayer(group.c_str());  
//   if(strcmp(circle->line_style(),"dot") == 0)
//     dwg.SetLineType("HIDDEN");
//   else if(strcmp(circle->line_style(),"center") == 0)
//     dwg.SetLineType("CENTER");
//   else
//     dwg.SetLineType("Continuous");
//   
//   set_ltype_color(dwg, circle->layer_name());
//   
//   dwg.Circle(circle->center().x,circle->center().y,circle->radius());
//   
// }


// static void save_arc(CDrawing& dwg, RArc * arc)
// {
// 	if(!arc){
// 		return;
// 	}
// 	if(strcmp(arc->group(),"HiddenFrame")== 0)
// 		return;
// 
// 	dwg.SetColor(arc->color_index());
// 	//此时层不是一般概念上的层，它是颜色和线性的标示
// 	string group = get_layer_name(arc->color_index(),arc->line_style());
// 	dwg.SetLayer(group.c_str());  	
// if(strcmp(arc->line_style(),"dot") == 0)
// 		dwg.SetLineType("HIDDEN");
// 	else if(strcmp(arc->line_style(),"center") == 0)
// 		dwg.SetLineType("CENTER");
// 	else
// 		dwg.SetLineType("Continuous");
// 
// 
// 	dwg.Arc(arc->center().x,arc->center().y,arc->radius(),arc->start_degree(),arc->end_degree());
// 
// }
// static void save_text(CDrawing& dwg, Text * txt)
// {
// 	if(!txt){
// 		return;
// 	}
// 	if(strcmp(txt->group(),"HiddenFrame")== 0)
// 		return;
// 
// 	//颜色
// 	dwg.SetColor(txt->color_index());
// 	dwg.SetLayer(txt->layer_name());  
// 	dwg.SetTextStyle("CustomStyle1");
// 	int iAttach = get_text_Attachment_style(txt->align_point());
// 	//防止文字太大，固定比例缩小，以后文字要用右上的对齐方法
// // 	float hight = txt->height();
// // 	txt->height(hight/2.0);//先缩小
// // 	dlhml::Rect rect = txt->box2d();
// 
//   std::vector<dlhml::Point> box;
//   txt->real_box_point(box);
// 
// 
//   dwg.Text(txt->text(),
//            box[0].x,
//            box[0].y,
//            box[3].x,
//            box[3].y,
//            txt->height(),
//            iAttach,
//            txt->rotation_degree(),
//            0);
// 
// // 	if(txt->align_point() == dlhml::Text::center_center){
// // 		dwg.Text(txt->text(),
// //       txt->position().x,
// //       txt->position().y,
// // 			txt->position().x,
// //       txt->position().y,
// // 			txt->height(),
// //       iAttach,
// //       0,
// //       0);
// // 	}else{
// // 		dwg.Text(txt->text(),
// //       txt->position().x,
// //       txt->position().y,
// // 			txt->position().x+rect.width(),
// //       txt->position().y,
// // 			txt->height(),
// //       iAttach,
// //       0,
// //       0);
// // 	}
// }

//*****************************************************************
static void get_basic(Database& db, vector<Entity*>& basic)
{
	dlhml::entity_iterator it= db.entity_begin();
	for(; it != db.entity_end(); ++it){
		if(!(*it)){
			continue;
		}
		(*it)->get_show(basic);
	}
}

static void save_entity(CDrawing& drawingSave, Entity* e)
{
	if(!e){
		return;
	}
	////Line,Circle,Arc,Text
	if(e->isa(MY_RUNTIME_CLASS(Line))){
		Line * ln = static_cast<Line*>(e);
		save_line(drawingSave, ln);
	}
	else if(e->isa(MY_RUNTIME_CLASS(Circle))){
		Circle * cir = static_cast<Circle*>(e);
		save_circle(drawingSave, cir);
	}
	else if(e->isa(MY_RUNTIME_CLASS(RArc))){
		RArc * arc = static_cast<RArc*>(e);
		save_arc(drawingSave, arc);
	}
	else if(e->isa(MY_RUNTIME_CLASS(Text))){
		Text * txt = static_cast<Text*>(e);
		save_text(drawingSave, txt);
	}
}

static void save_entities(CDrawing& drawingSave, vector<Entity*>& es)
{
	int i = 0;
	for(i=0; i<es.size(); ++i){
		save_entity(drawingSave, es[i]);
	}
}

static void save_db(CDrawing& drawingSave, Database& db)
{
	vector<Entity*> basic;
	get_basic(db, basic);
	save_entities(drawingSave, basic);
	dlhml::destory(basic);
}

bool output_dxf(string file,Database& db)
{
	CDrawing dwg;
	if(!dwg.Create())	{
    ::MessageBox(NULL, "Fatal error on creating CDrawing!", "DXF", MB_OK);
		return false;		
	}
	init_setting(dwg,db);
	////遍历输出
	save_db(dwg, db);

	if(!dwg.SaveDXFFile(file.c_str())){
		return false;
	}

	return true;
}


}//namespace

