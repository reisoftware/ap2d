// Transform_Func.cpp: implementation of the Transform_Func class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Transform_Func.h"
#include "Normal.h"
#include "Point.h"
#include <algorithm>
#include "Matrix_d.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Transform_Func::Transform_Func()
MCT_INIT1("Transform_Func")
{

}

Transform_Func::~Transform_Func()
{

}
/*
 *将圆弧拆分为线段，为使opengl操作方便，所得点数组顺时针排列
 *center：圆心
 *start：起点
 *end：终点所在直线上的一点，注意方向性
 *normal：圆弧所在平面的法线向量
 *flatnum：拆分的线段数
 *dest：拆分后所得点数组，个数较flatnum多一
*/
void Transform_Func::divide_arc(const Point &center, const Point &start, 
						const Point &end, const Normal& normal,int flatnum,CPt3DVector& dest)
{
	if(normal.is_zero_normal())
		return;

	Float distst = center.distanceto(start);
	Float disten = center.distanceto(end);
	if(EquFloat(distst,0.0) || EquFloat(disten,0.0))
		return;

	dest.clear();

	Float totalangle = arc_angle(center,start,end,normal);
	Float angle = totalangle / flatnum;

	dest.push_back(start);
	Point pt;
	for(int i=1; i<flatnum; i++)
	{
		next_arc_pt(center,dest[i-1],pt,normal,angle);
		dest.push_back(pt);
	}
	dest.push_back(end);
}
/*
 *圆弧逆时针旋转一定角度得到另一点
 *center: 圆心
 *pos: 圆弧上的当前点
 *next: 求得的圆弧上的下一点
 *normal: 圆弧所在平面的法线向量
 *angle: 角度
*/
//数学模型：
//Ax+By+Cz=0				平面点法式方程
//cos(alpha)=a*b/|a||b|		两向量夹角余弦
//x^2+y^2+z^2=r^2			球面方程
void Transform_Func::next_arc_pt(const Point &center, const Point &pos, 
						Point &next, const Normal& normal,Float angle)
{
	next.setdata(0.0,0.0,0.0);

	if(normal.is_zero_normal())
		return;

	Float r = center.distanceto(pos);
	if(EquFloat(r,0.0))
		return;

	if(EquFloat(angle,0.0))
	{
		next = pos;
		return;
	}

	while(angle > 2*pi)
		angle -= 2*pi;

	Float a = pos.x - center.x;
	Float b = pos.y - center.y;
	Float c = pos.z - center.z;

	Float A = normal.x();
	Float B = normal.y();
	Float C = normal.z();

	Float d0 = cos(angle)*r*r;

	Float x0 = 0.0;
	Float y0 = 0.0;
	Float z0 = 0.0;
	Float D = B*c-C*b;
	if(UEquFloat(D,0.0))
	{
		y0 = -(C*d0)/D;
		z0 = B*d0/D;
	}
	else
	{
		D = A*c-C*a;
		if(EquFloat(D,0.0))
		{
			D = A*b-B*a;
			x0 = -(B*d0)/D;
			y0 = A*d0/D;
		}
		else
		{
			x0 = -(C*d0)/D;
			z0 = A*d0/D;
		}
	}

	Float i = B*c-C*b;
	Float j = C*a-A*c;
	Float k = A*b-B*a;

	Float a1 = i*i+j*j+k*k;
	Float b1 = 2.0*(i*x0+j*y0+k*z0);
	Float c1 = x0*x0+y0*y0+z0*z0-r*r;

	Float t = (-b1+sqrt(b1*b1-4.0*a1*c1))/(2.0*a1);

	Float X = i*t+x0;
	Float Y = j*t+y0;
//	if(angle > PI_DLHML)
//		Y = -Y;
	Float Z = k*t+z0;

	next.setdata(X+center.x, Y+center.y, Z+center.z);

}


/*
 *圆弧的起点到终点的角度，
 *逆着法线向量的方向看，逆时针分布，范围0~2PI
 *center：圆心
 *start：起点
 *end：圆心与终点所在直线上的一点
 *normal：圆弧所在面的法线向量
*/
Float Transform_Func::arc_angle(const Point& center, const Point &start,
		const Point &end,const Normal& normal)
{
	if(normal.is_zero_normal())
		return 0.0;

	Float distst = center.distanceto(start);
	Float disten = center.distanceto(end);
	if(EquFloat(distst,0.0) || EquFloat(disten,0.0))
		return 0.0;

	if(start==end)
		return 2.0*pi;

	if(pt_in_line(center,start,end))
		return pi;

	Float ax = start.x - center.x;
	Float ay = start.y - center.y;
	Float az = start.z - center.z;
	Float bx = end.x - center.x;
	Float by = end.y - center.y;
	Float bz = end.z - center.z;

	Float totalangle = acos((ax*bx+ay*by+az*bz)/(distst*disten));
	Normal test1 = normal;
	Normal test2 = get_plane_normal(center,start,end);
	test1.set_unit();
	test2.set_unit();
	test2.set_reverse();
	if(test1 == test2)
		totalangle = 2.0*pi-totalangle;

	return totalangle;
}

