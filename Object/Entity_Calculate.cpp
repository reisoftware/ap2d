// Entity_Calculate.cpp: implementation of the Entity_Calculate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Entity_Calculate.h"
#include "Line.h"
#include "Circle.h"
#include "RArc.h"
#include "Normal.h"
#include "Matrix_d.h"
#include "Rect.h"
#include "export.h"
#include "calculate.h"
#include "geo_obj.h"
#include "../Geometry/calculate.h" 
#include "../Geometry/Point.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Entity_Calculate::Entity_Calculate()
MCT_INIT1("Entity_Calculate")
{

}

Entity_Calculate::~Entity_Calculate()
{

}
bool Entity_Calculate::middle_perpendicular_line(Line& line,const Point& st,const Point& ed)
{
	Point m1 = (st+ed)/2;
	m1.z = 0;
	Normal n1;
	n1.set_data(ed.x-st.x,ed.y-st.y,0);
	n1.set_unit();
	Point t(n1.x(),n1.y());
	Matrix mat;
	mat.set_z_rotation_radian(pi/2);
	t.transformby(mat);
	n1.set_data(t.x,t.y,0);
	Point m11 = m1.polarTo(100,n1);
	line.setdata(m1,m11);
	return true;
}
Float Entity_Calculate::line_angle_to_x_axis(const Line& line) const
{

  Float len = line.length();
	if(len < 0.0) 
		return	0 ;
	Point dp = line.end()-line.start();

  Float cosv = dp.x/len ;
	Float sinv = dp.y/len ;

  if(sinv >= 0)
		return acos(cosv) ;
	else if(sinv < 0)
		return 2.*pi-acos(cosv) ;
	return 0 ;
}
bool Entity_Calculate::line_tan(Float &a,const Line& line) const
{
	if(EquFloat(line.end().x,line.start().x))
		return false;
	a=(line.end().y-line.start().y)/(line.end().x-line.start().x);
	return true;
}
Float Entity_Calculate::line_B(const Line& line) const
{
	Float b=0.0;
	Float a;
	if(line_tan(a,line))
		b=line.start().y-line.start().x*a;
	return b;
}
bool Entity_Calculate::parallel(const Line& lhs,const Line& rhs) const
{
	Float a1,a2;
	if(line_tan(a1,lhs))
	{
		if(line_tan(a2,rhs))
		{
			return EquFloat(a1,a2);
		}
		else
			return false;
	}
	else if(line_tan(a2,rhs))
		return false;
	else
		 return true;
}

bool Entity_Calculate::point_in_linesegment(const Point &q,const Line& line) const
{
	Float dis1 = q.distanceto2d(line.start());
	Float dis2 = q.distanceto2d(line.end());
	Float dis3 = line.start().distanceto2d(line.end());
	return EquFloat(dis1+dis2,dis3);
}
bool Entity_Calculate::line_insect_line_segment(Point& ptIn,const Line& lhs,const Line& line) const
{
	if(line_insect_line(ptIn,lhs,line)){
		if(point_in_linesegment(ptIn,lhs) && point_in_linesegment(ptIn,line))
			return true;
	}
	return false;
}
bool Entity_Calculate::line_insect_line(Point& ptIn,const Line& lhs,const Line& line) const
{
	Float a1,b1,a2,b2;
	Point pt;
	b1=line_B(lhs);
	b2=line_B(line);
	if(parallel(lhs,line))
		return false;
	else
	{
		if(line_tan(a1,lhs))
		{
			
			if(line_tan(a2,line))
			{
				pt.x = (b2-b1)/(a1-a2);
				pt.y = pt.x*a1+b1;
			}
			else
			{
				pt.x = line.start().x;
				pt.y = pt.x*a1+b1;
			}
		}
		else if(line_tan(a2,line))
		{
			pt.x = lhs.start().x;
			pt.y = pt.x*a2+b2;
			
		}
	}
	ptIn = pt;
	return true;
}

// bool Entity_Calculate::line_insect_circle(Point& pt1,
//                                           Point& pt2,
//                                           const Line& line,
// 																					const Circle& circle) const
// { 
//   if( geo2d::intersect(circle, line, pt1, pt2)){
//     return true;
//   }
//   return false;
// 
// //	 int ptnum = intersect_line2circle( pt1.x,
// //                                      pt1.y,
// //                                      pt2.x,
// //                                      pt2.y,
// //		                                  line.start().x,
// //                                      line.start().y,
// //                                      line.end().x,
// //                                      line.end().y,
// //		                                  circle.center().x,
// //                                      circle.center().y,
// //                                      circle.radius());
// //   if(ptnum){
// //     return true;
// //   }
// //   return false;
// }  


//int Entity_Calculate::intersect_line2circle(Float& destpt1_x, 
//                                              Float& destpt1_y, 
//								                              Float& destpt2_x, 
//                                              Float& destpt2_y, 
//								                              Float linest_x,   
//                                              Float linest_y, 
//								                              Float lineed_x,   
//                                              Float lineed_y, 
//								                              Float center_x,   
//                                              Float center_y, 
//								                              Float rad) const
//{
//  Float L[3],C[3];
//  L[0] = linest_y - lineed_y;
//  L[1] = lineed_x - linest_x;
//  L[2] = linest_x*lineed_y - lineed_x*linest_y;
//  C[0] = center_x;
//  C[1] = center_y;
//  C[2] = rad;
//  Float d ,dd ,dp ,sa ,ca ,xa,ya;
//  dd = sqrt(L[0]*L[0] + L[1]*L[1]) ;
//  d = -(L[0]*C[0] + L[1]*C[1] + L[2] )/dd;  
//  if (MoreThen( fabs(d), fabs(C[2]) ))			
//  {
//    destpt1_x = 0.0;
//    destpt1_y = 0.0;
//    destpt2_x = 0.0;
//    destpt2_y = 0.0;
//    return 0;
//  }
//  if (EquFloat(fabs(d),C[2]))
//  {
//    d = C[2];
//    xa = (L[1]*L[1]*C[0] - L[0]*C[1]*L[1] - L[0]*L[2])/(dd*dd);
//    ya = (L[0]*L[0]*C[1] - L[0]*L[1]*C[0] - L[1]*L[2])/(dd*dd);	////µãa×ø±E
//    destpt1_x = xa ;
//    destpt1_y = ya ;
//    destpt2_x = xa ;
//    destpt2_y = ya ;
//    Float max_x=0,max_y=0,min_x=0,min_y=0;////Ïß¶ÎÈ¡Öµ·¶Î§
//    max_x = MoreThen(linest_x,lineed_x)?linest_x:lineed_x;	
//    max_y = MoreThen(linest_y,lineed_y)?linest_y:lineed_y;
//    min_x = LessThen(linest_x,lineed_x)?linest_x:lineed_x;
//    min_y = LessThen(linest_y,lineed_y)?linest_y:lineed_y;
//    if (EquFloat(destpt1_x,destpt2_x)&&EquFloat(destpt1_y,destpt2_y)&&
//      (!LessThen(destpt1_x,min_x))&&(!MoreThen(destpt1_x,max_x)))
//    {
//      destpt2_x = 0.0;
//      destpt2_y = 0.0;
//      return 1;
//    }
//    else 
//    {
//      destpt1_x = 0.0;
//      destpt1_y = 0.0;
//      destpt2_x = 0.0;
//      destpt2_y = 0.0;
//      return 0;
//    }
//    
//  }
//  xa = (L[1]*L[1]*C[0] - L[0]*C[1]*L[1] - L[0]*L[2])/(dd*dd);
//  ya = (L[0]*L[0]*C[1] - L[0]*L[1]*C[0] - L[1]*L[2])/(dd*dd);	
//  sa = L[0]/dd;
//  ca = -L[1]/dd;
//  dp = sqrt(C[2]*C[2] - d*d);   
//  destpt1_x = xa - dp*ca;
//  destpt1_y = ya - dp*sa;
//  destpt2_x = xa + dp*ca;
//  destpt2_y = ya + dp*sa;
//  Float max_x,max_y,min_x,min_y;@
//  max_x = MoreThen(linest_x,lineed_x)?linest_x:lineed_x;	
//  max_y = MoreThen(linest_y,lineed_y)?linest_y:lineed_y;
//  min_x = LessThen(linest_x,lineed_x)?linest_x:lineed_x;
//  min_y = LessThen(linest_y,lineed_y)?linest_y:lineed_y;
//  
//
//  if ((!LessThen(destpt2_x,min_x))&&
//      (!MoreThen(destpt2_x,max_x))&&
//      (!LessThen(destpt2_y,min_y))&&
//      (!MoreThen(destpt2_y,max_y)))
//  {  
//    if ((!LessThen(destpt1_x,min_x))&&
//        (!MoreThen(destpt1_x,max_x))&&
//        (!LessThen(destpt1_y,min_y))&&
//        (!MoreThen(destpt1_y,max_y)))	
//      return 2;
//    else
//    {
//      destpt1_x = destpt2_x;
//      destpt1_y = destpt2_y;
//      destpt2_x = 0.0;
//      destpt2_y = 0.0;
//      return 1;
//    }			
//  } 
//  else{ 
//    if ((!LessThen(destpt1_x,min_x)) &&
//        (!MoreThen(destpt1_x,max_x)) &&
//        (!LessThen(destpt1_y,min_y)) &&
//        (!MoreThen(destpt1_y,max_y)) )
//    {
//      destpt2_x = 0.0;
//      destpt2_y = 0.0;
//      return 1;
//    }
//  }
//  return 0;
//
//
//}

