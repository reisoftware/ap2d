// Replace_String.cpp: implementation of the Replace_String class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Replace_String.h"

#include "DB_View.h"
#include "Mgr_Database.h"
#include "Draw_Entities.h"
#include "str_tools.h"
#include "Draw_Entities.h"
#include "Draw_Entities.h"
#include "Text.h"
#include "Entity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Replace_String::Replace_String()
{

}

Replace_String::~Replace_String()
{

}
//**new*******************************************************************************
void Replace_String::draw_circle(dlhml::Text *t)
{
	dlhml::Rect rect = t->box2d();
	dlhml::Point center((rect.xmax()+rect.xmin())/2.0f,(rect.ymax()+rect.ymin())/2.0f);
	Draw_Entities draw;

	float r = t->dxf_height()/2.0f + t->dxf_height()/6.0f;
	draw.draw_circle(center,t->color_index(),r);

}
void Replace_String::draw_rect(dlhml::Text *t)
{
	dlhml::Rect rect = t->box2d();	
	Draw_Entities draw;
	draw.draw_rect(rect,t->color_index());

}
void Replace_String::draw_frame_style(dlhml::Text *t,CString style)
{
	if(style == "Circle"){
		draw_circle(t);
	}else if(style == "Rect"){
		draw_rect(t);
	}else if(strcmp(style,"Hide")==0){

	}else{
		AfxMessageBox("The replace stirng's style isn't deal.please check it.");
	}

	
}
void Replace_String::replace_text(dlhml::Text *t,CString style,CString sign)
{
	t->text(sign.GetBuffer(0));
	//此处不能缩小文字，可以考虑增大外框，2018-11-9
	t->dxf_height(t->dxf_height());//缩小一下文字
	t->re_calc_box2d();
	//绘制外形
	draw_frame_style(t,style);
}
void Replace_String::add_postfix(dlhml::Text *t,CString right,CString postfix)
{
	dlhml::Text *post_t = (dlhml::Text *)t->clone();
	dlhml::Rect rect = t->box2d();	
	double t_width = rect.width();
	post_t->position(dlhml::Point(post_t->position().x + t_width,post_t->position().y));
	CString str = " " + postfix + " " + right;
	post_t->text(str.GetBuffer(0));
	dlhml::Entity_ID id;
	post_t->post2db(*DB_View::instance()->database(),id);			

}

//SS400
void Replace_String::deal_equal(dlhml::Text *t,CString style,CString sign,CString postfix)
{
	//代替SS400
	replace_text(t,style,sign);
	//相等的字符串right="",所以直接复制即可。
	add_postfix(t,"",postfix);
}
//SS400 H100*199*8*10
void Replace_String::deal_head(CString right,CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix)
{
	//代替SS400
	replace_text(t,style,sign);
	//在t后跟设置的后缀字符串，注意属性利用t的属性，新生成Text，把后缀文字和原来剩余的文字文字相连即可
	add_postfix(t,right,postfix);
	//在t后跟设置的后缀字符串
}
//H100*199*8*10 SS400
void Replace_String::deal_tail(CString left,CString right,CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix)
{
	//改左侧的值
	t->text(left.GetBuffer(0));
	//生成t旁边的，位置变化单独的一个Text = “SS400”
	dlhml::Text *rep_t = (dlhml::Text *)t->clone();
	dlhml::Rect rect = t->box2d();	
	double t_width = rect.width();
	rep_t->position(dlhml::Point(rep_t->position().x + t_width,rep_t->position().y));
	CString merge_str = rep_str + " " +right;
	rep_t->text(merge_str.GetBuffer(0));
	dlhml::Entity_ID id;
	rep_t->post2db(*DB_View::instance()->database(),id);			
	//调用deal_head当做此种格式的字符串处理即可。

	deal_head(right,rep_str,rep_t,style,sign,postfix);

}

void Replace_String::deal_include(CString rep_str,dlhml::Text *t,CString style,CString sign,CString postfix)
{
	//处理包含
	CString val = t->text().c_str();

	CString left = val.Left(val.Find(rep_str));
	CString right = val.Right(val.GetLength() - val.Find(rep_str) - rep_str.GetLength());
	
	if(left !=""){
		//H100*100*8*19 SS400 IFC
		deal_tail(left,right,rep_str,t,style,sign,postfix);

	}else{
		//SS400  H100*100*8*19
		deal_head(right,rep_str,t,style,sign,postfix);
	}


}

void Replace_String::rep_text(CString rep_str,dlhml::Text *t ,CString style,CString sign,CString postfix)
{
	if(strcmp(t->text().c_str(),rep_str.GetBuffer(0)) == 0){
		//处理相等的字符串
		deal_equal(t,style,sign,postfix);
	}else{
		//处理包含的字符串
		deal_include(rep_str,t,style,sign,postfix);
	}
}

void Replace_String::rep_strings(CString rep_str,Entitys &texts,CString style,CString sign,CString postfix)
{
	for(int i=0;i<texts.size();i++){
		dlhml::Text *t = (dlhml::Text*)(texts[i]);		
		rep_text(rep_str,t ,style,sign,postfix);
	}
}

void Replace_String::replace(CString rep_str,CString style,CString sign,CString postfix)
{
	Entitys sel_ents,sel_texts,texts,sons;
	get_select_ents(DB_View::instance()->database(),sel_ents);	
	//暂时处理Text对象
	get_texts(DB_View::instance()->database(),sel_ents,sel_texts);
	if(sel_texts.size()>0){
		//有选中时
		get_texts_include_str(rep_str,sel_texts,texts);
		rep_strings(rep_str,texts,style,sign,postfix);		
	}else{
		//无选中时针对于全部字符串
		Entitys all_ents,all_texts,all_sons;
		get_ents(DB_View::instance()->database(),all_ents);	
		get_texts(DB_View::instance()->database(),all_ents,all_texts);
		get_texts_include_str(rep_str,all_texts,texts);
		
		if(texts.size()>0){
			rep_strings(rep_str,texts,style,sign,postfix);		
		}
	}

	DB_View::instance()->cur_view()->scene()->invalidate();

}




