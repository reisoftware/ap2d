// Create_Rect.h: interface for the Create_Rect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_CREATE_RECT_H__55BD6F07_D574_4493_A231_7AE120168AB1__INCLUDED_
#define AFX_CREATE_RECT_H__55BD6F07_D574_4493_A231_7AE120168AB1__INCLUDED_

/*
#include "Create_Entity.h"
#include "Rectentity.h"
#include <utility>
#include "Entity_ID.h"

namespace dlhml{
#ifndef DISPLAYBHX_EXPORTS
class Create_Rect : public Create_Entity  
#else
class DISPLAY_API Create_Rect : public Create_Entity  
#endif
{
public:
	Create_Rect(Scene& scene);
	virtual ~Create_Rect();
	void close();

private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	void xor_draw_p(Draw_Entity& paint);
	bool execute_p();
	bool unexecute_p();

	void addrect();

	Rectentity *prect_;
	//typedef std::pair<Point,Point> crpair;	
	Point cur_;			//鼠标当前位置
	//Rectentity property_;//for property record
	//crpair cr_;  	   //for redo create data 
	Entity_ID id_;	 //for undo delete

};
}
*/
#endif // !defined(AFX_CREATE_RECT_H__55BD6F07_D574_4493_A231_7AE120168AB1__INCLUDED_)
