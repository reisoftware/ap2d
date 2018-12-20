// Text_Dimension_Info.h: interface for the Text_Dimension_Info class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_DIMENSION_INFO_H__77378B28_F13F_49D1_8898_8CF2E8F6D917__INCLUDED_)
#define AFX_TEXT_DIMENSION_INFO_H__77378B28_F13F_49D1_8898_8CF2E8F6D917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Dimension.h"

#include "Lead_Dimension_Info.h"
namespace dlhml{


class OBJECT_API Text_Dimension_Info : public Dimension
{
	MY_DECLARE_DYNCREATE(Text_Dimension_Info)
public:
	Text_Dimension_Info();
	Text_Dimension_Info(const Text_Dimension_Info& rhs);
	Text_Dimension_Info& operator=(const Text_Dimension_Info& rhs);
	virtual ~Text_Dimension_Info();

	bool visit(Visitor& v);

	void set_dim_content(const std::vector<std::string> &names){names_ = names;}

	Color color_fact(){return color_fact_;}
	void color_fact(Color color){color_fact_=color;}
	//09.6.22
  void setctrl(const std::vector<Point>& pts);
  void getctrl(std::vector<Point>& pts) const;
  int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

public:
  virtual void get_line(std::vector<Entity*>& es)const{}
  virtual void get_show(std::vector<Entity*>& es)const;
public:
//	void dim_content(std::string dim_content);
//	std::string dim_content() const;
	void dim_sign(std::string dim_sign);
	std::string dim_sign() const;


	//设置文本的替换信息
	void set_replace_db(const std::vector<Text_Rep_Obj> &rep_db){rep_db_ = rep_db;}

private:
	Color color_fact_;
 	//09.8.26
	//LPTSTR	dim_content_;
	std::string	dim_sign_;


	std::vector<std::string> names_;

	void loadme(File& in);
	void saveme(const File& out) const;

	void save_luame(std::ofstream &out,int tab_num);
	void open_luame(lua_State *l);  
	
	void get_strme(char *out){;}
	void set_from_strme(char *in){;}

	void edit_propertyme(const Edit_Entity& edit);

	//void drawme(Draw_Entity& out) const;
	//void xor_drawme(Draw_Entity& out) const;

	errorinfo postme2db(Database& db,Entity_ID& id);

	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);

	Entity* cloneme() const;

	void closeme();

	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;

	Rect calc_box2d() const;

	//bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

	void draw_names(std::vector<Entity*>& es)const;

private:
	//不需要保存的信息
	std::vector<Text_Rep_Obj> rep_db_;;
	//**基类处理回调函数**********************************************************************************************
	void rep_text(Text *t,std::vector<Entity*>& es)const;
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_Text_Dimension_Info_INFO_H__77378B28_F13F_49D1_8898_8CF2E8F6D917__INCLUDED_)
