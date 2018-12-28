#include "StdAfx.h"
#include "Dxf_Save.h"

#include <vector>

#include "CadLib.h"
#include "Mgr_Dxfs.h"
#include "Global.h"

#include "../Object/Global.h"
#include "../Object/Entity.h"
#include "../Object/Line.h"
#include "../Object/Circle.h"
#include "../Object/Cut_Section.h"
#include "../Object/Arc_Arrow.h"

#include "DB_Font_Width_Factor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define txt_style_name  "rei"

using namespace std;

namespace dlhml{

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
static OBJHANDLE add_txtstyle(CDrawing& drawingSave)
{
	//  STYLE table type -------------------------
	STYLE	style;
	ZeroMemory(&style, sizeof(style));
//	STYLE.
	strcpy(style.Name, "Style1");
	strcpy(style.PrimaryFontFilename, "MS Mincho.TTF");
//	strcpy(style.PrimaryFontFilename, "MS Mincho.TTF");
	style.LastHeightUsed = 0.3;
	style.WidthFactor = 1;
//	strcpy(style.BigFontFilename, "MS Mincho.TTF");
//	style.FixedTextHeight =10;
//	style.StandardFlags='a';
//	style.TextGenerationFlags='a';
		
		//	style
//	style.Objhandle=drawingSave.AddTextStyle(&style);
	return drawingSave.AddTextStyle(&style);
}
//********************************************************
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
		//assert("add_txtstyle name = """);
		return 0;
	}
	OBJHANDLE obj;
	obj = drawingSave.AddTextStyle(&style);
	style.Objhandle = obj;
	return obj;
}
static void init_setting(CDrawing& drawing)
{
	//线形
	OBJHANDLE solid_objHand = add_lineType_solid(drawing);
	OBJHANDLE hidden_objHand = add_lineType_hidden(drawing);
	OBJHANDLE center_objHand = add_lineType_center(drawing);
	OBJHANDLE DASHDOT2_objHand = add_lineType_DASHDOT2(drawing);
	//层
	//1红色，2黄色，3绿色，4：水色，5蓝色，6品红，7白色，，
	add_layer(layer_white_hidden,hidden_objHand,7,drawing);
	add_layer("white_center",center_objHand,7,drawing);
	add_layer("white_solid" ,solid_objHand ,7,drawing);
	add_layer("yellow_solid",solid_objHand ,2,drawing);
	add_layer("shuise_solid",solid_objHand ,4,drawing);
	add_layer("green_solid" ,solid_objHand ,3,drawing);
	add_layer("APDXF", solid_objHand, 7, drawing);
	//设置锁定层
	add_lock_layer(g_lock_layer_name.c_str(),solid_objHand,7,drawing);
	//文本样式
//	OBJHANDLE textstyle_objHand = add_txtstyle(drawing);
	////2.21在此添加新的标注样式，保证导出时已存在需要的标注样式
	////暂时无标注
//	add_dxf_dim_style(drawing);
		//文本样式
//	add_txtstyle_standard(drawing);
}

//*****************************************************************
static string get_layer_name(int color, string typestr)
{
	LPCTSTR ltype = typestr.c_str();
	if(color == 7 && strcmp(ltype,"Continuous") == 0)
		return layer_white_solid;
	else if(color == 7 && strcmp(ltype,"dot") == 0)
		return layer_white_hidden;
	else if(color == 7 && strcmp(ltype,"center") == 0)
		return layer_white_center;
	else if(color == 2 && strcmp(ltype,"Continuous") == 0)
		return layer_yellow_solid;
	else if(color == 4 && strcmp(ltype,"Continuous") == 0)
		return layer_shuise_solid;
	else if(color == 3 && strcmp(ltype,"Continuous") == 0)
		return layer_green_solid;
	else 
		return layer_white_solid;
}
static void set_lock_layer_name()
{
	//NOOK
//	if(layer_lock_){
//		dwg->SetLayer(g_lock_layer_name);  
//	}
}

static int get_ltype_color(string layer,string& ltype)
{
	if(layer == layer_white_hidden){
		ltype = "HIDDEN";
		return 7;
	}else if(layer == layer_white_center){
		ltype = "CENTER";
		return 7;
	}else if(layer == layer_white_solid){
		ltype = "Continuous";
		return 7;
	}else if(layer == layer_yellow_solid){
		ltype = "Continuous";
		return 2;
	}else if(layer == layer_shuise_solid){
		ltype = "Continuous";
		return 4;
	}else if(layer == layer_green_solid){
		ltype = "Continuous";
		return 3;
	}else{
		ltype = "Continuous";
		return 7;

	}

}
static void set_ltype_color(CDrawing& dwg, string group)
{
	string ltype="";
	int color = get_ltype_color(group,ltype);
	dwg.SetLineType(ltype.c_str());
	dwg.SetLayer(group.c_str());  
}

