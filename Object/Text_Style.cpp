// Text_Style.cpp: implementation of the Text_Style class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Text_Style.h"
#include <TCHAR.H>
#include "Text.h"
#include "iolua.h"
#include "getrace.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{

Text_Style::Text_Style()
MCT_INIT1("Text_Style")
{
	strcpy(na,"");
	strcpy(PrimaryFontFilename,"");
	strcpy(BigFontFilename,"");
}
Text_Style::Text_Style(const Text_Style& rhs)
MCT_INIT1("Text_Style")
{
	name_ = rhs.name_;
	memcpy(&lf_, &rhs.lf_, sizeof(LOGFONT));

	//
	strcpy(na,rhs.na);
	StandardFlags = rhs.StandardFlags;
	TextGenerationFlags = rhs.TextGenerationFlags;
	strcpy(PrimaryFontFilename,rhs.PrimaryFontFilename);
	strcpy(BigFontFilename,rhs.BigFontFilename);
	ObliqueAngle = rhs.ObliqueAngle;
	FixedTextHeight = rhs.FixedTextHeight;
	WidthFactor = rhs.WidthFactor;
	LastHeightUsed = rhs.LastHeightUsed;

}
Text_Style& Text_Style::operator =(const Text_Style& rhs)
{
	if(this == &rhs)
		return *this;
	name_ = rhs.name_;
	memcpy(&lf_, &rhs.lf_, sizeof(LOGFONT));

	strcpy(na,rhs.na);
	StandardFlags = rhs.StandardFlags;
	TextGenerationFlags = rhs.TextGenerationFlags;
	strcpy(PrimaryFontFilename,rhs.PrimaryFontFilename);
	strcpy(BigFontFilename,rhs.BigFontFilename);
	ObliqueAngle = rhs.ObliqueAngle;
	FixedTextHeight = rhs.FixedTextHeight;
	WidthFactor = rhs.WidthFactor;
	LastHeightUsed = rhs.LastHeightUsed;
	//

	return *this;
}

Text_Style::~Text_Style()
{
}
Text_Style* Text_Style::create_me()
{
	return new Text_Style;
}
bool Text_Style::close()
{
	delete this;
	return true;
}

// void Text_Style::lua_load(iLua_File &fin)
// {
// 
// }
// 
// void Text_Style::lua_save(oLua_File &fout)const
// {
// 	fout.save_value("name_", name_);
// 	save_value(fout, "lf_", &lf_);
// }

HFONT Text_Style::get_null_font(const Text& text)
{
	LOGFONT lf;
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	::GetObject(hFont,sizeof(LOGFONT),&lf);
	lf.lfHeight = text.gdi_height();
	lf.lfEscapement = text.rotation()*1800/pi;
	lf.lfOrientation = lf.lfEscapement;
	return ::CreateFontIndirect(&lf);
}
HFONT Text_Style::get_font(const Text& text) const
{
	LOGFONT lf;
	memcpy(&lf, &lf_, sizeof(LOGFONT));
	//char name[] = "微软雅黑";
	std::string name = text.font();
	memset(&lf.lfFaceName,0,sizeof(lf.lfFaceName));
	memcpy(&lf.lfFaceName,name.c_str(),name.length());
	////此处使用gid_height
	lf.lfHeight = text.gdi_height();
	lf.lfWidth = text.gdi_height()*text.width_factor();
	lf.lfEscapement = text.rotation()*1800/pi;
	lf.lfOrientation = lf.lfEscapement;
	return ::CreateFontIndirect(&lf);
}
void Text_Style::save_lua(std::ofstream &out,char *name,int tab_num)
{

}
void Text_Style::open_lua(lua_State *l,char *name)
{


}








}
