// DB_Configure.cpp: implementation of the DB_Configure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_Configure.h"
#include "Mgr_File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DB_Configure::DB_Configure()
{

}

DB_Configure::~DB_Configure()
{

}
DB_Configure* DB_Configure::instance()
{	
	static DB_Configure g;
	return &g;
}

void DB_Configure::close()
{
	delete this;
}

void DB_Configure::init_combo_by_names_list(CString path,CComboBox &combox)
{
	combox.ResetContent( );
	CStringArray files;
	get_files_in_path(path,"",files);
	for (int i = 0 ;i < files.GetSize() ; i ++ )
	{
		combox.InsertString( i, files[i] );
	}
}

void DB_Configure::save_config_file(CString path,CString file_name,const CStringArray &strs)
{
	CStdioFile file;
	path = path + file_name;
	if (!file.Open(path,CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		#ifdef _DEBUG
		  afxDump << "Unable to open file" << "\n";
	   #endif
	   exit( 1 );
	}
	for (int i = 0;i < strs.GetSize( ); i++ )
	{
		file.WriteString(strs.GetAt(i));
		file.WriteString("\n");
	}
	file.Close();
	
}

void DB_Configure::open_config_file(CString path,CString file_name,CStringArray &strs)
{
	CStdioFile file;
	CString cur_path = path + file_name;
	if( !file.Open( cur_path, CFile::modeRead | CFile::typeText ) )
	{
		 #ifdef _DEBUG
				afxDump << "Unable to open file" << "\n";
		 #endif
		 exit( 1 );
	}

	CString str;
	while(file.ReadString(str))
	{
		strs.Add(str);
	}
	file.Close();
	
}