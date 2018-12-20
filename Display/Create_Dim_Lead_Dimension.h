// Create_Dim_Lead_Dimension.h: interface for the Create_Dim_Lead_Dimension class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREATE_DIM_LEAD_DIMENSION_H__83B0A5C5_2548_42B6_AC78_49815D1FB932__INCLUDED_)
#define AFX_CREATE_DIM_LEAD_DIMENSION_H__83B0A5C5_2548_42B6_AC78_49815D1FB932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Create_Entity.h"
#include "Entity_ID.h"
#include <string>
#include <vector>

namespace dlhml{
class Lead_Dimension;
class Block;

#ifndef DISPLAYTIAN_EXPORTS
class Create_Dim_Lead_Dimension : public Create_Entity  
#else
class DISPLAY_API Create_Dim_Lead_Dimension : public Create_Entity  
#endif
{
public:
	Create_Dim_Lead_Dimension(Scene& scene);
	virtual ~Create_Dim_Lead_Dimension();
	void close(){delete this;}
private:
	void mouse_move_p(UINT nFlags, const Point& pt);
	void left_button_down_p(UINT nFlags, const Point& pt);
	void right_button_up_p(UINT nFlags, const Point& pt);
	void key_down_p(UINT nChar, UINT nRepCnt, UINT nFlags);

	void xor_draw_p(Draw_Entity& paint);
	void add_dim(char* txt);

	bool execute_p();
	bool unexecute_p();
private:
//	LPTSTR dim_txt_;
	std::string dim_txt_;

private:
	Lead_Dimension* pLead_dim_;
	//保证每次只redo一个，需要重新生成命令
	void cmd_start();
	
	Block *p_block_;//属于，某个块


	
private:
	MCT_DEF
};
}

#endif // !defined(AFX_CREATE_DIM_LEAD_DIMENSION_H__83B0A5C5_2548_42B6_AC78_49815D1FB932__INCLUDED_)
