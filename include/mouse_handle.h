#ifndef _mouse_handle_h_
#define _mouse_handle_h_
#include "Mouse_State.h"
namespace gelib{
class AFX_EXT_CLASS Mouse_Handle{
	Mouse_State mouse_state_;
protected:
	~Mouse_Handle() {}
public:
	void OnLButtonDown(UINT nFlags,CPoint point);
	void OnLButtonUp(UINT nFlags,CPoint point);
	void OnLButtonDblClk(UINT nFlags,CPoint point);
	void OnMButtonDblClk(UINT nFlags,CPoint point);
	void OnMButtonDown(UINT nFlags,CPoint point);
	void OnMButtonUp(UINT nFlags,CPoint point);
	void OnMouseMove(UINT nFlags,CPoint point);
	void OnMouseWheel(UINT nFlags,short zDelta,CPoint point);

	void clear_line();
	void line_to(CPoint);
	void set_origin(CPoint pt) {mouse_state_.set_origin(pt);}
	
private:
	void move_center_2_cursor(CPoint pt);
	void draw_select_rect(CPoint point);
	void clear_rect(CClientDC& dc);

	void rotate_model(CPoint point);
	void offset_model(CPoint point);

};
}
#endif