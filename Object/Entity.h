// Entity.h: interface for the Entity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ENTITY_H__3AD42875_8D62_4B98_8EF9_41D12EF12C32__INCLUDED_
#define AFX_ENTITY_H__3AD42875_8D62_4B98_8EF9_41D12EF12C32__INCLUDED_


#include "Object1.h"
#include "Entity_ID.h"
#include "Rect.h"
#include "Color.h"
#include "Point.h"
#include <vector>
#include <string>

#include "../afc/counter.h"
#include "../afc/iolua.h"
#include "../afc/lua_fun.h"

// #define DLHML_ENTITY_CREATE_ME(class_name) dlhml::##class_name##::create_me()

namespace dlhml{

enum MY_CLASS {ENTITY, LINE_DIM, LINE_DIM_BLOCK, TEXT};
//enum DIM_MODE {PILEUP_DIM, CLOSED_DIM};
typedef int DIM_MODE;
const int PILEUP_DIM = 1;
const int CLOSED_DIM = 2;
//enum DIM_ROTA {ORTHO_DIM, ALIGN_DIM};
typedef int DIM_ROTA;
const int ORTHO_DIM = 1;
const int ALIGN_DIM = 2;


class File;
class Edit_Entity;
class Draw_Entity;
class Database;
class Matrix;
class Entity_Snap;
class Visitor;

class Line;
class RArc;
class Circle;
class Cloud_Line;


class OBJECT_API Entity : public Object
{
	MY_DECLARE_RUNTIME(Entity)
	static Object* createob();
public:
  friend class Database;
  friend class Database_Private;
  virtual MY_CLASS myclass()const{return ENTITY;}
protected:
	Entity();
	Entity(const Entity& rhs);
	Entity& operator=(const Entity& rhs);
public:
	virtual ~Entity();

public:
	int get_str(char *out);
	int set_from_str(char *in);
	void get_str_ent();
	void set_from_str_ent();
	void get_str_ent_sub(char *name);
	void set_from_str_ent_sub(char *name);

  void save_lua(std::ofstream &out,char *name,int tab_num);
  void open_lua(lua_State *l,char *name) ;

// 	virtual void lua_load(iLua_File &fin){;}
// 	virtual void lua_save(oLua_File &fout)const{;}
//
  void load(File& in);
  void save(const File& out) const;
  Entity* clone() const;
  void transformby(const Matrix& mat);
  
public:
  void draw(Draw_Entity& out) const;
  void xor_draw(Draw_Entity& out) const;
  bool envelop(const Rect& rect) const;
  bool intersect(const Rect& rect) const;

public:
  bool snap_endpoint(Point& pt,const Rect& rect) const;
  bool snap_center_point(Point& pt,const Rect& rect) const;
  bool snap_middle_point(Point& pt,const Rect& rect) const;
  bool snap_nearest_point(Point& pt,const Rect& rect) const;
  bool snap_perpendicular_point(Point& pt,const Rect& rect,const Point& o) const;
  bool snap_intersect_point(Point& pt,const Entity& ent,const Rect& rect) const;
  bool snap_intersect_point_imp(Point& pt,const Entity_Snap& snap,const Rect& rect) const;
  
public:
  bool close();
  errorinfo post2db(Database& db,Entity_ID& id);
 
public:
  void edit_property(const Edit_Entity& edit);
  void drag_start(const Matrix& mat);
  void drag_end(const Matrix& mat);
  
protected:
  //  子类各自实现
  virtual void loadme(File& in) = 0;
  virtual void saveme(const File& out) const = 0;
  virtual Entity* cloneme() const = 0;
  virtual void transformbyme(const Matrix& mat) = 0;

	
  virtual void save_luame(std::ofstream &out,int tab_num);
  virtual void open_luame(lua_State *l);

