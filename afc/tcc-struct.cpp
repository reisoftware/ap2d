
#include "stdafx.h"
#include "tcc.h"

#include <cassert>
#include <string>

#include "libtcc.h"
//#include "getrace.h"


  
namespace tcc{

  static std::string cur_script_;
  static std::string error_msg_;
  static void tcc_error_func(void * opaque, const char * msg)
  {
    std::string error_msg = msg;
    //throw error_msg;
    error_msg_ = msg;
  }

  std::string last_error()
  {
    return error_msg_;
  }

  ////删除哪个tcc对象问题，如果有嵌套多个tcc对象的现象。
  void exit(std::string msg)
  {
    if(msg.empty()){
      throw last_error().c_str();
    }
    throw msg.c_str();
  }

  static void destory_exit(afc::Tcc& t, std::string msg = "")
  {
    destory(t);
    exit(msg);
  }

  static std::string script_msg(std::string msg)
  {
    std::string s = "Error(";
    s += cur_script_;
    s += "):";
    s += msg;
    s += "\n";
    return s;
  }

  static void cur_script(const std::string& file)
  {
	  cur_script_ = file;
  }

  void create(afc::Tcc& t, const std::string& cur_path)
  {
    t.s_ = NULL;
    t.m_ = NULL;
	  //assert(!t.s_ && !t.m_ && "tcc::create(), must zero the tcc object");
    cur_script_ = "";

	  t.s_ = tcc_new();
    tcc_set_error_func(t.s_, NULL, &tcc_error_func);
    if(!t.s_){
      destory_exit(t);
    }

    std::string lib_path = cur_path + "lib\\";
    std::string inc_path = cur_path + "include\\";
	  tcc_add_library_path(t.s_, lib_path.c_str());
	  tcc_add_include_path(t.s_, inc_path.c_str());
	  tcc_set_output_type(t.s_, TCC_OUTPUT_MEMORY);
  }

  void add_symbol(afc::Tcc& t, const std::string& fname, void * fptr)
  {
	  assert(t.s_ && !fname.empty() && fptr && "tcc::add_symbol(), ");

    tcc_set_error_func(t.s_, NULL, &tcc_error_func);
	  tcc_add_symbol(t.s_, fname.c_str(), fptr);
  }

  void add_file(afc::Tcc& t, std::string file)
  {
	  assert(t.s_ && !file.empty() && "tcc::add_file(), ");
    cur_script_ = file;

    tcc_set_error_func(t.s_, NULL, &tcc_error_func);
	  if(tcc_add_file(t.s_, file.c_str()) == -1){
		  destory_exit(t);
	  } 
  }

  void add_code(afc::Tcc& t, std::string code)
  {
    assert(t.s_ && !code.empty() && "tcc::add_code(), ");
    cur_script_ = code;
  
    tcc_set_error_func(t.s_, NULL, &tcc_error_func);
    if(tcc_compile_string(t.s_, code.c_str()) == -1){
      destory_exit(t);
    } 
  }

  void relocate(afc::Tcc& t)
  {
	  assert(t.s_ && !t.m_ && "tcc::relocate(), a ! NULL, a NULL");

    tcc_set_error_func(t.s_, NULL, &tcc_error_func);

	  int memsize = tcc_relocate(t.s_, NULL);
	  if(memsize == -1){
		  destory_exit(t);
		  return;
	  }
    if(t.m_){
      free(t.m_);
    }
	  t.m_ = malloc(memsize);
	  if(!t.m_){
		  destory_exit(t, script_msg("Cann't allocate memory."));
		  return;
	  }
	  tcc_relocate(t.s_, t.m_);
  }

  void * get_symbol(afc::Tcc& t, std::string fname, bool thrownull)
  {
	  assert(t.s_ && !fname.empty() && "tcc::get_symbol(), ");
    tcc_set_error_func(t.s_, NULL, &tcc_error_func);

    void * ptr = tcc_get_symbol(t.s_, fname.c_str());
	  if(!ptr && thrownull){
		  std::string msg = "don't find the script function(";
		  msg += fname;
		  msg += ").";
		  destory_exit(t, script_msg(msg));
	  }
	  return ptr;
  }

  void destory(afc::Tcc& t)
  {
    if(t.s_){
      tcc_delete(t.s_);
      t.s_ = NULL;
    }
    if(t.m_){
	    free(t.m_);
	    t.m_ = NULL;
    }
  }



}//namespace

