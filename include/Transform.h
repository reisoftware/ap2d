#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "pt3d.h"
#include "GeNorm.h"
class CGeAxis;
namespace apcad{
	class  Transform_Base{
		private:
			virtual void transform_imp(CPt3D& pt) = 0;
		public: 
			virtual ~Transform_Base() {}
			void transform(CPt3D& pt) { transform_imp(pt);}
	};
	class  Rotate_X:public Transform_Base{
		private:
			double beta_;
			void transform_imp(CPt3D& pt) { pt.RotateX(beta_);}
		public:
			explicit Rotate_X(double beta):beta_(beta) {}
	};
	class  Rotate_Y:public Transform_Base{
		private:
			double beta_;
			void transform_imp(CPt3D& pt) { pt.RotateY(beta_);}
		public:
			explicit Rotate_Y(double beta):beta_(beta) {}
	};
	class  Rotate_Z:public Transform_Base{
		private:
			double beta_;
			void transform_imp(CPt3D& pt) { pt.RotateZ(beta_);}
		public:
			explicit Rotate_Z(double beta):beta_(beta) {}
	};
	class  Mirror_XY:public Transform_Base{
		private:
			void transform_imp(CPt3D& pt) { pt.MirrorXY();}
	};
	class  Mirror_YZ:public Transform_Base{
		private:
			void transform_imp(CPt3D& pt) {pt.MirrorYZ();}
	};
	class  Mirror_XZ:public Transform_Base{
		private:
			void transform_imp(CPt3D& pt) {pt.MirrorXZ();}
	};
	class  L2G:public Transform_Base{
		private:
			CGeAxis* axis_;
			void transform_imp(CPt3D& pt) { axis_->ChangeCoord(pt);}
		public:
			explicit L2G(CGeAxis* axis):axis_(axis) {}
	};
	class  G2L:public Transform_Base{
		private:
			CGeAxis* axis_;
			void transform_imp(CPt3D& pt) { axis_->G2L(pt);}
		public:
			explicit G2L(CGeAxis* axis):axis_(axis) {}
	};
	class  Offset:public Transform_Base{
		private:
			CPt3D pt_;
			void transform_imp(CPt3D& pt) { pt += pt_;}
		public:
			explicit Offset(const CPt3D& pt):pt_(pt) {}
	};
	class  Rotate:public Transform_Base{
		private:
			CGeNorm norm_;
			double beta_;
			void transform_imp(CPt3D& pt) { pt.rotate(norm_,beta_);}
		public:
			Rotate(const CGeNorm& norm,double beta):norm_(norm),beta_(beta) {}
	};
	class  Mirror:public Transform_Base{
		private:
			CGeNorm norm_;
			CPt3D pt_;
			void transform_imp(CPt3D& pt) { pt.mirror_plane(norm_,pt_);}
		public:
			explicit Mirror(const CGeNorm& norm,const CPt3D& pt)
			:norm_(norm),pt_(pt) {}
	};
	template<class T> T& rotate(T& t,const CGeNorm& norm,double beta)
	{
		Rotate obj(norm,beta);
		t.transform(obj);
		return t;
	}
	template<class T> T& mirror(T& t,const CGeNorm& norm,const CPt3D& pt)
	{
		Mirror obj(norm,pt);
		t.transform(obj);
		return t;
	}
	template<class T> T& rotate_x(T& t,double beta){
		Rotate_X obj(beta);
		t.transform(obj);
		return t;
	}
	template<class T> T& rotate_y(T& t,double beta){
		Rotate_y obj(beta);
		t.transform(obj);
		return t;
	}
	template<class T> T& rotate_z(T& t,double beta){
		Rotate_Z obj(beta);
		t.transform(obj);
		return t;
	}
	template<class T> T& mirror_xy(T& t){
		Mirror_XY obj;
		t.transform(obj);
		return t;
	}
	template<class T> T& mirror_yz(T& t){
		Mirror_YZ obj;
		t.transform(obj);
		return t;
	}
	template<class T> T& mirror_xz(T& t){
		Mirror_XZ obj;
		t.transform(obj);
		return t;
	}
	template<class T> T& l2g(T& t,CGeAxis* axis){
		L2G obj(axis);
		t.transform(obj);
		return t;
	}
	template<class T> T& g2l(T& t,CGeAxis* axis){
		G2L obj(axis);
		t.transform(obj);
		return t;
	}
	template<class T> T& offset(T& t,const CPt3D& pt){
		Offset obj(pt);
		t.transform(obj);
		return t;
	}
}
#endif
