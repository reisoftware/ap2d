// Text_Style.h: interface for the Text_Style class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TEXT_STYLE_H__ADAC2B9F_3243_44F5_933F_171F23C6D360__INCLUDED_
#define AFX_TEXT_STYLE_H__ADAC2B9F_3243_44F5_933F_171F23C6D360__INCLUDED_

#include "export.h"
#include "../afc/iolua.h"
#include "../afc/counter.h"

// class iLua_File;
// class oLua_File;
namespace dlhml{
class Text;
class OBJECT_API Text_Style  
{
	static void* operator new(size_t size){
		return ::operator new(size);
	}
	static void operator delete(void* ptr){
		::operator delete(ptr);
	}
public:
	Text_Style();
	Text_Style(const Text_Style& rhs);
	Text_Style& operator =(const Text_Style& rhs);
	~Text_Style();

	static Text_Style* create_me();
	void save_lua(std::ofstream &out,char *name,int tab_num);
  void open_lua(lua_State *l,char *name) ;

	static HFONT get_null_font(const Text& text);

	bool close();

// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout)const;
	void			name(std::string n)		{name_ = n;}
	std::string		name() const					{return name_;}

	void logfont(const LOGFONT& lf)	{memcpy(&lf_, &lf, sizeof(LOGFONT));}
	LOGFONT logfont() const					{return lf_;}

	HFONT get_font(const Text& text) const;



	//zhong 10-9-6
	char na[MAX_DXF_LEN];
	std::string name_p_;
	char StandardFlags;
	char TextGenerationFlags;
	char PrimaryFontFilename[MAX_DXF_BIG];
	std::string PrimaryFontFilename_p_;
	char	BigFontFilename[MAX_DXF_BIG];	// Big font filename
	std::string BigFontFilename_p_;
	double ObliqueAngle;
	double FixedTextHeight;
	double WidthFactor;
	double LastHeightUsed;

private:
	std::string name_;
	LOGFONT lf_;



	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_TEXT_STYLE_H__ADAC2B9F_3243_44F5_933F_171F23C6D360__INCLUDED_)