//*****************************************************************
static void save_line(CDrawing& dwg, Line * ln)
{
	if(!ln){
		return;
	}
	if(strcmp(ln->group().c_str(),"HiddenFrame")== 0)
		return;

	dwg.SetColor(ln->color_index());
	//此时层不是一般概念上的层，它是颜色和线性的标示
	string group = get_layer_name(ln->color_index(),ln->line_style());
	dwg.SetLayer(group.c_str());  

	if(strcmp(ln->line_style().c_str(),"dot") == 0)
		dwg.SetLineType("HIDDEN");
	else if(strcmp(ln->line_style().c_str(),"center") == 0)
		dwg.SetLineType("CENTER");
	else
		dwg.SetLineType("Continuous");

	set_lock_layer_name();  

	dwg.Line(ln->start().x,ln->start().y,ln->end().x,ln->end().y);
}
static void save_circle(CDrawing& dwg, Circle * circle)
{
	if(!circle){
		return;
	}

	if(strcmp(circle->group().c_str(),"HiddenFrame")== 0)
		return;

	dwg.SetColor(circle->color_index());
	//此时层不是一般概念上的层，它是颜色和线性的标示
	string group = get_layer_name(circle->color_index(),circle->line_style());
	dwg.SetLayer(group.c_str());  
	if(strcmp(circle->line_style().c_str(),"dot") == 0)
		dwg.SetLineType("HIDDEN");
	else if(strcmp(circle->line_style().c_str(),"center") == 0)
		dwg.SetLineType("CENTER");
	else
		dwg.SetLineType("Continuous");

	set_ltype_color(dwg, circle->layer_name());

	set_lock_layer_name();  
	dwg.Circle(circle->center().x,circle->center().y,circle->radius());

}
static void save_arc(CDrawing& dwg, RArc * arc)
{
	if(!arc){
		return;
	}
	if(strcmp(arc->group().c_str(),"HiddenFrame")== 0)
		return;

	dwg.SetColor(arc->color_index());
	//此时层不是一般概念上的层，它是颜色和线性的标示
	string group = get_layer_name(arc->color_index(),arc->line_style());
	dwg.SetLayer(group.c_str());  	
if(strcmp(arc->line_style().c_str(),"dot") == 0)
		dwg.SetLineType("HIDDEN");
	else if(strcmp(arc->line_style().c_str(),"center") == 0)
		dwg.SetLineType("CENTER");
	else
		dwg.SetLineType("Continuous");

	set_lock_layer_name();  

	dwg.Arc(arc->center().x,arc->center().y,arc->radius(),arc->start_degree2d(),arc->end_degree2d());

}

