// Mgr_Detail.h: interface for the Mgr_Detail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETAIL_MGR_H__5FF761F7_90D3_4074_92DF_9CA212CDD511__INCLUDED_)
#define AFX_DETAIL_MGR_H__5FF761F7_90D3_4074_92DF_9CA212CDD511__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace dlhml
{
	class Database;
}


class Mgr_Detail  
{
public:
	Mgr_Detail();
	virtual ~Mgr_Detail();

};
namespace detail
{
void download(std::string key);

void merge_detail(std::string name);

void delete_detail(std::string detail_name);


}


#endif // !defined(AFX_DETAIL_MGR_H__5FF761F7_90D3_4074_92DF_9CA212CDD511__INCLUDED_)
