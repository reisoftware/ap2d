
#include "stdafx.h"
#include "tcc.h"

#include <cassert>
#include <string>

#include "libtcc.h"
//#include "getrace.h"



namespace the{
static afc::string * error_msg_;
static void error_msg(void * opaque, const char * msg)
{
	assert(error_msg_);
  *error_msg_ += msg;
}

static void throw_error(afc::Tcc::Error& err)
{
	throw err;
}

}//namespace

namespace afc{

static Tcc * last_tcc_ = NULL;
void Tcc::exit(LPCTSTR msg)
{
	if(last_tcc_){
		afc::string str = msg;
		str += last_tcc_->error_.msg_;
		last_tcc_->error_.msg_ = str;
		last_tcc_->exit();
		return;
	}
	afc::Tcc::Error err;
	err.msg_ = msg;
	the::throw_error(err);
}

Tcc::Tcc()
{
	init();
}

Tcc::~Tcc()
{
	destroy();
}

void Tcc::init()
{
	s_ = NULL;
	m_ = NULL;
	the::error_msg_ = &error_.msg_;
	last_tcc_ = this;
}


void Tcc::create(LPCTSTR path)
{
	assert(path && "Tcc::create()");

	s_ = tcc_new();
  tcc_set_error_func(s_, NULL, &the::error_msg);
  if(!s_){
    exit();
		return;
  }

  afc::string lib_path = afc::string(path) + "lib\\";
  afc::string inc_path = afc::string(path) + "include\\";
	tcc_add_library_path(s_, lib_path);
	tcc_add_include_path(s_, inc_path);
	tcc_set_output_type(s_, TCC_OUTPUT_MEMORY);
}

void Tcc::add_symbol(LPCTSTR fname, void * fptr)
{
	assert(fname && "Tcc::add_symbol()");
	assert(fptr && "Tcc::add_symbol()");

  tcc_set_error_func(s_, NULL, &the::error_msg);
	tcc_add_symbol(s_, fname, fptr);
}

void Tcc::add_file(LPCTSTR file)
{
	assert(file && "Tcc::add_file()");
  script_ = file;

  tcc_set_error_func(s_, NULL, &the::error_msg);
	if(tcc_add_file(s_, file) == -1){
		exit();
		return;
	} 
}

void Tcc::add_code(LPCTSTR code)
{
	assert(code && "Tcc::add_code()");
  script_ = code;

  tcc_set_error_func(s_, NULL, &the::error_msg);
  if(tcc_compile_string(s_, code) == -1){
    exit();
		return;
  } 
}

void Tcc::relocate()
{
	assert(s_);
  tcc_set_error_func(s_, NULL, &the::error_msg);

	int memsize = tcc_relocate(s_, NULL);
	if(memsize == -1){
		exit();
		return;
	}
  if(m_){
    free(m_);
  }
	m_ = malloc(memsize);
	if(!m_){
		exit("Cann't allocate memory.");
		return;
	}
	tcc_relocate(s_, m_);
}

void * Tcc::get_symbol(LPCTSTR fname, bool thrownull)
{
	assert(s_ && "tcc::get_symbol()");
	assert(fname && "tcc::get_symbol()");
  tcc_set_error_func(s_, NULL, &the::error_msg);

  void * ptr = tcc_get_symbol(s_, fname);
	if(!ptr && thrownull){
		afc::string msg = "don't find the script function(";
		msg += fname;
		msg += ").";
		exit(msg);
	}
	return ptr;
}

void Tcc::exit()
{
	error_.msg_ += "\n";
	error_.msg_ += script_;
	the::throw_error(error_);
}

void Tcc::destroy()
{
  if(s_){
    tcc_delete(s_);
    s_ = NULL;
  }
  if(m_){
	  free(m_);
	  m_ = NULL;
  }
	the::error_msg_ = NULL;
	last_tcc_ = NULL;
}


}//namespace

  


