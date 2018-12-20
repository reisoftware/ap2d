#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_
#include "gl_lists.hpp"
template<class T>
class GL_Object{
private:
  unsigned modify_ :1;
  unsigned need_save_ :1;
  unsigned delete_ :1;
  unsigned visible_ :1;
  unsigned selected_ :1;
  unsigned redraw_2d_:1;
  unsigned :0;
  Gl_Lists lists_;
protected:
  GL_Object():modify_(0),need_save_(0),delete_(0),
	      visible_(1),selected_(0),redraw_2d_(1)
  {}

  ~GL_Object();
public:
  T* get_t() 
  {
    T* result = static_cast<T*>(this);
    return result;
  }
  void Serialize(CArchive& ar){
    BOOL flag;
    if(ar.IsLoading()){
      ar >> flag;
      if(flag)
				redraw_2d_ = 1;
      else
				redraw_2d_ = 0;
    }
    else{
      flag = need_redraw_2d();
      ar << flag;
    }
  }
  void clear_redraw_2d(){
    redraw_2d_ = 0;
    need_save_ = TRUE;
  }
  BOOL need_redraw_2d() { return redraw_2d_;}
  virtual void set_modify(BOOL modify) 
  { 
    modify_ = modify;
    if(modify_){
      set_need_save(TRUE);
      lists_.set_modify();
    }
  }
  BOOL is_modify() const { return modify_;}

  void set_need_save(BOOL save = FALSE) {
    need_save_ = save;
    if(need_save_)
      redraw_2d_ = 1;
  }
  BOOL is_need_save() const { return need_save_;}

  BOOL is_delete() const {return delete_;}
  void set_delete(BOOL bTrue) 
  {
    delete_ = bTrue;
    if(bTrue)
      need_save_ = TRUE;
  }

  void set_visible(BOOL visible) { visible_ = visible;}
  BOOL is_visible() const { return visible_;}
	
  BOOL is_select() const  { return selected_;}
  void set_select(BOOL bTrue) 
  {
    if(selected_ != bTrue)
      lists_.set_modify();
    selected_ = bTrue;
    if(!bTrue)
      get_t()->clear_pls_select();
  }
  void set_need_mklist()
  {
    lists_.set_modify();
  }
  BOOL draw()
  {
    T* t = get_t();
    if (!visible_ || delete_)
      return FALSE;
    if(modify_)
      {
	t->Modify();
	lists_.set_modify();
      }
    return TRUE;
  }
public:
  void clear_lists(CPlane& plane)
  {
    lists_.clear(plane);
  }
  void draw_3d(GLenum mode);
  void draw_section(GLenum mode,CPlane& plane,vector<CPt3D>& pts);
};
template<class T>
GL_Object<T>::~GL_Object()
{
}
template<class T>
void GL_Object<T>::draw_section(GLenum mode,CPlane& plane,vector<CPt3D>& pts)
{
  T* t = get_t();
  if(draw())
    lists_.draw_2d(t,plane,pts);

}
template<class T> 
void GL_Object<T>::draw_3d(GLenum mode)
{
  T* t = get_t();
  if(draw())
    lists_.draw_3d(t);
}
#endif
