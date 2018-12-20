// Three_Pt_Dimension_Block.h: interface for the Three_Pt_Dimension_Block class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_THREE_PT_DIMENSION_BLOCK_H__6435728B_CB6D_44E7_92F5_90677F09E008__INCLUDED_
#define AFX_THREE_PT_DIMENSION_BLOCK_H__6435728B_CB6D_44E7_92F5_90677F09E008__INCLUDED_

#include "Entity.h"
#include <vector>

namespace dlhml{
class Three_Pt_Dimension;
class Normal;
class Point;
class OBJECT_API Three_Pt_Dimension_Block : public Entity
{
	MY_DECLARE_DYNCREATE(Three_Pt_Dimension_Block)
public:
	Three_Pt_Dimension_Block();
	Three_Pt_Dimension_Block(const Three_Pt_Dimension_Block& rhs);
	Three_Pt_Dimension_Block& operator=(const Three_Pt_Dimension_Block& rhs);
	virtual ~Three_Pt_Dimension_Block();

  void dim_style(std::string style_name);//{}
  std::string dim_style()const;//{return NULL;}

  virtual void line_style(std::string style);//	{	string_copy(linestyle_,style);}
	virtual std::string line_style() const		;//	{	return linestyle_;}
	virtual void			color(COLORREF rgb)	;//	{	color_ = rgb;	}
	virtual COLORREF	color() const				 ;// {	return color_.rgb();}

	void insert(const Three_Pt_Dimension* pos,Three_Pt_Dimension* dim);
	void push_back(Three_Pt_Dimension* dim);
	void erase(Three_Pt_Dimension* dim);

	Three_Pt_Dimension* front();
	Three_Pt_Dimension* back();

	Three_Pt_Dimension* previous(const Three_Pt_Dimension* pos);
	Three_Pt_Dimension* next(const Three_Pt_Dimension* pos);


	////垂线点选标注线(如果点在任一延长线直线上，返回false)
	bool select_from_dimline(Three_Pt_Dimension*& dim, const Point& pt);
	////矩形选标注线引出线文本框
	Three_Pt_Dimension* select_from_dimline(const Rect& rc);
	void select_from_extendline(Three_Pt_Dimension*& prev,Three_Pt_Dimension*& next,const Rect& rc);
	Three_Pt_Dimension* select_from_text(const Rect& rc);

  bool is_in_beeline_by_entendline(const Rect& rc);
  bool is_in_beeline_by_entendline(const Point& pt);

	void offset_dimlines(const Normal& nor,Float off);
	void layout_dimlines(const Point& pos);
	void layout_base(const Point& pos);

	//front true,back false
	bool front_or_back_point(const Point& pt);

	int size() const;
	void clear();

	bool visit(Visitor& v);


private:
#pragma warning(push)
	#pragma warning(disable:4251)
	std::vector<Three_Pt_Dimension*> list_;
#pragma warning(pop)
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
//  //bet
  void selected(bool sel);
  bool selected() const;
//private:
//  bool sel_;
//  //ter
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_THREE_PT_DIMENSION_BLOCK_H__6435728B_CB6D_44E7_92F5_90677F09E008__INCLUDED_)
