// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CMODEL_429D1F49004E_INCLUDED
#define _INC_CMODEL_429D1F49004E_INCLUDED

#include "AxisRoot.h"
#include "CMember.h"
#include "CJoint.h"
#include "ReiGroup.h"
#include "MemType.h"
#include "Mems.h"
#include "Jnts.h"
#include "Nodes.h"
#include "Model_geographic.h"
#include "Project_Info.h"
#include <set>
using std::set;
#ifdef AFX_DATA
#undef AFX_DATA
#endif

#define	AFX_DATA AFX_EXT_DATA

#define SELECT_NODE2 0x00000004
#define SELECT_NODE1 0x00000002 //select node
#define SELECT_NODE 0x00000001
#define SELECT_MEMBER 0x00000008
#define SELECT_JOINT 0x00000010
#define SELECT_PLATE 0x00000020
#define SELECT_NODES 0X00000040
#define MULTI_SELECT 0X00000080
#define SHOW_SELECT   0x00010000

typedef vector<int> INTVECTOR;
#include "pt3d.h"

#include "Plates.h"
#include "ap.h"
typedef BOOL (*BROWSER_MEM_PARENT)(CMember* mem,void* parm);

class AFX_EXT_CLASS CModel 
{
private:
  HGLRC model_hrc_;
  double fColLen[3];

  std::vector<CAxisRoot> nets_;
  typedef std::map<std::string,gelib::Model_Geographic> GEOS;
  GEOS geos_;
  Nodes delete_nodes_;
  GEOS del_geos_;
  Project_Info project_info_;
	AP ap_;
private:
  CMember cur_col_;
  CMember cur_beam_;
  CJoint cur_jnt_;
private:
  void erase_from_groups(int mem_index);
public:
  typedef vector<int> INTARRAY;

  Mems memberAry;
  Jnts jointAry;
  Nodes mNodeArray;
  GroupVector m_groupVector;
  Plates pls_;

  unsigned int get_mems_count() const;
  unsigned int get_jnts_count() const;
public:
  double get_max_x() ;
  double get_max_y() ;
  double get_max_z() ;

  void get_axis_nodes(CPlane& plane,int type,std::vector<CPt3D>& ids);
	
  void draw_axis(gelib::Gl_Dc_Imp &dc,CPlane& plane,int type);
  CAxisRoot& axisnet();
public:
  void clear_lists(CPlane& plane);
  Project_Info& get_project_info();
	

  void update_number_data(int index,LPCTSTR path);
  BOOL load_number_data(int index,LPCTSTR path);

  int new_drawing();
  void del_drawing(int id);
  void update_drawing(int id,LPCTSTR path);
  void get_drawings(LPCTSTR path);
public:
  void set_cur_col(const CMember& mem) { cur_col_ = mem;}
  void set_cur_beam(const CMember& mem) { cur_beam_ = mem;}
  void set_cur_jnt(CJoint* jnt) { cur_jnt_ = *jnt;}
  CJoint& get_cur_jnt() { return cur_jnt_;}
  int get_cur_jnt_mems() const { return cur_jnt_.GetMemCount();}
public:
  HGLRC get_hrc() const { return model_hrc_;}
  void set_hrc(HGLRC hrc) { model_hrc_ = hrc;}
public:
  void get_geos(vector<const char*>& geos);
public:
  ~CModel();
  CModel();
	
  template <class FUN> void LoopMember(FUN f) 
  {
    /*		memberAry.for_each(f);	*/
    for(int i =0; i < memberAry.GetSize(); ++i)
      {
	CMember* pMember = &memberAry[i];
	if(f(pMember) == 1)
	  break;
      }
	
  }
  template <class FUN> void LoopJoint(FUN f)
  {
    /*	jointAry.for_each(f);*/
    for(int i =0; i < jointAry.GetSize(); ++i)
      {
	CJoint* pJnt = &jointAry[i];
	if(f(pJnt) ==1)
	  break;
      }

  }

private:
  void del_geos();
  void GetAllEndNode(set<int>& iNodeSet);
  void laod_project_info();
  void save_project_info();
public:
  CMember* get_first_select_mem();

  void ListCutPlane();
  void add_cut_plane(const char* name,gelib::Model_Geographic& geo);
  gelib::Model_Geographic* get_geo(const char* name);

  void update_plane(gelib::Model_Geographic& geo);
  void make_plate(vector<CPt3D>& ary,double thick);
  BOOL GetMemsFromCutPlane(const CPlane& plane,INTVECTOR & memIndexs);
  void SelectByType(CMemType& memType);
  BOOL DesignLocalAxis();
  void ReDrawAll();
  void DelNode(int iNum);
  void Add2Group();
  void OnGroup();
  void DelGroup(string sName);
  void SelectGroup(CReiGroup* pGroup);
  void Add2Group(CReiGroup* pGroup);
  CReiGroup* AddGroup(string sName);
  CReiGroup* GetGroup(string sGroupName);
  void ChangeRenderType(BOOL bLinFrame);
	
  BOOL IsEndPt(int iNodeNum);
  void DeleteSelJnts();
	
  CJoint* AddJoint(CJoint& jnt);
  CJoint* AddJnt(vector<int> &ary);
  CJoint* add_gj(vector<int>& ary);
  CJoint* add_jb(vector<int> &ary);
  CJoint* add_box(vector<int> &ary);
  CJoint* add_base(vector<int> &ary);
  CJoint* add_jblib(int nd);
  CJoint* add_gjlib(int nd);

  CMember* AddMember(CMember& member);
  void DrawJnt3D(GLenum mode);
  CString strWorkPath;

  void load_from_server();
  void save_2_server();
  void connect_2_server();

  BOOL InputDlg();
  void Serialize(CArchive &ar);
  int AddNode(NODE& nd);
  int find_node(CPt3D pt) const;
  void SetShow(BOOL show_select);

  CMember* AddBrace(int iNum1,int iNum2);
  void DeleteSelMember();
  CMember* AddCol(int iNodeNum);
  CMember* AddBeam(int iNum1, int iNum2);
  void add_axis(CPt3D pt1,CPt3D pt2);
  void selectMember(INTARRAY &ary,DWORD dwSelType);
  void revers_select();
  void select_member(vector<int>& arys);
  void select_joint(vector<int>& arys);
  void draw_mem_plates();
  void DrawMem3D(GLenum mode);

  void hide_select();
public:
  CMember* get_cur_member() const;
  CMember* GetMemberByInt(int num);
  CMember* browser_main_mem(CMember* mem,void* parm,BROWSER_MEM_PARENT fun);
  void browser_main_mem(CJoint* jnt,void* parm,BROWSER_MEM_PARENT fun);
  CJoint* GetJointByInt(int index);
  LPNODE GetNodeByNum(int NodeNum);
public:
	void set_index(int index);
	int get_index();
	void new_model();
  void del(CMember* mem);
  void del(CJoint* jnt);
  void undel(CMember* mem);
  void undel(CJoint* jnt);
  void edit(CMember& mem);
  void edit(CJoint& jnt);
};

#undef AFX_DATA
#define AFX_DATA
#endif /* _INC_CMODEL_429D1F49004E_INCLUDED */
