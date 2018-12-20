// Mgr_Database.cpp: implementation of the Mgr_Database class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "Mgr_Database.h"
#include "Database.h"

#include "ap2d_objs.h"
#include "DB_View.h"
#include "Circle.h"
#include "RArc.h"
#include "Line_Arrow.h"
#include "Arc_Arrow.h"
#include "Ln_Dim_Block.h"
#include "Lead_Dimension.h"
#include "Lead_Dimension_MT.h"
#include "Lead_Dimension_Block.h"
#include "Radius_Dimension.h"
#include "Text_Dimension.h"
#include <algorithm>
#include "Dlg_Select_Color.h"
#include "Mgr_Lua.h"
#include "MainFrm.h"
#include "cbk.h"
#include "Global.h"
#include <set>
#include <fstream>
#include "Mgr_File.h"
#include "Mgr_Convert.h"
#include "Angle_Dimension.h"
#include "Lead_Dimension_Info.h"
#include "Text_Dimension_Info.h"
#include "Ln_Dim_Direct.h"
#include "Ln_Dim_PlateSide.h"
#include "Dim_Angle.h"




#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace dlhml;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mgr_Database::Mgr_Database()
{

}

Mgr_Database::~Mgr_Database()
{

}
void get_ents(dlhml::Database *db,Entitys &ents)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		ents.push_back(*it);
	}
  
}
void get_str_by_ents(Entitys &ents,char *out)
{
	for(int i=0;i<ents.size();i++){
		char val[MAX_REDIS]={0};
		ents[i]->get_str(val);
		strcat(out,val);		
	}

}
void get_layer_ent(dlhml::Database *db,std::string layer_name,Entitys &ents)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		if(strcmp((*it)->layer_name().c_str(),layer_name.c_str())==0){
			ents.push_back(*it);
		}
  }

}
void show_ents_by_layer(dlhml::Database *db,std::string layer_name,bool show)
{
	Entitys ents;
	get_layer_ent(db,layer_name,ents);
	
	//层的操作，select和push_sor的区别，使用push_xor
	int size = ents.size();
	for(int i=0;i<ents.size();i++){
		//ents[i]->selected(show);
		DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(ents[i]);
		
	}
	AfxMessageBox("asdfadsdf");
}
void show_ents()
{
	Entitys ents;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);

	int size = ents.size();
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Line))){
			dlhml::Line *l = (dlhml::Line*) (ents[i]);
//			l->line_style("Cqontinuous");
//			l->layer_name("APDIM");
//			l->group("group1");

		}
	//	ents[i]->selected(true);
	}
}

