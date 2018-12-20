// Rect.h: interface for the Rect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_RECT_H__F4BFFA50_F5FE_4D4F_B991_4EE6755B7545__INCLUDED_
#define AFX_RECT_H__F4BFFA50_F5FE_4D4F_B991_4EE6755B7545__INCLUDED_

#include "export.h"
#include "Color.h"
#include "../afc/iolua.h"

namespace dlhml{
class Matrix;
class File;
class Point;
class OBJECT_API Rect  
{
public:
	Rect();
	Rect(const Rect& rhs);
	explicit Rect(const RECT& rect);
	Rect& operator=(const Rect& rhs){
		xmin_ = rhs.xmin_; 
		ymin_ = rhs.ymin_;
		xmax_ = rhs.xmax_;
		ymax_ = rhs.ymax_;
    seled_= rhs.seled_;
		return *this;
	}
	Rect& operator=(const RECT& rect);
	operator RECT() const{
		RECT rc;
		rc.left = static_cast<long>(min(xmin_,xmax_)); 
		rc.top = static_cast<long>(min(ymin_,ymax_));
		rc.right = static_cast<long>(max(xmin_,xmax_));
		rc.bottom = static_cast<long>(max(ymin_,ymax_));
		return rc;
	}
	~Rect(){}

	bool operator==(const Rect& rc) const{
		return EquFloat(xmin_,rc.xmin_) && 
			EquFloat(ymin_,rc.ymin_) && 
			EquFloat(xmax_,rc.xmax_) && 
			EquFloat(ymax_,rc.ymax_);
	}

	void set_reverse_minmax(){
		xmin_ = ymin_ = 3.40282e+038f;	//max float value
		xmax_ = ymax_ = -3.40282e+038f;	//min float value
	}

public:
  void update();

	void setdata(const Point& st,const Point& ed);

	void save_lua(std::ofstream &out,char *name,int tab_num);
	void open_lua(lua_State *l,char *name);

	void get_str_sub(char *name);
	void set_from_str_sub(char *name);

	Float height() const{		return ymax_-ymin_;	}
	Float width() const{		return xmax_-xmin_;	}

	void transformby(const Matrix& mat);
	bool intersect(const Rect& rect) const;
	bool envelop(const Rect& rc) const;

	void load(File& in);
	void save(const File& out) const;

	Float xmin() const{		return xmin_;	}
	Float ymin() const{		return ymin_;	}
	Float xmax() const{		return xmax_;	}
	Float ymax() const{		return ymax_;	}

	void xmin(Float val) { xmin_=val;	}
	void ymin(Float val) { ymin_=val;	}
	void xmax(Float val) { xmax_=val;	}
	void ymax(Float val) { ymax_=val;	}
private:
	Float xmin_;
	Float ymin_;
	Float xmax_;
	Float ymax_;

public:
	Rect operator*(Float f) const;
	Rect& operator*=(Float f) ;

public:
  void selected   (bool sel  ){seled_=sel   ;}
  void color_index(int  index){color_=index ;}

  bool selected   ()const{return seled_         ;}
  int	 color_index()const{return color_.index() ;}

private:
  bool  seled_;
  Color color_;		      
	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_RECT_H__F4BFFA50_F5FE_4D4F_B991_4EE6755B7545__INCLUDED_)
