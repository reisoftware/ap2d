// DB_View.cpp: implementation of the DB_View class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ap2D.h"
#include "DB_View.h"

#include <algorithm>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_View::DB_View()
{
	cur_ = NULL;

}

DB_View::~DB_View()
{	


}
void DB_View::close()
{
	for(int i=0;i<vs_.size();i++){
		vs_[i]->close();
	}

}
DB_View* DB_View::instance()
{	
	static DB_View db;
	return &db;
}
View * DB_View::get_view(std::string name) const
{
	int i=0;
	for(i=0; i<vs_.size(); ++i){
		if(strcmp(vs_[i]->name().c_str(),name.c_str())==0){
			return vs_[i];
		}
	}
	return NULL;
}
View * DB_View::add_view(std::string name)
{
	View * v = View::create();
	v->name(name);
	vs_.push_back(v);
	return vs_.back();
}
bool DB_View::find_view(std::string name)const
{
	View *v = get_view(name);
	if(v)
		return true;
	return false;	
}
bool DB_View::erase_view(View *view)
{
	std::vector<View*>::iterator it;
	it = std::find(vs_.begin(), vs_.end(), view);
	if(it == vs_.end()){
		return false;
	}
	vs_.erase(it);

	return true;
}

bool DB_View::erase_view(std::string name)
{
	View * v = get_view(name);
	if(!v){
		return false;
	}
	erase_view(v);
	return true;
}
void DB_View::change_name(std::string old,std::string new_name)
{
	if(old == new_name)
		return;
	View * v = get_view(old);
	if(!v){
		return;
	}
	v->name(new_name);

}


dlhml::Database* DB_View::database()
{
	return cur_->scene()->database();
}




void DB_View::clear_select()
{
	dlhml::entity_iterator it= cur_->scene()->database()->entity_begin();
	int num = cur_->scene()->database()->entity_size();
	for(; it != cur_->scene()->database()->entity_end(); ++it){
		(*it)->selected(false);
  }

}