bool get_select_ents(dlhml::Database *db,Entitys &sel_ents)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		if((*it)->selected())
			sel_ents.push_back(*it);
		
  }

	if(sel_ents.size()<1){
		return false;
	}	

	return true;
}
void clear_select(dlhml::Database *db)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		(*it)->selected(false);
  }
	DB_View::instance()->cur_view()->scene()->get_idle()->clear_selected();

}
bool is_lines(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Line_Arrow)))
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_circles(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Circle)))
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_arcs(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Arc_Arrow)))
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_texts(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text)))
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_dims(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension)) ||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_MT))||
			ents[i]->isa(MY_RUNTIME_CLASS(Radius_Dimension))||
			ents[i]->isa(MY_RUNTIME_CLASS(Angle_Dimension))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Info))||
			ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension_Info))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Direct))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_PlateSide))||
			ents[i]->isa(MY_RUNTIME_CLASS(Dim_Angle))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))
			)
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_dims_no_angle(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension)) ||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_MT))||
			ents[i]->isa(MY_RUNTIME_CLASS(Radius_Dimension))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Info))||
			ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension_Info))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Direct))||
			ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_PlateSide))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))
			)
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
bool is_dims_blk(Entitys &ents)
{
	int size = 0;
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))||
			ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))
			)
			size++;
	}
	if(size == ents.size())
		return true;
	else
		return false;
}
void get_layers(dlhml::Database *db,strings &layers)
{
	std::string layer_name;
	
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		layer_name = (*it)->layer_name();
		strings::iterator iter = std::find(layers.begin(),layers.end(),layer_name);
		if(iter == layers.end())
			layers.push_back(layer_name);
  }
	
}
void get_texts(dlhml::Database *db,const Entitys &ents,Entitys &texts)
{
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text))){
			texts.push_back(ents[i]);
		}
  }
}
void get_lines(dlhml::Database *db,const Entitys &ents,Entitys &lns)
{
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Line))){
			lns.push_back(ents[i]);
		}
  }
}
void get_lines(dlhml::Database *db,Entitys &lns)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		if((*it)->isa(MY_RUNTIME_CLASS(Line))){
			lns.push_back(*it);
		}	
  }

}
void get_line_arrows(dlhml::Database *db,const Entitys &ents,Entitys &lns)
{
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Line_Arrow))){
			lns.push_back(ents[i]);
		}
  }
}
void get_line_arrows(dlhml::Database *db,Entitys &lns)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		if((*it)->isa(MY_RUNTIME_CLASS(Line_Arrow))){
			lns.push_back(*it);
		}	
  }
	
}
static int get_else_layer_id(std::string layer_name,Ap_Layers &layer_hashs)
{
	for(int i=0;i<layer_hashs.size();i++){
		if(strcmp(layer_name.c_str(),layer_hashs[i].layer_name_.c_str()) == 0){
			return i;
		}
	}
	return -1;
}

static void add(dlhml::Entity *ent,Ap_Layers &layer_hashs)
{
	int else_pos = get_else_layer_id(ELSE_LAYER,layer_hashs);
	for(int i=0;i<layer_hashs.size();i++){
		if(strcmp(ent->layer_name().c_str(),layer_hashs[i].layer_name_.c_str()) == 0){
			layer_hashs[i].ents_.push_back(ent);
		}else{
			//实体都有层名，所以不处理else层的问题。
//			if(else_pos != -1){
//				layer_hashs[else_pos].ents_.push_back(ent);
//			}
		}
	}
}
void part_ents(dlhml::Database *db,Ap_Layers &layer_hashs)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		add((*it),layer_hashs);
  }

}
void change_color(dlhml::Database *db,int color_index)
{
	dlhml::entity_iterator it= db->entity_begin();
	for(; it != db->entity_end(); ++it){
		(*it)->color_index(color_index);
  }

}
void change_color(Entitys &ents,int color_index)
{
	for(int i=0;i<ents.size();i++){
		ents[i]->color_index(color_index);
	}
}
void show_ents_part(Entitys &ents,bool show)
{
	for(int i=0;i<ents.size();i++){
		ents[i]->visibility(show);
	}
	

}
void show_ents(dlhml::Database *db,std::string txt_val,Entitys &equ_txt_texts)
{
	Entitys ents;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);

	//txt_val = get_prefix

	int i=0;

	int size = ents.size();
	for(i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (ents[i]);
			if(strcmp(v->text().c_str(),txt_val.c_str())==0){
				equ_txt_texts.push_back(ents[i]);
				//v->selected(true);

			}

		}
	}
