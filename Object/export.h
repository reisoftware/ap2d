
#ifndef _EXPORT_H_DLHML_
#define _EXPORT_H_DLHML_

#include <vector>
#include <math.h>


#ifdef OBJECT_EXPORTS
#define OBJECT_API __declspec(dllexport)
#else
#define OBJECT_API __declspec(dllimport)
#endif

namespace dlhml{
struct OBJECT_API Error  
{
	enum info	{ OK				  =	0	,	          //正常，顺利
				  FileOpenFalse	  =	1	,	         //文件打开失败
				  FileOpenMode		=	2	,	        //文件打开参数错误(rb,wb)
				  FileCloseFalse	=	3	,	       //文件关闭失败
				  NullObjectP		  =	4	,	      //空LObject指针
				  NullDatabase		=	5	,	     //空数据集
				  ObjectIDbig		  =	6	,	    //ents id 超出范围
				  ObjectErase		  =	7	,	   //object已删除
				  ZeroObjectId		=	8	,	  //实体无id
				  NullObjectIdAry	=	9	,	 //空实体id数组
				  NullMaterialAry	=	10,	//空材料表模板
				  FileReadFalse	=	11,	//读失败
				  FileWriteFalse	=	12	//写失败
				};

// public:
// 	Error():ct_(Error){}
// private:
// 	MCT_DEF
};

typedef		Error::info		errorinfo;

typedef double Float;

const Float pi  = 3.14159265;
const Float pi2 = 2*pi;

const int MAX_DXF_LEN  = 512;
const int MAX_DXF_BIG  = 256;
const int LINE_ELEM_MAX_NUM  = 30;


const Float FLOAT_PRECISION_L = 0.0001;

inline bool WINAPI EquFloat(const Float& a, const Float& b)
{
	return fabs(a - b) < FLOAT_PRECISION_L;
}
inline bool WINAPI UEquFloat(const Float& a, const Float& b)
{
	return !EquFloat(a,b);
}
inline Float cos(Float f)
{
	return static_cast<Float>(::cos(f));
}
inline Float sin(Float f)
{
	return static_cast<Float>(::sin(f));
}
inline Float acos(Float f)
{
	return static_cast<Float>(::acos(f));
}
inline Float asin(Float f)
{
	return static_cast<Float>(::asin(f));
}
inline Float sqrt(Float f)
{
	return static_cast<Float>(::sqrt(f));
}
inline bool WINAPI LessThen(const double& a, const double& b)
{
	return b - a > FLOAT_PRECISION_L;
}
inline bool WINAPI MoreThen(const double& a, const double& b)
{
	return a - b > FLOAT_PRECISION_L;
}
inline bool WINAPI LessEqu(const double& a, const double& b)
{
	return a < b + FLOAT_PRECISION_L;
}
inline bool WINAPI MoreEqu(const double& a, const double& b)
{
	return a > b - FLOAT_PRECISION_L;
}

template<class T> 
void setat(std::vector<T>& ts, int i, const T& t)
{
  while(i<0) i+=ts.size();
  ts[i%ts.size()] = t;
}
template<class T>
const T& getat(const std::vector<T>& ts, int i)
{
  while(i<0) i+=ts.size();
  return ts[i%ts.size()];
}

inline double degree_2_radian(double a)
{
  return a*pi/180.0;
}

inline double radian_2_degree(double r)
{
  return r*180.0/pi;
}

inline void std_degree(double& a)
{
  while(MoreEqu(a,360.0)){
    a-=360.0;
  }
  while(LessThen(a,0)){
    a+=360.0;
  }
}

inline void std_radian(double& r)
{
  while(MoreEqu(r,2*pi)){
    r-=(2*pi);
  }
  while(LessThen(r,0)){
    r+=(2*pi);
  }
}

inline void radian_2_quadrand(double radian, int& quadrand)
{
  std_radian(radian);
  if     (MoreEqu(radian,0)    && LessThen(radian,pi/2   )){quadrand=1;}
  else if(MoreEqu(radian,pi/2) && LessThen(radian,pi     )){quadrand=2;}
  else if(MoreEqu(radian,pi  ) && LessThen(radian,pi*3/2 )){quadrand=3;}
  else                                                     {quadrand=4;}
}
inline void degree_2_quadrand(double degree, int& quadrand)
{
  double radian = degree_2_radian(degree);
  //degree_2_radian(degree, radian);
  radian_2_quadrand(radian, quadrand);
}

inline void radian_2_quadrand_re(double radian, int& quadrand)
{
  std_radian(radian);
  if     (MoreThen(radian,0)    && LessEqu(radian,pi/2   )){quadrand=1;}
  else if(MoreThen(radian,pi/2) && LessEqu(radian,pi     )){quadrand=2;}
  else if(MoreThen(radian,pi  ) && LessEqu(radian,pi*3/2 )){quadrand=3;}
  else                                                     {quadrand=4;}
}
inline void degree_2_quadrand_re(double degree, int& quadrand)
{
  double radian = degree_2_radian(degree);
  //degree_2_radian(degree, radian);
  radian_2_quadrand_re(radian, quadrand);
}


extern "C" OBJECT_API bool string_copy(LPTSTR& dest,LPCTSTR src);
extern "C" OBJECT_API void string_delete(LPTSTR& str);

/*
void string_replace(string & strBig, const string & strsrc, const string &strdst)
{
	string::size_type pos=0;
	string::size_type srclen=strsrc.size();
	string::size_type dstlen=strdst.size();
	while( (pos=strBig.find(strsrc, pos)) != string::npos)
	{
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}
*/

}

#endif //_EXPORT_H_DLHML_