	virtual void get_strme(char *out);
	virtual void set_from_strme(char *in);
protected:
  //  basic子类各自实现，Complex子类统一实现
  virtual void drawme(Draw_Entity& out) const = 0;
  virtual void xor_drawme(Draw_Entity& out) const = 0;
  virtual bool envelopme(const Rect& rect) const = 0;
  virtual bool intersectme(const Rect& rect) const = 0;
  virtual	Rect calc_box2d() const = 0;
  
protected:
  virtual bool snap_endpointme(Point& pt,const Rect& rect) const;
  virtual bool snap_center_pointme(Point& pt,const Rect& rect) const;
  virtual bool snap_middle_pointme(Point& pt,const Rect& rect) const;
  virtual bool snap_nearest_pointme(Point& pt,const Rect& rect) const;
  virtual bool snap_perpendicular_pointme(Point& pt,const Rect& rect,const Point& o) const;
  virtual bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
  virtual bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const = 0;
  
protected:
  //  待定
  virtual void closeme() = 0;
  virtual errorinfo postme2db(Database& db,Entity_ID& id) = 0;
  
protected:
  //  放弃
  virtual void edit_propertyme(const Edit_Entity& edit) = 0;
  virtual void drag_startme(const Matrix& mat) = 0;
  virtual void drag_endme(const Matrix& mat) = 0;


////////////////////  <<<  intersect  >>>  ////////////////////
public:
  void intersect(const Entity& e , std::vector<Point>& pts)const{intersectme(e ,pts);}
  void intersect(const Line  & ln, std::vector<Point>& pts)const{intersectme(ln,pts);}
  void intersect(const RArc  & ac, std::vector<Point>& pts)const{intersectme(ac,pts);}
  void intersect(const Circle& cr, std::vector<Point>& pts)const{intersectme(cr,pts);}

protected:
  virtual void intersectme(const Entity& e , std::vector<Point>& pts)const;
  virtual void intersectme(const Line  & ln, std::vector<Point>& pts)const;
  virtual void intersectme(const RArc  & ac, std::vector<Point>& pts)const;
  virtual void intersectme(const Circle& cr, std::vector<Point>& pts)const;

////////////////////  <<<  len and area(min inner rect)  >>>  ////////////////////
public:
  Float length()const{return length_p();}
  Float length(const Normal& nor)const;
  Float area_min_rect()const{return area_min_rect_p();}
  Float area_min_rect(const Normal& nor)const;

protected:
  virtual Float length_p()const{return -1;}
  virtual Float length_p(const Normal& nor)const{return -1;}
  virtual Float area_min_rect_p()const{return -1;}
  virtual Float area_min_rect_p(const Normal& nor)const{return -1;}

////////////////////  <<<    >>>  ////////////////////
public:
  Point polarTo(Float len, bool orderway=true)const{return polarTo_p(len,orderway);}
  void get_ptr(std::vector<Entity*>& ptrs){get_ptr_p(ptrs);}

protected:
  virtual Point polarTo_p(Float len, bool orderway=true)const{return Point(0,0,0);}
  virtual void get_ptr_p(std::vector<Entity*>& ptrs){ptrs.push_back(this);}

////////////////////  <<<    >>>  ////////////////////
public:
  void strech(const Matrix& mat); 

  virtual void moveto(const Point& pt);
  virtual void extend(const Line& ln){}
  virtual void trim  (const Line& ln){}
  //  打断当前实体，打断后的结果加入到os数组（无论是否打断成功都要clone后加入）
  virtual void split (const Line& ln, std::vector<Entity*>& os)const{os.push_back(clone());}
  virtual void split (int num, Float dis, std::vector<Entity*>& os)const{os.push_back(clone());}

public:
  virtual void  focus(Point pt){}
  virtual Point focus()   const{return Point(0,0,0);}

