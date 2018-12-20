// Transform_Func.h: interface for the Transform_Func class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_
#define AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_

#include "export.h"
#include <vector>
#include "../afc/counter.h"

namespace dlhml{

class Point;
typedef std::vector<Point> CPt3DVector;

class Normal;
class Matrix;
class OBJECT_API Transform_Func  
{
public:
	Transform_Func();
	~Transform_Func();

	//拆分弧为线段
	void divide_arc(const Point& center, const Point &start,
		const Point &end,const Normal& normal,int flatnum,CPt3DVector& dest);
	//得到弧上的下一个点
	void next_arc_pt(const Point &center, const Point &pos, 
						Point &next, const Normal& normal,Float angle);

	Float sin(Float x);
	Float cos(Float x);

	//得到平面法线向量
	Normal get_plane_normal(const Point& pt1,const Point& pt2, const Point& pt3);

	//三点是否在一直线上
	bool pt_in_line(const Point& pt1,const Point& pt2, const Point& pt3);

	//圆弧的夹角
	Float arc_angle(const Point& center, const Point &start,
		const Point &end,const Normal& normal);


	//以圆点为起点，终点在y轴正方向上的向量，经x-alpha,y-beta旋转至normal
	void rotation_normal_angle(const Normal& normal, Float& alpha, Float& beta);
	//确定两向量的变换所需矩阵
	void normal_matrix(const Normal& normal, Matrix& mat);
	//两任意向量的变换矩阵
	void noraml_to_normal_matrix(const Normal& src, const Normal& dest, Matrix& mat);

	//坐标系转换矩阵
	void coord_transform_mat(Matrix& mat,const Point& destO,
		const Normal& destOX,const Normal& destOY,const Normal& destOZ);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_)