/**/

	//按组分别处理
	std::string group_0 = "file_0";
	std::string group_1 = "file_1";
	Entitys ents_0,ents_1;
	get_ents_by_group(db,group_0,ents_0);
	get_ents_by_group(db,group_1,ents_1);

	std::string one_txt = Global::instance()->cur_val().sel_color_prop_.one_prefix_+txt_val+Global::instance()->cur_val().sel_color_prop_.one_postfix_;
	for(i=0;i<ents_0.size();i++){
		if(ents_0[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (ents_0[i]);
			if(strcmp(v->text().c_str(),one_txt.c_str())==0){
				equ_txt_texts.push_back(ents_0[i]);
			}

		}
	}
	std::string two_txt = Global::instance()->cur_val().sel_color_prop_.two_prefix_+txt_val+Global::instance()->cur_val().sel_color_prop_.two_postfix_;
	for(i=0;i<ents_1.size();i++){
		if(ents_1[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (ents_1[i]);
			if(strcmp(v->text().c_str(),two_txt.c_str())==0){
				equ_txt_texts.push_back(ents_1[i]);
			}

		}
	}

}
void show_equ_txts(dlhml::Database *db,Entitys &sel_texts)
{
	if(sel_texts.size()<1)
		return;
	dlhml::Text *txt = (dlhml::Text *)sel_texts[0];
	std::string txt_val =txt->text();

	Entitys ents,texts;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);

	int size = ents.size();
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (ents[i]);
			if(strcmp(v->text().c_str(),txt_val.c_str())==0){
				//v->selected(true);
				texts.push_back(v);
			}

		}
	}
	DB_View::instance()->cur_view()->scene()->get_idle()->set_xor(texts);
	
}

void check_equ_text(dlhml::Database *db,Entitys &sel_ents)
{
	Entitys texts;
	get_texts(db,sel_ents,texts);
	if(texts.size() <1 )
		return;
	int color =1,color_no2 = 1;
	dlhml::Text *one = (dlhml::Text*) (texts[0]);

	Global::instance()->cur_val().sel_color_prop_.cur_txt_val_ = one->text();


	if(afc::with_ctrl() || !Global::instance()->cur_val().sel_color_prop_.is_rember_color_){
		Dlg_Select_Color dlg;
		if(dlg.DoModal() == IDOK){
			color = dlg.get_color();
			color_no2 = dlg.get_color_no2();
		}
	}else{
		color = Global::instance()->cur_val().sel_color_prop_.cur_color_one_;
		color_no2 = Global::instance()->cur_val().sel_color_prop_.cur_color_two_;
	}
	change_color(texts,color,color_no2);

	for(int i=1;i<texts.size();i++){
		dlhml::Text *v = (dlhml::Text*) (texts[i]);
			if(strcmp(v->text().c_str(),one->text().c_str())!=0){
				AfxMessageBox("The texts aren't equal,please check them!");
				return;
			}

	}	

}
void change_group_name(Entitys &ents,std::string group)
{
	for(int i=0;i<ents.size();i++){
		ents[i]->group(group);
		
	}
}
int find_group(std::string group_name,Group_Txts &groups)
{
	for(int i=0;i<groups.size();i++){
		if(strcmp(group_name.c_str(),groups[i].group_name_.c_str())==0){
			return i;
		}		
	}
	return -1;
}
void print_info(Entitys &equ_txts)
{
	Group_Txts groups;
	Group_Txt item;
	int pos = -1;
	for(int i=0;i<equ_txts.size();i++){
		dlhml::Text *txt = (dlhml::Text*) (equ_txts[i]);


		pos = find_group(txt->group(),groups);
		if(pos == -1){
			item.group_name_ = txt->group();
			item.count_ = 1;
			groups.push_back(item);
		}else{
			groups[pos].count_++;
		}		
	}

	//执行减一操作
	if(!Global::instance()->cur_val().sel_color_prop_.include_cur_txt_){
		for(int i=0;i<groups.size();i++){
			if(strcmp(groups[i].group_name_.c_str(),Global::instance()->cur_val().sel_color_prop_.cur_txt_group_.c_str()) == 0){
				groups[pos].count_-= 1;
				break;
			}
		}
	}


	CString str;
	std::string info;
	for(i=0;i<groups.size();i++){
		str.Format("group = %s,text size = %d;  ",groups[i].group_name_.c_str(),groups[i].count_);
		info += str;
	}
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->set_status_str(info);
	

}
void change_color(Entitys &ents,int color_no1,int color_no2)
{
	if(ents.size()==0)
		return;
	std::string group = ents[0]->group();
	Entitys ones,twos;
	for(int i=0;i<ents.size();i++){
		if(strcmp(group.c_str(),ents[i]->group().c_str()) == 0){
			ones.push_back(ents[i]);
		}else{
			twos.push_back(ents[i]);
		}
	}

	for( i=0;i<ones.size();i++){
		ones[i]->color_index(color_no1);
	}
	for( i=0;i<twos.size();i++){
		twos[i]->color_index(color_no2);
	}

}

