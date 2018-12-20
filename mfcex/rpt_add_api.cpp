#include "stdafx.h"
#include "rpt_add_api.h"
#include "rpt_model.h"
#include <cassert>
#include "../include/getrace.h"
#include "../afc/format.h"
#include "../afc/rpt_api_state.h"
#include "../afc/rpt_def.h"



/////////////////////// << TCC >> ///////////////////////

void rpt_add_symbol(afc::Tcc &t)
{
  t.add_symbol("get_project_name", rpt_get_project_name);
  t.add_symbol("add_all", rpt_add_all);
  t.add_symbol("add_assembly", rpt_add_assembly);
  t.add_symbol("add_part", rpt_add_part);
}

/////////////////////// << api >> ///////////////////////

void rpt_get_project_name(char * buf, int bufsize)
{
	afc::string str = rpt::model().name();
	if(!str.c_str()){
		str = "";
	}
	strncpy(buf, str, bufsize-1);
	buf[bufsize-1] = 0;
}

// 	assert(rpt_api.table_dats);
// 	std::vector<afc::Dat>& dats = *rpt_api.table_dats;
// 	afc::Dat t;
// 
// 	std::vector<rpt::CRSteel*> ps;
// 	rpt::model().get_assembly(ps);
// 
// 	int n=ps.size();
// 	int i=0;
// 	for(i=0; i<n; ++i){
// 		t.set(ps[i], sizeof(RSteel));
// 		dats.push_back(t);
// 	}
#define rpt_add(callf)	\
	assert(rpt_api.table_dats);	\
	std::vector<afc::Dat>& dats = *rpt_api.table_dats;	\
	afc::Dat t;	\
	\
	std::vector<rpt::CRSteel*> ps;	\
	rpt::model().callf;	\
	\
	int n=ps.size();	\
	int i=0;	\
	for(i=0; i<n; ++i){	\
		t.set(ps[i], sizeof(RSteel));	\
		dats.push_back(t);	\
	}


void rpt_add_all()
{
	rpt_tcc_ptr(rpt_api.table_dats, "add_all()");
	rpt_add(get_all(ps));

}

void rpt_add_assembly()
{
	rpt_tcc_ptr(rpt_api.table_dats, "add_assembly()");
	rpt_add(get_assembly(ps));

}

void rpt_add_part(const char * no)
{
	rpt_tcc_ptr(rpt_api.table_dats, "add_part()");
	rpt_add(get_part(ps, no));
}



// 	strcpy(m.mat, "SS100");
// 	strcpy(m.spec, "H100*100*50*1");
// 	m.size = 100;
// 	d.set(&m, sizeof(Rpt_Steel));
// 	dats.push_back(d);
// 
// 	strcpy(m.mat, "SS200");
// 	strcpy(m.spec, "H200*200*50*2");
// 	m.size = 200;
// 	d.set(&m, sizeof(Rpt_Steel));
// 	dats.push_back(d);
// 
// 	strcpy(m.mat, "SS200");
// 	strcpy(m.spec, "H100*100*50*3");
// 	m.size = 210;
// 	d.set(&m, sizeof(Rpt_Steel));
// 	dats.push_back(d);


