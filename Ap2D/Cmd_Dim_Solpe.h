// Cmd_Dim_Solpe.h: interface for the Cmd_Dim_Solpe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Cmd_Dim_Solpe_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
#define AFX_Cmd_Dim_Solpe_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"
#include "Mgr_Dxfs.h"

class Cmd_Dim_Solpe : public dlhml::Create_Entity  
{
public:
	Cmd_Dim_Solpe(dlhml::Scene& scene);
	virtual ~Cmd_Dim_Solpe();
private:
	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	void right_button_down_p(UINT nFlags, const dlhml::Point& pt);

private:
	dlhml::Point cur_pt_;
	
	dlhml::Point pt_first_side_;
	dlhml::Point pt_second_side_;

private:
	void mouse_move_p(UINT nFlags, const dlhml::Point& pt);
	void xor_90_side();
	void xor_lean_side_move();
	void create_dim(const dlhml::Point &lean_point);
	std::string get_lean_value(double base,double len_one,double len_two);

};

#endif // !defined(AFX_CMD_DRAW_CENTER_H__6BBB1389_2DE6_4835_810A_9CF44D851654__INCLUDED_)