void get_ents_by_group(dlhml::Database *db,std::string group,Entitys &groups)
{
	Entitys ents;
	get_ents(db,ents);
	for(int i=0;i<ents.size();i++){
		if(strcmp(ents[i]->group().c_str(),group.c_str()) == 0){
			groups.push_back(ents[i]);
		}
	}
	
}
static void report_txts(std::ofstream &ofs,std::string group_name,Entitys &txts)
{
	if(txts.size()<1)
		return;
	ofs << group_name.c_str()<<"\n";
	Group_Txts all;
	Group_Txt t,temp;
	for(int i=0;i<txts.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts[i];
		t.txt_ = txt->text();
		t.count_ = 1;
		all.push_back(t);
	}


	std::set<std::string> txts_set;
	for(i=0;i<txts.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts[i];
		txts_set.insert(txt->text());
	}

	Group_Txts ts;

	std::set<std::string>::const_iterator it;
	for(it = txts_set.begin(); it != txts_set.end(); it++){
		t.txt_ = *it;
		t.count_ = std::count(all.begin(),all.end(),t);
		ts.push_back(t);
	}

	for(i=0;i<ts.size();i++){
		ofs << ts[i].txt_.c_str() << "		"<<ts[i].count_<<"\n";
	}



}
static void get_same_txts(std::set<std::string> &txts_set_0,std::set<std::string> &txts_set_1,strings &sames,strings &else_0,strings &else_1)
{
	std::set<std::string>::const_iterator it,it_find;
	for(it = txts_set_0.begin(); it != txts_set_0.end(); it++){
		it_find = std::find(txts_set_1.begin(),txts_set_1.end(),*it);
		if(it_find != txts_set_1.end()){
			sames.push_back(*it);
		}else{
			else_0.push_back(*it);
		}
	}
	
	for(it = txts_set_1.begin(); it != txts_set_1.end(); it++){
		it_find = std::find(txts_set_0.begin(),txts_set_0.end(),*it);
		if(it_find == txts_set_0.end()){
			else_1.push_back(*it);
		}
	}
	


}
static void report_txts(std::ofstream &ofs,std::string group_name_0,Entitys &txts_0,std::string group_name_1,Entitys &txts_1)
{
	if(txts_0.size()<1)
		return;
	std::string tab_one = "						";
	ofs <<tab_one.c_str()<< group_name_0.c_str()<<tab_one.c_str()<< group_name_1.c_str()<<"\n";
	Group_Txts all_0,all_1;
	Group_Txt t,temp;
	for(int i=0;i<txts_0.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts_0[i];
		t.txt_ = txt->text();
		t.count_ = 1;
		all_0.push_back(t);
	}
	for( i=0;i<txts_1.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts_1[i];
		t.txt_ = txt->text();
		t.count_ = 1;
		all_1.push_back(t);
	}


	std::set<std::string> txts_set_0,txts_set_1;
	for(i=0;i<txts_0.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts_0[i];
		txts_set_0.insert(txt->text());
	}
	for(i=0;i<txts_1.size();i++){
		dlhml::Text *txt = (dlhml::Text *)txts_1[i];
		txts_set_1.insert(txt->text());
	}

	strings sames,else_0,else_1;
	get_same_txts(txts_set_0,txts_set_1,sames,else_0,else_1);

	Group_Txts ts,errors,sames_ss;

	for( i=0;i<sames.size();i++){
		t.txt_ = sames[i];
		t.count_0_ = std::count(all_0.begin(),all_0.end(),t);
		t.count_1_ = std::count(all_1.begin(),all_1.end(),t);
		ts.push_back(t);		
	}

	std::string error_report = exe_path()+"error_report.txt";
	std::ofstream err_ofs(error_report.c_str());
	if(!err_ofs.is_open()){
		return;
	}

	for(i=0;i<ts.size();i++){
		ofs << ts[i].txt_.c_str() <<tab_one.c_str()<<ts[i].count_0_<<tab_one.c_str()<<ts[i].count_1_<<"\n";

		if(ts[i].count_0_ != ts[i].count_1_){
			errors.push_back(ts[i]);
			err_ofs << ts[i].txt_.c_str() <<tab_one.c_str()<<ts[i].count_0_<<tab_one.c_str()<<ts[i].count_1_<<"\n";
		}else{
			sames_ss.push_back(ts[i]);
		}
	}
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
	pM->show_list_report(errors);
	pM->show_same_list_report(sames_ss);
	err_ofs.close();

	if(else_0.size()>0){
		ts.clear();
		
		for( i=0;i<else_0.size();i++){
			t.txt_ = else_0[i];
			t.count_0_ = std::count(all_0.begin(),all_0.end(),t);
			ts.push_back(t);		
		}
		ofs << "\n\n\n";
		ofs << group_name_0.c_str()<<"\n";

		for(i=0;i<ts.size();i++){
			ofs << ts[i].txt_.c_str() <<tab_one.c_str()<<ts[i].count_0_<<"\n";
		}
	}
	if(else_1.size()>0){
		ts.clear();
		for( i=0;i<else_1.size();i++){
			t.txt_ = else_1[i];
			t.count_1_ = std::count(all_1.begin(),all_1.end(),t);
			ts.push_back(t);		
		}
		ofs << "\n\n\n";
		ofs << group_name_1.c_str()<<"\n";

		for(i=0;i<ts.size();i++){
			ofs << ts[i].txt_.c_str() <<tab_one.c_str()<<ts[i].count_1_<<"\n";
		}

	}



}
void create_report(dlhml::Database *db)
{
	//按组分别处理
	std::string group_0 = "file_0";
	std::string group_1 = "file_1";
	Entitys ents_0,ents_1,txts_0,txts_1;
	get_ents_by_group(db,group_0,ents_0);
	get_ents_by_group(db,group_1,ents_1);

	get_texts(db,ents_0,txts_0);
	get_texts(db,ents_1,txts_1);
	int size_1 = txts_1.size();
	int size_0 = txts_0.size();

	std::string file = exe_path()+"txts_report.txt";
	std::ofstream ofs(file.c_str());
	if(!ofs.is_open()){
		return;
	}
//	report_txts(ofs,group_0,txts_0);
//	report_txts(ofs,group_1,txts_1);
	report_txts(ofs,group_0,txts_0,group_1,txts_1);

	ofs.close();


 // ::ShellExecute(NULL, "open", file.c_str(), "", "", SW_SHOW);
//	std::string error_report = exe_path()+"error_report.txt";
//	::ShellExecute(NULL, "open", error_report.c_str(), "", "", SW_SHOW);
	
}
void show_text(dlhml::Database *db,std::string txt)
{
	Entitys ents,texts;
	get_ents(DB_View::instance()->cur_view()->scene()->database(),ents);

	int size = ents.size();
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (ents[i]);
			if(strcmp(v->text().c_str(),txt.c_str())==0){
				texts.push_back(v);
			}else
				ents[i]->visibility(false);
		}else
			ents[i]->visibility(false);
	}

	Entitys file0_ents,file1_ents;
	for( i=0;i<texts.size();i++){
		if(strcmp(texts[i]->group().c_str(),"file_0") == 0)
			file0_ents.push_back(texts[i]);
		else
			file1_ents.push_back(texts[i]);
	}

	change_color(file0_ents,Global::instance()->cur_val().sel_color_prop_.dbl_color_file0_);
	change_color(file1_ents,Global::instance()->cur_val().sel_color_prop_.dbl_color_file1_);

	DB_View::instance()->cur_view()->scene()->get_idle()->set_xor(texts);
	
}
void select_ents_by_layer(dlhml::Database *db,bool sel)
{
	Entitys ents,lay_ents;
	get_ents(db,ents);
	std::string layer0 = "file_0";
	for(int i=0;i<ents.size();i++){
		if(!ents[i]->visibility())
			continue;
		if(strcmp(ents[i]->group().c_str(),layer0.c_str()) == 0){
			ents[i]->selected(sel);
			lay_ents.push_back(ents[i]);
		}
	}
	DB_View::instance()->cur_view()->scene()->get_idle()->set_xor(lay_ents);
	

}
void reserve_select(dlhml::Database *db)
{
	Entitys ents;
	get_ents(db,ents);
	bool sel;
	for(int i=0;i<ents.size();i++){
		sel = ents[i]->selected();
		ents[i]->selected(!sel);
	}
}



