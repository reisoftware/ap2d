#ifndef _AFC_XLS_SHEET_H_
#define _AFC_XLS_SHEET_H_

#include "export.h"
#include "xls_cell.h"
#include <vector>

namespace afc{
namespace xls{

// struct pair
// {
// 	int first;
// 	double second;
// };

class AFCAPI Sheet
{
public:
	Sheet();

public:
	afc::string prefix;
	int id;	//prefix+id ¹¹³Ésheet name
	std::vector<Cell> cells;
	std::vector<Pos> borders;
	std::vector<double> ws;
	std::vector<double> hs;


public:
	afc::string name()const;

public:
	void clear();

};

AFCAPI void set_size(std::vector<double>& s, int xid, double size);
AFCAPI double get_size(const std::vector<double>& s, int xid);
AFCAPI double get_size_sum(const std::vector<double>& s, int xid); 

}//namespace
}//namespace



#endif//FILE
