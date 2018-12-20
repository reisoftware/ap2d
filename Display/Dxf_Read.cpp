// Dxf_Read.cpp: implementation of the Dxf_Read class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dxf_Read.h"
#include "cadlib.h"
#include "Scene_d.h"
#include "../Object/Database.h"
#include "../Object/Line.h"
#include "../Object/Text.h"
#include "../Object/Circle.h"
#include "../Object/RArc.h"
#include "../Object/Line_Type.h"
#include "../Object/Layer.h"
#include "getrace.h"



const std::string GROUP_DXF = "GROUP_DXF_INPUT";
const std::string GROUP_DIM = "GROUP_DIM";



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool plate_range_yellow = false; 
Dxf_Read::Dxf_Read()
MCT_INIT1("Dxf_Read")
{
	color_in_ = RGB(255,255,255);
	cur_num_ = 0;
	reduce_scale_ = 1;

}

Dxf_Read::~Dxf_Read()
{

}
BOOL Dxf_Read::read(std::string file,dlhml::Scene* scene)
{
	ents_.clear();
	scene_ = scene;
	//打开2000以上版本
	CDrawing drawing;
	if(!open_drawing(drawing))
		return FALSE;
	hDrawing_ = drawing.get_hdrawing();
	if((pDrawing_ = InitilizePDRAWING(hDrawing_))==NULL)
		return FALSE;
	hDxf_ = dxfOpenFile(file.c_str());
	PDXF		pDxf;
	if((pDxf = InitilizePDXF(hDxf_))==NULL)
	{
		GlobalUnlock(hDrawing_);
		return FALSE;
	}
	DWORD	dwCurrentSection = dxfFindNextSection(hDxf_);
	while(dwCurrentSection!=SEC_NOTSET)
	{
		switch(dwCurrentSection)
		{
			case SEC_HEADER:	// Header Section
				break;
			case SEC_TABLES:	// Tables Section
				read_tables();
				break;
			case SEC_BLOCKS:	// Blocks Section
				break;
			case SEC_ENTITIES:	// Entities Section
				read_entities(pDxf);
				break;
		}
		dwCurrentSection = dxfFindNextSection(hDxf_);
	}
	int count = scene_->database()->entity_size();
	TRACE_OUT("\t\t\t Dxf_Read::entities size = %d.\n",count);

	UnInitilizePDXF(hDxf_);
	if(!dxfCloseFile(hDxf_))
		return FALSE;
	return UnInitilizePDRAWING(hDrawing_);
}
BOOL Dxf_Read::read_entities(PDXF pDxf)
{
//	TRACE_OUT("\t\t\t Dxf_Read::read_entities start .\n");
	DXFENTITYHEADER	DxfEntityHeader;
	char			DxfEntityData[4096];
	ENTITYHEADER	EntityHeader;
	while(dxfReadEntityData_Direct(pDxf, &DxfEntityHeader, &DxfEntityData))
	{
		cur_num_++;
	//	TRACE_OUT("\t\t\t Dxf_Read::entity num = %d.\n",cur_num_);
		Z_EntProperties entProp;
		get_ent_header(DxfEntityHeader,EntityHeader,entProp);
		switch(DxfEntityHeader.EntityType)
		{
			case ENT_LINE:
				line_add_db(entProp,(PDXFENTLINE)&DxfEntityData);
			break;
			case ENT_POINT:
				point_add_db(entProp,(PDXFENTPOINT)&DxfEntityData);
			break;
			case ENT_CIRCLE:
				circle_add_db(entProp,(PDXFENTCIRCLE)&DxfEntityData);
			break;
			case ENT_ARC:
				arc_add_db(entProp,(PDXFENTARC)&DxfEntityData);
			break;
			case ENT_TEXT:
				text_add_db(entProp,(PDXFENTTEXT)&DxfEntityData);
			break;				
		}		
	}
//	TRACE_OUT("\t\t\t Dxf_Read::read_entities end .\n");
	return TRUE;
}
void Dxf_Read::text_add_db(const Z_EntProperties& entProp,PDXFENTTEXT txt)
{

	ENTTEXT			Text;
	STYLE			Style;
	ZeroMemory(&Text, sizeof(ENTTEXT));
	Text.Point0 = txt->Point0;
	strcpy(Text.strText, txt->strText);
	Text.TextData.Height = txt->TextData.Height;
	Text.TextData.RotationAngle = txt->TextData.RotationAngle;
	Text.TextData.WidthFactor = txt->TextData.WidthFactor;
	Text.TextData.Oblique = txt->TextData.Oblique;
	Text.TextData.GenerationFlag = txt->TextData.GenerationFlag;
	Text.TextData.Justification = txt->TextData.Justification;
	Text.TextData.SecondAlignmentPoint = txt->TextData.SecondAlignmentPoint;
	// Looking for text style name
	if(strlen(txt->TextData.TextStyleName)>0)
	{
		strcpy(Style.Name, txt->TextData.TextStyleName);
		if(drwFindTableType_Direct(pDrawing_, TAB_STYLE, FIND_BYNAME, &Style)>0)
			Text.TextData.TextStyleObjhandle = Style.Objhandle;
	}

	dlhml::Text *pNewTxt = dlhml::Text::create_me();
	dlhml::Point ptCenter;
	ptCenter.setdata(Text.Point0.x,Text.Point0.y);
	pNewTxt->align_point(dlhml::Text::left_bottom);

	//pNewTxt->style_name(txt->TextData.TextStyleName);

	
	pNewTxt->color(entProp.color);

	std::string str;
	str = Text.strText;

	//处理有[]号的字符串

	std::string::size_type pos = 0;
	while ( (pos = str.find("[",pos)) != std::string::npos){
		str.replace(pos,1,"(");
		pos++;
	}
	pos = 0;
	while ( (pos = str.find("]",pos)) != std::string::npos){
		str.replace(pos,1,")");
		pos++;
	}


	pNewTxt->setdata(ptCenter,str);
  pNewTxt->rotation(dlhml::degree_2_radian(Text.TextData.RotationAngle));
 	pNewTxt->layer_name(entProp.ch_layer);
	TRACE_OUT("circle layer = %s.\n",entProp.ch_layer);
	//pNewTxt->layer_name("Dxf Import");

	pNewTxt->group(GROUP_DXF);
	//字体拉长了，把比例因子引起来了
	/*
	if(Text.TextData.WidthFactor == 0)
	{
	//	Text.TextData.WidthFactor = 1;
		pNewTxt->width_factor(Text.TextData.WidthFactor);
	}
	*/
	pNewTxt->width_factor(Text.TextData.WidthFactor);
	//pNewTxt->font(Text.TextData.TextStyleObjhandle);
//	pNewTxt->font("微软雅黑");

	dlhml::Entity_ID id;
	pNewTxt->post2db(*scene_->database(),id);

	double h = Text.TextData.Height * reduce_scale_;
	pNewTxt->dxf_height(h);


	ents_.push_back(pNewTxt);



}
BOOL Dxf_Read::arc_add_db(const Z_EntProperties& entProp,PDXFENTARC arc)
{
	ENTARC			Arc;
	Arc.Point0 = arc->Point0;
	Arc.Radius = arc->Radius;
	Arc.StartAngle = arc->StartAngle;
	Arc.EndAngle = arc->EndAngle;

	dlhml::RArc *pNewArc = dlhml::RArc::create_me();
	dlhml::Point ptCenter;
	ptCenter.setdata(Arc.Point0.x,Arc.Point0.y);
  pNewArc->color(entProp.color);

	pNewArc->layer_name(entProp.ch_layer);
	TRACE_OUT("circle layer = %s.\n",entProp.ch_layer);

	//pNewArc->layer_name("Dxf Import");
	
	pNewArc->group(GROUP_DXF);

	pNewArc->line_style(entProp.ch_ltype);
	pNewArc->set_degree2d(ptCenter,Arc.Radius,Arc.StartAngle,Arc.EndAngle);
	dlhml::Entity_ID id; 
	pNewArc->post2db(*scene_->database(),id);
	ents_.push_back(pNewArc);
	return TRUE;
}
BOOL Dxf_Read::circle_add_db(const Z_EntProperties& entProp,PDXFENTCIRCLE circle)
{
	ENTCIRCLE		Circle;
	Circle.Point0 = circle->Point0;
	Circle.Radius = circle->Radius;

	dlhml::Circle *pNewCircle = dlhml::Circle::create_me();
	dlhml::Point ptCenter;
	ptCenter.setdata(Circle.Point0.x,Circle.Point0.y);
	pNewCircle->color(entProp.color);

	
	pNewCircle->group(GROUP_DXF);	
	pNewCircle->layer_name("layer_input_entities");

	pNewCircle->line_style(entProp.ch_ltype);
	pNewCircle->setdata(ptCenter,Circle.Radius);
	pNewCircle->layer_name(entProp.ch_layer);
	TRACE_OUT("circle layer = %s.\n",entProp.ch_layer);

	//pNewCircle->layer_name("Dxf Import");

	dlhml::Entity_ID id;
	pNewCircle->post2db(*scene_->database(),id);
	ents_.push_back(pNewCircle);
	return TRUE;
}
BOOL Dxf_Read::point_add_db(const Z_EntProperties& entProp,PDXFENTPOINT pt)
{
	BOOL result = TRUE;

	return result;
}

