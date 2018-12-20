
#ifndef TIAN_OBJECT_LN_DIM_DIRECT_H_
#define TIAN_OBJECT_LN_DIM_DIRECT_H_

#include "Dimension.h"

namespace dlhml{

class Line;
class Circle;
class Ln_Dim_Direct;

//typedef void (*pf_ln_dim_text)(Ln_Dim_Direct& dim);
class OBJECT_API Ln_Dim_Direct : public Dimension
{
  MY_DECLARE_DYNCREATE(Ln_Dim_Direct)
public:
  virtual MY_CLASS myclass()const{return LINE_DIM;}
public:
  Ln_Dim_Direct();
  Ln_Dim_Direct(const Ln_Dim_Direct& rhs);
  Ln_Dim_Direct& operator=(const Ln_Dim_Direct& rhs);
  virtual ~Ln_Dim_Direct();
  
public:
  //is show
  void show0(bool b)				                {show0_=b;}
  bool show0()const				                  {return show0_;}
  void end_show(bool b)				              {end_show_=b;}
  bool end_show() const				              {return end_show_;}

public:
  //text info
  void dim_text2(std::string str)			          ;
  void  text2_rotation(Float f)		          ;
  void  text2_position(const Point& pos)	  ;
  void  text2_normal(const Normal& nor)     ;
  void  align_point2(Text::AlignPt align)	  ;
  
  std::string dim_text2() const			            {return dim_text2_;}
  Float text2_rotation() const		          {return text2_rotation_;}
  Point text2_position() const					    {return text2_position_;}
  Text::AlignPt align_point2() const			  {return align_point2_;}

//  void dim_text3(std::string str)			          {string_copy(dim_text3_,str);}
//  void  text3_rotation(Float f)		          {text3_rotation_=f;}
//  void  text3_position(const Point& pos)		{text3_position_=pos;}
//  void  text3_normal(const Normal& nor);
//  void  align_point3(Text::AlignPt align)	  {align_point3_=align;}
//
//  std::string dim_text3() const				          {return dim_text3_;}
//  Point text3_position() const		          {return text3_position_;}
//  Float text3_rotation() const		          {return text3_rotation_;}
//  Text::AlignPt align_point3() const			  {return align_point3_;}

public:
  //data point
  void setdata(const Point& opt,
               const Point& spt,
               const Point& ept,
               const Point& stdim,
               const Point& eddim);
  void  opt(const Point& pt);	
  Point opt()const                          {return opt_;}
  void  spt(const Point& pt);	
  Point spt()const                          {return spt_;}
  void  ept(const Point& pt);
  Point ept()const                          {return ept_;}

  void  odm(const Point& pt);
  Point odm()const			                    {return odm_;}
  void  edm(const Point& pt);
  Point edm()const			                    {return edm_;}

public:
  //  angle
  void  ext_line_radian(Float a);
  Float ext_line_radian() const	;           
  void  dim_line_radian(Float a);
  Float dim_line_radian() const	;           
  void  dim_line_degree(Float a);           
  Float dim_line_degree() const ;
  
  bool get_text2_show(Text& text) const;
  bool get_text2_frame_show(Text& text, std::vector<Entity*>& es) const;
  bool get_text3_show(Text& text) const;
  
public:
  ////只有线，无线型、颜色
  //PILEUP
  bool get_o_lines(Line& exln ,Line& dmln) const;
  bool get_e_lines(Line& exln ,Line& dmln) const;
  //CLOSED
  bool get_s_lines(Line& sexln,Line& eexln,Line& sdmln) const;
  
////内部创建内存，需外部释放。
public:
  virtual void get_line(std::vector<Entity*>& es) const;
  virtual void get_show(std::vector<Entity*>& es) const;
  bool get_dim_lines_show(std::vector<Line   *>& lines   ) const;
  //PILEUP
  void get_pileup_show(std::vector<Entity*>& es) const;
  int  get_o_arrow_line_show  (std::vector<Line   *>& lines   ) const;
  int  get_e_arrow_line_show  (std::vector<Line   *>& lines   ) const;
  int  get_o_arrow_circle_show(std::vector<Circle *>& circles ) const;
  int  get_e_arrow_circle_show(std::vector<Circle *>& circles ) const;
  //CLOSED
  void get_closed_show(std::vector<Entity*>& es) const;
	int  get_s_arrow_line_show  (const Line& dim,std::vector<Line   *>& lines   ) const;
	int  get_s_arrow_circle_show(const Line& dim,std::vector<Circle *>& circles ) const;

