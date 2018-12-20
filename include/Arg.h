#ifndef _ARG_H_
#define _ARG_H

template <class T> struct CArg1
{
	typedef T type;
	T arg1;
};
template <class T1,class T2> struct CArg2
{
	typedef T1 type1;
	typedef T2 type2;
	T1 arg1;
	T2 arg2;
};
template <class T1,class T2,class T3> struct CArg3
{
	typedef T1 type1;
	typedef T2 type2;
	typedef T3 type3;
	T1 arg1;
	T2 arg2;
	T3 arg3;
};

template<class T> 
CArg1<T> make_arg1(const T& t)
{
	CArg1<T> arg;
	arg.arg1 = t;
	return arg;
}
template<class T1,class T2> 
CArg2<T1,T2> make_arg2(const T1& t1,const T2& t2)
{
	CArg2<T1,T2> arg;
	arg.arg1 = t1;
	arg.arg2 = t2;
	return arg;
}
template<class T1,class T2,class T3> 
CArg3<T1,T2,T3> make_arg3(const T1& t1,const T2& t2,const T3& t3)
{
	CArg3<T1,T2,T3> arg;
	arg.arg1 = t1;
	arg.arg2 = t2;
	arg.arg3 = t3;
	return arg;
}
#endif