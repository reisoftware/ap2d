#ifndef _gl_lists_hpp_
#define _gl_lists_hpp_
#include <vector>
#include "gl_list.hpp"
class CPlane;
class CPt3D;
class AFX_EXT_CLASS Gl_Lists{
  typedef std::vector<Gl_List*> LISTS;
  typedef LISTS::iterator iterator;
  LISTS lists_;
  iterator find(CPlane* plane);
public:
  Gl_Lists();
  ~Gl_Lists();
  Gl_Lists(const Gl_Lists& rhs);
  Gl_Lists& operator=(const Gl_Lists& rhs);
  void set_modify();
  void clear(CPlane& plane);
  template<class T>
  void draw_3d(T* t)
  {
    iterator it = find(0);
    Gl_List* gl_list = NULL; 
    if(it != lists_.end())
      gl_list = *it;
    else{
      gl_list = new Gl_List(0);
      lists_.push_back(gl_list);
    }
      
    gl_list->draw_3d(t);
  }

  template<class T>
  void draw_2d(T* t,CPlane& plane,std::vector<CPt3D>& pts)
  {
    iterator it = find(&plane);
    Gl_List* gl_list = NULL; 
    if(it != lists_.end())
      gl_list = *it;
    else{
      gl_list = new Gl_List(&plane);
      lists_.push_back(gl_list);
    }
      
    gl_list->draw_2d(t,plane,pts);
  }
};
#endif
