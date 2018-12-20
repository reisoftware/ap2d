#ifndef _NODE_H_
#define _NODE_H_
#include "../include/pt3d.h"
class NODE:public CPt3D{
public:
	int num;//½ÚµãºÅ
	BOOL need_save_;
	
	NODE::NODE():num(-1),need_save_(FALSE)
	{}
	
	BOOL operator ==(NODE const& rhs) const
	{
		return (GEXY::EquFloat(x,rhs.x) 
		    && GEXY::EquFloat(y,rhs.y)
				&& GEXY::EquFloat(z,rhs.z) );
	}
	void Serialize(CArchive& ar)
		{
		if(ar.IsLoading()){
			ar >> num;
			ar >> x;
			ar >> y;
			ar >>	z;
		}
		else{
			ar << num;
			ar << x;
			ar << y;
			ar << z;
		}
		}
};
int get_node_str(NODE* nd,char* out);
int set_node_from_str(NODE* nd,char* out);
typedef NODE* LPNODE;

#endif
