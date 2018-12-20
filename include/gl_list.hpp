#ifndef _gl_list_hpp_
#define _gl_list_hpp_
#include <vector>
#include "pt3d.h"
class CPlane;
class AFX_EXT_CLASS  Gl_List{
  GLuint list_name_;
  CPlane* plane_;
  BOOL modify_;
  std::vector<CPt3D> pts_;
  BOOL need_mklist();
  void call_list();
  Gl_List(const Gl_List&);
  Gl_List& operator =(const Gl_List&);
  int i;
public:
  explicit Gl_List(CPlane* plane);
  ~Gl_List();
  BOOL operator ==(const Gl_List& rhs) const;
  void set_modify();
  template<class T>
  void draw_3d(T* t)
  {
    if(need_mklist()){
      glNewList(list_name_, GL_COMPILE);
      t->MakeList();
      glEndList();
    }
    call_list();
  }

  template<class T>
  void draw_2d(T* t,CPlane& plane,vector<CPt3D>&pts)
  {
    if(need_mklist()){
      glNewList(list_name_,GL_COMPILE);
      pts_.clear();
      t->draw_2d(plane,pts_);
      glEndList();
    }
    call_list();
    copy(pts_.begin(),pts_.end(),back_inserter(pts));
  }

};
#endif
