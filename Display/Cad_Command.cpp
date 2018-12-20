
#include "StdAfx.h"
#include "Cad_Command.h"

#include "../include/getrace.h"

#include "../object/Point.h"
#include "Normal.h"
 
namespace dlhml
{

static int s_count;
static void trace_new()
{
	++s_count;
//	TRACE_OUT("\nnew cad(Cad_Command), count : %d\n", s_count);
}
static void trace_del()
{
	--s_count;
//	TRACE_OUT("\ndel cad(Cad_Command), count : %d\n", s_count);
}


Cad_Command::Cad_Command()
:xor_(NULL)
,new_(NULL)
,count_(1)
,cur_(NULL)
MCT_INIT2("Cad_Command")
{
	trace_new();
}

Cad_Command::~Cad_Command()
{
	trace_del();
}

LPCTSTR Cad_Command::endpt_cmd_out()
{
  return "Specify the target point or excursion.";
}

Point Cad_Command::key_cammand(const Point& begin, const Point& end)
{
  return end;
}
Point Cad_Command::key_cammand(const Point& begin, const Point& way, double val)
{
	Normal nor;
	nor.set_data(begin, way);
  if(nor.is_zero_normal()){
    nor.x(1);
  }
	return begin.polarTo(val, nor);
}

}//namespace