void create_dim_style(dlhml::Dimension_Style & dim_style)
{
	Prop_Ent::PageArrow page_arrow = Global::instance()->cur_val().page_arrow_;

	dim_style.arrow_style(get_arrow_style_by_name(Global::instance()->cur_val().page_arrow_.arrow_style_.c_str()));
	dim_style.text_precision(Global::instance()->cur_val().page_text_.precision_);

/*
	dim_style.rounding_type(Convert_Content::get_rounding_type(ap2d::Model::instance()->current_value().cur_dim_val.precision_));
	dim_style.bit_after_dot(Convert_Content::get_bit_after_dot(ap2d::Model::instance()->current_value().cur_dim_val.text_format_));
	dim_style.show_last_0(Convert_Content::get_show_last_0(ap2d::Model::instance()->current_value().cur_dim_val.text_format_));
*/

	dim_style.extend_start_off(Global::instance()->cur_val().page_dim_.start_offset_);
	dim_style.extend_end_off(Global::instance()->cur_val().page_dim_.end_offset_);
	dim_style.start_dim_length(Global::instance()->cur_val().page_dim_.start_dim_len_);
	dim_style.end_dim_length(Global::instance()->cur_val().page_dim_.end_offset_);
	
	dim_style.arrow_size(Global::instance()->cur_val().page_arrow_.arrow_level_);
	dim_style.text_height(Global::instance()->cur_val().page_text_.hight_);


	dim_style.text_frame_color(Global::instance()->cur_val().page_common_.color_);
	dim_style.txt_frame(get_txt_frame(Global::instance()->cur_val().page_text_.frame_kind_.c_str()));

	dim_style.line_color(Global::instance()->cur_val().page_common_.color_);
	dim_style.text_color(Global::instance()->cur_val().page_text_.color_);
	
//
//	CString txt_pos = ap2d::Model::instance()->current_value().cur_dim_val.text_pos_;
//	dlhml::Dimension_Style::TextPos pos = Convert_Content::get_txt_pos_by_name(txt_pos);
//	dim_style.text_pos(pos);

}

