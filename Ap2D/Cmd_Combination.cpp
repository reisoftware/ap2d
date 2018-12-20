// Cmd_Combination.cpp: implementation of the Cmd_Combination class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "Cmd_Combination.h"

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
Cmd_Combination::Cmd_Combination(dlhml::Scene& scene):Create_Entity(scene)
{

}

Cmd_Combination::~Cmd_Combination()
{

}

void Cmd_Combination::mouse_move_p(UINT nFlags, const dlhml::Point& pt)
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

void Cmd_Combination::left_button_down_p(UINT nFlags, const dlhml::Point& pt)
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
void Cmd_Combination::right_button_down_p(UINT nFlags, const dlhml::Point& pt)
{

}
void Cmd_Combination::xor_select_rect()
{
	dlhml::Painter* painter = scene_.get_painter();
	dlhml::Paint_Entity paint(scene_,*painter);


}
void Cmd_Combination::select_entity()
{

	
}