Float Transform_Func::sin(Float x)
{
	if(EquFloat(x,pi) || EquFloat(x,2.0*pi))
		return 0.0;
	else
		return ::sin(x);
}

Float Transform_Func::cos(Float x)
{
	if(EquFloat(x,pi/2.0f) || EquFloat(x,3.0f*pi/2.0f))
		return 0.0;
	else
		return ::cos(x);
}

/*
 *求得不在同一直线上的三点所确定的平面的法线向量
*/
Normal Transform_Func::get_plane_normal(const Point& pt1,const Point& pt2, const Point& pt3)
{
	if(!pt_in_line(pt1,pt2,pt3))
	{
		Float A2 = pt2.x - pt1.x;
		Float B2 = pt2.y - pt1.y;
		Float C2 = pt2.z - pt1.z;
		Float A3 = pt3.x - pt1.x;
		Float B3 = pt3.y - pt1.y;
		Float C3 = pt3.z - pt1.z;

		Float A = B2*C3 - C2*B3;
		Float B = C2*A3 - A2*C3;
		Float C = A2*B3 - B2*A3;

		return Normal(A,B,C);
	}
	else
		return Normal(0.0,0.0,0.0);
}

/*
 *三点是否确定一平面
*/
bool Transform_Func::pt_in_line(const Point& pt1,const Point& pt2, const Point& pt3)
{
	Float distance[3];
	distance[0] = pt1.distanceto(pt2);
	distance[1] = pt3.distanceto(pt2);
	distance[2] = pt1.distanceto(pt3);
	std::sort(distance,&distance[3]);
	return EquFloat((distance[0]+distance[1]),distance[2]);
}


/*
 *称圆点为起点，终点在y轴正方向上的向量为原始向量
 *normal：空间任意向量
 *alpha：原始向量绕x轴旋转的角度
 *beta：原始向量绕y轴旋转的角度
*/
void Transform_Func::rotation_normal_angle(const Normal& normal, Float& alpha, Float& beta)
{
	if(normal.is_zero_normal())
		return;

	alpha = 0.0;
	beta = 0.0;

	if(EquFloat(normal.x(),0.0))
	{
		if(EquFloat(normal.y(),0.0))			//z_axis
		{
			if(normal.z() > 0.0)
				alpha = pi / 2.0;
			else
				alpha = 3.0f*pi/2.0f;
		}
		else if(EquFloat(normal.z(),0.0))	//y_axis
		{
			if(normal.y() < 0.0)
				alpha = pi;
		}
		else								//yoz
		{
			if(normal.z() > 0.0)
				alpha = normal.angle_y_axis();
			else
				alpha = -normal.angle_y_axis();
		}
	}
	else if(EquFloat(normal.y(),0.0))
	{
		if(EquFloat(normal.z(),0.0))			//x_axis
		{
			if(normal.x() > 0.0)
			{
				alpha = pi/2.0;
				beta = pi/2.0;
			}
			else
			{
				alpha = pi/2.0;
				beta = 3.0f*pi/2.0f;
			}
		}
		else								//xoz
		{
			if(normal.x() > 0.0)
			{
				alpha = pi/2.0;
				beta = normal.angle_z_axis();
			}
			else
			{
				alpha = pi/2.0;
				beta = -normal.angle_z_axis();
			}
		}
	}
	else if(EquFloat(normal.z(),0.0))		//xoy
	{
		if(normal.x() > 0.0)
		{
			alpha = normal.angle_y_axis();
			beta = pi/2.0;
		}
		else
		{
			alpha = normal.angle_y_axis();
			beta = 3.0f*pi/2.0f;
		}
	}
	else									//任意方向
	{
		if(normal.z() < 0.0)
			alpha = -normal.angle_y_axis();
		else
			alpha = normal.angle_y_axis();
		if(normal.x() < 0.0)
			beta = -acos(normal.z()/sqrt(normal.z()*normal.z()+normal.x()*normal.x()));
		else
			beta = acos(normal.z()/sqrt(normal.z()*normal.z()+normal.x()*normal.x()));
	}
}

