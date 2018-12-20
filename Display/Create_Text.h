// Create_Text.h: interface for the Create_Text class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_REATE_TEXT_H__0B582803_27FB_4194_BE88_491F40D04506__INCLUDED_
#define AFX_REATE_TEXT_H__0B582803_27FB_4194_BE88_491F40D04506__INCLUDED_

#include "Create_Entity.h"
#include <string>
#include "Text.h"


namespace dlhml{
class Create_Text : public Create_Entity
{
public:
	Create_Text(Scene& scene,LPCTSTR cont,int height, int color_id);
	virtual ~Create_Text();
	void close();

private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);
  void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);

  void on_draw();

	void xor_draw();
	void addtext();

	std::string cont_;
  int hei_;
  int cid_;
	//Text text;
	Text* text_;
	
private:
	MCT_DEF
};
}

#endif // !defined(AFX_REATE_TEXT_H__0B582803_27FB_4194_BE88_491F40D04506__INCLUDED_)
