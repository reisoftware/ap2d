// Cmd_Cancel_Combination.cpp: implementation of the Cmd_Cancel_Combination class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Cancel_Combination.h"

#include "Global.h"
#include "DB_View.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Cmd_Cancel_Combination::Cmd_Cancel_Combination(dlhml::Scene& scene):Create_Entity(scene)
{

}

Cmd_Cancel_Combination::~Cmd_Cancel_Combination()
{
	

}

void Cmd_Cancel_Combination::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
{
	switch(step_)
	{
	case 1:
		xor_select_rect();
		end_ = pt;
		xor_select_rect();
		break;
	default:
		break;
	}
}

void Cmd_Cancel_Combination::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
{
	++step_;
	switch(step_)
	{
	case 1:
		begin_ = end_ = pt;
		//xor_select_rect();
		select_entity();
		step_=0;
		break;
	case 2:
		break;
	default:
		break;
	}
	

}
void Cmd_Cancel_Combination::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}
void Cmd_Cancel_Combination::xor_select_rect()
{
	dlhml::Painter* painter = scene_.get_painter();
	dlhml::Paint_Entity paint(scene_,*painter);


}
void Cmd_Cancel_Combination::select_entity()
{

	
}