std::string get_select_txt(dlhml::Database *db)
{
	
	Entitys sel_ents;
	get_select_ents(db,sel_ents);
	for(int i=0;i<sel_ents.size();i++){
		if(sel_ents[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (sel_ents[i]);
			return v->text();
		}
	}
	return "Txt";
}

void find_tool_text_sel(std::vector<dlhml::Entity*> data,std::vector<dlhml::Entity*>&  show_data,CString text)
{
	for (int i = 0 ; i < data.size(); i++ )
	{
		if(data[i]->isa(MY_RUNTIME_CLASS(Text)))
		{	
			Text * txt = static_cast<Text*>(data[i]);
			CString txt_val = txt->text().c_str();
		
			if(txt_val.Compare(text) == 0)
			{
					show_data.push_back(data[i]);
					
					DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);	
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}	
		else
			DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void find_tool_line_type_sel(std::vector<dlhml::Entity*> data,std::vector<dlhml::Entity*>&  show_data,CString text)
{
	for (int i = 0 ; i < data.size(); i++ )
	{
		if(data[i]->isa(MY_RUNTIME_CLASS(Line)) || data[i]->isa(MY_RUNTIME_CLASS(Line_Arrow)))
		{
			CString   ln_val = data[i]->line_style().c_str();
			if(ln_val.Compare(text) == 0)
			{
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else 
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void find_tool_type_sel(std::vector<dlhml::Entity*> data,std::vector<dlhml::Entity*>&  show_data,CString text)
{	
	for (int i = 0 ; i < data.size(); i++ )
	{	
		if (text.Compare("Line") == 0){
			if(data[i]->isa(MY_RUNTIME_CLASS(Line)) || data[i]->isa(MY_RUNTIME_CLASS(Line_Arrow)))
			{
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}
		else if (text.Compare("Circle") == 0){
			//AfxMessageBox("Circle");
			if(data[i]->isa(MY_RUNTIME_CLASS(Circle)))
			{
				//AfxMessageBox("Circle2");
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);	
		}
		else if (text.Compare("Arc") == 0){
			if(data[i]->isa(MY_RUNTIME_CLASS(RArc)) || data[i]->isa(MY_RUNTIME_CLASS(Arc_Arrow)) )
			{
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}
		else if (text.Compare("Text") == 0){
			if(data[i]->isa(MY_RUNTIME_CLASS(Text)))
			{
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}
		else if (text.Compare("Dim") == 0){
			if(data[i]->isa(MY_RUNTIME_CLASS(Text_Dimension)) ||
			data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension))||
			data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_MT))||
			data[i]->isa(MY_RUNTIME_CLASS(Radius_Dimension))||
			data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))||
			data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Info))||
			data[i]->isa(MY_RUNTIME_CLASS(Text_Dimension_Info))||
			data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Direct))||
			data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_PlateSide))||
			data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))
			)
			{
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
			}
			else
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		}
		else if (text.Compare("Other") == 0){
			if(
					data[i]->isa(MY_RUNTIME_CLASS(Line)) ||
					data[i]->isa(MY_RUNTIME_CLASS(Line_Arrow)) ||
					data[i]->isa(MY_RUNTIME_CLASS(Circle)) ||
					data[i]->isa(MY_RUNTIME_CLASS(RArc)) ||
					data[i]->isa(MY_RUNTIME_CLASS(Text)) ||
					data[i]->isa(MY_RUNTIME_CLASS(Text_Dimension)) ||
					data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension))||
					data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_MT))||
					data[i]->isa(MY_RUNTIME_CLASS(Radius_Dimension))||
					data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Block))||
					data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Info))||
					data[i]->isa(MY_RUNTIME_CLASS(Text_Dimension_Info))||
					data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_Direct))||
					data[i]->isa(MY_RUNTIME_CLASS(Ln_Dim_PlateSide))||
					data[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block)) 
				)
				DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
			else {
				show_data.push_back(data[i]);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);
			}
		}
	}
	DB_View::instance()->cur_view()->scene()->invalidate();

}

