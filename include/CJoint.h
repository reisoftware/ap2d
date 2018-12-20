// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CJOINT_429FBE1A035B_INCLUDED
#define _INC_CJOINT_429FBE1A035B_INCLUDED

#include "geconnect.h"
#include "geptr.h"
#include "jntbase.h"
#include "reiglobal.h"	
#include "gl_object.h"

#include "../include/node.h"
#ifdef AFX_DATA
#undef AFX_DATA
#endif
#define	AFX_DATA AFX_EXT_DATA

#define HORBAR_BREAK		0x00000004	//对于横杆在与柱子连接节点处断开
#define HORBAR_START		0x00000008  //此标志表示从基点到起点为节点的矢量方向
#define HORBAR_END      0x00000010  //
#define MANUAL_ADD      0x00010000  //手工加入的节点

#define JOINT_NEED_NUM  0x00001000
#define JOINT_NEED_DRAW 0X00002000

const int custom_jnt_type = 1000;

class CBolt;
class AFX_EXT_CLASS CJoint :public GL_Object<CJoint>
{
	friend class Gl_List;
	friend class GL_Object<CJoint>;
	friend class CModel;
	private:
	unsigned first_create_ ;

	GEXY::CPtr<CJntBase> lpJntBase;
	std::vector<int> mems_;
	CString memo_;
	DWORD type_;
	DWORD sub_type_;
	DWORD flags_;
	int index_;
	int base_nd_;	
	CGeConnect cnt_;
	CString no_; 
public:
	CJoint();
	~CJoint();

	CJoint(const CJoint& jnt);
	CJoint& operator = (const CJoint& jnt);

	virtual void set_modify(BOOL modify);

	void add_plate(const CGePlate& pl);
	void select_pl(int index);
	int get_base()const { return base_nd_;}
	void set_base(int num) { base_nd_ = num;}
	int get_index() const { return index_;}

	void set_type(DWORD type) { type_ = type;}
	void set_sub_type(DWORD type) { sub_type_ = type;}
	void add_flag(DWORD flag) { flags_ |= flag;}
	void remove_flag(DWORD flag) { flags_ &= ~flag;}

	DWORD get_type() const { return type_;}
	DWORD get_flags() const { return flags_;}


	BOOL assign(CJoint& jnt);
	void custom();

	void set_memo(CString memo);
	CString get_memo(CString memo) const;

	void set_jnt_name(CString sName);
	CString get_jnt_name() const;

	CGePlate* get_plate(int sub);
	void select_plate(int sub);
	void erase_plate(CGePlate* pl);

	BOOL HasMember(CMember *pMember);
	int GetMemCount() const;
	int get_member_no(int ary_index);
	CMember* GetMember(int aryIndex);
	void clear_mems();
	void add_mem(int mem_index);


	BOOL OnProperty(BOOL first=FALSE);
	LPNODE GetNodeBase();

	void Serialize(CArchive &ar);
	void draw_plates();

	BOOL CreateJntBase();

	void GetBolts(std::vector<CBolt>& bolts)  ;
	void unmodify_member() ;
	CPt3D get_offset(int mem_index);

	void set_first_create(BOOL bTrue){
		first_create_ = bTrue;
	}
	CGePlateVector& plates();

	BOOL need_num() const { return flags_ & JOINT_NEED_NUM;}
	BOOL need_draw() const { return flags_ & JOINT_NEED_DRAW;}
	void clear_need_draw() { flags_ &= ~JOINT_NEED_DRAW;set_need_save(TRUE);}
	void clear_need_num() { flags_ &= ~JOINT_NEED_NUM;set_need_save(TRUE);}
	private:
	void set_need_num() { flags_ |= JOINT_NEED_NUM;set_need_save(TRUE);}
	void set_need_draw() { flags_ |= JOINT_NEED_DRAW;set_need_save(TRUE);}

	void draw_2d(CPlane& plane,vector<CPt3D>& pts);
	void GetConnect();
	void clear_pls_select();
	BOOL is_bad();

	void MakeList();
	void Modify();
};


extern "C" AFX_EXT_API BOOL IsBoxJoint(const CJoint& jnt);
extern "C" AFX_EXT_API BOOL IsBaseJoint(const CJoint& jnt);
extern "C" AFX_EXT_API BOOL IsGjJoint(const CJoint& jnt);
extern "C" AFX_EXT_API BOOL IsGBJoint(const CJoint& jnt);
#undef AFX_DATA
#define AFX_DATA
#endif /* _INC_CJOINT_429FBE1A035B_INCLUDED */
