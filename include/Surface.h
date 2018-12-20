#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Polygon.h"
#include <vector>
namespace apcad{
  class Transform_Base;
  class AFX_EXT_CLASS Surface{
  private:
    Polygon outer_;
    vector<Polygon> inner_;

    void line_frame();
    void render();
  public:
    Polygon& get_outer() { return outer_;}
    vector<Polygon>& get_inner() { return inner_;}
    void draw_3d(BOOL lineframe);
    void set_outer(Polygon& outer);
    void add_inner(Polygon& inner);
    Surface(const vector<Pt4D>& outer,const vector<vector<Pt4D> >& inner);
    Surface() {}
    Surface(const Polygon& outer):outer_(outer) {}
    void transform(Transform_Base& transform_base);
    bool minus(const Polygon& cut);
    BOOL intersect(const Polygon& cut,Line& line);
  };

}
#endif
