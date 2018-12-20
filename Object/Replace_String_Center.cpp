// Replace_String_Center.cpp: implementation of the Replace_String_Center class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Replace_String_Center.h"

#include "Text.h"
#include "Entity.h"
#include "Circle.h"
#include "Rectentity.h"


using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace dlhml
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Replace_String_Center::Replace_String_Center()
{

}

Replace_String_Center::~Replace_String_Center()
{

}
//**new*******************************************************************************
void Replace_String_Center::draw_circle(Text *t,std::vector<Entity*>& es)
{
	Rect rect = t->box2d();
	Point center((rect.xmax()+rect.xmin())/2.0f,(rect.ymax()+rect.ymin())/2.0f);


	float r = t->dxf_height()/2.0f + t->dxf_height()/6.0f;

	dlhml::Circle *cir = dlhml::Circle::create_me();

	cir->color_index(t->color_index());
	cir->setdata(center,r);

	es.push_back(cir);



}
void Replace_String_Center::draw_rect(Text *t,std::vector<Entity*>& es)
{
	Rect rect = t->box2d();	
	Rectentity *rc = Rectentity::create_me();
	rc->color_index(t->color_index());
	rc->rect(rect);
	es.push_back(rc);

}
void Replace_String_Center::draw_frame_style(Text *t,std::string style,std::vector<Entity*>& es)
{
	if(strcmp(style.c_str(),"Circle") == 0){
		draw_circle(t,es);
	}else if(strcmp(style.c_str(), "Rect") == 0){
		draw_rect(t,es);
	}else if(strcmp(style.c_str(),"Hide")==0){

	}else{
		
	}


	
	
}
void Replace_String_Center::replace_text(Text *t,std::string style,std::string sign,std::vector<Entity*>& es)
{
	t->text(sign);
	t->dxf_height(t->dxf_height());//缩小一下文字
	t->re_calc_box2d();
	//绘制外形
	draw_frame_style(t,style,es);
}
void Replace_String_Center::add_postfix(Text *t,std::string right,std::string postfix,std::vector<Entity*>& es)
{
	Text *post_t = (Text *)t->clone();
	Rect rect = t->box2d();	
	double t_width = rect.width();
	post_t->position(Point(post_t->position().x + t_width,post_t->position().y));
	std::string str = " " + postfix + " " + right;
	//处理中心对齐的方式
	//**************************************
	if(t->align_point() == dlhml::Text::center_bottom)
	{
		post_t->align_point(dlhml::Text::left_bottom);
	}
	//处理字符串为空的情况，直接替换成“空串”
	if(strcmp(t->text().c_str(),"") == 0)
	{
		t->align_point(dlhml::Text::center_bottom);
	}
	//**************************************
	str.erase(0,str.find_first_not_of(" "));
	post_t->text(str);
	es.push_back(post_t);

}

//SS400
void Replace_String_Center::deal_equal(Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//代替SS400
	replace_text(t,style,sign,es);
	//相等的字符串right="",所以直接复制即可。
	add_postfix(t,"",postfix,es);
}
//SS400 H100*199*8*10
void Replace_String_Center::deal_head(std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//代替SS400
	replace_text(t,style,sign,es);
	//在t后跟设置的后缀字符串，注意属性利用t的属性，新生成Text，把后缀文字和原来剩余的文字文字相连即可
	add_postfix(t,right,postfix,es);
	//在t后跟设置的后缀字符串
}
//H100*199*8*10 SS400
void Replace_String_Center::deal_tail(std::string left,std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//改左侧的值
	t->text(left);
	//生成t旁边的，位置变化单独的一个Text = “SS400”
	Text *rep_t = (Text *)t->clone();
	Rect rect = t->box2d();	
	double t_width = rect.width();
	rep_t->position(Point(rep_t->position().x + t_width,rep_t->position().y));
	std::string merge_str = rep_str + " " +right;
	rep_t->text(merge_str);
	es.push_back(rep_t);
	//调用deal_head当做此种格式的字符串处理即可。

	deal_head(right,rep_str,rep_t,style,sign,postfix,es);

}

void Replace_String_Center::deal_include(std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	//处理包含
	std::string val = t->text().c_str();
	std::string left,right;

	int pos = val.find(rep_str);
	if(pos == -1)
		return;
	if(pos == 0){
		left = "";
		right = val.substr(pos+rep_str.length());
	}else{
		right = val.substr(pos+rep_str.length());
		left =val.assign(val.c_str(),pos);
	}




	
	if(left !=""){
		//H100*100*8*19 SS400 IFC
		deal_tail(left,right,rep_str,t,style,sign,postfix,es);

	}else{
		//SS400  H100*100*8*19
		deal_head(right,rep_str,t,style,sign,postfix,es);
	}


}

void Replace_String_Center::rep_text(std::string rep_str,Text *t ,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es)
{
	if(strcmp(t->text().c_str(),rep_str.c_str()) == 0){
		//处理相等的字符串
		deal_equal(t,style,sign,postfix,es);
	}else{
		//处理包含的字符串
		deal_include(rep_str,t,style,sign,postfix,es);
	}
}


}


