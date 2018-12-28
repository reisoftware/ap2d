// Model_DB.cpp: implementation of the Model_DB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Model_DB.h"
//void deal_error_Data(CStringArray newstr);
#include "dir.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Part::Part()
{

}

Part::~Part()
{

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_DB::Model_DB()
{

}

Model_DB::~Model_DB()
{

}
Model_DB* Model_DB::instance()
{	
	static Model_DB g;
	return &g;
}

void Model_DB::close()
{
	delete this;
}

CString Model_DB::get_section(CString name)
{
	CString str;
	for(int i=0;i<db_.size();i++){
		if(db_[i].name_== name)
			return db_[i].section_;
	}
	return "";
}
CString Model_DB::get_matrail(CString name)
{
	CString str;
	for(int i=0;i<db_.size();i++){
		if(db_[i].name_== name)
			return db_[i].matrial_;
	}
	return "";
}
BOOL Model_DB::get_part(CString name,Part &part)
{
	CString str;
	for(int i=0;i<db_.size();i++){
		if(db_[i].name_== name){
			part =  db_[i];
			return FALSE;
		}
	}
	return TRUE;
}

void deal_error_Data(CStringArray &newstr)
{
	int i = 0;
	while(1)
	{
		
		if ( i >= 7 )
			break;
		if ( i == 0 )
			newstr[i] = newstr[i] + newstr[i+1];
		else
			newstr[i] = newstr[i+1];
		i++;
	}
}


CString Model_DB::get_file_path()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	CString tmpdir;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径也就是当前运行程序的全路径利用方法一的解析路径的方法，即可得到程序所在路径。

	tmpdir = exeFullPath;
	tmpdir=tmpdir.Left(tmpdir.ReverseFind('\\'));	
	tmpdir = tmpdir + "\\";
	return tmpdir;
}


void 	Model_DB::deal_data_to_db(CString s)
{
	Part part;
	int strlen = s.GetLength();
	CString NChar = ' ';
	int npos;
	CStringArray newstr;
	for (int i = 0 ; i <= 7 ; i ++ )
	{
		if ( i ==  0 )
		{
			npos = s.Find(NChar);
			part.partno_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  1 )
			{
			npos = s.Find(NChar);
			part.section_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  2 )
		{
			npos = s.Find(NChar);
			part.numbers_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  3 )
		{
			npos = s.Find(NChar);
			part.matrial_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  4 )
		{
			npos = s.Find(NChar);
			part.lengths_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  5 )
		{
			npos = s.Find(NChar);
			part.area_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  6 )
		{
			npos = s.Find(NChar);
			part.weights_ = s.Left(npos);
			strlen = s.GetLength();
			s = s.Right(strlen-npos);
			s.TrimLeft();
		}
		else if  ( i ==  7 )
		{
			part.name_ = s;
		
		}
	}
	db_.push_back (part);
	
}

void Model_DB::create_db(CString file)
{
	
	save_per_line.RemoveAll();
	db_.clear();
	CStdioFile file_txt(file,CFile::modeRead);

	CString s;
	while(file_txt.ReadString(s)){
		
		save_per_line.Add(s);
		deal_data_to_db(s);	
			
	}
	file_txt.Close();

	CString new_file_all_path_ = get_file_path();
	new_file_all_path_= new_file_all_path_ + "configure\\";
	afc::dir::create_floder(new_file_all_path_);
	new_file_all_path_ = new_file_all_path_ + "partlist.txt";
	save(new_file_all_path_);


	

}


 void Model_DB::dim_name_styles_strs(CStringArray& strs)
{
	strs.Add("Name");
	strs.Add("*(Enter)*");
	strs.Add("Section");
	strs.Add("*(-Link)*");
	strs.Add("Matrail");
	strs.Add("*(Space Link)*");
	strs.Add("Num");
	strs.Add("*(Space Link)*");
	strs.Add("*(Enter)*");
	strs.Add("*(Enter)*");
	strs.Add("*(Enter)*");
	strs.Add("Length");
	strs.Add("*(Space Link)*");
	strs.Add("Weight");
	strs.Add("*(Enter)*");
	strs.Add("*(Space Link)*");
	strs.Add("AllWeight");
	strs.Add("*(Space Link)*");
}



