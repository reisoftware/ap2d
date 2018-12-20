// ommand_Line_Info.cpp: implementation of the Command_Line_Info class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command_Line_Info.h"
#include "MainFrm.h"

#include "str_tools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Command_Line_Info::Command_Line_Info(CEdit& current,CEdit& old)
:current_(current)
, old_(old)
MCT_INIT2("Command_Line_Info")
{

}

Command_Line_Info::~Command_Line_Info()
{

}

void Command_Line_Info::close()
{
	delete this;
}

void Command_Line_Info::show_command(LPCTSTR info,bool update)
{
	CString str;
	current_.GetWindowText(str);
	if(CString(info)=="back")
		str.Delete(str.GetLength()-1);
	else{
		str += "\r\n";
		str += info;
	}
	current_.SetWindowText(str);
	if(!update){
		current_.SetWindowText("");
		return;
	}
	CString old_txt;
	old_.GetWindowText(old_txt);
	old_txt += str;
	old_.SetWindowText(old_txt);
	old_.LineScroll(old_.GetLineCount(), 0);
// 	for(int i=0;i<str.GetLength();i++){
// 		TCHAR ch = str[i];
// 		old_.PostMessage(WM_CHAR,ch,0);
// 	}
// 	old_.PostMessage(WM_CHAR,'\n',0);
	current_.SetWindowText("");
}

// void Command_Line_Info::show_command(LPCTSTR info,bool update)
// {
// 	CString str;
// 	current_.GetWindowText(str);
// 	if(CString(info)=="back")
// 		str.Delete(str.GetLength()-1);
// 	else
// 		str += info;
// 	current_.SetWindowText(str);
// 	if(!update){
// 		current_.SetWindowText("");
// 		return;
// 	}
// 	for(int i=0;i<str.GetLength();i++){
// 		TCHAR ch = str[i];
// 		old_.PostMessage(WM_CHAR,ch,0);
// 	}
// 	old_.PostMessage(WM_CHAR,'\n',0);
// 	current_.SetWindowText("");
// }

bool Command_Line_Info::numeric_char(TCHAR ch) const
{
	return !IsCharAlpha(ch) && IsCharAlphaNumeric(ch);
}
bool Command_Line_Info::numeric_str(LPCTSTR str) const
{
	if(!str)
		return false;
  bool first_validate = true;
	int i=0;
	int num = strlen(str);
	for(;i<num;i++)
	{
    if(str[i] == '.'){
			first_validate=false;
			continue;
    }
    if(str[i] == ','){
			first_validate=true;
			continue;
    }
    if(first_validate && str[i] == '-'){
			first_validate=false;
      continue;
    }
    //if(first_validate && str[i] == ' '){
			//first_validate=false;
      //continue;
    //}
    if(numeric_char(str[i])){
			first_validate=false;
    }
    else{
      break;
    }
	}
	return i == num;
}
bool Command_Line_Info::get_two_value(Float& val1,Float& val2) const
{
	CString str;
	current_.GetWindowText(str);
  //String_Split ss;
  std::vector<std::string> vals;
  afc::split_string(vals, str.GetBuffer(0), ',');
  if(vals.size()<2){
    return false;
  }
  val1 = atof(vals[0].c_str());
  val2 = atof(vals[1].c_str());
  return true;

//	CString str;
//	current_.GetWindowText(str);
//	if(!numeric_str(str))
//		return false;
//	if(str.Replace(",",",")!=1)
//		return false;
//	int pos = str.Find(",");
//	val1 = atof(str.Mid(0,pos));
//	val2 = atof(str.Mid(pos+1));
//	return true;
}
bool Command_Line_Info::get_one_value(Float& val) const
{
	CString str;
	current_.GetWindowText(str);
  //String_Split ss;
  std::vector<std::string> vals;
  afc::split_string(vals, str.GetBuffer(0), ',');
  if(vals.size()<1){
    return false;
  }
  val = atof(vals[0].c_str());
  return true;

//  CString str;
//	current_.GetWindowText(str);
//	if(!numeric_str(str))
//		return false;
//	if(str.Find(",")!=-1)
//		return false;
//	val = atof(str);
//	return true;
}
int Command_Line_Info::get_string(LPTSTR str) const
{
	CString ss;
	current_.GetWindowText(ss);
	if(!str)
		return ss.GetLength();
	strcpy(str,ss);
	return ss.GetLength();
}
void Command_Line_Info::show_coord(LPCTSTR info)
{
	CMainFrame* pM = (CMainFrame*)AfxGetMainWnd();
//	pM->show_coord(info);
}
}