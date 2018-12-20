#ifndef _MFCEX_CAD_H_
#define _MFCEX_CAD_H_

#include "export.h"
#include <vector>
#include "../afc/xls_book.h"
#include "../object/Entity.h"
#include "../object/Normal.h"


namespace aex{

class AEXAPI Object
{
public:
	Object(const afc::xls::Book& xbook, const dlhml::Point& org);
	void output(std::vector<dlhml::Entity*>& ents);

private:	
	void output(std::vector<dlhml::Entity*>& ents, 
							const afc::xls::Sheet& xsheet);
	void output(std::vector<dlhml::Entity*>& ents, 
							const afc::xls::Cell& cell,
							const std::vector<double>& ws, 
							const std::vector<double>& hs);
	void output(std::vector<dlhml::Entity*>& ents, 
							const dlhml::Rect& rect);
	void output(std::vector<dlhml::Entity*>& ents, 
							const dlhml::Rect& rect,
							const afc::xls::Cell& cell);

private:
	const afc::xls::Book& xbook_;
	dlhml::Point org_;
// 	dlhml::Normal dis_;

};

}//namespace


#endif//FILE
