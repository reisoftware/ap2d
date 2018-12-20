
// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMEMBER_429FBB8102EE_INCLUDED
#define _INC_CMEMBER_429FBB8102EE_INCLUDED

#include "reiglobal.h"
#include "genorm.h"
#include "hbeam_cut.h"
#include "geconnect.h"
#include "gl_object.h"
#include "gebolts.h"
#include "../include/node.h"
#include "../include/hole.h"
#define ELEMENT_COLUMN    0x00000001  //column
#define ELEMENT_BEAM			0x00000002  //beam
#define ELEMENT_BRACE			0x00000004  //brace
#define ELEMENT_HORBAR    0x00000008  //horizontal bar(heng/dong cha etc.)

#define C_COLUMN          0x00000010 //大柱
#define P_COLUMN					0x00000020 //中柱
#define G_BEAM            0x00000040 //大梁
#define B_BEAM            0x00000080 //小梁
#define DP_BEAM           0x00000100 //胴缘
#define T_BEAM            0x00000200 //行架
#define S_MEM             0x00000400 //其他构件

#define TYPE_FLAG         0xFFFFF00F

#define NO_MODIFY					0x00010000
#define PART_MODIFY				0x00020000
#define COMPO_NEEDDRAW		0x00040000
#define PART_NEEDDRAW			0x00080000
#define STATE_FLAG				0xFFF0FFFF

struct REISECT;
class CModel;
/*
#define SECTION_H     1
#define SECTION_TUB   2
#define SECTION_PIP   3

//member类中定义cut_start和cut_end两个变量，分别表示两端的切割情况
typedef struct _member_cut 
{
  int sectType;//截面类型：H型、方管、圆管
  int cutType; //H型钢依次6种，方管1种，圆管1种
  double topCutLen;//上翼缘切割长度（切点至构件端的距离）
  double topWebCutHeight;//上翼缘边腹板切割高度（圆形切割时为半径）
  double topWebCutLen;//上翼缘边腹板切割宽度
  double topWebCutHeight2;//上翼缘边腹板切割斜口高和宽（对H第四种）

  double midCutLen;//腹板中部切口最深处到原构件端的长度
  double midCutPos;//中部切割中心到上边沿距离
  double midCutHeight;//中部切割高
  double midCutDepth;//中部切割口深

  double botCutLen;//下翼缘切割长度
  double botWebCutHeight;//下翼缘边腹板切割高度（圆形切割时为半径）
  double botWebCutLen;//下翼缘边腹板切割宽度
  double botWebCutHeight2;//下翼缘边腹板切割斜口高和宽（对H第四种）
}Member_Cut, *LPMember_Cut;

void member_get_cut_start(void* member, LPMember_Cut lpCutStart)
{
  CMember* mem = (CMember*)member;
  lpCutStart = &(mem->cut_start);
}

void member_get_cut_end(void* member, LPMember_Cut lpCutEnd)
{
  CMember* mem = (CMember*)member;
  lpCutEnd = &(mem->cut_end);
}
*/
class AFX_EXT_CLASS CMember:public GL_Object<CMember>//,public GeBolts
{
  friend class GL_Object<CMember>;
  friend class Gl_List;
  friend class CModel;
  typedef vector<int> INTARRAY;
 public:
  class AFX_EXT_CLASS Node_Ary{
    std::vector<int> nds_;
  public:
    int GetSize() const;
    int& operator[](int index);
    int const&  operator[](int index) const;
    void RemoveAll();
    void Add(int val);
    void erase(int index);
  };

 public:
	virtual void set_modify(BOOL modify);

  CString name() const;
  CString no() const;
  CString part_no() const;
  CString custom_no() const;
  CString no_prefix() const;
  CString part_prefix() const;
  CString section() const;
  CString material() const;

  CPt3D get_offset(int index) const;
  void set_offset(int index,const CPt3D& pt);
  CGePlateVector& plates();
  float color(int index) const;
  void color(int index,float val);

  void name(const CString& str);
  void no(const CString& str);
  void part_no(const CString& str);
  void custom_no(const CString& str);
  void no_prefix(const CString& str);
  void part_prefix(const CString& str);
  void section(const CString& str);
  void material(const CString& str); 

  int get_index() const { return index_;}
  int get_parent() const { return parent_;}
  void set_parent(int index) { parent_ = index;}
  void set_parent(CMember* mem) { parent_ = mem->index_;}
  double get_beta() const { return beta_;}
  void set_beta(double beta) { beta_ = beta;set_modify(TRUE);}
  void set_type(DWORD dwType)	{	type_ = dwType;	}
  DWORD get_type() const { return type_;}

