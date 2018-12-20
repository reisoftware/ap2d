// Matrix.cpp: implementation of the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix_d.h"

#include "Entity.h"
#include "Point.h"
#include "Line.h"
#include "Normal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma warning(push)
	#pragma warning(disable:4244)

namespace dlhml{
void Matrix::init()
{
	//x
	mat[0][0]=1;
	mat[1][0]=0;
	mat[2][0]=0;
	mat[3][0]=0;

	//y
	mat[0][1]=0;
	mat[1][1]=1;
	mat[2][1]=0;
	mat[3][1]=0;

	//z
	mat[0][2]=0;
	mat[1][2]=0;
	mat[2][2]=1;
	mat[3][2]=0;

	//
	mat[0][3]=0;
	mat[1][3]=0;
	mat[2][3]=0;
	mat[3][3]=1;
}
Matrix::Matrix()
{
	init();
}
Matrix::Matrix(const Matrix& rhs)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = rhs.mat[i][j];
		}
	}
}
Matrix& Matrix::operator=(const Matrix& rhs)
{
	if(this == &rhs)
		return *this;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = rhs.mat[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator=(Float (&m)[4][4])
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j] = m[i][j];
		}
	}
	return *this;
}
Matrix::~Matrix()
{

}
Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]+rhs.mat[i][j];
		}
	}
	return m;
}
Matrix Matrix::operator-(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]-rhs.mat[i][j];
		}
	}
	return m;
}
Matrix Matrix::operator*(const Matrix& rhs) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			Float sum = 0;
			for(int k=0;k<4;++k)
				sum += mat[i][k]*rhs.mat[k][j];
			m.mat[i][j] = sum;
		}
	}
	return m;
}
Matrix Matrix::operator*(Float val) const
{
	Matrix m;
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			m.mat[i][j]=mat[i][j]*val;
		}
	}
	return m;
}
Matrix& Matrix::operator+=(const Matrix& rhs)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]+=rhs.mat[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]-=rhs.mat[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator*=(const Matrix& rhs)
{
	Matrix m;
	m = *this * rhs;
	*this = m;
	return *this;
}
Matrix& Matrix::operator*=(Float val)
{
	for(int j=0;j<4;++j){
		for(int i=0;i<4;++i){
			mat[i][j]*=val;
		}
	}
	return *this;
}
void Matrix::set_move(Float dx, Float dy, Float dz)
{
	init();
	mat[3][0]=dx;
	mat[3][1]=dy;
	mat[3][2]=dz;
}
void Matrix::set_scale(Float dx, Float dy, Float dz)
{
	init();
	mat[0][0]=dx;
	mat[1][1]=dy;
	mat[2][2]=dz;
}
void Matrix::set_rotation(Float alpha, Float beta, Float gamma)
{
	init();
	//x
	mat[0][0]=cos(beta)*cos(gamma);
	mat[1][0]=sin(alpha)*sin(beta)*cos(gamma)-cos(alpha)*sin(gamma);
	mat[2][0]=cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma);
	//y
	mat[0][1]=cos(beta)*sin(gamma);
	mat[1][1]=sin(alpha)*sin(beta)*sin(gamma)+cos(alpha)*cos(gamma);
	mat[2][1]=cos(alpha)*sin(beta)*sin(gamma)-sin(alpha)*cos(gamma);
	//z
	mat[0][2]=-sin(beta);
	mat[1][2]=sin(alpha)*cos(beta);
	mat[2][2]=cos(alpha)*cos(beta);
}
void Matrix::set_x_rotation(Float alpha)
{
	init();
	//y
	mat[1][1]=cos(alpha);
	mat[2][1]=-sin(alpha);
	//z
	mat[1][2]=sin(alpha);
	mat[2][2]=cos(alpha);
}

void Matrix::set_y_rotation(Float beta)
{
	init();
	//x
	mat[0][0]=cos(beta);
	mat[2][0]=sin(beta);
	//z
	mat[0][2]=-sin(beta);
	mat[2][2]=cos(beta);
}

void Matrix::set_z_rotation(Float gamma)
{
	init();
	//x
	mat[0][0]=cos(gamma);
	mat[1][0]=-sin(gamma);
	//y
	mat[0][1]=sin(gamma);
	mat[1][1]=cos(gamma);
}
void Matrix::set_x_axis_mirror()
{
	init();
	mat[1][1]=-1;
}
void Matrix::set_y_axis_mirror()
{
	init();
	mat[0][0]=-1;
}

//求矩阵的逆，算法得自网上。
//采用部分主元法的高斯消去法求方阵的逆矩阵
void Matrix::inverse()
{
	int i,j,k;
	Float lMax,temp;

	Float B[4][4];
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(i != j)
				B[i][j] = 0.0;
			else
				B[i][j] = 1.0;
		}
	}

	for(i=0;i<4;i++){
		//寻找主元
		lMax = mat[i][i];
		k = i;
		for(j=i+1;j<4;j++){ //扫描从i+1到n的各行
			if( fabs(mat[j][i]) > fabs(lMax)){
				lMax = mat[j][i];
				k = j;
			}
		}
		//如果主元所在行不是第i行，进行行交换
		if(k!=i){
			for(j=0;j<4;j++){
				temp = mat[i][j] ;
				mat[i][j] = mat[k][j];
				mat[k][j] = temp;
				//B伴随计算
				temp = B[i][j];
				B[i][j] = B[k][j];
				B[k][j] = temp;
			}
		}
		//判断主元是否是0，如果是，则矩阵A不是满秩矩阵，不存在逆矩阵
		if(mat[i][i] == 0) return ;
		//消去A的第i列除去i行以外的各行元素
		temp = mat[i][i];
		for(j=0;j<4;j++){
			mat[i][j] = mat[i][j] / temp; //主对角线上元素变成1
			B[i][j] = B[i][j] / temp; //伴随计算
		}

		for(j=0;j<4;j++){ //行 0 -> n
			if(j!=i){  //不是第i行
				temp = mat[j][i];
				for(k=0;k<4;k++){ // j行元素 - i行元素* j行i列元素
					mat[j][k] = mat[j][k] - mat[i][k] * temp;
					B[j][k] = B[j][k] - B[i][k] * temp;
				}
			}
		}
	}

	Matrix t;
	t = B;
	*this *= t;

}

void Matrix::set_move(const Point & st, const Point& ed)
{
  set_move(Normal(st,ed));
}
void Matrix::set_move(const Normal& nor)
{
  set_move(nor.x(), nor.y(), nor.z());
}
void Matrix::set_move(const Point & pt )
{
  set_move(pt.x, pt.y, pt.z);
}
void Matrix::set_move(const Line & ln )
{
  Normal nor;
  nor.set_data(ln.start(),ln.end());
  set_move(nor);
}


}//namespace
#pragma warning(pop)

/*
相对过点（x，y）与x轴正向夹角为a的直线的对称变换
cosa*cosa-sina*sina					2*sina*cosa							0
2*sina*cosa							sina*sina-cosa*cosa					0
x(sinasina-cosacosa)-2ysinacosa+x	y(cosacosa-sinasina)-2xsinacosa+y	1
*/
