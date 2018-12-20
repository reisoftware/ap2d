// AxisRoot.h: interface for the CAxisRoot class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_AXISROOT_H__8F4D8EF5_A4A7_4FE0_8E1C_F4E4879B8EBC__INCLUDED_)
#define AFX_AXISROOT_H__8F4D8EF5_A4A7_4FE0_8E1C_F4E4879B8EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef AFX_DATA
#undef AFX_DATA
#endif
#define	AFX_DATA AFX_EXT_DATA


#include "ReiGlobal.h"
#include "Gl_Dc_Imp.h"

#include "GeNorm.h"
#define X_AXIS		0
#define Y_AXIS		1
#define Z_AXIS		2

class CModel;
class CPt3D;
class gelib::Gl_Dc_Imp;
class CPlane;
class AFX_EXT_CLASS CAxisRoot  
{
private:
	int xNum;
	int yNum;
	int nFloor;
public:
	typedef std::vector<double> AXIS_VAL;
	
	AXIS_VAL pXdis;
	AXIS_VAL pYdis;
	AXIS_VAL pFloorHeight;
	
private:
	BOOL visible_;// 是否隐藏轴线
	BOOL need_save_;
	BOOL delete_;
	COLORREF cl;
	
	CString name_;//轴网名称
	CString strLabelX;//x轴线字符，采用空格区分轴线标签
	CString strLabelY;//y轴线字符
	CString strLabelZ;//z轴线字符
	CString x_;
	CString y_;
	CString z_;
	
	int index_;
	CGeNorm normal_;
	CPt3D pt_;
	CGeAxis axis_;
public:
	CAxisRoot();
	~CAxisRoot();
	
	int get_index() const { return index_;}
	void set_index(int index) { index_ = index;need_save_ = TRUE;}
	double get_max_y() const;
	double get_max_z() const;
	double get_max_x() const;
	int get_nFloor() const;
	int get_xNum() const;
	int get_yNum() const;
	
	double get_beta();
	void set_center_beta(CPt3D pt,double beta);
	void set_center_beta(CPt3D pt1,CPt3D pt2);
	CString get_name()const { return name_;}
	void set_name(CString& name) { name_ = name;need_save_ = TRUE;}
	BOOL is_delete() const { return delete_;}
	void set_delete(BOOL bTrue) { delete_ = bTrue;}
	
	
	BOOL visible() const { return visible_;}
	
	BOOL is_need_save() { return need_save_;}
	void set_need_save(BOOL need_save) { need_save_ = need_save;}
	void set_visible(BOOL visible)
	{
		visible_ = visible;
	}
	void set_color(COLORREF r)
	{
		cl = r;
		need_save_ = TRUE;
	}
	void get_str(CString& x,CString& y,CString& z) const
	{
		x = x_; y = y_; z = z_;
	}
	void set_str(CString& x,CString& y,CString& z)
	{
		x_ = x; y_ = y; z_ = z;
		need_save_ = TRUE;
	}
	void get_lable(CString& x,CString& y,CString& z) const
	{
		x = strLabelX; y = strLabelY; z = strLabelZ;
	}
	void set_lable(CString& x,CString& y,CString& z)
	{
		strLabelX = x; strLabelY = y; strLabelZ = z;
		need_save_ = TRUE;
	}
public:
	void get_str(char* out);
	void set_from_str(char* out);
	void Serialize(CArchive &ar);
	void GetAxisLableFromStr(CString strRes,CStringArray& strAry);
	void SetData();
	void Draw3D(gelib::Gl_Dc_Imp &dc,CPlane& plane,int type);
	void get_nodes(CPlane& plane,int type,std::vector<CPt3D>& ids);
private:
	
	void draw_line(CPt3D pt1,CPt3D pt2,char *  str,gelib::Gl_Dc_Imp &dc);
	void draw_xy(gelib::Gl_Dc_Imp& dc,CPlane& g_plane);
	void draw_xz(gelib::Gl_Dc_Imp& dc,CPlane& g_plane);
	void draw_zy(gelib::Gl_Dc_Imp& dc,CPlane& g_plane);
	
	void get_xy_nodes(CPlane& g_plane,std::vector<CPt3D>& ids);
	void get_xz_nodes(CPlane& g_plane,std::vector<CPt3D>& ids);
	void get_zy_nodes(CPlane& g_plane,std::vector<CPt3D>& ids);
	//for local axis
	
	void DrawBorder(float xLen,float yLen,float zLen);
	
	void clearAll();
	void initStr(CString& strX, CString& strY, CString& strZ);
	void FormatStars(CString& str);
	void FormatStr(CString& str );
	void initData(CString& str, AXIS_VAL& pFloat, int& num);
	void l_2_g(CPt3D& pt);
	void g_2_l(CPlane& g,CPlane& l);
	
	
};


#undef AFX_DATA
#define AFX_DATA
#endif // !defined(AFX_AXISROOT_H__8F4D8EF5_A4A7_4FE0_8E1C_F4E4879B8EBC__INCLUDED_)
