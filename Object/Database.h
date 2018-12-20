// Database.h: interface for the Database class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DATABASE_H__B4BC17D8_FE6D_493A_8903_547F5DC61357__INCLUDED_
#define AFX_DATABASE_H__B4BC17D8_FE6D_493A_8903_547F5DC61357__INCLUDED_

#include "export.h"
#include <vector>

#include "counter.h"
#include "iolua.h"

namespace dlhml{
class Entity_ID;
class Entity;
class File;
class Rect;
class Point;
class Snap;
class Layer;
class Line_Type;
class Text_Style;
class Dimension_Style;
class Paint_Snap;
class Block;
class Group_Ents;

typedef std::vector<Entity*>::iterator entity_iterator;
typedef std::vector<Entity*>::const_iterator entity_const_iterator;

typedef std::vector<Entity_ID> EntityIDArray;
typedef std::vector<Text_Style*>::iterator txt_style_iterator;
typedef std::vector<Dimension_Style*>::iterator dim_style_iterator;
typedef std::vector<Line_Type*>::iterator ltype_iterator;
typedef std::vector<Layer*>::iterator layer_iterator;

class OBJECT_API Database  
{
	Database(const Database& rhs);
	Database& operator=(const Database& rhs);
protected:
	static void* operator new(size_t size){
		return ::operator new(size);
	}
	static void operator delete(void* ptr){
		::operator delete(ptr);
	}
	Database();
// 	virtual void calc_index(Entity* pEnt,Entity_ID& id//,ULONG index);
public:
	static Database* create_me();
	virtual ~Database();
	virtual void close() = 0;

	virtual errorinfo save_file(std::string filename) const = 0;
	virtual errorinfo open_file(std::string filename) = 0;

// 	virtual void lua_save(oLua_File &fout) const=0;
// 	virtual void lua_load(iLua_File &fin)=0;

	virtual void save_lua(char *file_name) const=0;
	virtual void open_lua(char *file_name,Database *db)=0;

	
	virtual void save_lua(std::vector<Entity*> &ents,std::string file_name) const=0;
	virtual void get_ents_by_luafile(std::vector<Entity*> &ents) =0;
	
	//entity
		//operator
	virtual errorinfo entity_push_back(Entity* pEnt,Entity_ID& id) = 0;
	virtual errorinfo entity_from_id(Entity*& pEnt,const Entity_ID& id) const = 0;
	virtual errorinfo erase_entity(const Entity_ID& id) = 0;
	virtual errorinfo remove_entity(const Entity_ID& id) = 0;
	virtual void clear_entity() = 0;
		//rect
	virtual Rect current_rect() const = 0;
	virtual void update_rect(const Entity* pEnt) = 0;
		//loop
	virtual entity_iterator entity_begin() = 0;
	virtual entity_iterator entity_end() = 0;
	virtual int entity_size() const = 0;
		//serialize
	virtual void load_entity(File& in) = 0;
	virtual void load_entity_to_id(File& in,EntityIDArray& ents) = 0;
	virtual void save_entity(const File& out) const = 0;
	virtual void load_entity_order(File& in,std::vector<EntityIDArray>& orders) = 0;
	virtual void save_entity_order(const File& out,const std::vector<EntityIDArray>& orders) const = 0;
		//function
	virtual errorinfo group_entity_rect(Rect& rect,const EntityIDArray& ents) const = 0;
	virtual errorinfo all_entity_rect(Rect& rect) const = 0;
	virtual bool snap_entity(Paint_Snap& ps,Point& pt,const Rect& rect,
		const Snap& flag,const Point& o) const = 0;
		
	//select block
	virtual bool select_block(Block*& block,const Point& pt) const   = 0;


	//layer style
	virtual void layer_push_back(Layer* layer) = 0;
	virtual bool get_layer(Layer*& layer,std::string name) const = 0;
	//line style
	virtual void linestyle_push_back(Line_Type* type) = 0;
	virtual bool get_linetype(Line_Type*& type,std::string name) const = 0;
	//text style
	virtual void textstyle_push_back(Text_Style* style) = 0;
	virtual bool get_textstyle(Text_Style*& style,std::string name) const = 0;
	//dimension style
	virtual void dimensionstyle_pushback(Dimension_Style* style) = 0;
	virtual bool get_dimensionstyle(Dimension_Style*& style,std::string name) const = 0;
	virtual bool delete_dimstyle(std::string name) = 0;

	//得到所有的样式集合
	virtual txt_style_iterator text_style_begin()=0;
	virtual txt_style_iterator text_style_end()=0;
	virtual dim_style_iterator dim_style_begin()=0;
	virtual dim_style_iterator dim_style_end()=0;
	
	virtual ltype_iterator lstyle_begin()=0;
	virtual ltype_iterator lstyle_end()=0;


	virtual layer_iterator layer_begin()=0;
	virtual layer_iterator layer_end()=0;

	//select group_ent
  virtual bool select_group(Group_Ents*& group,const Entity& ent)  = 0;
  virtual bool select_group(Group_Ents*& group,const Entity_ID& id)= 0;
	virtual bool select_group(Group_Ents*& group,const Point& pt) = 0;

	//添加和删除实体的组
	virtual void push_group_ent(Group_Ents* group_ent) = 0;
	virtual void remove_group_ent(Group_Ents* group_ent) = 0;
//virtual std::vector<Group_Ents*>::iterator group_ents_begin()=0;
//virtual std::vector<Group_Ents*>::iterator group_ents_end()=0;

	virtual void erase_ent_in_group(const Entity * ent)  =0;
//virtual void remove_ent_in_group(const Entity_ID& id)=0;
//virtual bool select_group(Group_Ents*& group,int id) =0;

//bet  
public:
	virtual void get_group_ents(std::vector<Group_Ents*>& gps)const=0; 
  //set all entity's highlight state
  virtual void selected_all(bool sel){}
//ter

private:
	MCT_DEF
};
}
#endif // !defined(AFX_DATABASE_H__B4BC17D8_FE6D_493A_8903_547F5DC61357__INCLUDED_)
