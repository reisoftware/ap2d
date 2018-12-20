#ifndef _GEOMETRY_OUTLINE_H_
#define _GEOMETRY_OUTLINE_H_

#include "export.h"
#include "Float.h"
#include <vector>
#include <list>


namespace geo{

class SLine;
class Point;

GEOAPI bool outline(const std::vector<SLine>& all, 
                    std::vector<int>& outer, 
                    std::vector<int>& other);


class Link_Table;

struct Ring
{
  std::vector<int> pts;
};

class Link
{
public:
  int pt_;
  std::list<int> lks_;
  
public:
  void entry(const Link_Table& lt, std::vector<int>& temp, std::vector<Ring>& rgs)const;
  ////prev_pt == -1, 表示不需要
  void get_outer(const Link_Table& lt, std::vector<int>& temp, Ring& rg, int prev_pt)const;
  
public:
  ////prev_pt == -1, 表示不需要
  int get_min_degree_pt(const Link_Table& lt, int prev_pt)const;
};

class Link_Table
{
public:
  std::vector<Point> pts_;
  std::vector<Link> dat_;
  
public:
  void get_rings(std::vector<Ring>& rgs)const;
  void get_outer(Ring& rg)const;

public:
  Float ring_area(const Ring& rg)const;
  void  ring_pts(const Ring& rg, std::vector<Point>& pts)const;
  int max_ring(std::vector<Ring>& rgs)const;
  bool is_in(const SLine& ln, const Ring& rg)const;
  
};


}//namespace

#endif//FILE