 public:
	 int set_from_str(char* out);
	 int get_str(char* out);
  void move_nd(CPt3D& pt1,CPt3D& pt2);
  void assign(const CMember& mem);
  BOOL is_cut() const;
  BOOL edit_cut();
  void set_cut(HBeam_Cut& cut);

  void select_plate(int index);
  HBeam_Cut GetMemCut() const;

  void mirror_plane(CGeNorm& normal,CPt3D const& pt);
  void Move(double len, CGeNorm* pNorm);
  void offset(double len,CGeNorm* normal);
  void SetOffset(LPNODE lpNd, CPt3D& pt);
  double GetSteelLen() const ;
  BOOL AddNode();
  CPt3D GetBase(LPNODE lpNd);
  CGeNorm GetNorm(LPNODE lpNd);

  void ModifyOffset(LPNODE lpNd, CPt3D* lpPt);
  BOOL IsNormalZ(LPNODE lpNd);
  BOOL IsNormal(LPNODE lpNd, CGeNorm* pNorm);

  void SetEnd(int iNum);
  void SetStart(int iNum);
  void Divide(int nSeg, BOOL bCut, INTARRAY& iNodeAry);
  void Serialize(CArchive& ar);
  int SetEnd(NODE& nd);
  int SetStart(NODE& nd);
  CPt3D get_real_start() const;
  CPt3D get_real_end() const;

  LPNODE GetEnd(CModel* model=NULL) const;
  LPNODE GetStart(CModel* model=NULL) const;
  REISECT GetSection() const;

	BOOL no_modify() const { return type_ & NO_MODIFY;}
	BOOL part_no_modify() const { return type_ & PART_MODIFY;}
	BOOL compo_need_draw() const { return type_ & COMPO_NEEDDRAW;}
	BOOL part_need_draw() const { return type_ & PART_NEEDDRAW;}

	void clear_part_draw() { type_ &= ~PART_NEEDDRAW;set_need_save(TRUE);}
	void clear_compo_draw() { type_ &= ~COMPO_NEEDDRAW;set_need_save(TRUE);}

  void draw_plates();
  CMember();
  ~CMember();
  CPt3D get_near_pt(CPt3D pt,CPlane& plane);	
 private:
	void set_part_modify() { type_ |= PART_MODIFY;set_need_save(TRUE);}
	void set_part_draw() { type_ |= PART_NEEDDRAW;set_need_save(TRUE);}
	void clear_no_modify() { type_ &= ~NO_MODIFY;set_need_save(TRUE);}
	void clear_part_modify() { type_ &= ~PART_MODIFY;set_need_save(TRUE);}

  void draw_2d(CPlane& plane,vector<CPt3D>& pts);
  void DrawNode3D(GLenum mode);
  void draw_node(LPNODE nd,BOOL bStart) const;
  void draw_node_3D(CPlane& plane,vector<CPt3D>& pts) const;
  void clear_pls_select();
  void Modify();
  void MakeList();
 private:
  HBeam_Cut cut_;
  int index_;
  int parent_;

  double beta_;
  DWORD type_;
  CString name_;
  CString no_;//构件号    //不能复制
  CString part_no_;//部品号//不能复制
  CString custom_no_;//构件自定义编号
  CString prefix_;// 构件号前缀
  CString part_prefix_;//部品号前缀
  CString section_;
  CString material_;//材质
  Node_Ary nodes_;

  float fColor[3];//显示颜色
  CPt3D mOffset[2];
  CGePlateVector plates_;//板的数组
  
  friend AFX_EXT_API BOOL set_no_modify(CMember* mem,void* parm);// { type_ |= NO_MODIFY;set_need_save(TRUE);}
  friend AFX_EXT_API BOOL set_compo_draw(CMember* mem,void* parm);// { type_ |= COMPO_NEEDDRAW;set_need_save(TRUE);}
};

extern "C" AFX_EXT_API BOOL IsAssemble_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsC_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsP_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsG_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsB_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsDP_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsT_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL IsS_Mem(const CMember& mem);
extern "C" AFX_EXT_API BOOL Is_COLUMN(const CMember& mem);
extern "C" AFX_EXT_API BOOL Is_BEAM(const CMember& mem);
extern "C" AFX_EXT_API BOOL Is_BRACE(const CMember& mem);

extern "C" AFX_EXT_API void SetMemType_C(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_P(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_G(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_B(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_DP(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_T(CMember& mem);
extern "C" AFX_EXT_API void SetMemType_S(CMember& mem);
extern "C" AFX_EXT_API void ClearMemType(CMember& mem);
#endif 
