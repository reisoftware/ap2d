// Lead_Dimension_Info.h: interface for the Lead_Dimension_Info class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_LEAD_DIMENSION_H__E0CB89BA_984C_4D8E_9972_407981C69B43__INCLUDED_
#define AFX_LEAD_DIMENSION_H__E0CB89BA_984C_4D8E_9972_407981C69B43__INCLUDED_

#include "Dimension.h"
#include "Rect.h"

namespace dlhml{
class Line;


class OBJECT_API Text_Rep_Obj  
{
public:
	Text_Rep_Obj(){;}
	virtual ~Text_Rep_Obj(){;}
	
	std::string rep_str_;
	std::string style_;
	std::string sign_;
	std::string postfix_;

};


class OBJECT_API Lead_Dimension_Info : public Dimension
{
	MY_DECLARE_DYNCREATE(Lead_Dimension_Info)
public:
	Lead_Dimension_Info();
	Lead_Dimension_Info(const Lead_Dimension_Info& rhs);
	Lead_Dimension_Info& operator=(const Lead_Dimension_Info& rhs);
	virtual ~Lead_Dimension_Info();

public:

public:
	void setdata(const Point& st,const Point& ed);

	void  start(const Point& st);
	Point start()const;
	void  end(const Point& ed);
	Point end()const;

public:
	void lead(bool b){lead_ = b;}
	bool lead() const{return lead_;}

	//设置文本的替换信息
	void set_replace_db(const std::vector<Text_Rep_Obj> &rep_db){rep_db_ = rep_db;}


public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;


	void get_str_sub(char *name);
	void set_from_str_sub(char *name);

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

public:
	bool visit(Visitor& v);

	void set_dim_content(const std::vector<std::string> &names){names_ = names;}

private:
	Point start_;
	//end点利用基类的text_position_代替
	bool lead_;

	std::vector<std::string> names_;

	mutable  double  text_max_len_;

private:
	//不需要保存的信息
	std::vector<Text_Rep_Obj> rep_db_;;
private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void loadme(File& in);
	void saveme(const File& out) const;

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

	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;


	void draw_names(std::vector<Entity*>& es)const;
private:
	//2016-5-17改变lead的画法
	double get_txt_max_width(std::vector<Entity*>& es)const;
	//进行替换
	void rep_text(Text *t,std::vector<Entity*>& es)const ;

	
	int check_null_replace(std::string name)const;

};
  

}//namespace
#endif//FILE


