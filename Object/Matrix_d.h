// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_MATRIX_H__4D09DE2C_D43E_4ADD_A55B_8E4B478E9C7F__INCLUDED_
#define AFX_MATRIX_H__4D09DE2C_D43E_4ADD_A55B_8E4B478E9C7F__INCLUDED_

#include "export.h"
#include "vector"
#include "Entity.h"

namespace dlhml{

//enum MAT_TYPE {MOVE_MAT, RAOTA_MAT, MIRROR_MAT, SCALE_MAT};
//enum MAT_TYPE {NONE_MAT, ZRAOTA_MAT, MIRROR_MAT};
////ZRAOTA_MAT:=>>Cloud_Line/Text/Dimension/Ln_Dim/Ln_Dim_Block
////MIRROR_MAT:=>>Cloud_Line


class Point;
class Normal;
class Entity;
class Line;

class OBJECT_API Matrix  
{
public:
	Matrix();
	Matrix(const Matrix& rhs);
	Matrix& operator=(const Matrix& rhs);
	Matrix& operator=(Float (&m)[4][4]);
	~Matrix();

	Matrix operator+(const Matrix& rhs) const;
	Matrix operator-(const Matrix& rhs) const;
	Matrix operator*(const Matrix& rhs) const;
	Matrix operator*(Float val) const;

	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(Float val);

	void reset() {init();}
	Float value(int row,int col) const {
		return mat[row][col];
	}

	void set_move(Float dx, Float dy, Float dz);
  void set_move(const Point & st, const Point& ed);
	void set_move(const Normal& nor);
  void set_move(const Point & pt );
	void set_move(const Line  & ln );
	void set_scale(Float dx, Float dy, Float dz);
	/*三维空间中的点先绕X轴旋转alpha，然后又绕Y轴旋转beta，再绕Z轴旋转gamma角度*/
	void set_rotation_radian(Float alpha, Float beta, Float gamma);//radian
	void set_x_rotation_radian(Float alpha);//radian
	void set_y_rotation_radian(Float beta);//radian
	void set_z_rotation_radian(Float gamma);//radian
  void set_rotation_degree(Float alpha, Float beta, Float gamma);
  void set_x_rotation_degree(Float alpha);
  void set_y_rotation_degree(Float beta);
  void set_z_rotation_degree(Float gamma);
	void set_x_axis_mirror();
	void set_y_axis_mirror();

	//求逆
	void inverse();
private:
	void init();
	Float mat[4][4];


//public:
//  //void mat_type(MAT_TYPE t) {type_=t     ;}
//  MAT_TYPE mat_type()const      {return type_;}
//  Float    rota_radian()const   {return rota_radian_;}
//  Float    scale_times()const   {return scale_times_;}
//
//private:
//  MAT_TYPE type_;
//  Float    rota_radian_;
//  Float    scale_times_;
//private:
//  void init_type();
private:
	MCT_DEF
};

template<class Entity>
inline void matcal(std::vector<Entity*>& entities, const Matrix& mat);


//inline
template<class Entity>
inline void matcal(std::vector<Entity*>& e, const Matrix& mat)
{
  int i=0;
  for(i=0; i<e.size(); i++){
    if(e[i]==NULL){
      continue;
    }
    e[i]->transformby(mat);
  }
}

}
#endif // !defined(AFX_MATRIX_H__4D09DE2C_D43E_4ADD_A55B_8E4B478E9C7F__INCLUDED_)
