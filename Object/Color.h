// Color.h: interface for the Color class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_COLOR_H__0BD32C7A_296D_4673_B009_390ACFD4956C__INCLUDED_
#define AFX_COLOR_H__0BD32C7A_296D_4673_B009_390ACFD4956C__INCLUDED_

#include "export.h"
#include "color_and_index.h"
#include <fstream>
#include "../afc/iolua.h"
#include "../afc/counter.h"

// class iLua_File;
// class oLua_File;
namespace dlhml{
class File;
class OBJECT_API Color  
{
public:
	Color():color_(0x00FFFFFF)MCT_INIT2("Color"){}
	Color(const Color& rhs):color_(rhs.color_)MCT_INIT2("Color"){}
	~Color(){}

	//serialize
// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout) const;

	void save_lua(std::ofstream &out,char *name,int tab_num);
	void open_lua(lua_State *l,char *name);

	void load(File& in);
	void save(const File& out) const;

	Color& operator = (const Color& rhs){
		color_=rhs.color_;
		return *this;
	}
	void operator = (COLORREF col){
		color_ = col;
	}
	void operator = (int index){
    color_ = dlhml::index_to_colorref(index);
	}
	COLORREF rgb() const{
		return color_;
	}
	static COLORREF inverse_rgb(COLORREF col);
	COLORREF inverse_rgb() const;
	int index() const{
    return dlhml::colorref_to_index(color_);
	}

private:
	//32位，颜色值，四个8位，
	//从低到高分别为：red、green、blue颜色分量值（0-255）
	COLORREF color_;
// 	int colorref_to_index(COLORREF col) const;
// 	COLORREF index_to_colorref(int index) const;

private:
	MCT_DEF
};
}
#endif // !defined(AFX_COLOR_H__0BD32C7A_296D_4673_B009_390ACFD4956C__INCLUDED_)
