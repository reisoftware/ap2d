#ifndef _GELIB_PT3D_H_
#define _GELIB_PT3D_H_
#include <vector>
using std::vector;
class CGeNorm;
class AFX_EXT_CLASS CPt3D  
{
public:
	void Set(double x,double y,double z);
	BOOL UserEdit();
	void MirrorYZ();
	void MirrorXZ();
	void MirrorXY();
	void mirror_plane(CGeNorm const& norm,CPt3D const& pt);

	double len_to(const CGeNorm& norm) const;

	void RotateX(double beta);
	void RotateY(double beta);
	void RotateZ(double beta);
	void Scale(double dScale);
	
	void rotate(const CGeNorm& normal,double delta);
	
	CString GetString() const;
//	CPt3D(LPNODE rhs);
	double Len(const CPt3D& rhs) const;
	
	CPt3D PolarTo(float len,CGeNorm const* pNormal) const;
	void Serialize(CArchive &ar);
	CPt3D();
	~CPt3D();
	CPt3D(const CPt3D& rhs);
	CPt3D& operator = (const CPt3D& rhs);
	
	CPt3D& operator += (const CPt3D& rhs);
	CPt3D& operator -= (const CPt3D& rhs);

	CPt3D operator + (const CPt3D& rhs) const;
	CPt3D operator - (const CPt3D& rhs) const;
	CPt3D(double xx, double yy, double zz);
	
	BOOL operator == (const CPt3D& rhs) const;
	BOOL operator < (const CPt3D& rhs) const;

//	LPNODE Add(LPNODE lpNd);
	
	double x;
	double y;
	double z;
};

typedef vector<CPt3D> CPt3DVector;

#endif