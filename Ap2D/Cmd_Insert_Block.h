// Cmd_Insert_Block.h: interface for the Cmd_Insert_Block class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMD_INSERT_BLOCK_H__95C73E64_04BC_49DE_ACA3_5C8E488CF342__INCLUDED_)
#define AFX_CMD_INSERT_BLOCK_H__95C73E64_04BC_49DE_ACA3_5C8E488CF342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Create_Entity.h"

class Cmd_Insert_Block : public dlhml::Create_Entity  
{
public:
	Cmd_Insert_Block(dlhml::Scene& scene);
	virtual ~Cmd_Insert_Block();

private:

	void left_button_down_p(UINT nFlags, const dlhml::Point& pt);
	dlhml::Point get_center();

	std::vector<dlhml::Entity*> ents_;

	void move(dlhml::Matrix move);
};

#endif // !defined(AFX_CMD_INSERT_BLOCK_H__95C73E64_04BC_49DE_ACA3_5C8E488CF342__INCLUDED_)
