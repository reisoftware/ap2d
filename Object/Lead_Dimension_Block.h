// Lead_Dimension_Block.h: interface for the Lead_Dimension_Block class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_LEAD_DIMENSION_BLOCK_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_
#define AFX_LEAD_DIMENSION_BLOCK_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_


#include "Entity.h"
#include <vector>

#include "Dimension.h"

namespace dlhml{
//class Text_Dimension;
class Lead_Dimension;
class Line;
class OBJECT_API Lead_Dimension_Block : public Dimension
{
	MY_DECLARE_DYNCREATE(Lead_Dimension_Block)
public:
	Lead_Dimension_Block();
	Lead_Dimension_Block(const Lead_Dimension_Block& rhs);
	Lead_Dimension_Block& operator=(const Lead_Dimension_Block& rhs);
	virtual ~Lead_Dimension_Block();
	void clear();

public:
  void  dim_pos(const Point& pt);
  Point dim_pos()const;
	void  start(const Point& pt);//{st_=pt;}
	Point start()const;//{return st_;}
  void  end(const Point& pt);
  Point end()const;

public:
	void lead(bool b){lead_ = b;}
	bool lead() const{return lead_;}

public:
	void push_back(Lead_Dimension * dim);
	void remove(Lead_Dimension * dim);
	void erase(Lead_Dimension * dim);

public:
	Lead_Dimension * front() const;
	Lead_Dimension * back () const;

	Lead_Dimension * prev(Lead_Dimension * dim) const;
	Lead_Dimension * next(Lead_Dimension * dim) const;

public:
  virtual void setdrag(const std::vector<Point>& pts, int index=0);
  virtual void getdrag(std::vector<Point>& pts) const;

public:
	enum POSWAY	{PW_UP, PW_DONW, PW_LEFT, PW_RIGHT};
	void update_txtpos(POSWAY w);
	void real_box_pt(std::vector<Point>& pts)const;

public:
  virtual void get_line(std::vector<Entity*>& es)const;
  virtual void get_show(std::vector<Entity*>& es)const;

private:
	void get_block_line(std::vector<Entity*>& es)const;
	Rect calc_box_dim()const;


public:
	bool visit(Visitor& v);
	
private:
	std::vector<Lead_Dimension*> list_;
	Point st_;
	Point ed_;
	bool lead_;
//	bool outer_;
	Rect mem_rc_;

  bool outer()const;
  void update_txtpos_up();
  void reset_txtpos_up(int cur);
  void get_txt(int cur, Text& txt);
  Float get_txt_hei(Text& txt);
  Float get_dim_hei(int cur);

private:
  void copy(const Lead_Dimension_Block& s, Lead_Dimension_Block& d);

private:
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l) ;
	
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

	//bool intersectme(const Rect& rect) const;
	//bool envelopme(const Rect& rect) const;

	//Rect calc_box2d() const;

	bool snap_intersect_pointme(Point& pt,const Entity& ent,const Rect& rect) const;
	bool snap_intersect_pointme(Point& pt,const Entity_Snap& snap,const Rect& rect) const;

public:
  Rect offset_box();    //  干涉后参与偏移部分的外框
  void offset_pp(); //  偏移位置++
  void offset_degree(Float f);
  void h_offset_way(int i);
  void h_offset_num(int i);
  void text_row_dis(Float f){text_row_dis_ = f;}
  int  offset_floor();  //  起始楼层
  int  span_floor();    //  占用层数
  int  floor_count();   //  楼层数

private:
  void offset_text();
  int offset_pos_;      //  偏移位置
  int offset_floor_;    //  偏移楼层
  Float offset_degree_;
  int h_offset_way_;
  int h_offset_num_;
  Float text_row_dis_;   //  行间距

private:
	MCT_DEF
};
}
#endif // !defined(AFX_LEAD_DIMENSION_BLOCK_H__15805EB8_6296_44DB_ACF2_4D8C565856C7__INCLUDED_)
