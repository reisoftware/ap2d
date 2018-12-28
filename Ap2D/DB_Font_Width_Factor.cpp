// DB_Font_Width_Factor.cpp: implementation of the DB_Font_Width_Factor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "DB_Font_Width_Factor.h"

#include "Model_DB.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Font_WF::Font_WF()
{

}

Font_WF::~Font_WF()
{

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Font_Width_Factor::DB_Font_Width_Factor()
{

}

DB_Font_Width_Factor::~DB_Font_Width_Factor()
{

}
DB_Font_Width_Factor* DB_Font_Width_Factor::instance()
{	
	static DB_Font_Width_Factor g;
	return &g;
}

void DB_Font_Width_Factor::close()
{
	delete this;
}
void DB_Font_Width_Factor::add(CString height,CString width_factor)
{
	Font_WF item;
	item.height_ = height;
	item.width_factor_  = width_factor;
	db_.push_back(item);
}
void DB_Font_Width_Factor::edit(CString height,CString width_factor)
{
	for (int i = 0 ; i<db_.size() ; i++)
	{
		if(db_[i].height_ == height){
			db_[i].width_factor_ = width_factor;
		
			return;
		}
	}
}

void DB_Font_Width_Factor::del(CString height)
{
	for (int i = 0 ; i<db_.size() ; i++)
	{
		if(db_[i].height_ == height){
			db_.erase(&db_[i]);		
			return;
		}
	}
}

void DB_Font_Width_Factor::save()
{
	CString cur_path = Model_DB::instance()->get_file_path();
	CString file_path = cur_path + "\\" + "font_width_factor_db.txt";

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
			file.WriteString(db_[i].height_);
			file.WriteString("    ");
			file.WriteString(db_[i].width_factor_);		
			file.WriteString("\n");
	}
	file.Close();
}
void DB_Font_Width_Factor::open()
{
	CString cur_path =  Model_DB::instance()->get_file_path();
	CString file_path = cur_path + "\\" + "font_width_factor_db.txt";
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
		Font_WF val;
		int npos;
		str.TrimLeft();
		npos = str.FindOneOf(NChar);
		val.height_ = str.Left(npos);
		int	strlen = str.GetLength();
		str = str.Right(strlen-npos);
		str.TrimLeft();		
		
		val.width_factor_ = str;
		db_.push_back (val);
	}
	file.Close();

}

std::vector<Font_WF> DB_Font_Width_Factor::retrun_db()
{
	return db_;
}
void  DB_Font_Width_Factor::show(CListCtrl &list)
{
	list.DeleteAllItems();
	for (int i = 0 ; i < db_.size()  ; i++ )
	{
		list.InsertItem(i,"");
		list.SetItemText(i, 0,db_[i].height_);
		list.SetItemText(i, 1,db_[i].width_factor_);
	}

}
CString DB_Font_Width_Factor::find(CString height)
{
	for (int i = 0 ; i<db_.size() ; i++)
	{
		if(db_[i].height_ == height){
			return db_[i].width_factor_;
		}
	}

	return "-1";
}