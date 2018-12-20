// Cut_Section.h: interface for the Cut_Section class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_CUT_SECTION_H__57FD8A1D_2CE9_451F_9B08_F5A86DD3A071__INCLUDED_
#define AFX_CUT_SECTION_H__57FD8A1D_2CE9_451F_9B08_F5A86DD3A071__INCLUDED_

#include "Entity.h"
#include "Point.h"
#include <vector>
#include "Entity_ID.h"

namespace dlhml{
class Line;
class Text;
class Group_Ents;
class OBJECT_API Cut_Section : public Entity  
{
	MY_DECLARE_DYNCREATE(Cut_Section)
public:
	Cut_Section();
	Cut_Section(const Cut_Section& rhs);
	Cut_Section& operator=(const Cut_Section& rhs);
	virtual ~Cut_Section();
public:

	void set_data(const Point& start,const Point& three,const Point& end)
		{start_=start;three_=three;end_=end;}
	void	start(const Point& pt) {start_ = pt;}
	Point	start() const {return start_;}
	void	three(const Point& pt)  {three_ = pt;}
	Point	three() const {return three_;}
	void	end(const Point& pt)  {end_ = pt;}
	Point	end() const {return end_;}

	void	section_pos(const Point& pt)  {section_pos_ = pt;}
	Point	section_pos() const {return section_pos_;}
	void	rect_left(const Point& pt)  {rect_left_ = pt;}
	Point	rect_left() const {return rect_left_;}
	void	rect_right(const Point& pt)  {rect_right_ = pt;}
	Point	rect_right() const {return rect_right_;}
	void dis_in(Float dis)					{dis_in_=dis;}
	Float dis_in() const					{return dis_in_;}
	void dis_out(Float dis)					{dis_out_=dis;}
	Float dis_out() const					{return dis_out_;}
	void sel_part(int sel)					{sel_part_=sel;}
	int sel_part() const					{return sel_part_;}

	void denote_text(std::string s)				{denote_text_ = s;}
	std::string denote_text() const				{return denote_text_;}
	void text_style(std::string s)				{text_style_= s;}
	std::string text_style() const					{return text_style_;}
	void text_height(Float h)					{text_height_=h;}
	Float text_height() const					{return text_height_;}

	void detail_id(const Entity_ID& id)	{detail_=id;}
	Entity_ID detail_id() const					{return detail_;}

	void id_blk_cut_in(const Entity_ID& id)	{id_blk_cut_in_=id;}
	Entity_ID id_blk_cut_in() const					{return id_blk_cut_in_;}

	void group_ents_cut_in(Group_Ents* group_ent)	{group_ent_=group_ent;}
	Group_Ents* group_ents_cut_in() const					{return group_ent_;}

	void delete_section();
	int selected(Entity*ent);

	Line* get_line_in_section(){return line_;}
	Text* get_text_in_section(){return text_;}
	void set_line_in_section(Line* line){line_ = line;}
	void set_text_in_section(Text* txt){text_ = txt;}

	void get_denote_show(Line (&line)[8],Text (&text)[2]) const;

	bool visit(Visitor& v);

	//09.6.22
  void setctrl(const std::vector<Point>& pts);
  void getctrl(std::vector<Point>& pts) const;
  int  pt_count()const;
	void setdrag(const std::vector<Point>& pts, int index);
	void getdrag(std::vector<Point>& pts) const;

	void txt_color(int txt_color)					{txt_color_=txt_color;}
	int txt_color() const					{return txt_color_;}

private:
	void push_back(Entity* ent);
	void save_luame(std::ofstream &out,int tab_num);
  void open_luame(lua_State *l)  ;
	
	void get_strme(char *out);
	void set_from_strme(char *in);

private:
	std::string denote_text_;
	std::string text_style_;
	Float text_height_;
	Point start_;
	Point end_;
	Point three_;	
	Entity_ID detail_;
	
	Point section_pos_;
	Point rect_left_;
	Point rect_right_;
	Float dis_in_;
	Float dis_out_;
	Entity_ID id_blk_cut_in_;

	Group_Ents* group_ent_;

	Line* line_;
	Text* text_;

	int txt_color_;

private:
#pragma warning(push)
	#pragma warning(disable:4251)
	std::vector<Entity*> section_ents_;
#pragma warning(pop)
	Database* private_db_;
	int sel_part_;
	mutable Entity* selected_;

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

private:
	MCT_DEF
};


}

#endif // !defined(AFX_CUT_SECTION_H__57FD8A1D_2CE9_451F_9B08_F5A86DD3A071__INCLUDED_)
