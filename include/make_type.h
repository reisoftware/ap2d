#ifndef _MAKE_TYPE_H_
#define _MAKE_TYPE_H_
namespace gelib{
template<class T,class T1>
T make_type(const T1& t1)
{
	return T(t1);
}
}
#endif