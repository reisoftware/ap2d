// DB_Detail.h: interface for the DB_Detail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_DETAIL_H__0E4D712E_CCED_48DD_A7BE_D0BC412B8614__INCLUDED_)
#define AFX_DB_DETAIL_H__0E4D712E_CCED_48DD_A7BE_D0BC412B8614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "DB_Templete.h"
#include "Mgr_Dxfs.h"

class Ap_Layer
{
public:
	Ap_Layer(){show_ = FALSE;lock_ = FALSE;;}
	virtual ~Ap_Layer(){;}

	void set_from_str_sub(char *name);
	void get_str_sub(char *name);

	std::string layer_name_;
	std::string hash_val_;

	std::string lua_path_name_;
	std::string lua_file_name_;
	Entitys ents_;

	BOOL show_;
	BOOL lock_;
	
};
typedef std::vector<Ap_Layer> Ap_Layers;
class Detail 
{
public:
	Detail(){;}
	virtual ~Detail(){;}
	bool operator==(const Detail& rhs)
	{
		if(strcmp(name_.c_str(),rhs.name_.c_str()) == 0 )
			return true;
		return false;
	}	

	void set_from_str(char *in);
	void get_str(char *out);

	bool get_ap_layer(std::string layer_name,Ap_Layer &ap_layer);

	void edit_show(std::string layer_name,BOOL show);
	void edit_lock(std::string layer_name,BOOL lock);

	std::string name_;
	std::string hash_val_; //主文件的hash值

	Ap_Layers ap_layers_; //每层的hash值

	strings change_layer_;
};
typedef std::vector<Detail> Details;


class DB_Detail : public DB_Templete<Details,Detail>
{
public:
	DB_Detail();
	virtual ~DB_Detail();

	bool is_have(std::string key);
	bool is_change(Detail &detail);

	std::string change_info(std::string name);

	void upload(std::string key);
	void download(std::string key);

	bool judge_hash(std::string detail_name,std::string layer_name,Ap_Layers &hashs);

	std::string get_layer_hash_val(std::string detail_name,std::string layer_name);

	void get_layers(std::string detail_name,strings &layer_file_names);
	void get_layers_name(std::string detail_name,strings &layer_file_names);

	void show(std::string detail_name,CComboBox & combo);

	BOOL get_show(std::string detail_name,std::string layer_name);
	BOOL get_lock(std::string detail_name,std::string layer_name);
	void edit_show(std::string detail_name,std::string layer_name,BOOL show);
	void edit_lock(std::string detail_name,std::string layer_name,BOOL lock);


private:
	void create_item(char *in);
	//apdim需要特殊对待
	BOOL apdim_show_;
	BOOL apdim_lock_;

};

#endif // !defined(AFX_DB_DETAIL_H__0E4D712E_CCED_48DD_A7BE_D0BC412B8614__INCLUDED_)
