// DB_Text_Replace.cpp: implementation of the DB_Text_Replace class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "DB_Text_Replace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Text_Replace::Text_Replace()
{

}

Text_Replace::~Text_Replace()
{

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Text_Replace::DB_Text_Replace()
{

}

DB_Text_Replace::~DB_Text_Replace()
{

}
DB_Text_Replace* DB_Text_Replace::instance()
{	
	static DB_Text_Replace g;
	return &g;
}

void DB_Text_Replace::close()
{
	delete this;
}
void DB_Text_Replace::add(Text_Replace& val)
{
	db_.push_back (val);
}
void DB_Text_Replace::edit(const Text_Replace &val)
{
	for (int i = 0 ; i<db_.size() ; i++)
	{
		if(db_[i].txt_ == val.txt_){
			db_[i].replace_ = val.replace_;
			db_[i].char_ = val.char_;
			db_[i].postfix_ = val.postfix_;
			return;
		}
	}
}
void DB_Text_Replace::del(int item)
{
	db_.erase( db_.begin( ) + item );
}

void DB_Text_Replace::save(CString file_path)
{
	CStdioFile file;
	if( !file.Open( file_path,  CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ) 
	{
		#ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}
	CString str;
	str.Format("%d",db_.size());
	for (int i = 0 ; i<db_.size() ; i++)
	{
			file.WriteString(db_[i].txt_);
			file.WriteString("    ");
			file.WriteString(db_[i].replace_);
			file.WriteString("    ");
			file.WriteString(db_[i].char_);
			file.WriteString("    ");
			file.WriteString(db_[i].postfix_);
			file.WriteString("\n");
	}
	file.Close();
}
void DB_Text_Replace::open(CString file_path)
{
	CStdioFile file;
	if( !file.Open( file_path,  CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead | CFile::typeText ) ) 
	{
		#ifdef _DEBUG
		 afxDump << "Unable to open file" << "\n";
	  #endif
	   exit( 1 );
	}
	db_.clear();
	CString str = "";
	while(file.ReadString(str))
	{
		CString NChar = ' ';
		Text_Replace cur_text_replace;
		int npos;
		str.TrimLeft();
		npos = str.FindOneOf(NChar);
		cur_text_replace.txt_ = str.Left(npos);
		int	strlen = str.GetLength();
		str = str.Right(strlen-npos);
		str.TrimLeft();

		npos = str.FindOneOf(NChar);
		cur_text_replace.replace_ = str.Left(npos);
		strlen = str.GetLength();
		str = str.Right(strlen-npos);
		str.TrimLeft();
		
		
		npos = str.FindOneOf(NChar);
		cur_text_replace.char_ = str.Left(npos);
		strlen = str.GetLength();
		str = str.Right(strlen-npos);
		str.TrimLeft();	
		
		
		cur_text_replace.postfix_ = str;
		db_.push_back (cur_text_replace);
	}
	file.Close();

}

std::vector<Text_Replace> DB_Text_Replace::retrun_db()
{
	return db_;
}

CString DB_Text_Replace::get_replace_string(CString cur_replace,CString cur_char)
{
	CString str = "";
	if(cur_replace == "Circle")
		str = "¡ð";
	else if(cur_replace == "Hide")
		str = "";
	else if(cur_replace == "Cross")
		str = "¡è";
	else if(cur_replace == "Triangle")
		str = "¨Œ";
	else if(cur_replace == "Rect")
		str = "¡õ";
	else
		str = cur_replace;
//¢Ù¢Ú¢Û¢Ü¢Ý¢Þ¢ß¢à¢á¢â
	return str;
}

void DB_Text_Replace::get_obj_format(std::vector<dlhml::Text_Rep_Obj> &reps)
{
	for(int i=0;i<db_.size();i++)
	{
		dlhml::Text_Rep_Obj rep;
		rep.rep_str_ = db_[i].txt_;
		rep.style_ = db_[i].replace_;
		rep.sign_ = db_[i].char_;
		rep.postfix_ = db_[i].postfix_;

				
		reps.push_back(rep);
	}

}