void Dxf_Read::line_add_db(const Z_EntProperties& entProp,PDXFENTLINE li)
{
  ENTLINE			Line;
  Line.Point0 = li->Point0;
  Line.Point1 = li->Point1;
  dlhml::Line *pNewLine = dlhml::Line::create_me();
  dlhml::Point ptStart,ptEnd;
  ptStart.setdata(Line.Point0.x,Line.Point0.y);
  ptEnd.setdata(Line.Point1.x,Line.Point1.y);

  pNewLine->color(entProp.color);
	pNewLine->group(GROUP_DXF);	



	pNewLine->layer_name(entProp.ch_layer);
	//pNewLine->layer_name("Dxf Import");
  
	pNewLine->line_style(entProp.ch_ltype);
  pNewLine->setdata(ptStart,ptEnd);
  dlhml::Entity_ID id;
  pNewLine->post2db(*scene_->database(),id);
	ents_.push_back(pNewLine);
}

void Dxf_Read::get_ent_header(const DXFENTITYHEADER &DxfEntityHeader,ENTITYHEADER	&EntityHeader,Z_EntProperties& entProp)
{
	ZeroMemory(&EntityHeader, sizeof(ENTITYHEADER));
	EntityHeader.EntityType = DxfEntityHeader.EntityType;
	EntityHeader.Color = DxfEntityHeader.Color;
	EntityHeader.Thickness = DxfEntityHeader.Thickness;
	EntityHeader.LineTypeScale = DxfEntityHeader.LineTypeScale;
	memcpy(EntityHeader.ExtrusionDirection, DxfEntityHeader.ExtrusionDirection, sizeof(double)*3);
	EntityHeader.LineWeight = DxfEntityHeader.LineWeight;
	LAYER			Layer;
	LTYPE			LType;
	if(strlen(DxfEntityHeader.LayerName)>0)
	{
		strcpy(Layer.Name, DxfEntityHeader.LayerName);
		if(drwFindTableType_Direct(pDrawing_, TAB_LAYER, FIND_BYNAME, &Layer)>0)
			EntityHeader.LayerObjhandle = Layer.Objhandle;
	}
	if(strlen(DxfEntityHeader.LTypeName)>0)
	{
		strcpy(LType.Name, DxfEntityHeader.LTypeName);
		if(drwFindTableType_Direct(pDrawing_, TAB_LTYPE, FIND_BYNAME, &LType)>0)
			EntityHeader.LTypeObjhandle = LType.Objhandle;
	}
	
	strcpy(entProp.ch_layer,Layer.Name);
	get_ltype(LType.Name,entProp.ch_ltype);
	entProp.color = get_color(EntityHeader.Color);

}
BOOL Dxf_Read::read_tables()
{
	DWORD		dwCurrentTableType;
	do
	{
		if((dwCurrentTableType = dxfFindNextTableType(hDxf_))==TAB_NOTSET)
			break;
		switch(dwCurrentTableType)
		{
			case TAB_DIMSTYLE:	// DimStyle TableType
				read_dimstyles();
				break;
			case TAB_LAYER:		// Layer TableType
				read_layers();
				break;
			case TAB_LTYPE:		// LType TableType
				read_ltypes();
				break;
			case TAB_STYLE:		// Style TableType
				read_styles();
				break;
		}		
	}
	while(dxfGetCurrentSection(hDxf_)==SEC_TABLES);
	return TRUE;
}
BOOL Dxf_Read::read_styles()
{
	STYLE		Style;
	DXFSTYLE	DxfStyle;
	do{
		if(dxfReadTableType(hDxf_, &DxfStyle)!=TAB_STYLE)
			break;

		strcpy(Style.Name, DxfStyle.Name);
		Style.StandardFlags = DxfStyle.StandardFlags;
		Style.TextGenerationFlags = DxfStyle.TextGenerationFlags;
		strcpy(Style.PrimaryFontFilename, DxfStyle.PrimaryFontFilename);
    //strcpy(Style.BigFontFilename, DxfStyle.BigFontFilename);
		Style.ObliqueAngle = DxfStyle.ObliqueAngle;
		Style.FixedTextHeight = DxfStyle.FixedTextHeight;
		Style.WidthFactor = DxfStyle.WidthFactor;
		Style.LastHeightUsed = DxfStyle.Height;

		drwAddTableType(hDrawing_, TAB_STYLE, &Style);
		D_STYLE d_style = Style;
		styles_.push_back(d_style);
		style_add_db(Style);
    txt_style_add_db(DxfStyle);
	} while(dxfGetCurrentTableType(hDxf_)==TAB_STYLE);
	return TRUE;
}
BOOL Dxf_Read::style_add_db(STYLE &style)
{

	return TRUE;
}
BOOL Dxf_Read::txt_style_add_db(DXFSTYLE &dxfstyle)
{
  dlhml::Text_Style *sty = dlhml::Text_Style::create_me();
  sty->name(dxfstyle.Name);
  strcpy(sty->na, dxfstyle.Name);
  sty->StandardFlags = dxfstyle.StandardFlags;
  sty->TextGenerationFlags = dxfstyle.TextGenerationFlags;
  strcpy(sty->PrimaryFontFilename, dxfstyle.PrimaryFontFilename);
  //strcpy(sty->BigFontFilename, dxfstyle.BigFontFilename);
  sty->ObliqueAngle = dxfstyle.ObliqueAngle;
  sty->FixedTextHeight = dxfstyle.FixedTextHeight;
  sty->WidthFactor = dxfstyle.WidthFactor;
  sty->LastHeightUsed = dxfstyle.Height;
  scene_->database()->textstyle_push_back(sty);
  return TRUE;
}

