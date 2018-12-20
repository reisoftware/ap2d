// Layer.cpp: implementation of the Layer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Layer.h"
#include "iolua.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
void Layer::init()
{
	on_ = false;
	frozen_ = false;
	lock_ = false;
	line_width_ = 1;
}
Layer::Layer()
MCT_INIT1("Layer")
{
	init();
}
Layer::Layer(const Layer& rhs)
MCT_INIT1("Layer")
{
	init();
	on_ = rhs.on_;
	frozen_ = rhs.frozen_;
	lock_ = rhs.lock_;
	line_width_ = rhs.line_width_;
	name_ = rhs.name_;
	line_type_ = rhs.line_type_;
	color_ = rhs.color_;
}
Layer& Layer::operator=(const Layer& rhs)
{
	if(this == &rhs)
		return *this;
	on_ = rhs.on_;
	frozen_ = rhs.frozen_;
	lock_ = rhs.lock_;
	line_width_ = rhs.line_width_;
	name_ = rhs.name_;
	line_type_ = rhs.line_type_;
	color_ = rhs.color_;
	return *this;
}
Layer::~Layer()
{
}
Layer* Layer::create_me()
{
	return new Layer;
}
bool Layer::close()
{
	delete this;
	return true;
}

// void Layer::lua_load(iLua_File &fin)
// {
// 
// }
// 
// void Layer::lua_save(oLua_File &fout)const
// {
// 	fout.save_value("on_", on_);
// 	fout.save_value("frozen_", frozen_);
// 	fout.save_value("lock_", lock_);
// 	fout.save_value("line_width_", line_width_);
// 	fout.save_value("name_", name_);
// 	fout.save_value("line_type_", line_type_);
// 	fout.save_value("color_", &color_);
// }

}