  void re_calc_box2d();//  强制重算box
  bool intersect_box2d(const Rect& rect) const;

public: 
	virtual void line_style(std::string style)	{	linestyle_ = style;}
	virtual std::string line_style() const			{	return linestyle_;}
	virtual void			color(COLORREF rgb)		{	color_ = rgb;	}
	virtual COLORREF	color() const				  {	return color_.rgb();}
  virtual void	color_index(int index){	color_ = index;	}
	virtual int		color_index() const		{return color_.index();}
	void line_width(int width)			{	linewidth_ = width;	}
	int line_width() const					{	return linewidth_;}
	void layer_name(std::string pname)	{	layername_ =pname;}
	std::string layer_name() const			{	return layername_;}
	void visibility(bool visible)		{visibility_ = visible;}
	bool visibility() const					{return visibility_;}
	void group(std::string pgroup)			{	group_ = pgroup;	}
	std::string	group() const						{	return group_;}
	////实体标识id,只读属性
	Entity_ID		entity_id() const		{	return id_;	}

public: 
	static void set_database(Database* db);
	virtual bool visit(Visitor& v) = 0;

public: 
	//09.1.15
	void			hide_color(COLORREF rgb)		{	color_ = rgb;	}
	COLORREF	hide_color() const				  {	return color_.rgb();}
	void if_hide(bool hide)		{if_hide_ = hide;}
	bool if_hide() const					{return if_hide_;}

	bool is_steel(){return is_steel_;}
	void is_steel(bool is_steel){is_steel_ = is_steel;}

protected:
	bool			seled_;			    ////是否选择
	bool 			visibility_;		////是否可见
	int				linewidth_;	    ////实体线宽
	std::string		linestyle_;	    ////实体线形
	std::string 		layername_;	    ////图层名
	std::string		group_;		      ////组
	Color 		color_;		      ////实体颜色

	Entity_ID id_;			      ////实体标识id
//	Rect			box2d_;		    ////图元包围盒
	//09.1.15
	Color 		hide_color_;		////隐藏颜色
	bool			if_hide_;

	static Database* static_current_db_;

	int real_color_;
	bool is_steel_;

private:
	void init();


public:
	virtual void selected(bool select);
	virtual bool selected()const{return seled_;}

////////////////////  <<<    >>>  ////////////////////
public:
  virtual void setctrl(const std::vector<Point>& pts){}
  virtual void getctrl(std::vector<Point>& pts) const{}
  virtual int  pt_count()const{return 0;}
  ////若没有实现setdrag()，则直接调用setdat()，此时index无用
  virtual void setdrag(const std::vector<Point>& pts, int index=0){setctrl(pts);}
  virtual void getdrag(std::vector<Point>& pts) const{getctrl(pts);}
  ////专用于设置拉伸点的选中状态，暂时只有Line_Arrow,Cloud_Line支持拉伸
  virtual void setstrech(const std::vector<Point>& pts){}
  virtual void getstrech(std::vector<Point>& pts) const{}

  //2016-5-24 zb
   virtual void set_step(int step){step_ = step;}

public:
  virtual bool is_ortho(){return false;}
  
public:
  virtual void get_show(std::vector<Entity*>& es)const;

public:
  Rect box2d() const;
  //const std::vector<Entity*>& get_basic()const;

protected:
  void box_change(bool b);
//   virtual void calc_box2d_record();   //entity统一实现
//   virtual void calc_basic_record();   //basic子类统一实现,Complex子类统一实现
   //2016-5-24 zb
	int step_;
private:
  bool box_change_;
  Rect box2d_record_;
  //std::vector<Entity*> basic_record_;


public:
//   std::string myclass_;
private:
	MCT_DEF
};


//#define DLHML_ENTITY_CREATE_ME(class_name) static_cast<Entity*>(dlhml::Runtime_Class::load(class_name)->createob())

OBJECT_API Entity * create_me(LPCTSTR class_name);


}
#endif // !defined(AFX_ENTITY_H__3AD42875_8D62_4B98_8EF9_41D12EF12C32__INCLUDED_)