BOOL Dxf_Read::read_ltypes()
{
	DXFLTYPE	DxfLType;
	LTYPE		LType;
	do{
		if(dxfReadTableType(hDxf_, &DxfLType)!=TAB_LTYPE)
			break;

		strcpy(LType.Name, DxfLType.Name);
		LType.StandardFlags = DxfLType.StandardFlags;
		strcpy(LType.DescriptiveText, DxfLType.DescriptiveText);
		LType.ElementsNumber = DxfLType.ElementsNumber;
		memcpy(LType.Elements, DxfLType.Elements, sizeof(double)*30);			// Line Elements (Max=30)
		LType.PatternLength = DxfLType.TotalPatternLength;

		drwAddTableType(hDrawing_, TAB_LTYPE, &LType);
		D_LTYPE d_ltype = LType;
		ltypes_.push_back(d_ltype);
		ltype_add_db(LType);
    ltype_add_db(DxfLType);
	} while(dxfGetCurrentTableType(hDxf_)==TAB_LTYPE);

	return TRUE;
}

BOOL Dxf_Read::ltype_add_db(LTYPE &ltype)
{
	return TRUE;
}
BOOL Dxf_Read::ltype_add_db(DXFLTYPE &ltype)
{
  if(strcmp(ltype.Name,"")==0)
    return FALSE;
  dlhml::Line_Type *sty = dlhml::Line_Type::create_me();
  sty->name(ltype.Name);
  strcpy(sty->Name, ltype.Name);
  sty->StandardFlags = ltype.StandardFlags;
  strcpy(sty->DescriptiveText, ltype.DescriptiveText);
  sty->ElementsNumber = ltype.ElementsNumber;
  
  memcpy(sty->Elements, ltype.Elements, sizeof(double)*30);			// Line Elements (Max=30)
  sty->PatternLength = ltype.TotalPatternLength;
  
  scene_->database()->linestyle_push_back(sty);
  
  return TRUE;
}

