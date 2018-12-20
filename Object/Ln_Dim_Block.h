#ifndef TIAN_OBJECT_LN_DIM_BLOCK_H_
#define TIAN_OBJECT_LN_DIM_BLOCK_H_

#include "Entity.h"
#include <vector>

namespace dlhml{
class Normal;
class Ln_Dim;
class Dimension_Style;
class OBJECT_API Ln_Dim_Block : public Entity
{
	MY_DECLARE_DYNCREATE(Ln_Dim_Block)
public:
  virtual MY_CLASS myclass()const{return LINE_DIM_BLOCK;}
public:
	Ln_Dim_Block();
	Ln_Dim_Block(const Ln_Dim_Block& rhs);
	Ln_Dim_Block& operator=(const Ln_Dim_Block& rhs);
	virtual ~Ln_Dim_Block();

public:
  void dim_style(std::string style_name);//{}
  std::string dim_style()const;//{return NULL;}
	
  void set_dim_style(const Dimension_Style& style);
  void set_dim_style(std::string style_name);
  void get_dim_style(Dimension_Style& style)const;
  void get_dim_style(std::string& style_name)const;

  virtual void line_style(std::string style);//	{	string_copy(linestyle_,style);}
	virtual std::string line_style() const		;//	{	return linestyle_;}
	virtual void			color(COLORREF rgb)	;//	{	color_ = rgb;	}
	virtual COLORREF	color() const				;// {	return color_.rgb();}
  
  virtual void	color_index(int index);
	int				color_index() const;
	
	void  dim_line_radian(Float f);
	Float dim_line_radian()const	;
  void  dim_line_degree(Float f);
  Float dim_line_degree()const	;

	void insert(const Ln_Dim* pos,Ln_Dim* dim);
	void push_back(Ln_Dim* dim);
	void erase(Ln_Dim* dim);

	Ln_Dim* front();
  Ln_Dim* last();
	Ln_Dim* back();

	Ln_Dim* previous(const Ln_Dim* pos);
	Ln_Dim* next(const Ln_Dim* pos);
	Ln_Dim* first_same_angle() const;

public:
  Ln_Dim*& operator[](int i){return list_[i];}
  const Ln_Dim*const & operator[](int i)const{return list_[i];}

public:
	//垂线点选标注线，返回插入位置
	Ln_Dim* select_from_dimline(const Point& pt);
	//矩形选标注线，文本框，引出线，pos=1为起点标注线，pos=2为终点标注线
	Ln_Dim* select_from_dimline(int& pos,const Rect& rc);
	Ln_Dim* select_from_text(int& pos,const Rect& rc);
	Ln_Dim* select_from_extendline(int& pos,const Rect& rc);
  //点选引出线，包括引出线直线（非线段）。
	Ln_Dim* select_from_extendline(int& pos,const Point& pt);
	
  
  //精确点、矩形选起点、终点部分，pos=1为起点部分，pos=2为终点部分
	//Ln_Dim* select(int& pos,const Rect& rc);
	//确定插入位置
	Ln_Dim* get_insert_pos(const Point& pt);

  //整组移动
	void offset_dimlines(const Normal& nor,Float off);
	void offset_dimlines(const Normal& nor);
	void layout_dimlines(const Point& pos);
	void layout_base(const Point& pos);

  bool is_in_beeline_by_entendline(const Rect& rc);
  bool is_in_beeline_by_entendline(const Point& pt);

	//front true,back false
	bool front_or_back_point(const Point& pt);
	bool pt_in_block_range(const Point& pt);

	int size() const;
	void clear();

	bool visit(Visitor& v);

public:
  void ext_line_normal(Normal& nor); 

public:
  Point opt()const;
  void  opt(const Point& pt);
  Point odm()const;
  void  odm(const Point& pt);
  Point text_position()const;
  void  text_position(const Point& pt);

public:
  void recal_e_pt();

private:
  bool is_sort(Ln_Dim* dim1, Ln_Dim* dim2);

private:
  DIM_MODE dim_mode_;
	Float dim_line_radian_;
#pragma warning(push)
	#pragma warning(disable:4251)
	std::vector<Ln_Dim*> list_;
#pragma warning(pop)
private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

	void loadme(File& in);
	void saveme(const File& out) const;

	void edit_propertyme(const Edit_Entity& edit);

	void drawme(Draw_Entity& out) const;
	void xor_drawme(Draw_Entity& out) const;

	errorinfo postme2db(Database& db,Entity_ID& id);

	void transformbyme(const Matrix& mat);
	void drag_startme(const Matrix& mat);
	void drag_endme(const Matrix& mat);

	Entity* cloneme() const;

	void closeme();

	bool intersectme(const Rect& rect) const;
	bool envelopme(const Rect& rect) const;

	Rect calc_box2d() const;

	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;


public:
  virtual void get_show(std::vector<Entity*>& es)const;

public:
  virtual void selected(bool sel);
  virtual bool selected()const;
  void show0(bool b);
  bool show0();
  void recal_show0();
private:
  bool show0_;
public:
  void mode(DIM_MODE m);
  DIM_MODE mode()const;
public:
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;


  //bool is_0_superposition(const Ln_Dim_Block& rhs)const; 

public:
  void text_row_dis(Float f){text_row_dis_ = f;}

private:
  Float text_row_dis_;   //  行间距


  friend int recal_line_block(Ln_Dim_Block& blk);
private:
  int dim_count_;
  void dim_count(bool add);

private:
  void setdrag_pileup(const std::vector<Point>& pts, int index);
  void getdrag_pileup(std::vector<Point>& pts)const;
  void setdrag_closed(const std::vector<Point>& pts, int index);
  void getdrag_closed(std::vector<Point>& pts)const;

private:
	MCT_DEF
};
}
#endif//FILE
