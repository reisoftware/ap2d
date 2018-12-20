// Mgr_Layers.h: interface for the Mgr_Layers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MGR_LAYERS_H__FB656B91_4162_40E8_B577_202708C42AD5__INCLUDED_)
#define AFX_MGR_LAYERS_H__FB656B91_4162_40E8_B577_202708C42AD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DB_Layer.h"

namespace dlhml
{
	class Database;
}
class Layer_Info  
{
public:
	Layer_Info();
	virtual ~Layer_Info(){;}

	bool cur_part_;
	bool cur_sheet_;
	bool cur_cut_;
	bool cur_view_;
	bool cur_mark_;
	bool cur_dim_;

	bool ser_part_;
	bool ser_sheet_;
	bool ser_cut_;
	bool ser_view_;
	bool ser_mark_;
	bool ser_dim_;
	bool ser_ap_dim_;



};



class Mgr_Layers  
{
public:
	Mgr_Layers();
	virtual ~Mgr_Layers();

	
};


void hidden_layers(const Layer_Info &info,dlhml::Database *db);
void download_layers(const Layer_Info &info,dlhml::Database *db);
void download_layers(DB_Layer &db_layer,dlhml::Database *db);

void download_layer(std::string layer_name,dlhml::Database *db);


void upload_layers(dlhml::Database *db);


#endif // !defined(AFX_MGR_LAYERS_H__FB656B91_4162_40E8_B577_202708C42AD5__INCLUDED_)