BOOL Dxf_Read::read_layers()
{
	DXFLAYER	DxfLayer;
	LAYER		Layer;
	LTYPE		LType;
	do
	{
		if(dxfReadTableType(hDxf_, &DxfLayer)!=TAB_LAYER)
			break;
		strcpy(Layer.Name, DxfLayer.Name);
		Layer.StandardFlags = DxfLayer.StandardFlags;
		Layer.Color = DxfLayer.Color;
//						Layer.LineWeight = DxfLayer.LineWeight;
//						Layer.PlotFlag = DxfLayer.PlotFlag;
//						Layer.PlotStyleObjhandle;
		strcpy(LType.Name, DxfLayer.LineType);
		if(drwFindTableType_Direct(pDrawing_, TAB_LTYPE, FIND_BYNAME, &LType)>0)
			Layer.LineTypeObjhandle = LType.Objhandle;
		else
		{
			// Line type is unavailable
			dxfCloseFile(hDxf_);
			GlobalUnlock(hDrawing_);
			return FALSE;
		}

		drwAddTableType(hDrawing_, TAB_LAYER, &Layer);
		D_LAYER d_layer = Layer;
		layers_.push_back(d_layer);
		layer_add_db(Layer);
	}
	while(dxfGetCurrentTableType(hDxf_)==TAB_LAYER);
	return TRUE;

}
BOOL Dxf_Read::read_dimstyles()
{
	DXFDIMSTYLE	DxfDimStyle;
	DIMSTYLE	DimStyle;
	STYLE		Style;
	do{
		if(dxfReadTableType(hDxf_, &DxfDimStyle)!=TAB_DIMSTYLE)
			break;
		strcpy(DimStyle.Name, DxfDimStyle.Name);
		DimStyle.StandardFlags = DxfDimStyle.StandardFlags;
		DimStyle.dimasz = DxfDimStyle.DIMASZ;
		strcpy(DimStyle.dimblk1, DxfDimStyle.DIMBLK1);
		strcpy(DimStyle.dimblk2, DxfDimStyle.DIMBLK2);
		DimStyle.dimclrd = DxfDimStyle.DIMCLRD;
		DimStyle.dimclre = DxfDimStyle.DIMCLRE;
		DimStyle.dimclrt = DxfDimStyle.DIMCLRT;
		DimStyle.dimdle = DxfDimStyle.DIMDLE;
		DimStyle.dimexe = DxfDimStyle.DIMEXE;
		DimStyle.dimexo = DxfDimStyle.DIMEXO;
		DimStyle.dimgap = DxfDimStyle.DIMGAP;
		DimStyle.dimtxt = DxfDimStyle.DIMTXT;
		DimStyle.dimtad = DxfDimStyle.DIMTAD;
		strcpy(Style.Name, DxfDimStyle.DIMTXSTY);
		if(drwFindTableType_Direct(pDrawing_, TAB_STYLE, FIND_BYNAME, &Style)>0)
			DimStyle.dimtxstyObjhandle = Style.Objhandle;
		else
		{
		}
		drwAddTableType(hDrawing_, TAB_DIMSTYLE, &DimStyle);
//			D_DIMSTYLE d_dimstyle = DimStyle;
//			dim_styles_.push_back(d_dimstyle); 
//		dimstyle_add_db(DimStyle);
	} while(dxfGetCurrentTableType(hDxf_)==TAB_DIMSTYLE);

	return TRUE;
}