/*
 *start：源向量
 *mat：变换矩阵
*/
void Transform_Func::normal_matrix(const Normal& normal, Matrix& mat)
{
	if(normal.is_zero_normal())
		return;

	mat.reset();

	Float alpha = 0.0;
	Float beta = 0.0;

	rotation_normal_angle(normal,alpha,beta);

	mat.set_rotation_radian(alpha,beta,0.0);

}

/*
 *两任意向量（模相等，起点为同一点）间的变换矩阵
 *操作：
 *1。取源向量与目的向量的法向量，将之先绕x轴旋转再绕y轴旋转，使之与z轴重合
 *2。绕z轴旋转两向量间的夹角。
 *3。作1的逆变换。
 *src(in):  源向量
 *dest(in): 目的向量
 *mat(out): 矩阵
*/
void Transform_Func::noraml_to_normal_matrix(const Normal& src, const Normal& dest, Matrix& mat)
{
	if(src.is_zero_normal() || dest.is_zero_normal())
		return ;

	mat.reset();

	Point O;
	Point ptSrc;
	ptSrc.setdata(src.x(),src.y(),src.z());
	Point ptDest;
	ptDest.setdata(dest.x(),dest.y(),dest.z());

	Matrix temp;

	Normal normal = get_plane_normal(O,ptSrc,ptDest);
	if(normal.is_zero_normal())
	{
		Normal _src = src;
		_src.set_unit();
		Normal _dest = dest;
		_dest.set_unit();
		Point t1,t2;
		t1.setdata(_src.x(),_src.y(),_src.z());
		t2.setdata(_dest.x(),_dest.y(),_dest.z());
		if(t1!=t2)
		{
			mat *= -1;			//两点关于原点对称（在同一直线上）
			return;
		}
		else
			return ;			//两点位同一点
	}
	normal.set_unit();

	Float gamma = arc_angle(O,ptSrc,ptDest,normal);

	Float lena = sqrt(normal.y()*normal.y()+normal.z()*normal.z());
	Float alpha = 0.0;
	if(UEquFloat(lena,0.0))
		alpha = acos(normal.z()/lena);
	if(normal.y() < 0.0)
		alpha = 2.0*pi - alpha;

	temp.set_x_rotation_radian(alpha);
	mat *= temp;

	ptSrc.setdata(normal.x(),normal.y(),normal.z());
	ptSrc.transformby(temp);

	Float lenb = sqrt(ptSrc.x*ptSrc.x+ptSrc.z*ptSrc.z);
	Float beta = 0.0;
	if(UEquFloat(lenb,0.0))
		beta = acos(ptSrc.z/lenb);
	if(ptSrc.x > 0.0)
		beta = 2.0*pi-beta;

	temp.set_y_rotation_radian(beta);
	mat *= temp;

	temp.set_z_rotation_radian(gamma);
	mat *= temp;

	temp.set_y_rotation_radian(beta);
	temp.inverse();
	mat *= temp;

	temp.set_x_rotation_radian(alpha);
	temp.inverse();
	mat *= temp;

}
/*
坐标系转换矩阵:点(物体)在不同坐标系之间的坐标变换,
如，屏幕坐标系内的点转换为世界坐标系内的点(同为右手坐标系)
变换方法:
（1）平移源坐标系统，使它的坐标原点与目的坐标系统的原点重合；
（2）进行一些旋转变换，使两坐标系的坐标轴重叠。
destO : 目的坐标系统的原点在源坐标系内的坐标值(用于确定平移值)
destOX : 目的坐标系统的ox轴在源坐标系内的向量值(用于确定旋转角度)
destOY : 目的坐标系统的oy轴在源坐标系内的向量值(用于确定旋转角度)
destOZ : 目的坐标系统的oz轴在源坐标系内的向量值(用于确定旋转角度)
*/
void Transform_Func::coord_transform_mat(Matrix& mat,const Point& destO,
		const Normal& destOX,const Normal& destOY,const Normal& destOZ)
{
/*	mat.reset();
	LMatrix temp;
	temp.SetToMove(-destO.x(),-destO.y(),-destO.z());
	mat *= temp;
	temp.reset();
	LNormal ox = destOX;
	LNormal oy = destOY;
	LNormal oz = destOZ;
	ox.SetUnit();
	oy.SetUnit();
	oz.SetUnit();
	LNormal dest(ox.X(),oy.Y(),oz.Z());
	LNormal src(1,1,1);
	NToNMat(dest,src,temp);
	mat *= temp;*/
}

}
