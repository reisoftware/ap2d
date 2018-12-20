#include "StdAfx.h"
#include "call_tcc.h"
#include "tcc.h"
#include "dir.h"
#include <cassert>

namespace afc{

static void exit(LPCTSTR msg)
{
  ::MessageBox(NULL, msg, "tcc", MB_OK);
}


void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_code(func_code);
    t.relocate(); 
    typedef void(*PF)();
    PF pf = (PF)t.get_symbol(func_name);
    pf();
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}

void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name, void * param1)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_code(func_code);
    t.relocate();
    typedef void(*PF)(void *);
    PF pf = (PF)t.get_symbol(func_name);
    pf(param1);
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}

void call_code(PF_ADD_SYMBOL pf_symbol, LPCTSTR func_code, LPCTSTR func_name, void * param1, void * param2)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_code(func_code);
    t.relocate(); 
    typedef void(*PF)(void *, void *);
    PF pf = (PF)t.get_symbol(func_name);
    pf(param1, param2);
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}






void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_file(file);
    t.relocate(); 
    typedef void(*PF)();
    PF pf = (PF)t.get_symbol(func_name);
    pf();
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}

void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name, void * param1)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_file(file);
    t.relocate(); 
    typedef void(*PF)(void *);
    PF pf = (PF)t.get_symbol(func_name);
    pf(param1);
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}

void call_script(PF_ADD_SYMBOL pf_symbol, LPCTSTR file, LPCTSTR func_name, void * param1, void * param2)
{
  assert(pf_symbol);
  try{
    afc::Tcc t;
		t.create(afc::dir::exe_path().c_str());
    pf_symbol(t);
    t.add_file(file);
    t.relocate(); 
    typedef void(*PF)(void *, void *);
    PF pf = (PF)t.get_symbol(func_name);
    pf(param1, param2);
  }catch(afc::Tcc::Error err){
    exit(err.msg_);
  }
}



}//namespace