void Model_DB::set_dim_name_style( CStringArray& strs)
{
//	dim_name_styles_ = strs;
	dim_name_styles_.RemoveAll();

	for (int i= 0;i<strs.GetSize();i++)
	{
		dim_name_styles_.Add(strs.GetAt(i));
	}
}

void Model_DB::init_dim_styles()
{
	dim_name_styles_.RemoveAll();
	dim_name_styles_.Add("PartNo");
	dim_name_styles_.Add("*(Enter)*");
	dim_name_styles_.Add("Matrail");
	dim_name_styles_.Add("*(Space Link)*");
	dim_name_styles_.Add("Section");

}

void Model_DB::get_name_strs(Part part,	CStringArray& strs_new)
{
	if(dim_name_styles_.GetSize() == 0){
		init_dim_styles();
	}


//	CStringArray strs_new;
	CString str = "";
	for(int i=0;i<dim_name_styles_.GetSize();i++)
	{ 
		if(dim_name_styles_.GetAt(i)=="Name")
		{
			CString str1= part.name_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="PartNo")
		{
			CString str1= part.partno_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="Section")
		{
			CString str1= part.section_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="Matrail")
		{
			CString str1= part.matrial_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="Num")
		{
			CString str1= part.numbers_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="Length")
		{
			CString str1= part.lengths_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="Weight")
		{
			CString str1= part.weights_;
			str = str + str1;
		}
		else if (dim_name_styles_.GetAt(i)=="ALLWeight")
		{
			CString str1= part.area_;
			str = str + str1;
		}
		else if(dim_name_styles_.GetAt(i)=="*(-Link)*")
		{
			CString str1 = "-";
			str = str + str1;
		}
		else if(dim_name_styles_.GetAt(i)=="*(Space Link)*")
		{
			CString str1 = " ";
			str = str + str1;
		}
		else
		{
           strs_new.Add(str);
					 str="";
		}
    
	}
	strs_new.Add(str);


}


void Model_DB::get_dim_name_strs(CString name,CStringArray& strs_new )
{
	
	Part part;
	int i;
	int states = 1;
	CString cur_path = get_file_path();
	CString file_all_path = cur_path + "\\" + "signs_replace.txt";
	model_db_text_replace.instance()->open(file_all_path);
	std::vector<Text_Replace> text_db_ =  model_db_text_replace.instance()->retrun_db();
	for (i = 0; i<db_.size();i++)
	{
		
		if ( name == db_[i].partno_ )
		{
			part.partno_ = db_[i].partno_;
			part.name_ = db_[i].name_;
			part.section_ = db_[i].section_;
			part.numbers_ = db_[i].numbers_;
			part.matrial_ = db_[i].matrial_;
/*
			//不需要自动替换
			for (int j = 0;j < text_db_.size(); j++ )
			{
				if ( part.matrial_.Compare(text_db_[j].txt_) == 0 )
				{
					
					part.matrial_ = model_db_text_replace.get_replace_string(text_db_[j].replace_,text_db_[j].char_);
				}
			}
			*/
			part.lengths_ = db_[i].lengths_;
			part.area_ = db_[i].area_;
			part.weights_ = db_[i].weights_;
			states = 2;
			break;
		}

	}

	if( states == 1 )
	{
		MessageBox(NULL,_T("Name have not find!"),_T("Warning"),MB_OK);
		
	}
	else 
		get_name_strs(part,strs_new);
}


void Model_DB::get_names(CStringArray& names)
{
	int i;
	for (i = 0; i<db_.size();i++)
	{
		names.Add(db_[i].partno_);
	}
}
void Model_DB::open(CString file)
{
	db_.clear();
	CStdioFile file_txtopen;
	if (file_txtopen.Open(file,CFile::modeRead) )
	{
		CString s;
		while(file_txtopen.ReadString(s))
		{
			deal_data_to_db(s);	
		}
		file_txtopen.Close();
		
	}


}

Parts Model_DB::retrun_model_db()
{
	return db_;
}


void Model_DB::save(CString file)
{
	//partlist.txt

	CStdioFile new_file_txt(file,CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	//new_file_txt.WriteString();
	//new_file_txt.WriteString("\n");
	for ( int i = 0;i < save_per_line.GetSize() ; i++ )
	{
		new_file_txt.WriteString(save_per_line.GetAt(i));
		new_file_txt.WriteString("\n");
	}
		new_file_txt.Close();

}