//0 ==== leftbottom
//1 ==== leftcenter
//2 ==== rightbottom
//3 ==== 
//4 ==== center
static int get_text_Attachment_style(dlhml::Text::AlignPt style)
{
//  return TJ_LEFT;
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

static void save_text(CDrawing& dwg, Text * txt)
{
	if(!txt){
		return;
	}
	if(strcmp(txt->group().c_str(),"HiddenFrame")== 0)
		return;

	//颜色
	dwg.SetColor(txt->color_index());
	dwg.SetLayer(txt->layer_name().c_str());  
	dwg.SetTextStyle(txt->style_name().c_str());

	dwg.SetLayer("APDXF");

	double txt_width = txt->dxf_height();
	
	std::string group = txt->group();
	dlhml::Point pos ;
	pos = txt->position();
	if(strcmp(group.c_str(),"GROUP_DXF_INPUT")==0)
	{
		//处理导入的图幅文字
		txt->align_point(dlhml::Text::left_bottom);
		int iAttach = get_text_Attachment_style(txt->align_point());
		
		double height_deal = txt->dxf_height();

		//此处是文字的宽度因子
		double font_wf_scale = Global::instance()->setting().reduce_scale_export_;
		double font_wf = txt->width_factor();

/*
		//处理比例因子的问题
		CString str_wf;
		str_wf.Format("%f",txt->width_factor());
		CString wf = DB_Font_Width_Factor::instance()->find(str_wf);
		double wf_float = atof(wf);
		if(wf == "-1")
		{
			wf_float = txt->width_factor();
		}
		else
		{
			 wf_float = atof(wf);
		}

		dwg.Text(txt->text().c_str(), 
		txt->position().x,txt->position().y,
		txt->position().x,txt->position().y,
		height_deal,iAttach,txt->rotation_radian()*180/3.1415926f,wf_float);
*/
		dwg.Text(txt->text().c_str(), 
		txt->position().x,txt->position().y,
		txt->position().x,txt->position().y,
		height_deal,iAttach,txt->rotation_radian()*180/3.1415926f,font_wf) ;
	}
	else
	{
		//此处是在ap2d中添加的文字，

		//txt->align_point(dlhml::Text::center_top);
		//系统中的添加文字的，有一定的偏离，所以也计算中cad中的偏离
		//pos = offset_point(txt->position());
	/*
		Normal nor;
		radian_2_normal2d(txt->rotation_degree()+dlhml::pi/2, nor);
		double dis = 4.0;
		if(EquFloat(txt->rotation_degree(),0)){
			pos = txt->position();
			pos.y = pos.y+dis;
		
		}else{
			pos = txt->position().polarTo(dis, nor);

		}
	*/
		//处理添加的标注信息文字

		int iAttach = get_text_Attachment_style(txt->align_point());

		
	//	double height_deal = txt->dxf_height() * Global::instance()->setting().reduce_scale_export_;
		double height_deal = txt->dxf_height();

		Line ln = txt->dxf_base_line();

		dwg.Text(txt->text().c_str(), 
		ln.start().x,ln.start().y,
		ln.end().x, ln.end().y,
		height_deal,iAttach,txt->rotation_radian()*180/3.1415926f,txt->width_factor());

	}

	
}
static void save_cut_section(CDrawing& dwg, Cut_Section * v)
{
	if(!v){
		return;
	}
	if(strcmp(v->group().c_str(),"HiddenFrame")== 0)
		return;

	//颜色
	dwg.SetColor(v->color_index());
	dwg.SetLayer(v->layer_name().c_str());  
	dwg.SetTextStyle("Standard");

	//v->
//	int iAttach = get_text_Attachment_style(v->align_point());
//	//防止文字太大，固定比例缩小，以后文字要用右上的对齐方法
//	float hight = v->dxf_height();
//	txt->dxf_height(hight/2.0);//先缩小
//	dlhml::Rect rect = txt->box2d();
//
//	set_lock_layer_name();  
//
//	if(txt->align_point() == dlhml::Text::center_center){
//		dwg.Text(txt->text().c_str(),txt->position().x,txt->position().y,
//			txt->position().x,txt->position().y,
//			txt->dxf_height(),iAttach,0,0);
//	}else{
//		dwg.Text(txt->text().c_str(),txt->position().x,txt->position().y,
//			txt->position().x+rect.width(),txt->position().y,
//			txt->dxf_height(),iAttach,0,0);
//	}
}
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
static void save_arc_arrow(CDrawing& dwg, Arc_Arrow *v)
{
	Entitys lns;
	Entitys shows;
	v->get_line(lns);
	v->get_show(shows);

	

}
static void save_shows(CDrawing& dwg, Entitys &ents)
{
	for(int i=0;i<ents.size();i++){
		Entity *e = ents[i];
		if(e->isa(MY_RUNTIME_CLASS(Line))){
			Line * ln = static_cast<Line*>(e);
			save_line(dwg, ln);
		}
		else if(e->isa(MY_RUNTIME_CLASS(Circle))){
			Circle * cir = static_cast<Circle*>(e);
			save_circle(dwg, cir);
		}
		else if(e->isa(MY_RUNTIME_CLASS(RArc))){
			RArc * arc = static_cast<RArc*>(e);
			save_arc(dwg, arc);
		}
		else if(e->isa(MY_RUNTIME_CLASS(Text))){
			Text * txt = static_cast<Text*>(e);
			save_text(dwg, txt);
		}
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
	}else{
		Entitys shows;
		e->get_show(shows);
		save_shows(drawingSave,shows);
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

bool save_dxf(string file,Database& db)
{
	CDrawing dwg;
	if(!dwg.Create())	{
		AfxMessageBox("Fatal error on creating CDrawing!");
		return false;		
	}
	init_setting(dwg);
	////遍历输出
	save_db(dwg, db);

	if(!dwg.SaveDXFFile(file.c_str())){
		return false;
	}

	return true;
}


}//namespace
