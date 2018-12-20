// Text_Dimension.h: interface for the Text_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TEXT_DIMENSION_H__A80A8A00_FC59_400D_8EBF_202F3BDE62C9__INCLUDED_
#define AFX_TEXT_DIMENSION_H__A80A8A00_FC59_400D_8EBF_202F3BDE62C9__INCLUDED_

#include "Dimension.h"

namespace dlhml{
class OBJECT_API Text_Dimension : public Dimension
{
	MY_DECLARE_DYNCREATE(Text_Dimension)
public:
	Text_Dimension();
	Text_Dimension(const Text_Dimension& rhs);
	Text_Dimension& operator=(const Text_Dimension& rhs);
	virtual ~Text_Dimension();

	bool visit(Visitor& v);

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


private:
	Color color_fact_;
 	//09.8.26
	//LPTSTR	dim_content_;
	std::string	dim_sign_;

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

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_TEXT_DIMENSION_H__A80A8A00_FC59_400D_8EBF_202F3BDE62C9__INCLUDED_)
