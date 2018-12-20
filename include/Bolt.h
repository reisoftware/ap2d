#ifndef __BOLT_H__
#define __BOLT_H__
#include <vector>

typedef unsigned int MemNo;
const MemNo MAIN_MEMBER = 0;//main member
const MemNo SUB_MEMBER = 1;//sub member

class BoltPlate
{
	friend class CBolt;
public:
	enum PlateSite{FlangePlate,WebPlate,JointPlate};
	BoltPlate(MemNo memno,double t,PlateSite plateSite):memberno_(memno),t_(t),plateSite_(plateSite) {}

	MemNo  memno() const  {return memberno_;}
	double t() const {return t_;}
	PlateSite platesite() const {return plateSite_;}

	
private:
	MemNo memberno_;
	PlateSite plateSite_;
	double t_;//the plate thick;
};
class Jnt_Axis;
class AFX_EXT_CLASS CBolt
{
public:
	CBolt();
	double D() const ;
	double L() const ;
	unsigned int Num() const {return num_;}
	char const * type() const ;

	void SetD(double Dia) ;
	void SetL(double len) ;
	void SetType(char const * str) throw(std::length_error&);
	void SetNum(unsigned int num) {num_ = num;}
	void PushPlate(MemNo memno,double t,BoltPlate::PlateSite plateSite=BoltPlate::FlangePlate);

	typedef std::vector<BoltPlate>::const_iterator iterator;

	iterator PlBegin() const {return pls.begin();}
	iterator PlEnd() const {return pls.end();}

private:
	unsigned int num_;
	double D_;//Diameter
	double L_;//Length
	char type_[16];//string type;
	std::vector<BoltPlate> pls;
};
#endif //__BOLT_H__