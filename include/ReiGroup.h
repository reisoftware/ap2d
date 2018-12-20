// ReiGroup.h: interface for the CReiGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REIGROUP_H__0A5A226A_9F6E_49E2_A0E5_9AE443C8AC1F__INCLUDED_)
#define AFX_REIGROUP_H__0A5A226A_9F6E_49E2_A0E5_9AE443C8AC1F__INCLUDED_
#include "serialize.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef AFX_DATA
#undef AFX_DATA
#endif

#define	AFX_DATA AFX_EXT_DATA
#include <vector>
typedef std::vector<int> IVECTOR;
class CModel;
using std::string;
class AFX_EXT_CLASS CReiGroup  
{
public:
	void Serialize(CArchive& ar);
	BOOL In(int index);
	void SetIndex(int index);
	int GetIndex() const;
	void SetName(string sRht);
	string GetName() const;
	int GetAt(int pos);
	int GetIndexCount();
	BOOL DelIndex(int index);
	BOOL AddIndex(int index);
	CReiGroup();
	virtual ~CReiGroup();

	BOOL operator == (const CReiGroup& rht) const;

	void set_need_save(BOOL need_save) { need_save_ = need_save;}
	BOOL is_need_save() const { return need_save_;}

	void set_delete(BOOL bTrue) { delete_ = bTrue;}
	BOOL is_delete() const { return delete_;}
private:
	IVECTOR indexVector;
	string sName;
	int index;

	BOOL need_save_;
	BOOL delete_;
};
inline CArchive& operator << (CArchive& ar,CReiGroup& ary)
{
	ary.Serialize(ar);
	return ar;
}
inline CArchive& operator >> (CArchive& ar,CReiGroup& ary)
{
	ary.Serialize(ar);
	return ar;
}

inline CArchive& operator << (CArchive& ar,std::vector<CReiGroup>& ary)
{
	return Serialize(ar,ary);
}
inline CArchive& operator >> (CArchive& ar,std::vector<CReiGroup>& ary)
{
	return Serialize(ar,ary);
}
typedef std::vector<CReiGroup> GroupVector;
#undef AFX_DATA
#define AFX_DATA
#endif // !defined(AFX_REIGROUP_H__0A5A226A_9F6E_49E2_A0E5_9AE443C8AC1F__INCLUDED_)