bool Dxf_Read::open_drawing(CDrawing& drawing)
{
	if(drawing.isOpen())
		drawing.Destroy();
	if(!drawing.Create())
		return false;
	return true;	
}
BOOL Dxf_Read::layer_add_db(LAYER &layer)
{
	LTYPE ltype;
	get_ltype(layer.LineTypeObjhandle,ltype);
	
	dlhml::Color col;
	col = layer.Color;
	dlhml::Layer* layer_new = NULL;
	bool if_have = scene_->database()->get_layer(layer_new,layer.Name);
	if(if_have && layer_new != NULL){
		layer_new->color(col);
		layer_new->line_type(ltype.Name);
	}else{
		dlhml::Layer* pLayer = dlhml::Layer::create_me();
		pLayer->name(layer.Name);
		pLayer->color(col);
		pLayer->line_type(ltype.Name);
		scene_->database()->layer_push_back(pLayer);
	}

	return TRUE;	
}

bool Dxf_Read::get_ltype(OBJHANDLE obj_handle,LTYPE & ltype)
{
	for(int i=0;i<ltypes_.size();i++)
	{
		if(ltypes_[i].Objhandle == obj_handle){
			ltype.Objhandle = ltypes_[i].Objhandle;
			strcpy(ltype.Name, ltypes_[i].Name);
			ltype.StandardFlags = ltypes_[i].StandardFlags;
			strcpy(ltype.DescriptiveText, ltypes_[i].DescriptiveText);
			ltype.ElementsNumber = ltypes_[i].ElementsNumber;
			ltype.Elements[30] = ltypes_[i].Elements[30];
			ltype.PatternLength = ltypes_[i].PatternLength;
			return true;
		}
	}

	return false;
}
void Dxf_Read::get_ltype(char* ch_ltype_old,char* ch_ltype)
{
  if(strcmp(ch_ltype_old,"Continuous") == 0)
  {
    strcpy(ch_ltype,"Continuous");	
  }
  else if(strcmp(ch_ltype_old,"CENTER") == 0||
    strcmp(ch_ltype_old,"CENTER2") == 0||
    strcmp(ch_ltype_old,"CENTERX2") == 0||
    strcmp(ch_ltype_old,"DASHDOT") == 0||
    strcmp(ch_ltype_old,"DASHDOT2") == 0||
    strcmp(ch_ltype_old,"DASHDOTX2") == 0)
  {
    strcpy(ch_ltype,"center");
  }
  else if(strcmp(ch_ltype_old,"HIDDEN") == 0||
    strcmp(ch_ltype_old,"DOT") == 0||
    strcmp(ch_ltype_old,"XKITLINE01") == 0||
    strcmp(ch_ltype_old,"XKITLINE02") == 0||
    strcmp(ch_ltype_old,"XKITLINE03") == 0||
    strcmp(ch_ltype_old,"XKITLINE04") == 0||
    strcmp(ch_ltype_old,"DASHED") == 0)
  {
    strcpy(ch_ltype,"dot");
  }
  else
  {
    strcpy(ch_ltype,"Continuous");	
  }
}