void find_tool_color_sel(std::vector<dlhml::Entity*>  data,int color_index)
{
	for (int i = 0 ; i < data.size() ; i++ )
	{
		DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
		if (data[i]->color_index() == color_index)
		{
			DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);		
		}
		else
			DB_View::instance()->cur_view()->scene()->get_idle()->erasexor(data[i]);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
}

void mgr_db_init_dlg_sel_tab_text_data(std::vector<dlhml::Entity*>  data,std::vector<dlhml::Entity*> all_datas,CListCtrl & list_nums)
{
	int num = 0;
	std::vector<dlhml::Entity*> new_ents;
	for (int i = 0 ; i < data.size(); i++ )
	{
		if(data[i]->isa(MY_RUNTIME_CLASS(Text)))
		{	
			int states = 0;
			std::vector<dlhml::Entity*>::iterator var;
			for (var = new_ents.begin();var != new_ents.end() ; var++ ){
				CString cur_text = static_cast<Text*>(data[i])->text().c_str();
				if ( cur_text.Compare(static_cast<Text*>(*var)->text().c_str()) == 0 )
				{
					states = 1;
				}
			}
			if ( states == 0 ){
					new_ents.push_back(data[i]);
					int cur_text_nums = 0;
					Text * txt = static_cast<Text*>(data[i]);
					CString txt_val = txt->text().c_str();
					CString temp_str;
					list_nums.InsertItem(num,"");
					temp_str.Format("%d",(num+1));
					list_nums.SetItemText(num,0,temp_str);
					list_nums.SetItemText(num,1,txt_val);
					for (int j = 0 ; j < all_datas.size() ; j++ )
					{
						if ( all_datas[j]->isa(MY_RUNTIME_CLASS(Text)) )
						{	
							Text * txt2 = static_cast<Text*>(all_datas[j]);
							CString new_txt_val = txt2->text().c_str();
							if ( new_txt_val.Compare(txt_val) == 0 )
								cur_text_nums++;
						}
					}
					temp_str.Format("%d",cur_text_nums);
					list_nums.SetItemText(num,2,temp_str);
					num++;
				}
		}		
	}
}

