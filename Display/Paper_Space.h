// Paper_Space.h: interface for the Paper_Space class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_PAPER_SPACE_H__AF7E5225_BF3F_41B0_BF25_76B07ECAD317__INCLUDED_
#define AFX_PAPER_SPACE_H__AF7E5225_BF3F_41B0_BF25_76B07ECAD317__INCLUDED_

#include "display_export.h"
#include "Matrix_d.h"
#include "Snap.h"

//#include <vector>
#include "Flags.h"

namespace dlhml{
class Point;
class DISPLAY_API Paper_Space  
{
public:
	Paper_Space();
	Paper_Space(const Paper_Space& rhs);
	Paper_Space& operator=(const Paper_Space& rhs);
	~Paper_Space();

	bool ortho() const										{return ortho_;}
	void ortho(bool bortho)								{ortho_ = bortho;}

	COLORREF background_color() const			{return background_color_;}
	void background_color(COLORREF col)		{background_color_=col;}

	COLORREF entity_color() const					{return entity_color_;}
	void entity_color(COLORREF col)				{entity_color_=col;}

	LPCTSTR line_style() const						{return line_style_;}
	void line_style(LPCTSTR style)				{string_copy(line_style_,style);}

	LPCTSTR layer() const									{return layer_;}
	void layer(LPCTSTR lay)								{string_copy(layer_,lay);}

	void set_move(Float dx,Float dy,Float dz);
	void set_scale(Float sx,Float sy,Float sz);

	Matrix screen_to_world() const;
	Matrix world_to_screen() const;

	Point get_current_center(const Point& screen_center) const;
	Float get_current_scale() const;

	Snap* get_snap_flag()			{return &snap_;}


  bool add_to_dim_list() const					{return dim_flags_[0];}
	void add_to_dim_list(bool b)					{dim_flags_[0] = b   ;}
  bool erase_from_dim_list() const			{return dim_flags_[1];}
	void erase_from_dim_list(bool b)			{dim_flags_[1]=b     ;}
	bool align_dim_base() const						{return dim_flags_[2];}
	void align_dim_base(bool b)						{dim_flags_[2] = b   ;}
	bool reset0_to_dim_list() const				{return dim_flags_[3];}
	void reset0_to_dim_list(bool b)				{dim_flags_[3] = b   ;}

  bool size_dim_continue() const				{return dim_flags_[4];}
	void size_dim_continue(bool b)				{dim_flags_[4] = b   ;}

  void radio_dim_flags(int index)       {dim_flags_.radio(index);}
	void init_dim_flags()								  {dim_flags_.init();}


private:
	Snap snap_;
	bool		ortho_;					          //横平、竖直
	COLORREF background_color_;				//背景色
	COLORREF entity_color_;				    //当前实体缺省颜色
	LPTSTR	line_style_;					    //线形
	LPTSTR	layer_;					          //图层
	Matrix screen_to_world_;
  //Matrix world_to_screen_;

  Flags dim_flags_; //  标志
                    //  0:打断标注/新增尺寸线
                    //  1:删除尺寸线
                    //  2:对齐引出线基点
                    //  3:重设零点（仅限于累加标注）
                    //  4:连续标注（不退出连续话下一组，无需重新指定基准线）

private:
	bool string_copy(LPTSTR& dest,LPCTSTR src);
	void string_delete(LPTSTR& str);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_PAPER_SPACE_H__AF7E5225_BF3F_41B0_BF25_76B07ECAD317__INCLUDED_)
