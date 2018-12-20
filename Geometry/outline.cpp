#include "StdAfx.h"
#include "outline.h"
#include "SLine.h"
#include "calculate.h"
#include "calculate2.h"

#include <list>
#include <fstream>
#include <cassert>

#include "../afc/dir.h"

namespace geo{



//////////////////////// << output link table >> //////////////////////////
static void output(std::ofstream& ofs, Link& o)
{
  ofs << o.pt_ << "-->";
  std::list<int>::iterator it = o.lks_.begin();
  for(; it != o.lks_.end(); ++it){
    ofs << *it << ",";
  }
  ofs << "\n";
}

static bool output(Link_Table& lt)
{
  std::string exe_path = afc::dir::exe_path();
  std::string txt_file = exe_path + "outline_link_table.txt";
  std::ofstream ofs(txt_file.c_str());
  if(!ofs.is_open()){
    return false;
  }
  int n=lt.dat_.size();
  int i=0;
  for(i=0; i<n; ++i){
    output(ofs, lt.dat_[i]);
  }
  ofs.close();
  return true;
}

//////////////////////// << output rgs >> //////////////////////////
static void output(std::ofstream& ofs, const Point& pt)
{
  ofs << "[" << pt.x << ", " << pt.y << "]; ";
}

static void output(std::ofstream& ofs, Ring& rg)
{
  int n=rg.pts.size();
  int i=0;
  for(i=0; i<n; ++i){
    output(ofs, rg.pts[i]);
  }
}

static bool output(std::vector<Ring>& rgs)
{
  std::string exe_path = afc::dir::exe_path();
  std::string txt_file = exe_path + "outline_rings.txt";
  std::ofstream ofs(txt_file.c_str());
  if(!ofs.is_open()){
    return false;
  }
  int n=rgs.size();
  int i=0;
  for(i=0; i<n; ++i){
    ofs << i <<": ";
    output(ofs, rgs[i]);
    ofs << "\n";
  }
  ofs.close();
  return true;
}

//////////////////////// << output rgs >> //////////////////////////
static void output(std::ofstream& ofs, SLine& ln)
{
  output(ofs, ln.pt1);
  output(ofs, ln.pt2);
  ofs << "\n";
}


static bool output(std::vector<int>& lns, std::string tip)
{
  std::string exe_path = afc::dir::exe_path();
  std::string txt_file = exe_path + "outline_";
  txt_file += tip;
  txt_file += ".txt";
  std::ofstream ofs(txt_file.c_str());
  if(!ofs.is_open()){
    return false;
  }
  ofs << tip << "\n";
  int n=lns.size();
  int i=0;
  for(i=0; i<n; ++i){
    ofs << i <<": ";
    ofs << lns[i] << "\n";
  }
  ofs.close();
  return true;
}

//////////////////////// << fill_link_table >> //////////////////////////
////若有重复，不在压入
static int push_pts(const Point& pt, std::vector<Point>& pts)
{
  int n=pts.size();
  int i=0;
  for(i=0; i<n; ++i){
    if(pts[i] == pt){
      return i;
    }
  }
  pts.push_back(pt);
  return i;
}

////把pt加入到lk链中（如果lk链不存在，新建）
static void push_link_table(int lk, int pt, Link_Table& lt)
{
  int n=lt.dat_.size();
  int i=0;
  for(i=0; i<n; ++i){
    if(lt.dat_[i].pt_ == lk){
      lt.dat_[i].lks_.push_back(pt);
      return;
    }
  }
  Link the;
  the.pt_ = lk;
  the.lks_.push_back(pt);
  lt.dat_.push_back(the);
}

static void push_link_table(const SLine& src, 
                            Link_Table& lt)
{
  int pos1 = push_pts(src.pt1, lt.pts_);
  int pos2 = push_pts(src.pt2, lt.pts_);
  push_link_table(pos1, pos2, lt);
  push_link_table(pos2, pos1, lt);
}


static void fill_link_table(const std::vector<SLine>& src, 
                            Link_Table& lt)
{
  int n=src.size();
  int i=0;
  for(i=0; i<n; ++i){
    push_link_table(src[i], lt);
  }
}

//////////////////////// << get_rings >> //////////////////////////
////如果只有2个以内的点，不能成多边形
static void get_ring(const Link_Table& lt, std::vector<int>& temp, int pos, Ring& rg)
{
  int n=temp.size();
  if(n-pos <= 2){
    return;
  }
  int i=0;
  for(i=pos; i<n; ++i){
    int pt = temp[i];
    rg.pts.push_back(pt); 
//     Point pt = lt.pts_[temp[i]];
//     rg.pts.push_back(pt); 
  }
}

static int push(std::vector<int>& temp, int pt)
{
  int n=temp.size();
  int i=0;
  for(i=0; i<n; ++i){
    if(temp[i] == pt){
      return i;
    }
  }
  temp.push_back(pt);
  return -1;
} 

void Link::entry(const Link_Table& lt, 
                 std::vector<int>& temp, 
                 std::vector<Ring>& rgs)const
{
  int pos = push(temp, pt_);
  if(pos != -1){
    Ring rg;
    get_ring(lt, temp, pos, rg);
    if(rg.pts.empty()){
      return;
    }
    rgs.push_back(rg);
    return;
  }

  std::list<int>::const_iterator it = lks_.begin();
  for(; it != lks_.end(); ++it){
    lt.dat_[*it].entry(lt, temp, rgs);
  }
  temp.pop_back();
}

void Link_Table::get_rings(std::vector<Ring>& rgs)const
{
  int n=dat_.size();
  int i=0;
  for(i=0; i<n; ++i){
    std::vector<int> temp;
    dat_[i].entry(*this, temp, rgs);
  }
}

//////////////////////// << get_outer >> //////////////////////////
////prev_pt == -1, 表示不需要
int Link::get_min_degree_pt(const Link_Table& lt, int prev_pt)const
{
  Float min_deg = 360;
  int min_id = 0;
  std::list<int>::const_iterator it = lks_.begin();
  for(; it != lks_.end(); ++it){
    Float it_deg = 0;
    if(prev_pt == -1){
      it_deg = geo::get_degree(lt.pts_[pt_], lt.pts_[*it]);
    }else{
      it_deg = geo::get_degree(lt.pts_[pt_], lt.pts_[prev_pt], lt.pts_[*it]);
    }
    if(min_deg > it_deg){
      min_deg = it_deg;
      min_id = *it;
    }
  }
  return min_id;
}

////prev_pt == -1, 表示不需要
void Link::get_outer(const Link_Table& lt, std::vector<int>& temp, Ring& rg, int prev_pt)const
{
  int pos = push(temp, pt_);
  if(pos != -1){
    get_ring(lt, temp, pos, rg);
    return;
  }

  int min_id = 0;
  if(prev_pt == -1){
    min_id = get_min_degree_pt(lt, -1);
  }else{
    min_id = get_min_degree_pt(lt, prev_pt);
  }
  lt.dat_[min_id].get_outer(lt, temp, rg, pt_);
}

void Link_Table::get_outer(Ring& rg)const
{
  std::vector<int> temp;
  int rb_pt = geo::rightdown_pt2d(pts_);  ////最右下的点
  assert(rb_pt >= 0);
  assert(rb_pt < dat_.size());
  dat_[rb_pt].get_outer(*this, temp, rg, -1);
}

//////////////////////// << max ring >> //////////////////////////
static bool output_area(const Ring& rg)
{
  std::string exe_path = afc::dir::exe_path();
  std::string txt_file = exe_path + "outline_area.txt";
  std::ofstream ofs(txt_file.c_str());
  if(!ofs.is_open()){
    return false;
  }
  ofs << "rg: ";
  int n=rg.pts.size();
  int i=0;
  for(i=0; i<n; ++i){
    output(ofs, rg.pts[i]);
  }
  ofs.close();
  return true;
}

void Link_Table::ring_pts(const Ring& rg, std::vector<Point>& pts)const
{
  int n=rg.pts.size();
  int i=0;
  for(i=0; i<n; ++i){
    Point pt = pts_[rg.pts[i]];
    pts.push_back(pt);
  }
}


Float Link_Table::ring_area(const Ring& rg)const
{
  if(rg.pts.size() <= 2){
    return 0;
  }
  assert(output_area(rg));
  std::vector<Point> pts;
  ring_pts(rg, pts);
  Float it_area = get_area(pts);
  return it_area;
}

int Link_Table::max_ring(std::vector<Ring>& rgs)const
{
  double max_area = 0;
  int max_id = -1;
  int n=rgs.size();
  int i=0;
  for(i=0; i<n; ++i){
    Float it_area = ring_area(rgs[i]);
    if(max_area < it_area){
      max_area = it_area;
      max_id = i;
    }
  }
  return max_id;
}

//////////////////////// << outer other >> //////////////////////////
bool Link_Table::is_in(const SLine& ln, const Ring& rg)const
{
  int n=rg.pts.size();
  int i=0;
  for(i=0; i<n; ++i){
    SLine it_ln(pts_[rg.pts[i]], pts_[rg.pts[(i+1)%n]]);
    if(it_ln == ln){
      return true;
    }
  }
  return false;
}

////在src里找出外轮廓（rg的边），放入outer，其他放入other
static void identify(const Link_Table& lt,
                     const Ring& rg, 
                     const std::vector<SLine>& src, 
                     std::vector<int>& outer, 
                     std::vector<int>& other)
{
  int n=src.size();
  int i=0;
  for(i=0; i<n; ++i){
    if(lt.is_in(src[i], rg)){
      outer.push_back(i);
    }else{
      other.push_back(i);
    }
  }
}

//////////////////////// << main >> //////////////////////////
bool outline(const std::vector<SLine>& all, 
              std::vector<int>& outer, 
              std::vector<int>& other)
{
	if(all.empty())
		return false;
  assert(!all.empty());
  Link_Table lt;
  fill_link_table(all, lt);
  assert(output(lt));

  std::vector<Ring> rgs;
  lt.get_rings(rgs);
  if(rgs.empty()){
    return false;
  }
  assert(output(rgs));
  int max_id = lt.max_ring(rgs);
  assert(max_id >= 0 && max_id < rgs.size());
  identify(lt, rgs[max_id], all, outer, other);
//   Ring rg;
//   lt.get_outer(rg);
//   identify(rg, src, outer, other);

  assert(output(outer, "outer"));
  assert(output(other, "other"));
	return true;
} 



}//namespace
