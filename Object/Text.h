
#ifndef _TIAN_OBJECT_TEXT_H_
#define _TIAN_OBJECT_TEXT_H_

#pragma warning (disable:4251)

#include "Entity.h"
#include "Point.h"
#include "Text_Style.h"

namespace dlhml{
class OBJECT_API Text : public Entity
{
	MY_DECLARE_DYNCREATE(Text)
public:
  virtual MY_CLASS myclass()const{return TEXT;}
public:
	enum AlignPt{
		left_top = 1,
		left_center,
		left_bottom,
		center_top,
		center_center,
		center_bottom,
		right_top,
		right_center,
		right_bottom
	};
	Text();
	Text(const Point& _pos,std::string _content);
	Text(const Point& _pos,std::string _content,std::string _font);
	Text(const Text& rhs);
	Text& operator=(const Text& rhs);
	virtual ~Text();

	void		setdata(const Point& pos,std::string cont);
	void		setdata(const Point& pos,std::string cont,std::string name);

  std::string text()const;				     
  void  text(std::string cont);
  std::string font()const;				     
  void  font(std::string name);
  Point position()const;					
  void	position(const Point& pos);
  Float	rotation()const;		        
  void	rotation(Float r);
  Float	rotation_radian()const;	    
  void	rotation_radian(Float r);
  Float	rotation_degree()const;	    
  void	rotation_degree(Float r);
  AlignPt align_point()const;					
	void	align_point(AlignPt pt);

  Float	dxf_height()const;	
  void	dxf_height(Float h);
  Float gdi_height()const;
  void	gdi_height(Float h);


  void		style_name(std::string s)			      ;
  void    style_val (const Text_Style& s) ;
  void		width_factor(Float wf)			    ;
  
  

	std::string     style_name()const;				
  Text_Style  style_val ()const;

	Float	width_factor()const;			

	HFONT	get_font() const;
	void	horizontal_size(SIZE& sz) const;
	void	horizontal_rect(Rect& rect) const;
  
  void real_box_pt(std::vector<Point>& pts)const;
  //void real_txt_pt(std::vector<Point>& pts)const;
	void left_top_point(Point& lt) const;
  Line dxf_base_line()const;
  Line dxf_bottom_line()const;
  Line center_line()const;

	bool visit(Visitor& v);

public:
// 	virtual void selected(bool select){/*seled_=select;*/}
// 	virtual bool selected()const			{return seled_;}
// 	virtual void lua_load(iLua_File &fin);
// 	virtual void lua_save(oLua_File &fout)const;
public:
  virtual void setctrl(const std::vector<Point>& pts);
  virtual void getctrl(std::vector<Point>& pts) const;
  virtual int  pt_count()const;

public:
  Point center()const;

protected:
  virtual Point focus()const{return postion_;}

	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

private:
  std::string		content_;
  std::string		font_;
	Point			postion_;
  Float			rotation_radian_;
	AlignPt		align_point_;

	std::string		 style_name_;
  Text_Style style_val_ ;
  Float			dxf_height_;  ////dxf(autocad):dxf_heigtht_*gdi_scale() == gdi_height_
	Float			width_factor_;

	void init();

protected:
  void std_sz_change(bool b)const;
  void std_sz_record(Float cx, Float cy)const;
private:
  bool  std_sz_change_;
  Float std_cx_record_;   
  Float std_cy_record_;   


  void real_box_change(bool b)const;
  bool real_es_changed_;
  std::vector<Point> real_box_record_;

private:
  void real_4pt(std::vector<Point>& pts)const; //, bool extend_h
//   void extend_box(const Rect& rc, Rect& txt, Rect& box)const;
  ////计算记忆数据
  //void std_size()const;


private:
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
//   void set_crurent_db();

private:
	MCT_DEF
};

inline Float gdi_scale()
{
  return 300.0/206.0;
}

inline Float text_height_dxf_2_gdi(Float dxf_h)
{
  return dxf_h * gdi_scale();
}

inline Float text_height_gdi_2_dxf(Float gdi_h)
{
  return gdi_h / gdi_scale();
}

OBJECT_API Float seemly_gdi_height(const Rect& rc, std::string row);
OBJECT_API Float seemly_gdi_height(const Rect& rc, const std::vector<std::string>& row);


}//namespace
#endif//FILE
