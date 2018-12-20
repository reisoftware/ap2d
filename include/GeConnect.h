// GeConnect.h: interface for the CGeBolt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GECONNECT_H__5D50A8E8_023D_4B94_B6BC_775D1C02C2A0__INCLUDED_)
#define AFX_GECONNECT_H__5D50A8E8_023D_4B94_B6BC_775D1C02C2A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pt4d.h"
#include "Norm_Cut.h"
#include "Vertex_Cut.h"
#include "gebolts.h"
#include "ReiGlobal.h"
#ifdef AFX_DATA
#undef AFX_DATA
#endif
#define	AFX_DATA AFX_EXT_DATA

#define PL_NEED_NUM  0x00000001
#define PL_NEED_DRAW 0X00000002
class CGeNorm;
class CModel;
class CJoint;
class CMember;
class CGeMem;
class CGeJnt;
class CGlFont;
class CPlane;
class CGeAxis;

namespace apcad{
  class Polygon;
  class Surface;
  class Transform_Base;
}

typedef std::vector<Pt4D> CPt4DVector;

class AFX_EXT_CLASS CGePlate:public GeBolts 
{
public:
  int owner() const;
  void owner(int index);
  const CString& name() const;
  void name(const CString& str);
  const CString& prefix() const;
  void prefix(const CString& str);
  const CString& material() const;
  void material(const CString& str);
  const CString& custom() const;
  void custom(const CString& str);
  const CString& guid() const;
  void guid(const CString& str);

  double w() const;
  double h() const;
  double t() const;
  void w(double val);
  void h(double val);
  void t(double val);

	BOOL need_num() { return flags_ & PL_NEED_NUM;}
	BOOL need_draw() { return flags_ & PL_NEED_DRAW;}
	void set_need_num() { flags_ |= PL_NEED_NUM;}
	void set_need_draw() { flags_ |= PL_NEED_DRAW;}
	
	void clear_need_draw() { flags_ &= ~PL_NEED_DRAW;}
public:
  CGePlate();
	void clear_need_num() { flags_ &= ~PL_NEED_NUM;}

  virtual ~CGePlate();
	
  void Load(CString sPath);
  void Save(CString sPath);
  BOOL UserEdit();
  void Serialize(CArchive &ar);

  double get_thick() const { return thick;}

  BOOL get_normal(CGeNorm& normal) const;
  apcad::Polygon get_polygon() const;
  void get_polygons(std::vector<apcad::Polygon>& polygons) const;
  void get_holes_polygon(std::vector<apcad::Polygon>& polygons) const;
	
  void get_surfaces(std::vector<apcad::Surface>& surfaces);
  void get_hole_surface(std::vector<apcad::Surface>& surfaces) const;
	void get_front_hole(apcad::Surface& surface) ;
	void get_back_hole(apcad::Surface& surface);

  CPt4DVector& get_vertexs() { return pts;}
  Pt4D get_vertex(int index) const;
  int get_vertexs_size() const;
  void AddVertex(CPt3D& pt,BOOL bArc = FALSE);
  void add_vertex(int begin,int end,const Pt4D& pt);
  void del_vertex(int index);
  void round_angle(int index,double r);
  void bolt_angle(int index,double r);
  void unround(int index);
  void move_vertex(int index,const CPt3D& pt);

  void add_inner(CPt4DVector& inner);
  void set_outer(CPt4DVector& outer);

  CGeNorm GetFrontBack(CPt4DVector& front,CPt4DVector& back);
	
  void transform(apcad::Transform_Base& transform_base);
  CPt3D get_near_pt(CPt3D& pt,CPlane& plane);
  void draw_section(CPlane& plane,vector<CPt3D>& pts);
  void draw_3d(GLfloat color[]);
	
  void enable_select(BOOL bTrue) { selected_  = bTrue;}
  BOOL select_state() const {return selected_;}

  void add_norm_cut(const Norm_Cut& cut);
  void clear_norm_cut();

  void modify(const CPt3D& pt1,const CPt3D& pt2,const CPt3D& pt3);

  const vector<Norm_Cut>& get_norm_cuts() const { return norm_cuts_;}
private:
  CPt4DVector pts;
  BOOL selected_;

  vector<Norm_Cut> norm_cuts_;
  vector<Vertex_Cut> vertex_cuts_;
  vector<CPt4DVector> inners_;
	DWORD flags_;//need_num need_draw

  int iMemNum; // 依附构件编号
  CString sName;//板的编号
  CString preFix;//编号前缀
  CString sMat;//材质
  CString sCutom;//自定义,需要保存
  CString sGuid;

  double width;
  double height;
  double thick;

  void draw_2D(CPt3DVector& pts,CPlane& plane,vector<CPt3D>& sect_pts);
  void draw_intersect(CPt3DVector& pts,CPlane& plane,vector<CPt3D>& sect_pts);
  void draw_section(CPt3DVector& pts,CPlane& plane,vector<CPt3D>& sect_pts);
	
  BOOL get_axis(CGeAxis& axis);

  void drag_polygon(const apcad::Polygon& polygon,vector<apcad::Surface>& surfaces) const;

};
typedef vector<CGePlate> CGePlateVector;
class AFX_EXT_CLASS CGeConnect  
{
public:
  void Clear();
  void RotateZ(double beta,CJoint* pJnt);
  void RecalPlate(CGeNorm *pNormal, CPt3D *lpPt);
  void AddPlate(CGePlate& plate);
  void Draw3D(float cr[3]);
  void draw_section(CPlane& plane,vector<CPt3D>& pts,BOOL highlight);
  void append(const CGePlateVector& pls);
  int size() const;
	void set_modify();
  CGeConnect();
  ~CGeConnect();
private:	
  CGePlateVector plateVector;//板的数组
  friend class CJoint;
};

#undef AFX_DATA
#define AFX_DATA
#endif // !defined(AFX_GECONNECT_H__5D50A8E8_023D_4B94_B6BC_775D1C02C2A0__INCLUDED_)
