// Select_Pen.cpp: implementation of the Select_Pen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Select_Pen.h"
#include "Line_Type.h"
#include "Entity.h"
#include "Painter.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace dlhml{
Select_Pen::Select_Pen(Painter& painter,const Entity& ent,const Line_Type* lt)
:painter_(painter)
MCT_INIT2("Select_Pen")
{
	if(NULL == lt){				//无线型
		//DWORD style[]={2,2};
		//pen_ = Line_Type::get_pen(style,sizeof(style)/sizeof(DWORD),RGB(102,127,204));
	}else{
    pen_ = lt->get_pen(ent.color(), ent.selected());
//		if(ent.selected()){	//选择
//			//DWORD style[]={1,1};
// 			pen_ = lt->get_pen(ent.color(), true);
//      //pen_ = lt->get_pen(style, 3, ent.color());
//		}else{							//正常
//			pen_ = lt->get_pen(ent.color(), false);
//		}
	}
	old_pen_ = painter_.select_pen(pen_);

//	if(NULL == lt){				//无线型
//		DWORD style[]={2,2};
//		pen_ = Line_Type::get_pen(style,sizeof(style)/sizeof(DWORD),RGB(102,127,204));
//	}else{
//		if(ent.selected()){	//选择
//			DWORD style[]={1,1};
//      pen_ = Line_Type::get_pen(style, sizeof(style)/sizeof(DWORD), ent.color());
//		}else{							//正常
//			pen_ = lt->get_pen(ent.color());
//		}
//	}
//	old_pen_ = painter_.select_pen(pen_);
}

Select_Pen::~Select_Pen()
{
	painter_.select_pen(old_pen_);
	::DeleteObject(pen_);
}
}
