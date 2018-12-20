// DB_Templete.h
#ifndef _DB_TEMPLETE_H_
#define _DB_TEMPLETE_H_

#include <algorithm>
template<class DB,class Item>
class DB_Templete
{
public:
	DB_Templete(){;}
	~DB_Templete(){;}
public:
	DB::const_iterator begin()const {return items_.begin();}
	DB::const_iterator end()const {return items_.end();}
	BOOL push(const Item& item)
	{
		DB::iterator iter = std::find(items_.begin(),items_.end(),item);
		if(iter != items_.end()){
			*iter = item;
			return false;
		}
		items_.push_back(item);
		return true;
	}
	BOOL get(std::string name,Item& item)
	{
		DB::iterator iter = find(name);
		if(iter != items_.end()){
			item = *iter;
			return true;
		}
		return false;
	}
	BOOL delete_item(std::string name)
	{
		DB::iterator iter = find(name);
		if(iter != items_.end()){
			items_.erase(iter);
			return true;
		}
		return false;
	}
	DB::iterator find(std::string name)
	{
		Item temp;
		temp.name_ = name;
		return std::find(items_.begin(),items_.end(),temp);
	}	
	BOOL find_have(std::string name)
	{
		DB::iterator iter = find(name);
		if(iter == items_.end())
			return false;
		return true;
	}	
	BOOL edit(const Item& item)
	{
		DB::iterator iter = std::find(items_.begin(),items_.end(),item);
		if(iter != items_.end()){
			(*iter) = item;
			return true;
		}
		return false;
	}
	void show(CComboBox & combo)
	{
		DB::iterator iter = items_.begin();
		for(;iter != items_.end();++iter){
			combo.AddString((*iter).name_);
		}
	}
	int size()
	{
		return items_.size();
	}
	void clear()
	{
		items_.clear();
	}
protected:
	DB items_;

};


#endif
