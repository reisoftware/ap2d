
#ifndef _TIAN_OBJECT_LINE_TYPE_H_
#define _TIAN_OBJECT_LINE_TYPE_H_

#include "export.h" 
#include <vector> 
#include "iolua.h"
#include "../afc/counter.h"

#pragma warning (disable:4786) 

// class iLua_File;
// class oLua_File;
namespace dlhml{ 
  
OBJECT_API LPCTSTR lt_continue();
OBJECT_API LPCTSTR lt_dot();
OBJECT_API LPCTSTR lt_center();
  
class OBJECT_API Line_Type  
{
public:
  Line_Type();
  Line_Type(const Line_Type& rhs);
  Line_Type& operator =(const Line_Type& rhs);
  virtual ~Line_Type();
  
  static Line_Type* create_me();
  bool	close();

	void save_lua(std::ofstream &out,char *name,int tab_num);
  void open_lua(lua_State *l,char *name) ;
  void			name(LPCTSTR n)				{string_copy(name_,n);}
  LPCTSTR		name() const					{return name_;}
  
  void set_style(DWORD* style,int num);
  HPEN get_pen(COLORREF col, bool sel) const;
  HPEN get_pen(DWORD* style,int num,COLORREF col)const;
  
	char	Name[MAX_DXF_LEN];		// Line Type Name
	char	StandardFlags;			// Standard flags
	char	DescriptiveText[MAX_DXF_LEN];	// Descriptive Text
	short	ElementsNumber;			// Line Elements Number
	double	Elements[LINE_ELEM_MAX_NUM];			// Line Elements (Max=30)
	double	PatternLength;          // Length of linetype pattern
private:
  LPTSTR name_;
#pragma warning(push)
#pragma warning(disable:4251)
  std::vector<DWORD> style_;
#pragma warning(pop)
  
  static void* operator new(size_t size){
    return ::operator new(size);
  }
  static void operator delete(void* ptr){
    ::operator delete(ptr);
  }

	//zhong 10-9-6



	
	private:
		MCT_DEF
};


}//namespace
#endif//FILE
