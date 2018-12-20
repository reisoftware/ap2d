// Layer.h: interface for the Layer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_LAYER_H__EBDD1ED3_E923_41BD_A72B_9B2E92063536__INCLUDED_
#define AFX_LAYER_H__EBDD1ED3_E923_41BD_A72B_9B2E92063536__INCLUDED_

#include "export.h"
#include "Color.h"

namespace dlhml{
class OBJECT_API Layer  
{
public:
	Layer();
	Layer(const Layer& rhs);
	Layer& operator=(const Layer& rhs);
	~Layer();

	static Layer* create_me();
	bool close();

// 	void lua_load(iLua_File &fin);
// 	void lua_save(oLua_File &fout)const;
	void on(bool b)						{on_=b;}
	bool on() const						{return on_;}
	void frozen(bool b)				{frozen_=b;}
	bool frozen() const				{return frozen_;}
	void lock(bool b)					{lock_=b;}
	bool lock() const					{return lock_;}
	void line_width(int w)		{line_width_=w;}
	int line_width() const		{return line_width_;}
	void name(std::string n)			{name_ = n;}
	std::string name() const			{return name_;}
	void line_type(std::string lt)	{line_type_=lt;}
	std::string line_type() const		{return line_type_;}
	void color(Color col)			{color_=col;}
	Color color() const				{return color_;}

private:
	bool on_;
	bool frozen_;
	bool lock_;
	int line_width_;
	std::string name_;
	std::string line_type_;
	Color color_;

	void init();

	static void* operator new(size_t size){
		return ::operator new(size);
	}
	static void operator delete(void* ptr){
		::operator delete(ptr);
	}

private:
	MCT_DEF
};
}
#endif // !defined(AFX_LAYER_H__EBDD1ED3_E923_41BD_A72B_9B2E92063536__INCLUDED_)
