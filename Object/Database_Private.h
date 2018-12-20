// Database_Private.h: interface for the Database_Private class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DATABASE_PRIVATE_H__FB8DC03E_1961_4227_8CF1_830E2DB94A06__INCLUDED_
#define AFX_DATABASE_PRIVATE_H__FB8DC03E_1961_4227_8CF1_830E2DB94A06__INCLUDED_

#include "Database.h"
#include "Rect.h"
#include "Group_Ents.h"
#include "iolua.h"
namespace dlhml{
class Database_Private : public Database
{
public:
	Database_Private();
	virtual ~Database_Private();
	void close();

	errorinfo save_file(std::string filename) const;
	errorinfo open_file(std::string filename);

// 	void lua_save(oLua_File &fout) const;
// 	void lua_load(iLua_File &fin);

	void save_lua(char *file_name) const;
	void open_lua(char *file_name,Database *db);

	void get_ents_by_luafile(std::vector<Entity*> &ents);

	void save_lua(std::vector<Entity*> &ents,std::string file_name) const;



	errorinfo entity_push_back(Entity* pEnt,Entity_ID& id);
	errorinfo entity_from_id(Entity*& pEnt,const Entity_ID& id) const;
	////erase和remove
	errorinfo erase_entity(const Entity_ID& id);
	errorinfo remove_entity(const Entity_ID& id);
	void clear_entity();

	Rect current_rect() const;
	void update_rect(const Entity* pEnt);

	entity_iterator entity_begin();
	entity_iterator entity_end();
	int entity_size() const;

	void load_entity(File& in);
	void load_entity_to_id(File& in,EntityIDArray& ents);
	void save_entity(const File& out) const;
	void load_entity_order(File& in,std::vector<EntityIDArray>& orders);
	void save_entity_order(const File& out,const std::vector<EntityIDArray>& orders) const;

	errorinfo group_entity_rect(Rect& rect,const EntityIDArray& ents) const;
	errorinfo all_entity_rect(Rect& rect) const;

	bool snap_entity(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool select_block(Block*& block,const Point& pt) const;

	void layer_push_back(Layer* layer);
	bool get_layer(Layer*& layer,std::string name) const;
	void clear_layer();

	void linestyle_push_back(Line_Type* type);
	bool get_linetype(Line_Type*& type,std::string name) const;
	void clear_linetype();

	void textstyle_push_back(Text_Style* style);
	bool get_textstyle(Text_Style*& style,std::string name) const;
	void clear_textstyle();

	void dimensionstyle_pushback(Dimension_Style* style);
	bool get_dimensionstyle(Dimension_Style*& style,std::string name) const;
	void clear_dimensionstyle();
	bool delete_dimstyle(std::string name);
	
	txt_style_iterator text_style_begin();
	txt_style_iterator text_style_end();
	dim_style_iterator dim_style_begin();
	dim_style_iterator dim_style_end();

	ltype_iterator lstyle_begin();
	ltype_iterator lstyle_end();

	layer_iterator layer_begin();
	layer_iterator layer_end();

	void push_group_ent(Group_Ents* group_ent) ;
	void clear_group_ents();

	void remove_group_ent(Group_Ents* group_ent);
	bool select_group(Group_Ents*& group,const Point& pt);
	//bool select_group(Group_Ents*& group,int id);
	
  bool select_group(Group_Ents*& group,const Entity& ent);
  bool select_group(Group_Ents*& group,const Entity_ID& id);

//	std::vector<Group_Ents*>::iterator group_ents_begin();
//	std::vector<Group_Ents*>::iterator group_ents_end();


	void erase_ent_in_group(const Entity * ent);
	//void remove_ent_in_group(const Entity_ID& id);

private:
	bool snap_endpt(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool snap_middle(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool snap_center(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool snap_perpendicular(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool snap_intersect(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;
	bool snap_nearest(Paint_Snap& ps,Point& pt,const Rect& rect,const Snap& flag,const Point& o) const;

private:
	static const ULONG START_ENTITY_NO;

	entity_iterator find(const Entity_ID& id);
	entity_const_iterator find(const Entity_ID& id) const;

  ULONG index_;
  Rect box2d_;
  
  std::vector<Entity*> entlist_;
  std::vector<Layer*> layerlist_;
  std::vector<Line_Type*> linetypelist_;
  std::vector<Text_Style*> textstylelist_;
  std::vector<Dimension_Style*> dimensionstylelist_;


	//添加记录保存一些组的变量
	void get_group_ents(std::vector<Group_Ents*>& gps)const; 
	//std::vector<Group_Ents*> group_ents_; 
	bool have(Group_Ents* group_ent);

//bet
private:
  void selected_all(bool sel);

//	int open_db(lua_State *l);
//ter

private:
  virtual void calc_index(Entity* pEnt,Entity_ID& id);


	

private:
	MCT_DEF
};
}
#endif // !defined(AFX_DATABASE_PRIVATE_H__FB8DC03E_1961_4227_8CF1_830E2DB94A06__INCLUDED_)
