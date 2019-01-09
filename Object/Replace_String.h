// Replace_String.h: interface for the Replace_String class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_)
#define AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <vector>

namespace dlhml
{

class Text;
class Entity;

class Replace_String  
{
public:
	Replace_String();
	virtual ~Replace_String();


	double rep_text(std::string rep_str,Text *t ,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es);

	//½Ó¿Ú
	void replace_text(Text *t,std::string style,std::string sign,std::vector<Entity*>& es);
private:
	void deal_equal(Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es);
	void deal_include(std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es);


	void deal_head(std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es);
	void deal_tail(std::string left,std::string right,std::string rep_str,Text *t,std::string style,std::string sign,std::string postfix,std::vector<Entity*>& es);

	void deal_null_sign(Text *t,std::string right,std::string postfix,std::vector<Entity*>& es);

private:
	void add_postfix(Text *t,std::string right,std::string postfix,std::vector<Entity*>& es);
	double draw_frame_style(Text *t,std::string style,std::vector<Entity*>& es);
	double draw_circle(Text *t,std::vector<Entity*>& es);
	double draw_rect(Text *t,std::vector<Entity*>& es);

private:
	double row_len_;
	void set_max_txt_len(double len);

};

}

#endif // !defined(AFX_REPLACE_STRING_H__005FFC7A_E123_4C77_8500_EDBAAE3420C2__INCLUDED_)
