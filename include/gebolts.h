#ifndef _GEBOLTS_H_
#define _GEBOLTS_H_
#include "gebolt.h"
#include "transform.h"
using namespace apcad;
class AFX_EXT_CLASS GeBolts{
  std::vector<CGeBolt> bolts_;
public:
  typedef std::vector<CGeBolt>::iterator iterator;
	typedef std::vector<CGeBolt>::const_iterator const_iterator;
  void add_bolt(CPt3D start,double dia,double hole_d,CString type,int jnt_index);
  void add_bolt(CGeBolt bolt);
  iterator bolts_begin();
  iterator bolts_end();
	const_iterator bolts_begin() const;
	const_iterator bolts_end() const;
  int bolts_size() const;
//  void add_bolts(iterator first,iterator last);
	void add_bolts(CGeBolt* first,CGeBolt* last);
  void clear_bolts();
	void Serialize(CArchive &ar);
	void transform(Transform_Base& transform_base);
};
#endif
