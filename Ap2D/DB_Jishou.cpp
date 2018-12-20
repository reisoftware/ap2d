// DB_Jishou.cpp: implementation of the DB_Jishou class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ap2d.h"
#include "DB_Jishou.h"
#include "Mgr_File.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Jishou::DB_Jishou()
{
	
}

DB_Jishou::~DB_Jishou()
{

}



DB_Jishou* DB_Jishou::instance()
{
	static DB_Jishou g;
	return &g;
}


void DB_Jishou::init_data()
{
	JS_db_.clear();
	CStdioFile file;
	CString	files_path = exe_path().c_str();
	files_path = files_path + "configure" + "\\";
	CString filename = "jishou_data.txt";
	if (!file.Open(files_path + filename,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead |CFile::typeText )){
		#ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
   #endif
   exit( 1 );
	}
	CString perline;
	while (file.ReadString(perline)){
		Ji1Shou data;
		int pos = 0;
		pos =  perline.Find(";");
		CString tempstr = perline.Left(pos);
		data.ass_no_ = tempstr.Right(tempstr.GetLength()-tempstr.Find("=") - 1);
		perline.Replace(tempstr+";","");
		pos =  perline.Find(";");
		tempstr = perline.Left(pos); 
		data.l_joint_ = tempstr.Right(tempstr.GetLength()-tempstr.Find("=") - 1);
		perline.Replace(tempstr+";","");
		pos =  perline.Find(";");
		tempstr = perline.Left(pos); 
		data.r_joint_ = tempstr.Right(tempstr.GetLength()-tempstr.Find("=") - 1);
		JS_db_.push_back(data);
	}
	file.Close();
}

void DB_Jishou::save_cur_file()
{
	CString	files_path = exe_path().c_str();
	files_path = files_path + "configure" + "\\";
	CString filename = "jishou_data.txt";
	CStdioFile file;
	if (!file.Open(files_path + filename,CFile::modeCreate  | CFile::modeWrite |CFile::typeText )){
		#ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
   #endif
   exit( 1 );
	}
	for (int i = 0 ; i < JS_db_.size() ; i++ ){
		file.WriteString("Assembley=" + JS_db_[i].ass_no_ + ";");
		file.WriteString("Left Joint=" + JS_db_[i].l_joint_+ ";");
		file.WriteString("Right Joint=" + JS_db_[i].r_joint_+ ";");
		file.WriteString("\n");
	}
	file.Close();
	
}

JS DB_Jishou::return_js_db() //js ×ª¶¨Òåtypedef std::vector<JiShou> JS;
{
	return JS_db_;
}

void DB_Jishou::add_data_to_db(Ji1Shou& data)
{
	JS_db_.push_back(data);
}

Ji1Shou DB_Jishou::get_sel_data()
{
	return sel_data_;
}


void DB_Jishou::set_sel_data(Ji1Shou& data,BOOL status)
{
	edit_ = status;
	sel_data_ = data;
}

void DB_Jishou::change_vector_iter(Ji1Shou& data)
{

}

BOOL DB_Jishou::re_status()
{
	return edit_;
}

void DB_Jishou::init_jishou_db(JS& datas)
{
	JS_db_.clear();
	JS_db_ = datas;
}

void DB_Jishou::del_iter(Ji1Shou& data)
{
	JS::iterator iter;
	for (iter = JS_db_.begin() ; iter != JS_db_.end() ; iter++ ){
		if ( iter->ass_no_.Compare(data.ass_no_) == 0 ){
			JS_db_.erase(iter);
			break;
		}
	}
}