	void get_str_sub(char *name);
	void set_from_str_sub(char *name);

protected:

public:
  //  外部创建内存，内部直接使用，返回使用数量。
private:
  //  从外部创建内存，到内部创建的转换
//  void push_o_arrow_line_show(std::vector<Entity*>& es)const;
//  void push_e_arrow_line_show(std::vector<Entity*>& es)const;
//  void push_o_arrow_circle_show(std::vector<Entity*>& es)const;
//  void push_e_arrow_circle_show(std::vector<Entity*>& es)const;
  
public:
  //  外部创建内存，内部直接使用，返回使用数量。
private:
  //  从外部创建内存，到内部创建的转换
//  void push_s_arrow_circle_show(std::vector<Entity*>& es)const;
//  void push_s_arrow_line_show(std::vector<Entity*>& es)const;

  
public:
  void align_dim_lines(const Point& pos);
  void align_base(const Point& pos);
  
  bool pt_in_range(const Point& pt) const;
  
  bool visit(Visitor& v);

public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;
  
public:
  void mode(DIM_MODE m);
  void rota(DIM_ROTA m);
  DIM_MODE mode()const{return dim_mode_;}
  DIM_ROTA rota()const{return dim_rota_;}

public:
  void ext_line_normal(Normal& nor);
  //flags  1=o, 2=e
  void offset_dm(const Normal nor, Float dis, int flags);
  //void offset_dm(const Normal nor, int flags);
  void re0_dm();
    
private:
  DIM_MODE dim_mode_;
  DIM_ROTA dim_rota_;
private:
  bool  show0_;
  bool  end_show_;
  Float dim_line_radian_;
private:
  //data point
  Point opt_;
  Point spt_;
  Point ept_;
  Point odm_;
  Point edm_;
private:
  Text txt2_;
  std::string dim_text2_;
  std::string dim_text3_;
  Float  text2_rotation_;
  Float  text3_rotation_;
  Point  text2_position_;
  Point  text3_position_;
  Text::AlignPt align_point2_;
  Text::AlignPt align_point3_;

protected:
  void txt2_record(const Text& txt)const;
  void txt2_change(bool b)const;
private:
  Text txt2_record_;
  bool txt2_change_;
  
private:
  void loadme(File& in);
  void saveme(const File& out) const;

	void save_luame(std::ofstream &out,int tab_num);
	void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);
  
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

// public:
//   Rect offset_box();    //  干涉后参与偏移部分的外框
//   void offset_pp(); //  偏移位置++
//   void text_row_dis(Float f){text_row_dis_ = f;}
//   int  offset_floor();  //  起始楼层
//   int  span_floor();    //  占用层数
//   int  floor_count();   //  楼层数
//   
// private:
//   void offset_text();
//   int offset_floor_;    //  偏移楼层
//   Float text_row_dis_;   //  行间距
  
public:
	Float get_span_oe() const;
	Float get_span_se() const;
	//static pf_ln_dim_text pf_content_;	//	设置文字内容的函数指针
	bool user_content_;					//	用户自定义文本内容标志

private:
	MCT_DEF
};
}
#endif//FILE
//private:
//  从外部创建内存，到内部创建的转换
  //template<class T> 
//  void get_entitits_show(std::vector<Entity*>& es,
//  int (Ln_Dim_Direct::*show_ptr)(std::vector<Line*>))const;
//  {
//    std::vector<Line*> oln_arraw;
//    oln_arraw.resize(ARROW_LINE_COUNT);
//    int i=0;
//    for(i=0; i<oln_arraw.size(); i++){
//      oln_arraw[i] = Line::create_me();
//    }
//    int oln_arraw_num = show_ptr(oln_arraw);
//    for(i=0; i<oln_arraw_num; i++){
//      es.push_back(oln_arraw[i]->clone());
//    }
//    for(i=0; i<oln_arraw.size(); i++){
//      oln_arraw[i]->close();
//    }
//    return; 
//  }
