
#include "stdafx.h"
#include "iolua.h"

/*
 * oLua_File class 
 * output the classes to file of lua format
 */

// oLua_File::oLua_File(const char *ofile)
// : ofstream(ofile), cur_level_(1)
// {
// 	if (!*this)
// 		return;
// 	*this << "entry" << "{" << "\n";
// }
// 
// oLua_File::~oLua_File()
// {
// 	if (!*this)
// 		return;
// 	*this << "}";
// }
// 
// oLua_File& oLua_File::ident()
// {
// 	int i = 0;
// 	while (i++ < cur_level_)
// 		*this << '\t';
// 	return *this;
// }
// 
// oLua_File& save_value(oLua_File &fout, const char *key, const LOGFONT *val)
// {
// 	fout.ident();
// 	fout << key << " = {\n";
// 	fout.add_level();
// 
// 	fout.save_value("lfHeight", val->lfHeight);
// 	fout.save_value("lfWidth", val->lfWidth);
// 	fout.save_value("lfEscapement", val->lfEscapement);
// 	fout.save_value("lfOrientation", val->lfOrientation);
// 	fout.save_value("lfWeight", val->lfWeight);
// 	fout.save_value("lfItalic", val->lfItalic);
// 	fout.save_value("lfUnderline", val->lfUnderline);
// 	fout.save_value("lfStrikeOut", val->lfStrikeOut);
// 	fout.save_value("lfCharSet", val->lfCharSet);
// 	fout.save_value("lfOutPrecision", val->lfOutPrecision);
// 	fout.save_value("lfClipPrecision", val->lfClipPrecision);
// 	fout.save_value("lfQuality", val->lfQuality);
// 	fout.save_value("lfPitchAndFamily", val->lfPitchAndFamily);
// 	fout.save_value("lfFaceName", val->lfFaceName);
// 
// 	fout.sub_level();
// 	fout.ident();
// 	fout << "},\n";
// 	return fout;
// }

//////////////////////////////////////////////////////////////////////////

//oLua_File& oLua_File::save_value(const char *key, int val)
//{
//	this->ident();
//	(*this) << key << " = " << val << ",\n";
//	return *this;
//}
//
//oLua_File& oLua_File::save_value(const char *key, double val)
//{
//	this->ident();
//	(*this) << key << " = " << val << ",\n";
//	return *this;
//}
//
//oLua_File& oLua_File::save_value(const char *key, const char *val)
//{
//	this->ident();
//	(*this) << key << " = [[" << val << "]]" << ",\n";
//	return *this;
//}
//
//oLua_File& oLua_File::save_value(const char *key, bool val)
//{
//	this->ident();
//	(*this) << key << " = " << val << ",\n";
//	return *this;
//}



