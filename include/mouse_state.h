
#ifndef _mouse_state_h_
#define _mouse_state_h_
namespace gelib{
class AFX_EXT_CLASS Mouse_State{
	UINT flags_;
	CPoint last_;
	CPoint origin_;
public:

	Mouse_State():flags_(0) {}

	CPoint last() { return last_; }
	CPoint origin() { return origin_; }
  
	Mouse_State& set_last(CPoint pt) { last_ = pt; return *this;}
	Mouse_State& set_origin(CPoint pt) { origin_ = pt; return *this;}
	
	BOOL lbutton_flag() { return flags_ & MK_LBUTTON;	}
	BOOL rbutton_flag() {	return flags_ & MK_RBUTTON;	}
	BOOL mbutton_flag() {	return flags_ & MK_MBUTTON;	}
	
	Mouse_State& clear_lbutton_flag() {	flags_ &= ~MK_LBUTTON; return *this;	}
	Mouse_State& clear_rbutton_flag() {	flags_ &= ~MK_RBUTTON; return *this;	}
	Mouse_State& clear_mbutton_flag() {	flags_ &= ~MK_MBUTTON; return *this;	}

	Mouse_State& set_flags(UINT flags) { flags_ = flags;  return *this;}

};
inline 
BOOL ctrl_key_down()
{
	return (GetKeyState(VK_CONTROL) & 0x8000);
}
}
#endif