bool Entity_Calculate::radian_Arc(Float& radian_max,Float& radian_min,
							Float Arc[],Float CC[]) const
{
	Float radian[3];   

  if((Arc[0] - CC[0])/CC[2] ==1)
		radian[0] = 0.0;  
	else 
	{
		if ((Arc[0] - CC[0])/CC[2] ==-1)
			radian[0] = pi; 
		else
		{
			if((Arc[1]- CC[1])>0)
				radian[0] =acos((Arc[0] - CC[0] )/CC[2]);
			else
				radian[0] = acos(-(Arc[0] - CC[0])/CC[2]) +pi;
		}
	}

  if((Arc[2] - CC[0])/CC[2] ==1)
		radian[1] = 0.0;  
	else 
	{
		if ((Arc[2] - CC[0])/CC[2] ==-1)
			radian[1] = pi;
		else
		{
			if((Arc[3]-CC[1])>0)
				radian[1] =acos((Arc[2] -CC[0])/CC[2]);
			else 
				radian[1] = acos(-(Arc[2] - CC[0])/CC[2]) +pi;
		} 
	}

  if((Arc[4] - CC[0])/CC[2] ==1)
		radian[2] = 0.0; 
	else 
	{
		if ((Arc[4] - CC[0])/CC[2] ==-1)
			radian[2] = pi; 
		else
		{
			if((Arc[5]-CC[1])>0)
				radian[2] =acos((Arc[4] -CC[0])/CC[2]);
			else 
				radian[2] = acos(-(Arc[4] - CC[0])/CC[2]) +pi;
		}
	}

  if (radian[1]>radian[0]&&radian[0]>radian[2])
		radian[2] = radian[2] + 2*pi;
	if (radian[1]>radian[2]&&radian[2]>radian[0])
		radian[0] = radian[0] + 2*pi;
	if (radian[2]>radian[0]&&radian[0]>radian[1])
	{
		radian[0] = radian[0] + 2*pi;
		radian[1] = radian[1] + 2*pi;
	}
	if (radian[0]>radian[2]&&radian[2]>radian[1])
	{
		radian[1] = radian[1] +2*pi;
		radian[2] = radian[2] +2*pi;
	}
	
	if (radian[0]>radian[2]) 
	{
		radian_max = radian[0];
		radian_min = radian[2];
		Float temp;
		temp = Arc[0];
		Arc[0] = Arc[4];
		Arc[4] = temp;
		temp = Arc[1];
		Arc[1] = Arc[5];
		Arc[5] = temp;
	}
	else
	{
		radian_max = radian[2];
		radian_min = radian[0];
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////////
int Entity_Calculate::radian_intersec(Float IntersecRadian[],Float m_intersec[],Float CC[]) const
{

  if((m_intersec[0] - CC[0])/CC[2] ==1)
		IntersecRadian[0] = 0.0;  
	else 
	{
		if((m_intersec[0] - CC[0])/CC[2] ==-1)
			IntersecRadian[0] = pi; 
		else
		{
			if((m_intersec[1]-CC[1])>0)
				IntersecRadian[0] =acos((m_intersec[0] -CC[0])/CC[2]);
			else 
				IntersecRadian[0] = acos(-(m_intersec[0] - CC[0])/CC[2]) +pi;
		}
	}   

  if((m_intersec[2] - CC[0])/CC[2] ==1 )
		IntersecRadian[1] = 0.0;  
	else 
	{
		if((m_intersec[2] - CC[0])/CC[2] ==-1) 
			IntersecRadian[1] = pi; 
		else
		{
			if((m_intersec[3]-CC[1])>0)
				IntersecRadian[1] =acos((m_intersec[2] -CC[0])/CC[2]);
			else 
				IntersecRadian[1] = acos(-(m_intersec[2] - CC[0])/CC[2]) +pi;
		} 
	}
	return 0;
} 

// bool Entity_Calculate::line_insect_arc( Point& pt1,
//                                        Point& pt2,
//                                        const Line& line,
//                                        const RArc& arc) const
// {
// 	Point arcst,arced,arcpt;
//   arc.getdata(arcst,arcpt,arced);
//   int ptnum = geo2d::intersect(arc, line, pt1, pt2);
// 
// 
// //	int ptnum = intersect_line2arc( pt1.x,
// //                                  pt1.y,
// //                                  pt2.x,
// //                                  pt2.y,
// //                                  line.start().x,
// //                                  line.start().y,
// //		                              line.end().x,
// //                                  line.end().y,
// //                                  arcst.x,
// //                                  arcst.y,
// //                                  arced.x,
// //                                  arced.y,
// //                                  arcpt.x,
// //                                  arcpt.y);
//   if(ptnum == 0){
//     return false;
//   }
//   if(ptnum == 1){
//     if(line.is_in_segline(pt1)){
//       return true; 
//     }
//     else{
//       return false;
//     }
//   }
//   if(ptnum == 2){
//     if(line.is_in_segline(pt1) && line.is_in_segline(pt2)){
//       return true;
//     }
//     else{
//       return false;
//     }
//   }
//   return false;
// } 

//int Entity_Calculate::intersect_line2arc(Float& pt1_x,
//                                          Float& pt1_y,
//                                          Float& pt2_x,
//                                          Float& pt2_y,
//									                        Float lst_x,
//                                          Float lst_y, 
//									                        Float led_x,
//                                          Float led_y, 
//									                        Float arcst_x,
//                                          Float arcst_y, 
//									                        Float arced_x,
//                                          Float arced_y, 
//									                        Float arc_x,
//                                          Float arc_y) const
//{
//  
//  
//  pt1_x = 0.0,pt1_y = 0.0;
//  pt2_x = 0.0,pt2_y = 0.0;
//  Point pt_stPos;   // ÆÁÄ»×ø±ê£¬Ô²»¡µÚÒ»µE
//  Point pt_endPos;  // ÆÁÄ»×ø±ê£¬Ô²»¡ÖÕµE
//  double CL1[3],CL2[3];   //×é³ÉÔ²»¡µÄÁ½ÌõÖ±Ïß²ÎÊı
//  double LL[3];           //Ö±Ïß²ÎÊı
//  double CC[3];           //Ô²ĞÄ×ø±EÍÔ²ĞÄ°E¶
//  double intersec[4];     //´æ·Å´ıÅĞ¶¨µÄ½»µE
//  double Arc[6];          //´æ·ÅÔ²»¡Èıµã×ø±ê£»
//  Arc[0] = arcst_x,Arc[1] = arcst_y;
//  Arc[2] = arc_x,  Arc[3] = arc_y;
//  Arc[4] = arced_x,Arc[5] = arced_y;
//  
//  LL[0] = lst_y - led_y;
//  LL[1] = led_x - lst_x;
//  LL[2] = lst_x*led_y - led_x*lst_y;
//  CL1[0]=2*(arc_x-arcst_x);
//  CL1[1]=2*(arc_y-arcst_y);
//  CL1[2]=arc_x*arc_x+arc_y*arc_y-arcst_x*arcst_x-arcst_y*arcst_y;
//  CL2[0]=2*(arced_x-arc_x);
//  CL2[1]=2*(arced_y-arc_y);
//  CL2[2]=arced_x*arced_x+arced_y*arced_y-arc_x*arc_x-arc_y*arc_y;
//  CC[0] = (CL1[1]*CL2[2]-CL2[1]*CL1[2])/(CL1[1]*CL2[0]-CL2[1]*CL1[0]);
//  CC[1] = (CL2[0]*CL1[2]-CL1[0]*CL2[2])/(CL1[1]*CL2[0]-CL2[1]*CL1[0]);
//  CC[2] = sqrt((CC[0]-arcst_x)*(CC[0]-arcst_x) +
//    (CC[1]-arcst_y)*(CC[1]-arcst_y));
//  
//  double d ,dd ,dp ,sa ,ca ,xa,ya;
//  dd = sqrt(LL[0]*LL[0] + LL[1]*LL[1]);
//  d = -(LL[0]*CC[0] + LL[1]*CC[1] + LL[2] )/dd;  //Ô²ĞÄµ½Ö±ÏßµÄÓĞÏûÚàÀE	
//  //Èç¹ûÔ²ĞÄÓE±Ïß¾àÀEóÓÚ°E¶ÔòÃ»ÓĞ½»µE
//  if (MoreThen(fabs(d),fabs(CC[2])))					 
//    return 0;
//  xa = (LL[1]*LL[1]*CC[0] - LL[0]*CC[1]*LL[1] - LL[0]*LL[2])/(dd*dd);
//  ya = (LL[0]*LL[0]*CC[1] - LL[0]*LL[1]*CC[0] - LL[1]*LL[2])/(dd*dd);	//µãa×ø±E
//  sa = LL[0]/dd;
//  ca = -LL[1]/dd;
//  dp = sqrt(CC[2]*CC[2] - d*d);    //¼ÆËãd'µÄÖ²
//  intersec[0] = xa - dp*ca;
//  intersec[1] = ya - dp*sa;
//  intersec[2] = xa + dp*ca;
//  intersec[3] = ya + dp*sa;
//  double max_x,max_y,min_x,min_y;//Ïß¶ÎÈ¡Öµ·¶Î§
//  max_x = MoreThen(lst_x,led_x)? lst_x:led_x;	
//  max_y = MoreThen(lst_y,led_y)? lst_y:led_y;
//  min_x = LessThen(lst_x,led_x)? lst_x:led_x;
//  min_y = LessThen(lst_y,led_y)? lst_y:led_y;
//  
//  //ÈıµãÒÔ¼°½»µã»¡¶È
//  double IntersecRadian[2];      //Ô²»¡»¡¶È
//  double radian_max,radian_min;  //Ô²»¡»¡¶È×ûĞóºÍ×ûì¡Öµ
//  radian_Arc(radian_max,radian_min,Arc,CC);
//  radian_intersec(IntersecRadian,intersec,CC);
//  
//  BOOL Inter1 = false,Inter2 = false;
//  if(MoreThen(intersec[0],min_x||EquFloat(min_x,intersec[0])) && 
//    (LessThen(intersec[0],max_x)||EquFloat(min_x,intersec[0]))&&
//    (MoreThen(intersec[1],min_y)||EquFloat(intersec[1],min_y)) && 
//    (LessThen(intersec[1],max_y)||EquFloat(intersec[1],max_y))&&
//    ((((LessThen(IntersecRadian[0],radian_max)||(EquFloat(IntersecRadian[0],radian_max)))
//    &&(MoreThen(IntersecRadian[0],radian_min)||(EquFloat(IntersecRadian[0],radian_min))))
//    ||((LessThen((IntersecRadian[0]+2*pi),radian_max)||(EquFloat((IntersecRadian[0]+2*pi),radian_max))
//    &&(MoreThen((IntersecRadian[0]+2*pi),radian_min)||(EquFloat((IntersecRadian[0]+2*pi),radian_min))))))))
//  {
//    pt1_x = intersec[0];
//    pt1_y = intersec[1];
//    Inter1 = true;
//  }
//  //ÅĞ¶ÏµÚ¶ş¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
//  if (MoreThen(intersec[2],min_x||EquFloat(min_x,intersec[2])) && 
//    (LessThen(intersec[2],max_x)||EquFloat(min_x,intersec[2]))&&
//    (MoreThen(intersec[3],min_y)||EquFloat(intersec[3],min_y)) && 
//    (LessThen(intersec[3],max_y)||EquFloat(intersec[3],max_y))&&
//    ((((LessThen(IntersecRadian[1],radian_max)||(EquFloat(IntersecRadian[1],radian_max)))
//    &&(MoreThen(IntersecRadian[1],radian_min)||(EquFloat(IntersecRadian[1],radian_min))))
//    ||((LessThen((IntersecRadian[1]+2*pi),radian_max)||(EquFloat((IntersecRadian[1]+2*pi),radian_max))
//    &&(MoreThen((IntersecRadian[1]+2*pi),radian_min)||(EquFloat((IntersecRadian[1]+2*pi),radian_min))))))))
//  {
//    pt2_x = intersec[2];
//    pt2_y = intersec[3];
//    Inter2 = true;
//  }
//  if(Inter1&&Inter2){
//    return 2;
//  }
//  if(Inter1){
//    return 1;
//  }
//  if(Inter2){
//    pt1_x=pt2_x;
//    pt1_y=pt2_y;
//    return 1;
//  }
//  return 0;
////  if (Inter1||Inter2)
////    return true;
////  else    
////    return false;		
//
//
////08.11.03
////	pt1_x = 0.0,pt1_y = 0.0;
////        pt2_x = 0.0,pt2_y = 0.0;
//////	CPoint pt_stPos;   // ÆÁÄ»×ø±ê£¬Ô²»¡µÚÒ»µE
////
//////	CPoint pt_endPos;  // ÆÁÄ»×ø±ê£¬Ô²»¡ÖÕµE
////
////	Float CL1[3],CL2[3];   //×é³ÉÔ²»¡µÄÁ½ÌõÖ±Ïß²ÎÊı
////	Float LL[3];           //Ö±Ïß²ÎÊı
////	Float CC[3];           //Ô²ĞÄ×ø±EÍÔ²ĞÄ°E¶
////	Float intersec[4];     //´æ·Å´ıÅĞ¶¨µÄ½»µE
////
////	Float Arc[6];          //´æ·ÅÔ²»¡Èıµã×ø±ê£»
////	Arc[0] = arcst_x,Arc[1] = arcst_y;
////	Arc[2] = arc_x,  Arc[3] = arc_y;
////	Arc[4] = arced_x,Arc[5] = arced_y;
////	
////    LL[0] = lst_y - led_y;
////	LL[1] = led_x - lst_x;
////	LL[2] = lst_x*led_y - led_x*lst_y;
////	CL1[0]=2*(arc_x-arcst_x);
////	CL1[1]=2*(arc_y-arcst_y);
////	CL1[2]=arc_x*arc_x+arc_y*arc_y-arcst_x*arcst_x-arcst_y*arcst_y;
////	CL2[0]=2*(arced_x-arc_x);
////	CL2[1]=2*(arced_y-arc_y);
////	CL2[2]=arced_x*arced_x+arced_y*arced_y-arc_x*arc_x-arc_y*arc_y;
////	CC[0] = (CL1[1]*CL2[2]-CL2[1]*CL1[2])/(CL1[1]*CL2[0]-CL2[1]*CL1[0]);
////	CC[1] = (CL2[0]*CL1[2]-CL1[0]*CL2[2])/(CL1[1]*CL2[0]-CL2[1]*CL1[0]);
////	CC[2] = sqrt((CC[0]-arcst_x)*(CC[0]-arcst_x) +
////		(CC[1]-arcst_y)*(CC[1]-arcst_y));
////	
////    Float d ,dd ,dp ,sa ,ca ,xa,ya;
////	dd = sqrt(LL[0]*LL[0] + LL[1]*LL[1]);
////	d = -(LL[0]*CC[0] + LL[1]*CC[1] + LL[2] )/dd;  //Ô²ĞÄµ½Ö±ÏßµÄÓĞÏûÚàÀE	
////	//Èç¹ûÔ²ĞÄÓE±Ïß¾àÀEóÓÚ°E¶ÔòÃ»ÓĞ½»µE
////	if (fabs(d)>fabs(CC[2]))					 
////		return FALSE;
////	xa = (LL[1]*LL[1]*CC[0] - LL[0]*CC[1]*LL[1] - LL[0]*LL[2])/(dd*dd);
////	ya = (LL[0]*LL[0]*CC[1] - LL[0]*LL[1]*CC[0] - LL[1]*LL[2])/(dd*dd);	//µãa×ø±E
////
////	sa = LL[0]/dd;
////	ca = -LL[1]/dd;
////	dp = sqrt(CC[2]*CC[2] - d*d);    //¼ÆËãd'µÄÖ²
////	intersec[0] = xa - dp*ca;
////	intersec[1] = ya - dp*sa;
////	intersec[2] = xa + dp*ca;
////	intersec[3] = ya + dp*sa;
////	Float max_x,max_y,min_x,min_y;//Ïß¶ÎÈ¡Öµ·¶Î§
////	max_x = (lst_x>led_x)? lst_x:led_x;	
////	max_y = (lst_y>led_y)? lst_y:led_y;
////	min_x = (lst_x<led_x)? lst_x:led_x;
////	min_y = (lst_y<led_y)? lst_y:led_y;
////	
////	//ÈıµãÒÔ¼°½»µã»¡¶È
////	Float IntersecRadian[2];      //Ô²»¡»¡¶È
////	Float radian_max,radian_min;  //Ô²»¡»¡¶È×ûĞóºÍ×ûì¡Öµ
////	radian_Arc(radian_max,radian_min,Arc,CC);
////	radian_intersec(IntersecRadian,intersec,CC);
////
////    BOOL Inter1 = FALSE,Inter2 = FALSE;
////	if ((intersec[0]>min_x||EquFloat(min_x,intersec[0])) && 
////		((intersec[0]<max_x)||EquFloat(min_x,intersec[0]))&&
////		((intersec[1]>min_y)||EquFloat(intersec[1],min_y)) && 
////		((intersec[1]<max_y)||EquFloat(intersec[1],max_y))&&
////		(((((IntersecRadian[0]<radian_max)||(EquFloat(IntersecRadian[0],radian_max)))
////		&&((IntersecRadian[0]>radian_min)||(EquFloat(IntersecRadian[0],radian_min))))
////		||((((IntersecRadian[0]+2*pi)<radian_max)||(EquFloat((IntersecRadian[0]+2*pi),radian_max))
////		&&(((IntersecRadian[0]+2*pi)>radian_min)||(EquFloat((IntersecRadian[0]+2*pi),radian_min))))))))
////		{
////				pt1_x = intersec[0];
////				pt1_y = intersec[1];
////				Inter1 = TRUE;
////		}
////		//ÅĞ¶ÏµÚ¶ş¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
////	if ((intersec[2]>min_x||EquFloat(min_x,intersec[2])) && 
////		((intersec[2]<max_x)||EquFloat(min_x,intersec[2]))&&
////		((intersec[3]>min_y)||EquFloat(intersec[3],min_y)) && 
////		((intersec[3]<max_y)||EquFloat(intersec[3],max_y))&&
////		(((((IntersecRadian[1]<radian_max)||(EquFloat(IntersecRadian[1],radian_max)))
////		&&((IntersecRadian[1]>radian_min)||(EquFloat(IntersecRadian[1],radian_min))))
////		||((((IntersecRadian[1]+2*pi)<radian_max)||(EquFloat((IntersecRadian[1]+2*pi),radian_max))
////		&&(((IntersecRadian[1]+2*pi)>radian_min)||(EquFloat((IntersecRadian[1]+2*pi),radian_min))))))))
////		{
////				pt2_x = intersec[2];
////				pt2_y = intersec[3];
////				Inter2 = TRUE;
////		}
////	if (Inter1||Inter2)
////		return TRUE;
////	else    
////		return FALSE;		
//}
bool Entity_Calculate::line_parallel(Line& dest,const Line& src,const Point& o) const
{
	if(point_in_linesegment(o,src)){
		dest = src;
		return true;
	}
	Point pp;
	bool b = line_perpendicular(pp,src,o);
	Matrix mat;
	mat.set_move(o.x-pp.x,o.y-pp.y,0);
	dest = src;
	dest.transformby(mat);
	return b;
}
bool Entity_Calculate::line_perpendicular(Point& out,
                                          const Line& line,
                                          const Point& o) const
{
  Normal lnnor(line);
  lnnor.set_unit();
  Normal ptnor(lnnor);
  ptnor.rota_z(90);
  ptnor.set_unit();
  Line ptln;
  ptln.setdata(o, ptnor);
  return line_insect_line(out, ptln, line);

//	Float p[2],p1[2],p2[2],pt[2];
//	p1[0] = line.start().x;
//	p1[1] = line.start().y;
//	p2[0] = line.end().x;
//	p2[1] = line.end().y;
//	pt[0] = o.x;
//	pt[1] = o.y;
//	bool b = point_perpendicular(p,p1,p2,pt);
//	out.setdata(p[0],p[1],0);
//	return b;
}
////////////////////////////////////////////////////////////////////
//¼ÆËã¹ıÒÑÖªµãÓëÒÑÖªÏßµÄ´¹×ã
//´¹×ãÎªÓÚÏß¶ÎÄÚ·µ»ØTRUE£¬·ñÔò·µ»ØFALSE
//p1£¬p2ÎªÏß¶ÎÁ½¶Ğµã×ø±ê
//ptÎªÒÑÖªµã×ø±ê
//pÎªÇóµÄ´¹×ãµã×ø±ê
///////////////////////////////////////////////////////////////////										
bool Entity_Calculate::point_perpendicular(Float p[2],Float p1[2],Float p2[2],Float pt[2]) const
{
	if(EquFloat(p1[0],p2[0])&&EquFloat(p2[1],p1[1])){  //Èç¹ûÁ½µãÏàµÈ£¬Ïß¶Î²»´æÔÚ
		p[0] = p1[0];
		p[1] = p1[1];
		return false;
	}
	//Ö±ÏßÓÃ·¨Ïß·½³Ì   aX + bY +c = 0À´±íÊ¾
	Float L0[3];   //Í¨¹ıÒÑÖªµÄÁ½µã£¬ËùÇóÖ±Ïß·½³Ì
	Float L[3];    //´¹Ïß·½³Ì
	L0[0] = p2[1] - p1[1];
	L0[1] = p1[0] - p2[0];
	L0[2] = p2[0]*p1[1] - p1[0]*p2[1];
	/*L[0] = L0[1];
	L[1] = -L0[0];
	L[2] = L0[1]*pt[1] - L0[0]*pt[0];*/
	
	if (EquFloat(L0[0],0.0))        //Ö±Ïß·½³ÌÖĞa=0µÄÇé¿ö
	{
		p[0] = pt[0];
		p[1] = -L0[2]/L0[1];
		L[0] = 1.0;
		L[1] = 0.0;
		L[2] = -p[0];
	}
	else if(EquFloat(L0[1],0.0))      //Ö±Ïß·½³ÌÖĞb=0Çé¿ö
	{
		p[0] = -L0[2]/L0[0];
		p[1] = pt[1];
		L[0] = 0.0;
		L[1] = 1.0;
		L[2] = -pt[1];
	}
	else if (EquFloat((L0[0]*pt[0] + L0[1]*pt[0] + L0[2]),0.0))
	{                            //ptµãÔÚÖ±ÏßÉÏ
		p[0] = pt[0];
		p[1] = pt[1];
		L[0] = -L0[0];
		L[1] = L0[0];
		L[2] = L0[1]*pt[0] - L0[0]* pt[1];	
	}
	//ÒÔÏÂÎªÒ»°ãÇé¿öÊ±´¹×ãÓë´¹Ïß
	else 
	{	
		p[0] = (L0[1]*L0[1]*pt[0] - L0[0]*L0[1]*pt[1] - L0[0]*L0[2])/
			(L0[0]*L0[0] + L0[1]*L0[1]);
		p[1] = (L0[0]*L0[0]*pt[1] - L0[0]*L0[1]*pt[0] - L0[1]*L0[2])/
			(L0[0]*L0[0] + L0[1]*L0[1]);
		L[0] = p[1] - pt[1];
		L[1] = -(p[0] - pt[0]);
		L[2] = -pt[0]*p[1] + p[0]*pt[1];
	}
	
	Float max_x,min_x,max_y,min_y;
	max_x = (p2[0] >p1[0])? p2[0]:p1[0];
	min_x = (p2[0] <p1[0])? p2[0]:p1[0];
	max_y = (p2[1] >p1[1])? p2[1]:p1[1];
	min_y = (p2[1] <p1[1])? p2[1]:p1[1];
	if ((EquFloat(p[0],max_x)||EquFloat(p[0],min_x)||(p[0]>min_x&&p[0]<max_x))&&
		(EquFloat(p[1],max_y)||EquFloat(p[1],min_y)||(p[1]>min_y&&p[1]<max_y)))
		return true;
	else
		return false;
}

bool Entity_Calculate::linesegment_insect_rect(const Line& lines,const Rect& rect)
{
	Point st,ed,ptin;
	Line line;

	st.setdata(rect.xmin(),rect.ymax(),0.0);
	ed.setdata(rect.xmax(),rect.ymax(),0.0);
	line.setdata(st,ed);
  if(line_insect_line_segment(ptin,line,lines)){
		return true;
  }

	st.setdata(rect.xmax(),rect.ymax(),0.0);
	ed.setdata(rect.xmax(),rect.ymin(),0.0);
	line.setdata(st,ed);
  if(line_insect_line_segment(ptin,line,lines)){
		return true;
  }

	st.setdata(rect.xmax(),rect.ymin(),0.0);
	ed.setdata(rect.xmin(),rect.ymin(),0.0);
	line.setdata(st,ed);
  if(line_insect_line_segment(ptin,line,lines)){
		return true;
  }

	st.setdata(rect.xmin(),rect.ymin(),0.0);
	ed.setdata(rect.xmin(),rect.ymax(),0.0);
	line.setdata(st,ed);
  if(line_insect_line_segment(ptin,line,lines)){
		return true;
  }

	return false;
}
bool Entity_Calculate::rect_insect_beeline(const Rect& rect, const Line& beeline)
{
	Point st,ed,ptin;
	Line line;

	st.setdata(rect.xmin(),rect.ymax(),0.0);
	ed.setdata(rect.xmax(),rect.ymax(),0.0);
	line.setdata(st,ed);
  if(line_insect_line(ptin,line,beeline)){
		return true;
  }

	st.setdata(rect.xmax(),rect.ymax(),0.0);
	ed.setdata(rect.xmax(),rect.ymin(),0.0);
	line.setdata(st,ed);
  if(line_insect_line(ptin,line,beeline)){
		return true;
  }

	st.setdata(rect.xmax(),rect.ymin(),0.0);
	ed.setdata(rect.xmin(),rect.ymin(),0.0);
	line.setdata(st,ed);
  if(line_insect_line(ptin,line,beeline)){
		return true;
  }

	st.setdata(rect.xmin(),rect.ymin(),0.0);
	ed.setdata(rect.xmin(),rect.ymax(),0.0);
	line.setdata(st,ed);
  if(line_insect_line(ptin,line,beeline)){
		return true;
  }

	return false;
}

//void Entity_Calculate::get_ents_rect(Rect& rect,const std::vector<Entity*>& ents)
//{
//	if(ents.size() == 0)
//		return ;
//	rect.set_reverse_minmax();
//	std::vector<Entity*>::const_iterator iter = 0;
//	iter = ents.begin();
//	for(; iter != ents.end(); ++iter){
//		Rect temp = (*iter)->box2d();
//		rect.xmin(min(rect.xmin(),temp.xmin()));
//		rect.ymin(min(rect.ymin(),temp.ymin()));
//		rect.xmax(max(rect.xmax(),temp.xmax()));
//		rect.ymax(max(rect.ymax(),temp.ymax()));
//	}
//}

bool Entity_Calculate::circle_insect_circle(Point& pt1,Point& pt2,const Circle& lhs,const Circle& rhs) const
{
  if(&lhs == &rhs){
    return false;
  }
  if(lhs == rhs){
    return false;
  }
	return intersect_cir2cir(pt1.x,pt1.y,pt2.x,pt2.y,lhs.center().x,lhs.center().y,
		lhs.radius(),rhs.center().x,rhs.center().y,rhs.radius());
}

bool Entity_Calculate::intersect_cir2cir(Float& pt1_x,Float& pt1_y,Float& pt2_x,Float& pt2_y,
		Float center1_x,Float center1_y,Float rad_1,
		Float center2_x,Float center2_y,Float rad_2) const
{
	Float C1[3],C2[3];
	C1[0] = center1_x,C1[1] = center1_y;
	C1[2] = rad_1;
	C2[0] = center2_x,C2[1] = center2_y;
	C2[2] = rad_2;
	Float d,sa,sb,sina,sinb,cosa,cosb,x1,y1,x2,y2;
	//¼ÆËãÁ½Ô²ĞÄ¾àÀë
	d = sqrt((C1[0]-C2[0])*(C1[0]-C2[0]) + (C1[1]-C2[1])*(C1[1]-C2[1]));
	sa = fabs(C1[2]) + fabs(C2[2]);
	sb = fabs(fabs(C1[2]) - fabs(C2[2]));
	if ((d>sa||d<sb)&&(UEquFloat(d,sa)||UEquFloat(d,sb)))     //Á½Ô²ÏàÀëÇé¿ö 
		return false;
	//¼ÆËãcos b
	cosb = (C1[2] * C1[2] + d*d - C2[2]*C2[2])/(2*d*fabs(C1[2]));
	//¼ÆËãsin b
	sinb = sqrt(fabs(1.0 - cosb*cosb));
	if (C1[2]>0.0) sinb = -sinb ;    //µ±r1>0Ê±£¬sinbÈ¡¸ººÅ
	cosa = (C2[0] - C1[0])/d;     //¼ÆËãcosa
	sina = (C2[1] - C2[1])/d;     //¼ÆËãsina
	x1 = fabs(C1[2])*cosb;
	y1 = fabs(C1[2])*sinb;
	x2 = x1;
	y2 = -y1;
	if (EquFloat(d,sa)||EquFloat(d,sb))  //Á½Ô²ÄÚÇĞºÍÍâÇĞµÄÇé¿ö
	{
		pt1_x = x1*cosa + C1[0];
		pt1_y = x1*sina + C1[1];
		pt2_x = 0.0;
		pt2_y = 0.0;
	}
	else                                 //Á¬Ô²Ïà½»µÄÇé¿ö
	{
		pt1_x = x1*cosa - y1*sina + C1[0];
		pt1_y = x1*sina + y1*cosa + C1[1];
		pt2_x = x2*cosa - y2*sina + C1[0];
		pt2_y = x2*sina + y2*cosa + C1[1];
	}
	return true;
		
	
}
bool Entity_Calculate::circle_insect_arc(Point& pt1,Point& pt2,const Circle& circle,const RArc& arc) const
{
	Point arcst,arced,arcpt;
  arcst = arc.start();
  arced = arc.end();
	//arc.get_end_point(arcst,arced);
	return intersect_cir2arc(pt1.x,pt1.y,pt2.x,pt2.y,circle.center().x,circle.center().y,
		circle.radius(),arcst.x,arcst.y,arced.x,arced.y,arcpt.x,arcpt.y);
}
bool Entity_Calculate::intersect_cir2arc(Float& pt1_x,Float& pt1_y,Float& pt2_x,Float& pt2_y,
								   Float center_x,Float center_y,
								   Float rad,
								   Float arcst_x,Float arcst_y,
								   Float arced_x,Float arced_y,
								   Float arc_x,Float arc_y
								   ) const
{
	Float Arc[6];   //Ô²»¡×ø±ê£¬°´µÚÒ»µã£¬µÚ¶şµã£¬µÚÈıµãË³Ğò´æ´¢
	Float C1L1[3],C1L2[3];   //×é³ÉµÚÒ»¸öÔ²»¡µÄÁ½ÌõÖ±Ïß²ÎÊı
	Float CC1[3],CC2[3];     //Ô²ĞÄ×ø±êºÍÔ²ĞÄ°ë¾¶
	
	Arc[0] = arcst_x, Arc[1] = arcst_y;
	Arc[2] = arc_x,   Arc[3] = arc_y;
	Arc[4] = arced_x, Arc[5] = arced_y;
	CC2[0] = center_x;
	CC2[1] = center_y;
    CC2[2] = rad;
	//¸ù¾İ¸ø¶¨µÄÈıµã£¬¿ÉÈ·¶¨Á½ÌõÖ±Ïß£¬¾İÁ½ÌõÖ±ÏßÈ·¶¨Ô²»¡
	C1L1[0]=2*(arc_x-arcst_x);
	C1L1[1]=2*(arc_y-arcst_y);
	C1L1[2]=arc_x*arc_x+arc_y*arc_y-arcst_x*arcst_x-arcst_y*arcst_y;
	C1L2[0]=2*(arced_x-arc_x);
	C1L2[1]=2*(arced_y-arc_y);
	C1L2[2]=arced_x*arced_x+arced_y*arced_y-arc_x*arc_x-arc_y*arc_y;
	CC1[0] = (C1L1[1]*C1L2[2]-C1L2[1]*C1L1[2])/(C1L1[1]*C1L2[0]-C1L2[1]*C1L1[0]);
	CC1[1] = (C1L2[0]*C1L1[2]-C1L1[0]*C1L2[2])/(C1L1[1]*C1L2[0]-C1L2[1]*C1L1[0]);
	CC1[2] = sqrt((CC1[0]-arcst_x)*(CC1[0]-arcst_x) +
		(CC1[1]-arcst_y)*(CC1[1]-arcst_y));	
	Float d,sa,sb,sina,sinb,cosa,cosb,x1,y1,x2,y2;
    //Á½Ô²»¡Ô²ĞÄ¾àÀë
	d = sqrt((CC1[0]-CC2[0])*(CC1[0]-CC2[0]) + (CC1[1]-CC2[1])*(CC1[1]-CC2[1]));
	//Ô²»¡°ë¾¶Ö®ºÍ
	sa = fabs(CC1[2]) + fabs(CC2[2]);
	//Ô²»¡°ë¾¶Ö®²î
	sb = fabs(fabs(CC1[2]) - fabs(CC2[2]));
	if ((d>sa||d<sb)&&(UEquFloat(d,sa)||UEquFloat(d,sb)))     //Á½Ô²»¡ÏàÀëÇé¿ö 
		return FALSE;	
	//¼ÆËãcos b
	cosb = (CC1[2] * CC1[2] + d*d - CC2[2]*CC2[2])/(2*d*fabs(CC1[2]));
	//¼ÆËãsin b
	sinb = sqrt(fabs(1.0 - cosb*cosb));
	if (CC1[2]>0.0) sinb = -sinb ;    //µ±r1>0Ê±£¬sinbÈ¡¸ººÅ
	cosa = (CC2[0] - CC1[0])/d;     //¼ÆËãcosa
	sina = (CC2[1] - CC1[1])/d;     //¼ÆËãsina
	x1 = fabs(CC1[2])*cosb;
	y1 = fabs(CC1[2])*sinb;
	x2 = x1;
	y2 = -y1;
	
    Float intersec[4];         //ÁÙÊ±´æ·ÅÁ½½»µã	
	Float IntersecRadian1[2];  //½»µãÔÚÔ²»¡ÉÏµÄ»¡¶È
	Float radian1_max,radian1_min;      //½»µãÔÚµÚÒ»¸ö»¡ÉÏ»¡¶È×î´ó×îĞ¡Öµ
	BOOL Inter1 = FALSE,Inter2 = FALSE;  //Á½¸ö½»µãÊÇ·ñ´æÔÚµÄ±êÖ¾Î»
	
	if (EquFloat(d,sa)||EquFloat(d,sb))  //Ô²ÓëÔ²»¡ÄÚÇĞºÍÍâÇĞµÄÇé¿ö
	{
		intersec[0] = x1*cosa + CC1[0]; 
		intersec[1] = x1*sina + CC1[1]; 
		intersec[2] = 0.0 ;
		intersec[3] = 0.0 ;
		radian_Arc(radian1_max,radian1_min,Arc,CC1);
		radian_intersec(IntersecRadian1,intersec,CC1);
		if((EquFloat(radian1_max,IntersecRadian1[0]))||
			(EquFloat(radian1_min,IntersecRadian1[0]))||
			(EquFloat(radian1_max,IntersecRadian1[0]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[0]+2*pi))||
			((IntersecRadian1[0]<radian1_max)&&IntersecRadian1[0]>radian1_min)||
			((IntersecRadian1[0]+2*pi<radian1_max)&&IntersecRadian1[0]+2*pi>radian1_min))
		{
			pt1_x = intersec[0];
			pt1_y = intersec[1];
			pt2_x = 0.0;
			pt2_y = 0.0;
			return TRUE;
		}
		else   //¸Ãµã²»ÔÚµÚ¶şÌõÔ²»¡ÉÏ
		{
			pt1_x = 0.0;
			pt1_y = 0.0;
			return FALSE;
		}		
	}
	else   //Ô²ÓëÔ²»¡Ïà½»µÄÇé¿ö
	{
		intersec[0] = x1*cosa - y1*sina + CC1[0];
		intersec[1] = x1*sina + y1*cosa + CC1[1];
		intersec[2] = x2*cosa - y2*sina + CC1[0];
		intersec[3] = x2*sina + y2*cosa + CC1[1];
		
		
		radian_Arc(radian1_max,radian1_min,Arc,CC1);
		radian_intersec(IntersecRadian1,intersec,CC1);
		//ÅĞ¶ÏµÚÒ»¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
		if((EquFloat(radian1_max,IntersecRadian1[0]))||
			(EquFloat(radian1_min,IntersecRadian1[0]))||
			(EquFloat(radian1_max,IntersecRadian1[0]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[0]+2*pi))||
			((IntersecRadian1[0]<radian1_max)&&IntersecRadian1[0]>radian1_min)||
			((IntersecRadian1[0]+2*pi<radian1_max)&&IntersecRadian1[0]+2*pi>radian1_min))
		{
				pt1_x = intersec[0];
				pt1_y = intersec[1];
				Inter1 = TRUE;
		}
		//ÅĞ¶ÏµÚ¶ş¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
		if((EquFloat(radian1_max,IntersecRadian1[1]))||
			(EquFloat(radian1_min,IntersecRadian1[1]))||
			(EquFloat(radian1_max,IntersecRadian1[1]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[1]+2*pi))||
			((IntersecRadian1[1]<radian1_max)&&IntersecRadian1[1]>radian1_min)||
			((IntersecRadian1[1]+2*pi<radian1_max)&&IntersecRadian1[1]+2*pi>radian1_min))
		{
			pt2_x = intersec[2];
			pt2_y = intersec[3];
			Inter2 = TRUE;
		}
		if(Inter1||Inter2)			
			return TRUE;
		else
		{
			pt1_x = 0.0;
			pt1_y = 0.0;
			pt2_x = 0.0;
			pt2_y = 0.0;
			return FALSE;
		}		
	}
}
bool Entity_Calculate::arc_insect_arc(Point& pt1,
                                      Point& pt2,
                                      const RArc& arc1,
                                      const RArc& arc2) const
{
  Point a1p1, a1p2, a1p3;
  Point a2p1, a2p2, a2p3;
  a1p1 = arc1.start();
  a1p2 = arc1.path();
  a1p3 = arc1.end();
  //arc1.getdata(a1p1,a1p2,a1p3);
  a2p1 = arc2.start();
  a2p2 = arc2.path();
  a2p3 = arc2.end();
  //arc2.getdata(a2p1,a2p2,a2p3);
  return intersect_arc2arc (pt1.x, pt1.y, 
                            pt2.x, pt2.y,
                            a1p1.x,a1p1.y,
                            a1p3.x,a1p3.y,
                            a1p2.x,a1p2.y,
                            a2p1.x,a2p1.y,
                            a2p3.x,a2p3.y,
                            a2p2.x,a2p2.y);

  
//	Point mest,meed,mept;
//	arc1.get_end_point(mest,meed);
//	Point arcst,arced,arcpt;
//	arc2.get_end_point(arcst,arced);
//	return intersect_arc2arc(pt1.x,pt1.y,pt2.x,pt2.y,mest.x,mest.y,meed.x,meed.y,
//		mept.x,mept.y,arcst.x,arcst.y,arced.x,arced.y,arcpt.x,arcpt.y);
}
bool Entity_Calculate::intersect_arc2arc(Float& pt1_x,  Float& pt1_y,
                                         Float& pt2_x,  Float& pt2_y,
								                         Float arcst1_x,Float arcst1_y,
								                         Float arced1_x,Float arced1_y,
								                         Float arc1_x,  Float arc1_y,
								                         Float arcst2_x,Float arcst2_y,
								                         Float arced2_x,Float arced2_y,
								                         Float arc2_x,  Float arc2_y) const
{
	Float Arc1[6],Arc2[6];   //Ô²»¡×ø±ê£¬°´µÚÒ»µã£¬µÚ¶şµã£¬µÚÈıµãË³Ğò´æ´¢
	Float C1L1[3],C1L2[3];   //×é³ÉµÚÒ»¸öÔ²»¡µÄÁ½ÌõÖ±Ïß²ÎÊı
	Float C2L1[3],C2L2[3];   //×é³ÉµÚ¶ş¸öÔ²»¡µÄÁ½ÌõÖ±Ïß²ÎÊı
	Float CC1[3],CC2[3];     //Ô²ĞÄ×ø±êºÍÔ²ĞÄ°ë¾¶
	
	Arc1[0] = arcst1_x, Arc1[1] = arcst1_y;
	Arc1[2] = arc1_x,   Arc1[3] = arc1_y;
	Arc1[4] = arced1_x, Arc1[5] = arced1_y;
	Arc2[0] = arcst2_x, Arc2[1] = arcst2_y;
	Arc2[2] = arc2_x,   Arc2[3] = arc2_y;
	Arc2[4] = arced2_x, Arc2[5] = arced2_y;
	//¸ù¾İ¸ø¶¨µÄÈıµã£¬¿ÉÈ·¶¨Á½ÌõÖ±Ïß£¬¾İÁ½ÌõÖ±ÏßÈ·¶¨Ô²»¡
	C1L1[0]=2*(arc1_x-arcst1_x);
	C1L1[1]=2*(arc1_y-arcst1_y);
	C1L1[2]=arc1_x*arc1_x+arc1_y*arc1_y-arcst1_x*arcst1_x-arcst1_y*arcst1_y;
	C1L2[0]=2*(arced1_x-arc1_x);
	C1L2[1]=2*(arced1_y-arc1_y);
	C1L2[2]=arced1_x*arced1_x+arced1_y*arced1_y-arc1_x*arc1_x-arc1_y*arc1_y;
	CC1[0] = (C1L1[1]*C1L2[2]-C1L2[1]*C1L1[2])/(C1L1[1]*C1L2[0]-C1L2[1]*C1L1[0]);
	CC1[1] = (C1L2[0]*C1L1[2]-C1L1[0]*C1L2[2])/(C1L1[1]*C1L2[0]-C1L2[1]*C1L1[0]);
	CC1[2] = sqrt((CC1[0]-arcst1_x)*(CC1[0]-arcst1_x) +
		(CC1[1]-arcst1_y)*(CC1[1]-arcst1_y));
	//¸ù¾İ¸ø¶¨µÄÈıµã£¬¿ÉÈ·¶¨Á½ÌõÖ±Ïß£¬¾İÁ½ÌõÖ±ÏßÈ·¶¨Ô²»¡
	C2L1[0]=2*(arc2_x-arcst2_x);
	C2L1[1]=2*(arc2_y-arcst2_y);
	C2L1[2]=arc2_x*arc2_x+arc2_y*arc2_y-arcst2_x*arcst2_x-arcst2_y*arcst2_y;
	C2L2[0]=2*(arced2_x-arc2_x);
	C2L2[1]=2*(arced2_y-arc2_y);
	C2L2[2]=arced2_x*arced2_x+arced2_y*arced2_y-arc2_x*arc2_x-arc2_y*arc2_y;
	CC2[0] = (C2L1[1]*C2L2[2]-C2L2[1]*C2L1[2])/(C2L1[1]*C2L2[0]-C2L2[1]*C2L1[0]);
	CC2[1] = (C2L2[0]*C2L1[2]-C2L1[0]*C2L2[2])/(C2L1[1]*C2L2[0]-C2L2[1]*C2L1[0]);
	CC2[2] = sqrt((CC2[0]-arcst2_x)*(CC2[0]-arcst2_x) +
		(CC2[1]-arcst2_y)*(CC2[1]-arcst2_y));
	Float d,sa,sb,sina,sinb,cosa,cosb,x1,y1,x2,y2;
    //Á½Ô²»¡Ô²ĞÄ¾àÀë
	d = sqrt((CC1[0]-CC2[0])*(CC1[0]-CC2[0]) + (CC1[1]-CC2[1])*(CC1[1]-CC2[1]));
	//Ô²»¡°ë¾¶Ö®ºÍ
	sa = fabs(CC1[2]) + fabs(CC2[2]);
	//Ô²»¡°ë¾¶Ö®²î
	sb = fabs(fabs(CC1[2]) - fabs(CC2[2]));
	if ((d>sa||d<sb)&&(UEquFloat(d,sa)||UEquFloat(d,sb)))     //Á½Ô²»¡ÏàÀëÇé¿ö 
		return FALSE;
	
	//¼ÆËãcos b
	cosb = (CC1[2] * CC1[2] + d*d - CC2[2]*CC2[2])/(2*d*fabs(CC1[2]));
	//¼ÆËãsin b
	sinb = sqrt(fabs(1.0 - cosb*cosb));
	if (CC1[2]>0.0) sinb = -sinb ;    //µ±r1>0Ê±£¬sinbÈ¡¸ººÅ
	cosa = (CC2[0] - CC1[0])/d;     //¼ÆËãcosa
	sina = (CC2[1] - CC1[1])/d;     //¼ÆËãsina
	x1 = fabs(CC1[2])*cosb;
	y1 = fabs(CC1[2])*sinb;
	x2 = x1;
	y2 = -y1;
	
    Float intersec[4];        //ÁÙÊ±´æ·ÅÁ½½»µã
	//½»µãÔÚÔ²»¡Ò»ºÍÔ²»¡¶şÉÏµÄ»¡¶È
	Float IntersecRadian1[2],IntersecRadian2[2];  
	Float radian1_max,radian1_min;      //½»µãÔÚµÚÒ»¸ö»¡ÉÏ»¡¶È×î´ó×îĞ¡Öµ
	Float radian2_max,radian2_min;      //½»µãÔÚµÚ¶ş¸ö»¡ÉÏ»¡¶È×î´ó×îĞ¡Öµ
	BOOL Inter1 = FALSE,Inter2 = FALSE;  //Á½¸ö½»µãÊÇ·ñ´æÔÚµÄ±êÖ¾Î»
	
	if (EquFloat(d,sa)||EquFloat(d,sb))  //Á½Ô²ÄÚÇĞºÍÍâÇĞµÄÇé¿ö
	{
		intersec[0] = x1*cosa + CC1[0]; 
		intersec[1] = x1*sina + CC1[1]; 
		intersec[2] = 0.0 ;
		intersec[3] = 0.0 ;
		radian_Arc(radian1_max,radian1_min,Arc1,CC1);
		radian_Arc(radian2_max,radian2_min,Arc2,CC2);
		radian_intersec(IntersecRadian1,intersec,CC1);
		radian_intersec(IntersecRadian2,intersec,CC2);
		if((EquFloat(radian1_max,IntersecRadian1[0]))||
			(EquFloat(radian1_min,IntersecRadian1[0]))||
			(EquFloat(radian1_max,IntersecRadian1[0]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[0]+2*pi))||
			((IntersecRadian1[0]<radian1_max)&&IntersecRadian1[0]>radian1_min)||
			((IntersecRadian1[0]+2*pi<radian1_max)&&IntersecRadian1[0]+2*pi>radian1_min))
		{
			if ((EquFloat(radian2_max,IntersecRadian2[0]))||
				(EquFloat(radian2_min,IntersecRadian2[0]))||
				(EquFloat(radian2_max,IntersecRadian2[0]+2*pi))||
				(EquFloat(radian2_min,IntersecRadian2[0]+2*pi))||
				((IntersecRadian2[0]<radian2_max)&&IntersecRadian2[0]>radian2_min)||
				((IntersecRadian2[0]+2*pi<radian2_max)&&IntersecRadian2[0]+2*pi>radian2_min))
			{
				pt1_x = intersec[0];
				pt1_y = intersec[1];
				pt2_x = 0.0;
				pt2_y = 0.0;
				return TRUE;
			}
			else   //¸Ãµã²»ÔÚµÚ¶şÌõÔ²»¡ÉÏ
			{
				pt1_x = 0.0;
				pt1_y = 0.0;
				return FALSE;
			}
		}
		else    //¸Ãµã²»ÔÚµÚÒ»ÌõÔ²»¡ÉÏ
		{
			pt1_x = 0.0;
			pt1_y = 0.0;
			return FALSE;
		}
	}
	else   //Á½Ô²Ïà½»µÄÇé¿ö
	{
		intersec[0] = x1*cosa - y1*sina + CC1[0];
		intersec[1] = x1*sina + y1*cosa + CC1[1];
		intersec[2] = x2*cosa - y2*sina + CC1[0];
		intersec[3] = x2*sina + y2*cosa + CC1[1];
		
		
		radian_Arc(radian1_max,radian1_min,Arc1,CC1);
		radian_Arc(radian2_max,radian2_min,Arc2,CC2);
		radian_intersec(IntersecRadian1,intersec,CC1);
		radian_intersec(IntersecRadian2,intersec,CC2);
		//ÅĞ¶ÏµÚÒ»¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
		if((EquFloat(radian1_max,IntersecRadian1[0]))||
			(EquFloat(radian1_min,IntersecRadian1[0]))||
			(EquFloat(radian1_max,IntersecRadian1[0]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[0]+2*pi))||
			((IntersecRadian1[0]<radian1_max)&&IntersecRadian1[0]>radian1_min)||
			((IntersecRadian1[0]+2*pi<radian1_max)&&IntersecRadian1[0]+2*pi>radian1_min))
		{
			if ((EquFloat(radian2_max,IntersecRadian2[0]))||
				(EquFloat(radian2_min,IntersecRadian2[0]))||
				(EquFloat(radian2_max,IntersecRadian2[0]+2*pi))||
				(EquFloat(radian2_min,IntersecRadian2[0]+2*pi))||
				((IntersecRadian2[0]<radian2_max)&&IntersecRadian2[0]>radian2_min)||
				((IntersecRadian2[0]+2*pi<radian2_max)&&IntersecRadian2[0]+2*pi>radian2_min))
			{
				pt1_x = intersec[0];
				pt1_y = intersec[1];
				Inter1 = TRUE;
			}
		}
		//ÅĞ¶ÏµÚ¶ş¸ö½»µãÊÇ·ñÔÚÁ½¶ÎÔ²»¡ÉÏ
		if((EquFloat(radian1_max,IntersecRadian1[1]))||
			(EquFloat(radian1_min,IntersecRadian1[1]))||
			(EquFloat(radian1_max,IntersecRadian1[1]+2*pi))||
			(EquFloat(radian1_min,IntersecRadian1[1]+2*pi))||
			((IntersecRadian1[1]<radian1_max)&&IntersecRadian1[1]>radian1_min)||
			((IntersecRadian1[1]+2*pi<radian1_max)&&IntersecRadian1[1]+2*pi>radian1_min))
		{
			if ((EquFloat(radian2_max,IntersecRadian2[1]))||
				(EquFloat(radian2_min,IntersecRadian2[1]))||
				(EquFloat(radian2_max,IntersecRadian2[1]+2*pi))||
				(EquFloat(radian2_min,IntersecRadian2[1]+2*pi))||
				((IntersecRadian2[1]<radian2_max)&&IntersecRadian2[1]>radian2_min)||
				((IntersecRadian2[1]+2*pi<radian2_max)&&IntersecRadian2[1]+2*pi>radian2_min))
			{
				pt2_x = intersec[2];
				pt2_y = intersec[3];
				Inter2 = TRUE;
			}
		}
		if(Inter1||Inter2)
			return TRUE;
		else
		{
			pt1_x = 0.0;
			pt1_y = 0.0;
			pt2_x = 0.0;
			pt2_y = 0.0;
			return FALSE;
		}		
	}
}

/*
// Float area(const std::vector<Point>& pts)
// {
//   if(pts.size() < 3){
//     return 0;
//   }
//   Float myarea=-1;
//   Float a_area=0;
//   Line   ln  ;
//   Point  foot;
//   int i=0;
//   for(i=0; i<pts.size(); i++){
//     if(!area_by_side(pts, i, a_area)){
//       continue;
//     }
//     if(myarea < 0){
//       myarea = a_area;
//     }else{
//       myarea = min(myarea, a_area);
//     }
//   }
//   return myarea;
// }
*/


bool area_by_side(const std::vector<Point>& pts, int index, Float& myarea)
{
  if(pts.size() < 3){
    return false;
  }
  Point foot;
  Normal nor1, nor2;
  Line ln(pts[index+0], pts[index+1]);
  Normal lnnor(ln);
  lnnor.set_unit();
  Float max_dis=0;
  Float min_len=lnnor.dis_by_way(getat(pts,index+0));
  Float max_len=lnnor.dis_by_way(getat(pts,index+1));
  int i=0;
  for(i=2; i<pts.size(); i++){
    foot = ln.perpendicular(getat(pts,index+i));
    max_len = max(max_len , lnnor.dis_by_way(getat(pts,index+i)));
    min_len = min(min_len , lnnor.dis_by_way(getat(pts,index+i)));
    if(foot == getat(pts,index+i)){
      continue;
    }
    nor1.set_data(foot, getat(pts,index+i));
    nor1.set_unit();
    if(nor2.is_zero_normal()){
      nor2 = nor1;
    }else if(nor1 != nor2){
      return false;
    }
    max_dis = max(max_dis , foot.distanceto(getat(pts,index+i)));    
  }
  myarea = (max_len-min_len)*max_dis;
  return true;
}



////¸ù¾İ½Ç¶ÈÇóÆäËùÔÚ×ø±êÖá¡¢ÏóÏŞÎ»ÖÃ.
DEGREE_POS degree_pos(Float deg)
{
  std_degree(deg);
  if(EquFloat(deg,0)){
    return AXIS_0;
  }
  else if(LessThen(deg,90)){
    return QD_1;
  }
  else if(EquFloat(deg,90)){
    return AXIS_90;
  }
  else if(LessThen(deg,180)){
    return QD_2;
  }
  else if(EquFloat(deg,180)){
    return AXIS_180;
  }
  else if(LessThen(deg,270)){
    return QD_3;
  }
  else if(EquFloat(deg,270)){
    return AXIS_270;
  }
  else{
    return QD_4;
  }
}

}//namespace