void show_sel_tab_txt(CString cur_str,std::vector<dlhml::Entity*> data)
{
	for (int i = 0 ; i < data.size() ; i++ )
	{
		if(data[i]->isa(MY_RUNTIME_CLASS(Text)))
		{
			Text * txt = static_cast<Text*>(data[i]);
			CString txt_val = txt->text().c_str();
			if ( txt_val.Compare(cur_str) == 0 )
			{
				data[i]->visibility(true);
				DB_View::instance()->cur_view()->scene()->get_idle()->push_xor(data[i]);	
			}
			else
				data[i]->visibility(false);
		}
		else 
			data[i]->visibility(false);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
}


void show_tab_txt_dlg_all_ents(std::vector<dlhml::Entity*> data)
{
	for (int i = 0 ; i < data.size() ; i++ ){
			data[i]->visibility(true);
	}
	DB_View::instance()->cur_view()->scene()->invalidate();
}


//得到集合中字符串等于参数str的文本实体集合
void get_texts_equal_str(CString str,const Entitys &sel_texts,Entitys &texts)
{
	for(int i=0;i<sel_texts.size();i++){
		if(sel_texts[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (sel_texts[i]);
			if(strcmp(v->text().c_str(),str.GetBuffer(0))	 == 0){
				texts.push_back(v);
			}
		}
	}
	

}
//处理包含该字符串的集合
void get_texts_include_str(CString str,const Entitys &sel_texts,Entitys &texts)
{
	for(int i=0;i<sel_texts.size();i++){
		if(sel_texts[i]->isa(MY_RUNTIME_CLASS(Text))){
			dlhml::Text *v = (dlhml::Text*) (sel_texts[i]);
			if(strstr(v->text().c_str(),str.GetBuffer(0))	 != NULL){
				texts.push_back(v);
			}
		}
	}

}
//得到集合中标注内所有的文字
void get_sons_in_ents(dlhml::Database *db,const Entitys &ents,Entitys &sons)
{

	for(int i=0;i<ents.size();i++){
			ents[i]->get_show(sons);
	/*
		if(ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension))){
		//	dlhml::Lead_Dimension *v = (dlhml::Lead_Dimension*) (ents[i]);	
			ents[i]->get_show(es);

		}else if(ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))){
		
		}else if(ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension))){
		
		}else if(ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Block))){
			
		}

	*/
	}

}
void get_lead_dim_infos(dlhml::Database *db,const Entitys &ents,Entitys &dim_blks)
{
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Lead_Dimension_Info))){
			dim_blks.push_back(ents[i]);
		}
	}

}
void get_text_dim_infos(dlhml::Database *db,const Entitys &ents,Entitys &dim_blks)
{
	for(int i=0;i<ents.size();i++){
		if(ents[i]->isa(MY_RUNTIME_CLASS(Text_Dimension_Info))){
			dim_blks.push_back(ents[i]);
		}
	}

}