COLORREF Dxf_Read::get_color(int color)
{
  return dlhml::index_to_colorref(color);
}

// COLORREF Dxf_Read::get_color(int color)
// 	COLORREF col;
// 	if(color == 0)
// 		col = RGB(255,255,255);
// 	else if(color == 1)//红色
// 		col = RGB(255,0,0);
// 	else if(color == 2)//黄色
// 		col = RGB(255,255,0);
// 	else if(color == 3)//绿色
// 		col = RGB(0,255,0);
// 	else if(color == 4)//水色
// 		col = RGB(0,255,255);
// 	else if(color == 5)//蓝色
// 		col = RGB(0,0,255);
// 	else if(color == 6)//品红色
// 		col = RGB(255,0,255);
//   else if(color == 7)//白色
//     col = RGB(255,255,255);
//   else if(color == 8)//黑色
//     col = RGB(0,0,0);
// 	else
// 		col = RGB(255,255,255);
// 
// 
// 	return col;
// }

int		GCode;
char	strValue[2048];
BOOL Dxf_Read::dxfReadEntityData_Direct( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	BOOL	result;

	// Check if current section is ENTITIES or BLOCKS
	if(pDxf->Read.CurrentSection!=SEC_ENTITIES)
	{
		if((pDxf->Read.CurrentSection!=SEC_BLOCKS) || (!pDxf->Read.isBlockOpen))
		{
			// Can not read entity data
			return FALSE;
		}
	}

	dxfStorePos(pDxf);
	ReadParamFromDxfFile(pDxf, GCode, strValue);
	if(GCode!=0)
	{
		// Can not read entity data
		dxfRestorePos(pDxf);
		return FALSE;
	}

	SetEntityHeaderDefaultValues(pEntityHeader);	// Set Entities Header to Default Values
	result = FALSE;

	do {
		if(strcmp(strValue, "LINE")==0)
		{
			ReadLineData(pDxf, pEntityHeader, (PDXFENTLINE)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "POINT")==0)
		{
	//		ReadPointData(pDxf, pEntityHeader, (PDXFENTPOINT)pEntityData);
			ReadPointData_pri(pDxf, pEntityHeader, (PDXFENTPOINT)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "CIRCLE")==0)
		{
			ReadCircleData(pDxf, pEntityHeader, (PDXFENTCIRCLE)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "ELLIPSE")==0)
		{
			ReadEllipseData(pDxf, pEntityHeader, (PDXFENTELLIPSE)pEntityData);
			result = TRUE;
			break;
		}
    else if(strcmp(strValue, "TEXT")==0 || strcmp(strValue, "MTEXT")==0)
		{
			ReadTextData(pDxf, pEntityHeader, (PDXFENTTEXT)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "ARC")==0)
		{
			ReadArcData(pDxf, pEntityHeader, (PDXFENTARC)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "SOLID")==0)
		{
			ReadSolidData(pDxf, pEntityHeader, (PDXFENTSOLID)pEntityData);
			result = TRUE;
			break;
		}
		else if(strcmp(strValue, "INSERT")==0)
		{
			ReadInsertData(pDxf, pEntityHeader, (PDXFENTINSERT)pEntityData);
			result = TRUE;
			break;
		}
		//This code is implemented by tran duy dung
		//*******************************************************************
		else if(strcmp(strValue, "POLYLINE")==0){
			ReadPolyLineData(pDxf, pEntityHeader, (PDXFENTPOLYLINE)pEntityData);
			result = TRUE;
			break;
		}
		//*******************************************************************
		else if(strcmp(strValue, "DIMENSION")==0)
		{
			ReadDimensionData(pDxf, pEntityHeader, (PDXFENTDIMENSION)pEntityData);
			result = TRUE;
			break;
		}
		else
		{
			// Unknown entity
			// Looking for next entity
			do {
				ReadParamFromDxfFile(pDxf, GCode, strValue);
			} while(GCode!=0);
		}
	} while((strcmp(strValue, "ENDBLK")!=0) && (strcmp(strValue, "ENDSEC")!=0) && (pDxf->Read.CurrentPos<pDxf->Read.FileSize));

	if((pDxf->Read.CurrentSection==SEC_BLOCKS) && (pDxf->Read.isBlockOpen))
	{
		//此时为块
		int block = 0;

		if((GCode==0) && (strcmp(strValue, "ENDBLK")==0))
		{
			pDxf->Read.isBlockOpen = FALSE;

			do{
				dxfStorePos(pDxf);
				ReadParamFromDxfFile(pDxf, GCode, strValue);
			} while(GCode!=0);

			if(strcmp(strValue, "ENDSEC")==0)
				pDxf->Read.CurrentSection = SEC_NOTSET; // Blocks section has been finished
			else // Reached to the next block
				dxfRestorePos(pDxf);
		}
		else
			dxfRestorePos(pDxf);

	}
	else
	{
		if((GCode==0) && (strcmp(strValue, "ENDSEC")==0))
			pDxf->Read.CurrentSection = SEC_NOTSET; // Entities section has been finished
		else
			dxfRestorePos(pDxf);
	}

	return result;//
}
BOOL Dxf_Read::ReadPointData_pri( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTPOINT pPoint )
{
	ZeroMemory(pPoint, sizeof(DXFENTPOINT));

	pEntityHeader->EntityType = ENT_POINT;

	ReadParamFromDxfFile(pDxf, GCode, strValue);
	while(GCode!=0)
	{
		switch(GCode)
		{
		case 8:		// Layer Name
			strcpy(pEntityHeader->LayerName, strValue);
			//赋值给记录信息
			strcpy(pPoint->info, strValue);
			break;
		case 62:	// Color
			pEntityHeader->Color = atoi(strValue);
			break;
		case 6:		// Line Type
			strcpy(pEntityHeader->LTypeName, strValue);
			break;
		case 39:	// Thickness
			pEntityHeader->Thickness = atof(strValue);
			break;
		case 48:	// Linetype scale
			pEntityHeader->LineTypeScale = atof(strValue);
			break;
		case 10:	// Point location X
			pPoint->Point0.x = atof(strValue);
			break;
		case 20:	// Point location Y
			pPoint->Point0.y = atof(strValue);
			break;
		case 30:	// Point location Z
			pPoint->Point0.z = atof(strValue);
			break;
 		}

		dxfStorePos(pDxf);
		ReadParamFromDxfFile(pDxf, GCode, strValue);
	}
	
	return TRUE;
}





