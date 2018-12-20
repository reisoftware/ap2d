/*-------------------------------------------------------------------*\
|  CadLib Version 2.1                                                 |
|  Written by Omid Shahabi <omid_shahabi@hotmail.com>                 |
|  Copyright ?2002-2004                                              |
|  Pars Technology Development Co.                                    |
|                                                                     |
|  This software is distributed on an "AS IS" basis, WITHOUT WARRANTY |
|  OF ANY KIND, either express or implied.                            |
|                                                                     |
|                                                                     |
|  CadLib.cpp: The interface for CadIO.dll                            |
\*-------------------------------------------------------------------*/

#include "stdafx.h"
#include "CadLib.h"
#include <float.h>

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

const LPCTSTR block_name = "*D1";
const LPCTSTR g_baseling_dimstyle = "BASE_LINE_DIM_STYLE";

#define ISLIBRARYLOADED();         \
	if(!isLibraryLoaded)           \
	{                              \
		/* Library is not loaded*/ \
		return FALSE;              \
	}                              \

CDrawing::CDrawing()
MCT_INIT1("CDrawing")
{
	bool result;

	m_hDrawing = NULL;
	isLibraryLoaded = true;

	// load CadIO.dll
	hinstCadIO = LoadLibrary( "CadIO.dll" );
	if( !hinstCadIO )
	{
		// Cannot load CadIO.dll
		isLibraryLoaded = false;
        return;
	}

	result = true;
	// Construction & Destruction
	result &= ((drwCreate = (HDRAWING(*)())
		GetProcAddress( hinstCadIO, "drwCreate" )) != NULL);
	result &= ((drwDestroy = (BOOL(*)(HDRAWING))
		GetProcAddress( hinstCadIO, "drwDestroy" )) != NULL);

	// TABLES
	result &= ((drwAddTableType = (OBJHANDLE(*)(HDRAWING, DWORD, LPVOID))
		GetProcAddress( hinstCadIO, "drwAddTableType" )) != NULL);
	result &= ((drwDeleteTableType = (BOOL(*)(HDRAWING, DWORD, OBJHANDLE))
		GetProcAddress( hinstCadIO, "drwDeleteTableType" )) != NULL);
	result &= ((drwFindTableType = (OBJHANDLE(*)(HDRAWING, DWORD, DWORD, LPVOID))
		GetProcAddress( hinstCadIO, "drwFindTableType" )) != NULL);
	// BLOCKS
	result &= ((drwAddBlock = (OBJHANDLE(*)(HDRAWING, PBLOCKHEADER))
		GetProcAddress( hinstCadIO, "drwAddBlock" )) != NULL);
	result &= ((drwDeleteBlock = (BOOL(*)(HDRAWING, OBJHANDLE))
		GetProcAddress( hinstCadIO, "drwDeleteBlock" )) != NULL);
	result &= ((drwFindBlock = (OBJHANDLE(*)(HDRAWING, DWORD, PBLOCKHEADER))
		GetProcAddress( hinstCadIO, "drwFindBlock" )) != NULL);
	// ENTITIES
	result &= ((drwAddEntity = (OBJHANDLE(*)(HDRAWING, OBJHANDLE, PENTITYHEADER, LPVOID))
		GetProcAddress( hinstCadIO, "drwAddEntity" )) != NULL);
	result &= ((drwDeleteEntity = (BOOL(*)(HDRAWING, LPCTSTR, OBJHANDLE))
		GetProcAddress( hinstCadIO, "drwDeleteEntity" )) != NULL);
	result &= ((drwChangeEntity = (BOOL(*)(HDRAWING, LPCTSTR, PENTITYHEADER, LPVOID))
		GetProcAddress( hinstCadIO, "drwChangeEntity" )) != NULL);
	result &= ((drwFindEntity = (OBJHANDLE(*)(HDRAWING, LPCTSTR, PENTITYHEADER, LPVOID, DWORD))
		GetProcAddress( hinstCadIO, "drwFindEntity" )) != NULL);
	// Datafile dataexchange
	result &= ((drwSaveDataToFile = (BOOL(*)(HDRAWING, DWORD, LPCTSTR, HWND))
		GetProcAddress( hinstCadIO, "drwSaveDataToFile" )) != NULL);
	result &= ((drwLoadDataFromFile = (BOOL(*)(HDRAWING, OBJHANDLE, DWORD, LPCTSTR, HWND))
		GetProcAddress( hinstCadIO, "drwLoadDataFromFile" )) != NULL);
	// Drawing Window View
	result &= ((drwInitView = (BOOL(*)(HDRAWING, int, int, int, int))
		GetProcAddress( hinstCadIO, "drwInitView" )) != NULL);
	result &= ((drwPaint = (BOOL(*)(HDRAWING, HDC))
		GetProcAddress( hinstCadIO, "drwPaint" )) != NULL);
	result &= ((drwGetViewProperties = (BOOL(*)(HDRAWING, PVIEW))
		GetProcAddress( hinstCadIO, "drwGetViewProperties" )) != NULL);
	result &= ((drwSetViewProperties = (BOOL(*)(HDRAWING, PVIEW))
		GetProcAddress( hinstCadIO, "drwSetViewProperties" )) != NULL);
	result &= ((drwGetDrawingBorder = (BOOL(*)(HDRAWING, PREALRECT))
		GetProcAddress( hinstCadIO, "drwGetDrawingBorder" )) != NULL);
	result &= ((drwZoomExtents = (BOOL(*)(HDRAWING))
		GetProcAddress( hinstCadIO, "drwZoomExtents" )) != NULL);

	//<Author>:zhong
	//<Add>=Date:2007/11/15
	result &= ((drw_get_ents = (BOOL(*)(HDRAWING,dlhml::Database&))
		GetProcAddress( hinstCadIO, "drw_get_ents" )) != NULL);

	//</Add>
	//</Author>
	//<Author>:zhong
	//<Add>=Date:2007/11/19
	result &= ((save_dxf_ents = (BOOL(*)(HDRAWING,LPCTSTR,dlhml::Database&))
		GetProcAddress( hinstCadIO, "save_dxf_ents" )) != NULL);
	//</Add>
	//</Author>
	//09.2.5
//	result &= ((drwLoadDataFromFile_db = (BOOL(*)(HDRAWING, OBJHANDLE, DWORD, LPCTSTR, Database&))
//		GetProcAddress( hinstCadIO, "drwLoadDataFromFile_db" )) != NULL);

	if(!result)
	{
		// Cannot load all functions from library
		isLibraryLoaded = false;
		return;
	}
}

CDrawing::~CDrawing()
{
	if(m_hDrawing!=NULL)
		Destroy();
	// Unload CadIO.dll
	if(isLibraryLoaded)
		FreeLibrary ( hinstCadIO );
	isLibraryLoaded = false;
}

BOOL CDrawing::isOpen()
{
	if((!isLibraryLoaded) || (m_hDrawing==NULL))
		return FALSE;
	else
		return TRUE;
}

// Construction & Destruction -------------------------------------
BOOL CDrawing::Create( )
{
	ISLIBRARYLOADED();
	if(m_hDrawing!=NULL)
	{
		// Drawing is already created
		return FALSE;
	}

	if((m_hDrawing = drwCreate())!=NULL)
	{
		m_EntityHeader.LayerObjhandle = CurrentLayerObjhandle = 0;// Layer 0
		m_EntityHeader.LTypeObjhandle = CurrentLTypeObjhandle = 0;// ByLayer
		m_EntityHeader.Color = CurrentColor = 256;				  // ByLayer
		m_EntityHeader.Thickness = CurrentThickness = 0;
		m_EntityHeader.LineTypeScale = 1.0;
		CurrentDimStyleObjhandle = 0;
		CurrentStyleObjhandle = 0;
		ActiveBlockObjhandle = 0;	// Entities section
	}

	return (m_hDrawing!=NULL);
}

BOOL CDrawing::Destroy( )
{
	BOOL result;
	ISLIBRARYLOADED();
	result = drwDestroy(m_hDrawing);
	if(result)
		m_hDrawing = NULL;
	return result;
}

// Drawing View
BOOL CDrawing::InitView( int x, int y, int nWidth, int nHeight )
{
	ISLIBRARYLOADED();
	if(m_hDrawing!=NULL)
		return drwInitView(m_hDrawing, x, y, nWidth, nHeight);
	else
		return NULL;
}

BOOL CDrawing::Paint( HDC hdc )
{
	ISLIBRARYLOADED();
	return drwPaint(m_hDrawing, hdc );
}

double CDrawing::GetZoomLevel( )
{
	ISLIBRARYLOADED();

	VIEW drwview;
	if(drwGetViewProperties(m_hDrawing, &drwview))
		return drwview.ZoomLevel;
	else
		return 0;
}

BOOL CDrawing::SetZoomLevel(double ZoomLevel)
{
	ISLIBRARYLOADED();

	VIEW drwview;
	if(drwGetViewProperties(m_hDrawing, &drwview))
	{
		double cx;
		double cy;
		cx = drwview.ViewLeft + ((drwview.WindowRight-drwview.WindowLeft)/2)*(1/(drwview.PPU*drwview.ZoomLevel));
		cy = drwview.ViewBottom + ((drwview.WindowBottom-drwview.WindowTop)/2)*(1/(drwview.PPU*drwview.ZoomLevel));

		drwview.ZoomLevel = ZoomLevel;
		drwview.ViewLeft = cx - ((drwview.WindowRight-drwview.WindowLeft)/2)*(1/(drwview.PPU*drwview.ZoomLevel));
		drwview.ViewBottom = cy - ((drwview.WindowBottom-drwview.WindowTop)/2)*(1/(drwview.PPU*drwview.ZoomLevel));
		if(drwSetViewProperties(m_hDrawing, &drwview))
			return TRUE;
	}
	return FALSE;
}

BOOL CDrawing::GetViewProperties( PVIEW pView )
{
	ISLIBRARYLOADED();
	return drwGetViewProperties(m_hDrawing, pView);
}

BOOL CDrawing::SetViewProperties( PVIEW pView )
{
	ISLIBRARYLOADED();
	return drwSetViewProperties(m_hDrawing, pView);
}

BOOL CDrawing::GetDrawingBorder( PREALRECT pRect )
{
	ISLIBRARYLOADED();
	return drwGetDrawingBorder(m_hDrawing, pRect);
}

BOOL CDrawing::ZoomExtents( )
{
	ISLIBRARYLOADED();
	return drwZoomExtents(m_hDrawing);
}

// Configuration ---------------------------------------------------
BOOL CDrawing::SetLayer( LPCTSTR Name )
{
	LAYER Layer;
	strcpy(Layer.Name, Name);
	if(drwFindTableType(m_hDrawing, TAB_LAYER, FIND_BYNAME, &Layer)>0)
	{
		CurrentLayerObjhandle = Layer.Objhandle;
		m_EntityHeader.LayerObjhandle = CurrentLayerObjhandle;
		SetLineType(NULL); // Set linetype to default
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDrawing::SetLineType( LPCTSTR Name )
{
	LTYPE LType;

	// Check for default linetype
	if(Name==NULL)
	{
		CurrentLTypeObjhandle = 0;
		m_EntityHeader.LTypeObjhandle = 0;
		return TRUE;
	}

	strcpy(LType.Name, Name);
	if(drwFindTableType(m_hDrawing, TAB_LTYPE, FIND_BYNAME, &LType)>0)
	{
		CurrentLTypeObjhandle = LType.Objhandle;
		m_EntityHeader.LTypeObjhandle = CurrentLTypeObjhandle;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDrawing::SetTextStyle( LPCTSTR Name )
{
	STYLE Style;
	strcpy(Style.Name, Name);
	if(drwFindTableType(m_hDrawing, TAB_STYLE, FIND_BYNAME, &Style)>0)
	{
		CurrentStyleObjhandle = Style.Objhandle;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDrawing::SetDimStyle( LPCTSTR Name )
{
	DIMSTYLE DimStyle;
	strcpy(DimStyle.Name, Name);
	if(drwFindTableType(m_hDrawing, TAB_DIMSTYLE, FIND_BYNAME, &DimStyle)>0)
	{
		CurrentDimStyleObjhandle = DimStyle.Objhandle;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDrawing::SetColor( short Color )
{
	CurrentColor = Color;
	m_EntityHeader.Color = CurrentColor;
	return TRUE;
}

BOOL CDrawing::SetThickness( double Thickness )
{
	CurrentThickness = Thickness;
	m_EntityHeader.Thickness = CurrentThickness;
	return TRUE;
}

double CDrawing::SetLineTypeScale( double LineTypeScale )
{
	double prevLineTypeScale = m_EntityHeader.LineTypeScale;
	m_EntityHeader.LineTypeScale = LineTypeScale;
	return prevLineTypeScale;
}

// TABLES ----------------------------------------------------------
OBJHANDLE CDrawing::AddTableType( DWORD dwTableType, LPVOID pTableType )
{
	ISLIBRARYLOADED();
//	return drwAddTableType(m_hDrawing, dwTableType, pTableType);
	return drwAddTableType_pri(m_hDrawing, dwTableType, pTableType);
}
OBJHANDLE CDrawing::drwAddTableType_pri( HDRAWING hDrawing, DWORD dwTableType, LPVOID pTableType )
{
	PDRAWING	pDrawing;
	int			CurrentTType;
	OBJHANDLE	NewTableTypeObjhandle;

	// Initialize pDrawing ------------------
	if((pDrawing = InitilizePDRAWING(hDrawing))==NULL)
		return 0;

	// Check for duplication
	if(drwFindTableType_Direct(pDrawing, dwTableType, FIND_BYNAME, pTableType)!=0)
	{
		// TableType already exists
		GlobalUnlock(hDrawing);
		//已存在时需要把句柄值传出

		return 0;
	}

	NewTableTypeObjhandle = pDrawing->LastObjhandle + 1;

	switch( dwTableType )
	{
	case TAB_DIMSTYLE:
		if(pDrawing->Tables.NumDimStyles>=MAX_DIMSTYLES)
		{
			// Cannot add more DimStyles
			GlobalUnlock(hDrawing);
			return 0;
		}

		STYLE		Style;
		Style.Objhandle = ((PDIMSTYLE)pTableType)->dimtxstyObjhandle;
		if(drwFindTableType(hDrawing, TAB_STYLE, FIND_BYHANDLE, &Style)<=0)
		{
			// Cannot find textstyle used for this dimstyle
			GlobalUnlock(hDrawing);
			return 0;
		}

		CurrentTType = pDrawing->Tables.NumDimStyles;
		CopyMemory(&pDrawing->Tables.DimStyle[CurrentTType], pTableType, sizeof(DIMSTYLE));
		pDrawing->Tables.DimStyle[CurrentTType].Objhandle = NewTableTypeObjhandle;
		pDrawing->Tables.NumDimStyles++;
	//	dxfAddTextStyle(pDrawing)
		break;

	case TAB_LAYER:
		if(pDrawing->Tables.NumLayers>=MAX_LAYERS)
		{
			// Cannot add more Layers
			GlobalUnlock(hDrawing);
			return 0;
		}

		LTYPE	LType;
		LType.Objhandle = ((PLAYER)pTableType)->LineTypeObjhandle;
		if(drwFindTableType(hDrawing, TAB_LTYPE, FIND_BYHANDLE, &LType)<=0)
		{
			// Cannot find linetype used for this layer
			GlobalUnlock(hDrawing);
			return 0;
		}

		CurrentTType = pDrawing->Tables.NumLayers;
		CopyMemory(&pDrawing->Tables.Layer[CurrentTType], pTableType, sizeof(LAYER));
		pDrawing->Tables.Layer[CurrentTType].Objhandle = NewTableTypeObjhandle;
		pDrawing->Tables.NumLayers++;
		break;

	case TAB_LTYPE:
		if(pDrawing->Tables.NumLTypes>=MAX_LTYPES)
		{
			// Cannot add more LineTypes
			GlobalUnlock(hDrawing);
			return 0;
		}

		CurrentTType = pDrawing->Tables.NumLTypes;
		CopyMemory(&pDrawing->Tables.LType[CurrentTType], pTableType, sizeof(LTYPE));
		pDrawing->Tables.LType[CurrentTType].Objhandle = NewTableTypeObjhandle;
		pDrawing->Tables.NumLTypes++;
		break;

	case TAB_STYLE:
		if(pDrawing->Tables.NumStyles>=MAX_STYLES)
		{
			// Cannot add more TextStyles
			GlobalUnlock(hDrawing);
			return 0;
		}

		CurrentTType = pDrawing->Tables.NumStyles;
		CopyMemory(&pDrawing->Tables.Style[CurrentTType], pTableType, sizeof(STYLE));
		pDrawing->Tables.Style[CurrentTType].Objhandle = NewTableTypeObjhandle;
		pDrawing->Tables.NumStyles++;
		break;

	default:
		// Unknown Table Type
		GlobalUnlock(hDrawing);
		return 0;
	}

	pDrawing->LastObjhandle++;

	// UnInitilize pDrawing -----------------
	UnInitilizePDRAWING(hDrawing);

	return NewTableTypeObjhandle;
}

OBJHANDLE CDrawing::AddLayer( PLAYER pLayer )
{
	return AddTableType(TAB_LAYER, pLayer);
}

OBJHANDLE CDrawing::AddLinetype( PLTYPE pLineType )
{
	return AddTableType(TAB_LTYPE, pLineType);
}

OBJHANDLE CDrawing::AddTextStyle( PSTYLE pTextStyle )
{
	return AddTableType(TAB_STYLE, pTextStyle);
}


OBJHANDLE CDrawing::AddDimStyle( PDIMSTYLE pDimStyle )
{
	return AddTableType(TAB_DIMSTYLE, pDimStyle);
}

BOOL CDrawing::DeleteTableType( DWORD dwTableType, OBJHANDLE TableTypeObjhandle )
{
	ISLIBRARYLOADED();
	return drwDeleteTableType(m_hDrawing, dwTableType, TableTypeObjhandle);
}

BOOL CDrawing::DeleteLayer( OBJHANDLE LayerObjhandle )
{
	return DeleteTableType(TAB_LAYER, LayerObjhandle);
}

BOOL CDrawing::DeleteLinetype( OBJHANDLE LineTypeObjhandle )
{
	return DeleteTableType(TAB_LTYPE, LineTypeObjhandle);
}

BOOL CDrawing::DeleteTextStyle( OBJHANDLE TextStyleObjhandle )
{
	return DeleteTableType(TAB_STYLE, TextStyleObjhandle);
}

BOOL CDrawing::DeleteDimStyle( OBJHANDLE DimStyleObjhandle )
{
	return DeleteTableType(TAB_DIMSTYLE, DimStyleObjhandle);
}

OBJHANDLE CDrawing::FindTableType( DWORD dwTableType, DWORD dwFindType, LPVOID pTableType )
{
	ISLIBRARYLOADED();
	return drwFindTableType(m_hDrawing, dwTableType, dwFindType, pTableType);
}

// BLOCKS ----------------------------------------------------------
OBJHANDLE CDrawing::AddBlock( PBLOCKHEADER pBlockHeader, LPCTSTR strFileName )
{
	OBJHANDLE	result;
	ISLIBRARYLOADED();
	result = drwAddBlock(m_hDrawing, pBlockHeader);
	if((strFileName!=NULL) && result)
		drwLoadDataFromFile(m_hDrawing, result, 0, strFileName, NULL);
	return result;
}

BOOL CDrawing::DeleteBlock( OBJHANDLE BlockObjhandle )
{
	ISLIBRARYLOADED();
	return drwDeleteBlock(m_hDrawing, BlockObjhandle);
}

OBJHANDLE CDrawing::FindBlock( DWORD dwFindType, PBLOCKHEADER pBlockHeader )
{
	ISLIBRARYLOADED();
	return drwFindBlock(m_hDrawing, dwFindType, pBlockHeader );
}

BOOL CDrawing::SetActiveBlock( OBJHANDLE ohBlock )
{
	ISLIBRARYLOADED();

	if(ohBlock==NULL)
		ActiveBlockObjhandle = NULL; // Entities section is active now
	else
	{
		BLOCKHEADER BlockHeader;
		OBJHANDLE	ohBlockHeader;
		BlockHeader.Objhandle = ohBlock;
		ohBlockHeader = drwFindBlock(m_hDrawing, FIND_BYHANDLE, &BlockHeader);
		if(ohBlockHeader==0) // Block Not Found
			return FALSE;
		else
			ActiveBlockObjhandle = ohBlockHeader;
	}

	return TRUE;
}

BOOL CDrawing::SetActiveBlock( LPCTSTR strBlockName )
{
	ISLIBRARYLOADED();

	if(strBlockName==NULL)
		ActiveBlockObjhandle = NULL; // Entities section is active now
	else
	{
		BLOCKHEADER BlockHeader;
		OBJHANDLE	ohBlockHeader;
		strcpy(BlockHeader.Name, strBlockName);
		ohBlockHeader = drwFindBlock(m_hDrawing, FIND_BYNAME, &BlockHeader);
		if(ohBlockHeader==0) // Block Not Found
			return FALSE;
		else
			ActiveBlockObjhandle = ohBlockHeader;
	}

	return TRUE;
}

OBJHANDLE CDrawing::GetActiveBlock( )
{
	ISLIBRARYLOADED();
	return ActiveBlockObjhandle;
}

// ENTITIES --------------------------------------------------------
OBJHANDLE CDrawing::AddEntity( OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	ISLIBRARYLOADED();
//	return drwAddEntity(m_hDrawing, BlockObjhandle, pEntityHeader, pEntityData);
	return drwAddEntity_pri(m_hDrawing, BlockObjhandle, pEntityHeader, pEntityData);
}
OBJHANDLE CDrawing::drwAddEntity_pri( HDRAWING hDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	PDRAWING		pDrawing;
	OBJHANDLE		NewEntityObjhandle;

	// Initialize pDrawing ------------------
	if((pDrawing = InitilizePDRAWING(hDrawing))==NULL)
		return 0;

	NewEntityObjhandle = drwAddEntity_Direct(pDrawing, BlockObjhandle, pEntityHeader, pEntityData);
	if(NewEntityObjhandle==0)
	{
		GlobalUnlock(hDrawing);
		return 0;
	}

	// UnInitilize pDrawing -----------------
	UnInitilizePDRAWING(hDrawing);

	return NewEntityObjhandle;
}

OBJHANDLE CDrawing::drwAddEntity_Direct( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	PENTITIES		pEntities;
//	ENTITYHEADER	EntityHeader;
	OBJHANDLE		NewEntityObjhandle;

	if(BlockObjhandle!=NULL)
	{ // Search for block name
		DWORD i = FindBlockPosByHandle( pDrawing, BlockObjhandle );
		if(i<0)
		{
			// The block cannot be found
			return 0;
		}
		else
			pEntities = &pDrawing->Blocks[i].Entities;
	}
	else
		pEntities = &pDrawing->Entities;

	// Initialize EntityHeader
	NewEntityObjhandle = pDrawing->LastObjhandle + 1;
	pEntityHeader->Objhandle = NewEntityObjhandle;
	pEntityHeader->Deleted = FALSE;
//	EntityHeader.EntityType = usEntityType;
//	EntityHeader.LayerObjhandle = pDrawing->Tables.CurrentLayerHandle;
//	EntityHeader.LTypeObjhandle = pDrawing->Tables.CurrentLineTypeHandle;
//	EntityHeader.Color = pDrawing->Tables.CurrentColor;

	// Add Entity to list
	if( !AddEntity(pDrawing, pEntities, pEntityHeader, pEntityData) )
	{
		return 0;
	}

	pDrawing->LastObjhandle++;

	return NewEntityObjhandle;
}
BOOL CDrawing::AddEntity( PDRAWING pDrawing, PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	BOOL result;
	OBJHANDLE		BlockObjhandle1;

	switch( pEntityHeader->EntityType )
	{
	case ENT_LINE:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTLINE));
		break;

	case ENT_POINT:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTPOINT));
		break;

	case ENT_CIRCLE:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTCIRCLE));
		break;

	case ENT_ELLIPSE:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTELLIPSE));
		break;

	case ENT_TEXT:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTTEXT));
		break;

	case ENT_ARC:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTARC));
		break;

	case ENT_SOLID:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTSOLID));
		break;

	case ENT_INSERT:
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTINSERT));
		break;

	case ENT_POLYLINE:
		PENTVERTEX pVertex;
		pVertex = new ENTVERTEX[((PENTPOLYLINE)pEntityData)->nVertex];
		memcpy(pVertex, ((PENTPOLYLINE)pEntityData)->pVertex, sizeof(ENTVERTEX)*((PENTPOLYLINE)pEntityData)->nVertex);
		((PENTPOLYLINE)pEntityData)->pVertex = pVertex;
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTPOLYLINE));
		break;

	case ENT_DIMENSION:
		BlockObjhandle1 = ((PENTDIMENSION)pEntityData)->BlockheaderObjhandle;

		if(BlockObjhandle1==NULL)
		{
			DIMSTYLE		DimStyle;
			BLOCKHEADER		BlockHeader;
			OBJHANDLE		BlockObjhandle;
			char			buf[32];
			// Looking for dim style
			DimStyle.Objhandle = PENTDIMENSION(pEntityData)->DimStyleObjhandle;
			if(drwFindTableType_Direct(pDrawing, TAB_DIMSTYLE, FIND_BYHANDLE, &DimStyle)>0)
			{
				// Create a new Dimension Block
				ZeroMemory(&BlockHeader, sizeof(BLOCKHEADER));
				strcpy(BlockHeader.Name, "*D");
				strcat(BlockHeader.Name, ltoa(++pDrawing->LastDimBlkNum, buf, 10));
				BlockHeader.Flags = 1;
				BlockHeader.BasePoint.x = 0;
				BlockHeader.BasePoint.y = 0;
				BlockHeader.BasePoint.z = 0;
				BlockHeader.LayerObjhandle = pEntityHeader->LayerObjhandle;
				BlockObjhandle = drwAddBlock_Direct(pDrawing, &BlockHeader);

				if(BlockObjhandle!=NULL)
				{
				//	DimLinear( pDrawing, BlockObjhandle, pEntityHeader, PENTDIMENSION(pEntityData), &DimStyle );
					DimLinear_pri( pDrawing, BlockObjhandle, pEntityHeader, PENTDIMENSION(pEntityData), &DimStyle );
					PENTDIMENSION(pEntityData)->BlockheaderObjhandle = BlockObjhandle;
				}
			}

		}
		result = AddToEntitiesList(pEntities, pEntityHeader, pEntityData, sizeof(ENTDIMENSION));
		break;

	default: // Entity is not accepted
		result = FALSE;
	}

	if(!result)
		return FALSE;
	else
		pEntities->EntitiesNumber++;

	return TRUE;
}
BOOL CDrawing::DimLinear_pri( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pDimHeader, PENTDIMENSION pDimension, PDIMSTYLE pDimStyle )
{
	/*
	BOOL			result;
	double			TextWidth;
	double			a, a1, a2, a3;
	double			sina1, cosa1;
	double			sina2, cosa2;
	REALPOINT		A1, A2, A3;
	REALPOINT		B1, B2, B3;
	REALPOINT		C1, C2, C3;
	double			pi = 3.1415926535;

	double			x1 = pDimension->DefPoint3.x;			// x position of start point
	double			y1 = pDimension->DefPoint3.y;			// y position of start point
	double			x2 = pDimension->DefPoint4.x;			// x position of end point
	double			y2 = pDimension->DefPoint4.y;			// y position of end point
	double			x3 = pDimension->DimLineDefPoint.x;		// x position of dimension line
	double			y3 = pDimension->DimLineDefPoint.y;		// y position of dimension line
	double			angle = pDimension->DimRotationAngle;	// dim-line's rotation angle
	LPCTSTR			text = pDimension->DimText;				// dim-line's text (dafault is NULL)

	ENTITYHEADER	EntityHeader;
	ENTPOINT		Point;
	ENTLINE			Line;
	ENTTEXT			Text;

	memcpy(&EntityHeader, pDimHeader, sizeof(ENTITYHEADER));
	// Writting dimension data to the drawing  ---------------------
	result = TRUE;

	a = tan( angle*pi/180 );
	if(a!=0)
	{
		A1.x = (y1 - y3 + x1/a + a*x3) / (a + 1/a);
		A1.y = a * (A1.x - x3) + y3;
		B1.x = (y2 - y3 + x2/a + a*x3) / (a + 1/a);
		B1.y = a * (B1.x - x3) + y3;

		a1 = (A1.y - y1) / (A1.x - x1);
		sina1 = (A1.x>x1 ? 1 : -1) * sin( atan(a1) );
		cosa1 = (A1.x>x1 ? 1 : -1) * cos( atan(a1) );
		A2.x = A1.x + cosa1*pDimStyle->dimexe;
		A2.y = A1.y + sina1*pDimStyle->dimexe;
		A3.x = x1 + cosa1*pDimStyle->dimexo;
		A3.y = y1 + sina1*pDimStyle->dimexo;

		a2 = (B1.y - y2) / (B1.x - x2);
		sina2 = (B1.x>x2 ? 1 : -1) * sin( atan(a2) );
		cosa2 = (B1.x>x2 ? 1 : -1) * cos( atan(a2) );
		B2.x = B1.x + cosa2*pDimStyle->dimexe;
		B2.y = B1.y + sina2*pDimStyle->dimexe;
		B3.x = x2 + cosa2*pDimStyle->dimexo;
		B3.y = y2 + sina2*pDimStyle->dimexo;
	}
	else
	{
		A1.x = x1;
		A1.y = y3;
		B1.x = x2;
		B1.y = y3;

		A2.x = A1.x;
		A2.y = A1.y + _copysign(pDimStyle->dimexe, A1.y-y1);
		A3.x = x1;
		A3.y = y1 + _copysign(pDimStyle->dimexo, A1.y-y1);

		B2.x = B1.x;
		B2.y = B1.y + _copysign(pDimStyle->dimexe, B1.y-y2);
		B3.x = x2;
		B3.y = y2 + _copysign(pDimStyle->dimexo, B1.y-y2);
	}

	C1.x = (A1.x + B1.x) / 2;
	C1.y = (A1.y + B1.y) / 2;

	// Begin & End Points ----
	EntityHeader.EntityType = ENT_POINT;
	Point.Point0.x = x1; Point.Point0.y = y1;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Point);
	Point.Point0.x = x2; Point.Point0.y = y2;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Point);

	// Dimension Line ----
	EntityHeader.Color = pDimStyle->dimclrd;

	switch(pDimStyle->dimtad)
	{
	case 0: // Centered
		// At this time the program cannot calculate the exact width of the text
		TextWidth = (strlen(text) * pDimStyle->dimtxt * 0.3) + pDimStyle->dimgap*2;
		C2.x = C1.x + _copysign( cos(angle*pi/180), A1.x-B1.x)*TextWidth;
		C2.y = C1.y + _copysign( sin(angle*pi/180), A1.x-B1.x)*TextWidth;
		C3.x = C1.x + _copysign( cos(angle*pi/180), B1.x-A1.x)*TextWidth;
		C3.y = C1.y + _copysign( sin(angle*pi/180), B1.x-A1.x)*TextWidth;

		EntityHeader.EntityType = ENT_LINE;
		Line.Point0.x = A1.x; Line.Point0.y = A1.y;
		Line.Point1.x = C2.x; Line.Point1.y = C2.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
		Line.Point0.x = C3.x; Line.Point0.y = C3.y;
		Line.Point1.x = B1.x; Line.Point1.y = B1.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);

		// Text
		EntityHeader.Color = pDimStyle->dimclrt;

		EntityHeader.EntityType = ENT_TEXT;
		Text.Point0.x = C1.x; Text.Point0.y = C1.y;
		Text.TextData.SecondAlignmentPoint.x = C1.x; Text.TextData.SecondAlignmentPoint.y = C1.y;
		Text.TextData.Height = pDimStyle->dimtxt;
		Text.TextData.RotationAngle = angle;
		Text.TextData.Justification = TJ_MIDDLE;
		Text.TextData.WidthFactor = 0;
		Text.TextData.TextStyleObjhandle = pDimStyle->dimtxstyObjhandle;
		strcpy(Text.strText, pDimension->DimText);
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Text);
		break;
	case 1: // Above
		EntityHeader.EntityType = ENT_LINE;
		Line.Point0.x = A1.x; Line.Point0.y = A1.y;
		Line.Point1.x = B1.x; Line.Point1.y = B1.y;
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
		// Text
		EntityHeader.Color = pDimStyle->dimclrt;

		EntityHeader.EntityType = ENT_TEXT;
		Text.Point0.x = C1.x + cos((angle+90)*pi/180)*(pDimStyle->dimgap+pDimStyle->dimtxt/2);
		Text.Point0.y = C1.y + sin((angle+90)*pi/180)*(pDimStyle->dimgap+pDimStyle->dimtxt/2);
		Text.TextData.SecondAlignmentPoint.x = Text.Point0.x;
		Text.TextData.SecondAlignmentPoint.y = Text.Point0.y;
		Text.TextData.Height = pDimStyle->dimtxt;
		Text.TextData.RotationAngle = angle;
		Text.TextData.Justification = TJ_MIDDLE;
		Text.TextData.WidthFactor = 0;
		Text.TextData.TextStyleObjhandle = pDimStyle->dimtxstyObjhandle;
		strcpy(Text.strText, pDimension->DimText);
		drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Text);
		break;
	}

	// Arrow Heads ----
	EntityHeader.Color = pDimStyle->dimclrd;

	a3 = (B1.y - A1.y) / (B1.x - A1.x);

	if(B1.x>A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}
	else if(B1.x<A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}
	else // (B1.x==A1.x)
	{
		// 1st Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, A1.x, A1.y, (B1.y>A1.y?0:1)*pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk1, 1 );
		// 2nd Arrow Head
		result &= dimDrawArrowHead( pDrawing, BlockObjhandle, &EntityHeader, B1.x, B1.y, (B1.y>A1.y?1:0)*pi+atan(a3), pDimStyle->dimasz, pDimStyle->dimblk2, 2 );
	}

	// Extension Lines ----
	EntityHeader.Color = pDimStyle->dimclre;
	// 1st Extension Line
	EntityHeader.EntityType = ENT_LINE;
	Line.Point0.x = A2.x; Line.Point0.y = A2.y;
	Line.Point1.x = A3.x; Line.Point1.y = A3.y;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
	// 2nd Extension Line
	EntityHeader.EntityType = ENT_LINE;
	Line.Point0.x = B2.x; Line.Point0.y = B2.y;
	Line.Point1.x = B3.x; Line.Point1.y = B3.y;
	drwAddEntity_Direct(pDrawing, BlockObjhandle, &EntityHeader, &Line);
	return result;
*/
	return true;
}
BOOL CDrawing::dimDrawArrowHead( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pHeader, double cx, double cy, double Angle, double ArrowSize, LPCTSTR ArrowHeadName, int BLKNum )
{
	ENTLINE		Line;
	ENTSOLID	Solid;

	// Write arrow head data to the Block-refrence

	for(int i=0; i<ArrowHeadsNum; i++)
	{
		if((strcmp(ArrowHeadName, ArrowHeads[i].ArrowHeadName)==0)
			&& (BLKNum==ArrowHeads[i].BLKNum))
		{
			if(strcmp(ArrowHeads[i].Command, "LINE")==0)
			{
				pHeader->EntityType = ENT_LINE;
				Line.Point0.x = cx + ((cos(Angle)*ArrowHeads[i].Param1-sin(Angle)*ArrowHeads[i].Param2)*ArrowSize);
				Line.Point0.y = cy + ((sin(Angle)*ArrowHeads[i].Param1+cos(Angle)*ArrowHeads[i].Param2)*ArrowSize);
				Line.Point1.x = cx + ((cos(Angle)*ArrowHeads[i].Param3-sin(Angle)*ArrowHeads[i].Param4)*ArrowSize);
				Line.Point1.y = cy + ((sin(Angle)*ArrowHeads[i].Param3+cos(Angle)*ArrowHeads[i].Param4)*ArrowSize);
				drwAddEntity_Direct(pDrawing, BlockObjhandle, pHeader, &Line);
			}
			else if(strcmp(ArrowHeads[i].Command, "SOLID")==0)
			{
				pHeader->EntityType = ENT_SOLID;
				Solid.Point0.x = cx + ((cos(Angle)*ArrowHeads[i].Param1-sin(Angle)*ArrowHeads[i].Param2)*ArrowSize);
				Solid.Point0.y = cy + ((sin(Angle)*ArrowHeads[i].Param1+cos(Angle)*ArrowHeads[i].Param2)*ArrowSize);
				Solid.Point1.x = cx + ((cos(Angle)*ArrowHeads[i].Param3-sin(Angle)*ArrowHeads[i].Param4)*ArrowSize);
				Solid.Point1.y = cy + ((sin(Angle)*ArrowHeads[i].Param3+cos(Angle)*ArrowHeads[i].Param4)*ArrowSize);
				Solid.Point2.x = cx + ((cos(Angle)*ArrowHeads[i].Param5-sin(Angle)*ArrowHeads[i].Param6)*ArrowSize);
				Solid.Point2.y = cy + ((sin(Angle)*ArrowHeads[i].Param5+cos(Angle)*ArrowHeads[i].Param6)*ArrowSize);
				Solid.Point3.x = cx + ((cos(Angle)*ArrowHeads[i].Param7-sin(Angle)*ArrowHeads[i].Param8)*ArrowSize);
				Solid.Point3.y = cy + ((sin(Angle)*ArrowHeads[i].Param7+cos(Angle)*ArrowHeads[i].Param8)*ArrowSize);
				drwAddEntity_Direct(pDrawing, BlockObjhandle, pHeader, &Solid);
			}
		}
	}

	return TRUE;
}
BOOL CDrawing::AddToEntitiesList(PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData, WORD EntitySize)
{
	LPVOID		pEntitiesData;

	// Initialize pEntitiesData ----------
	pEntitiesData = GlobalLock(pEntities->hEntities);
	if(pEntitiesData==NULL)
	{
		// GlobalLock error
		return FALSE;
	}

	// Check if we need more memory space for entities data
	if((pEntities->FreePos + sizeof(ENTITYHEADER) + EntitySize) >= pEntities->TotalSize)
	{
		// Unlock hDrawing -------------------
		GlobalUnlock(pEntities->hEntities);
/*		if(!GlobalUnlock(pEntities->hEntities) && (GetLastError()!=NO_ERROR))
		{
			// memory error
			return FALSE;
		}*/
		
		pEntities->hEntities = GlobalReAlloc(
				pEntities->hEntities,
				pEntities->TotalSize + 65536,
				GHND );

		pEntities->TotalSize = GlobalSize( pEntities->hEntities );
		if((pEntities->FreePos + sizeof(ENTITYHEADER) + EntitySize) >= pEntities->TotalSize)
		{
			// Memory limitation error
			return FALSE;
		}

		pEntitiesData = GlobalLock(pEntities->hEntities);
		if(pEntitiesData==NULL)
		{
			// GlobalLock error
			return NULL;
		}
	}
	
	// Init EntityHeader for previous entity position
	pEntityHeader->PreviousEntityPos = pEntities->LastEntityPos;
	pEntityHeader->NextEntityPos = pEntities->FreePos + sizeof(ENTITYHEADER) + EntitySize;

	// Copy entity data to memory
	CopyMemory((LPVOID)((DWORD)pEntitiesData+pEntities->FreePos), pEntityHeader, sizeof(ENTITYHEADER));
	CopyMemory((LPVOID)((DWORD)pEntitiesData+pEntities->FreePos+sizeof(ENTITYHEADER)), (LPVOID)pEntityData, EntitySize);

	// Update pointers
	pEntities->LastEntityPos = pEntities->FreePos;
	pEntities->FreePos += sizeof(ENTITYHEADER) + EntitySize;

	// Unlock hDrawing -------------------
	GlobalUnlock(pEntities->hEntities);
/*	if(!GlobalUnlock(pEntities->hEntities) && (GetLastError()!=NO_ERROR))
	{
		// memory error
		return FALSE;
	}*/

	return TRUE;
}
int CDrawing::FindBlockPosByHandle( PDRAWING pDrawing, OBJHANDLE BlockObjhandle )
{
	for(unsigned int i=0; i<pDrawing->BlocksNumber; i++)
		if(pDrawing->Blocks[i].Objhandle==BlockObjhandle)
			return i;
	
	return -1;
}

BOOL CDrawing::DeleteEntity( LPCTSTR strBlockName, OBJHANDLE EntityObjhandle )
{
	ISLIBRARYLOADED();
	return drwDeleteEntity(m_hDrawing, strBlockName, EntityObjhandle);
}

BOOL CDrawing::ChangeEntity( PENTITYHEADER pEntityHeader, LPVOID pEntityData, LPCTSTR strBlockName )
{
	ISLIBRARYLOADED();
	return drwChangeEntity(m_hDrawing, strBlockName, pEntityHeader, pEntityData);
}

OBJHANDLE CDrawing::FindEntity( DWORD dwFindType, PENTITYHEADER pEntityHeader, LPVOID pEntityData, LPCTSTR strBlockName )
{
	ISLIBRARYLOADED();
	return drwFindEntity(m_hDrawing, strBlockName, pEntityHeader, pEntityData, dwFindType);
}

OBJHANDLE CDrawing::Arc( double cx, double cy, double r, double StartAngle, double EndAngle )
{
	ENTARC arc;
	arc.Point0.x = cx;
	arc.Point0.y = cy;
	arc.Radius = r;
	arc.StartAngle = StartAngle;
	arc.EndAngle = EndAngle;
	m_EntityHeader.EntityType = ENT_ARC;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &arc);
}

OBJHANDLE CDrawing::Circle( double cx, double cy, double r )
{
	ENTCIRCLE circle;
	circle.Point0.x = cx;
	circle.Point0.y = cy;
	circle.Radius = r;
	m_EntityHeader.EntityType = ENT_CIRCLE;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &circle);
}

/*OBJHANDLE CDrawing::Ellipse( double cx, double cy, double ex, double ey, double Ratio, double StartParam, double EndParam )
{
	ENTELLIPSE ellipse;
	ellipse.CenterPoint.x = cx;
	ellipse.CenterPoint.y = cy;
	ellipse.MajorAxisEndPoint.x = ex;
	ellipse.MajorAxisEndPoint.y = ey;
	ellipse.MinorToMajorRatio = Ratio;
	ellipse.StartParam = StartParam;
	ellipse.EndParam = EndParam;
	m_EntityHeader.EntityType = ENT_ELLIPSE;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &ellipse);
}
*/
OBJHANDLE CDrawing::DimLinear( double x1, double y1, double x2, double y2, double x3, double y3,
							  double angle, LPCTSTR text)//2.22 add
{
	ENTDIMENSION dimension;
	ZeroMemory(&dimension, sizeof(ENTDIMENSION));
	dimension.DefPoint3.x = x1;
	dimension.DefPoint3.y = y1;
	dimension.DefPoint4.x = x2;
	dimension.DefPoint4.y = y2;
	dimension.DimLineDefPoint.x = x3;
	dimension.DimLineDefPoint.y = y3;
	dimension.DimRotationAngle = angle;
	strcpy(dimension.DimText, text);
	dimension.DimStyleObjhandle = CurrentDimStyleObjhandle;
	m_EntityHeader.EntityType = ENT_DIMENSION;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &dimension);
}
//2.22 add
OBJHANDLE CDrawing::DimLinear( double x1, double y1, double x2, double y2, double x3, double y3, double angle,
	LPCTSTR text,LPCTSTR dim_kind,double dimline_angle,double angle_dim_x1, double angle_dim_y1)
{
	ENTDIMENSION dimension;
	ZeroMemory(&dimension, sizeof(ENTDIMENSION));
	dimension.DefPoint3.x = x1;
	dimension.DefPoint3.y = y1;
	dimension.DefPoint4.x = x2;
	dimension.DefPoint4.y = y2;
	dimension.DimLineDefPoint.x = x3;
	dimension.DimLineDefPoint.y = y3;
	dimension.DimRotationAngle = angle;
	strcpy(dimension.DimText, text);
	dimension.DimStyleObjhandle = CurrentDimStyleObjhandle;
	m_EntityHeader.EntityType = ENT_DIMENSION;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &dimension);

}

OBJHANDLE CDrawing::InsertBlock( OBJHANDLE BlockObjhandle, double x, double y, double xScale, double yScale, double Rotation )
{
	ENTINSERT insert;
	insert.BlockHeaderObjhandle = BlockObjhandle;
	insert.Point0.x = x;
	insert.Point0.y = y;
	insert.XScale = xScale;
	insert.YScale = yScale;
	insert.RotationAngle = Rotation;
	m_EntityHeader.EntityType = ENT_INSERT;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &insert);
}

OBJHANDLE CDrawing::InsertBlock( LPCTSTR BlockName, double x, double y, double xScale, double yScale, double Rotation )
{
	BLOCKHEADER BlockHeader;
	OBJHANDLE BlockHandle;
	strcpy(BlockHeader.Name, BlockName);
	BlockHandle = drwFindBlock(m_hDrawing, FIND_BYNAME, &BlockHeader);
	if(BlockHandle==0) // Block Not Found
		return 0;
	else
		return InsertBlock( BlockHandle, x, y, xScale, yScale, Rotation );
}


OBJHANDLE CDrawing::Line( double x1, double y1, double x2, double y2 )
{
	ENTLINE line;
	line.Point0.x = x1;
	line.Point0.y = y1;
	line.Point1.x = x2;
	line.Point1.y = y2;
	m_EntityHeader.EntityType = ENT_LINE;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &line);
}

OBJHANDLE CDrawing::Solid( REALPOINT &Point0, REALPOINT &Point1, REALPOINT &Point2, REALPOINT &Point3 )
{
	ENTSOLID solid;
	solid.Point0 = Point0;
	solid.Point1 = Point1;
	solid.Point2 = Point2;
	solid.Point3 = Point3;
	m_EntityHeader.EntityType = ENT_SOLID;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &solid);
}

OBJHANDLE CDrawing::Text(LPCTSTR Text, 
                         double x1, 
                         double y1, 
                         double x2, 
                         double y2, 
                         double Height, 
						             short Justification, 
                         double Rotation, 
                         double WidthFactor )
{
	ENTTEXT text;
	text.Point0.x = x1;
	text.Point0.y = y1;
	strcpy(text.strText, Text);
	text.TextData.Height = Height;
	text.TextData.RotationAngle = Rotation;
	text.TextData.WidthFactor = WidthFactor;
	text.TextData.Justification = Justification;//
	text.TextData.SecondAlignmentPoint.x = x2;
	text.TextData.SecondAlignmentPoint.y = y2;
	text.TextData.TextStyleObjhandle = CurrentStyleObjhandle;
	m_EntityHeader.EntityType = ENT_TEXT;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &text);
}

OBJHANDLE CDrawing::Text(LPCTSTR Text, 
                         double x, 
                         double y, 
                         double Height, 
                         double Rotation, 
                         double WidthFactor )
{
	return this->Text(Text, x, y, x, y, Height, TJ_LEFT, Rotation, WidthFactor);
}

OBJHANDLE CDrawing::PolyLine( PENTVERTEX pVertex, int nVertex, unsigned short Flag )
{
	ENTPOLYLINE polyline;
	polyline.pVertex = pVertex;
	polyline.nVertex = nVertex;
	polyline.Flag = Flag;
	m_EntityHeader.EntityType = ENT_POLYLINE;
	return AddEntity(ActiveBlockObjhandle, &m_EntityHeader, &polyline);
}
// Datafile data-exchange ------------------------------------------
BOOL CDrawing::SaveDXFFile( LPCTSTR FileName, HWND hWndProgress )
{
	ISLIBRARYLOADED();
//	return drwSaveDataToFile(m_hDrawing, 0, FileName, hWndProgress);
	return drwSaveDataToFile_pri(m_hDrawing, 0, FileName, hWndProgress);
}
BOOL CDrawing::drwSaveDataToFile_pri( HDRAWING hDrawing, DWORD Reserved, LPCTSTR strFileName, HWND hWndProgress )
{
	long	CurrentEntityNum;
	long	TotalEntitiesNum;
	int		ProgPercent;
	HWND	hProgWnd;

	PDRAWING	pDrawing;
	HDXF		hDxf;

	// Initialize pDrawing ------------------
	if((pDrawing = InitilizePDRAWING(hDrawing))==NULL)
		return FALSE;

	if(strFileName==NULL)
	{
		// Filename can not be NULL
		GlobalUnlock(hDrawing);
		return FALSE;
	}

	// Set Progress Percent to 0
	hProgWnd = hWndProgress;
	ProgPercent = 0;
	SendMessage(hWndProgress, WM_PROGRESS, ProgPercent, 0);
	// Count Total Entities Number
	TotalEntitiesNum = pDrawing->Entities.EntitiesNumber;
	for(UINT i=0; i<pDrawing->BlocksNumber; i++)
		TotalEntitiesNum += pDrawing->Blocks[i].Entities.EntitiesNumber;
	CurrentEntityNum = 0;

	// Creating DXF file and writing data in it
	hDxf = dxfCreateFile(strFileName);

	// Header Section ------------------------------------------
	dxfSectionBegin(hDxf, SEC_HEADER);
	dxfSectionEnd(hDxf);

	// Tables Section ------------------------------------------
	dxfSectionBegin(hDxf, SEC_TABLES);

	//  LTYPE table type -------------------------
	dxfTableTypeBegin(hDxf, TAB_LTYPE);

	DXFLTYPE	ltype;
	for(i=0; i<pDrawing->Tables.NumLTypes; i++)
	{
		strcpy(ltype.Name, pDrawing->Tables.LType[i].Name);
		ltype.StandardFlags = pDrawing->Tables.LType[i].StandardFlags;
		strcpy(ltype.DescriptiveText, pDrawing->Tables.LType[i].DescriptiveText);
		ltype.ElementsNumber = pDrawing->Tables.LType[i].ElementsNumber;
		CopyMemory(ltype.Elements, pDrawing->Tables.LType[i].Elements, sizeof(double)*30);
		ltype.TotalPatternLength = pDrawing->Tables.LType[i].PatternLength;

		dxfAddLinetype(hDxf, &ltype);
	}

	dxfTableTypeEnd(hDxf);

	//  LAYER table type -------------------------
	dxfTableTypeBegin(hDxf, TAB_LAYER);

	for(i=0; i<pDrawing->Tables.NumLayers; i++)
	{
		LTYPE	LType;
		char*	pLTypeName;

		LType.Objhandle = pDrawing->Tables.Layer[i].LineTypeObjhandle;
		if(drwFindTableType(hDrawing, TAB_LTYPE, FIND_BYHANDLE, &LType)>0)
			pLTypeName = LType.Name;
		else
			pLTypeName = NULL;

		dxfAddLayer_pri(hDxf,
			pDrawing->Tables.Layer[i].Name,
			pDrawing->Tables.Layer[i].Color,
			pLTypeName, pDrawing->Tables.Layer[i].StandardFlags
		);
	}
	
	dxfTableTypeEnd(hDxf);

	//  STYLE table type -------------------------
	dxfTableTypeBegin( hDxf, TAB_STYLE );

	DXFSTYLE tstyle;
	for(i=0; i<pDrawing->Tables.NumStyles; i++)
	{
		strcpy(tstyle.Name, pDrawing->Tables.Style[i].Name);
		strcpy(tstyle.PrimaryFontFilename, pDrawing->Tables.Style[i].PrimaryFontFilename);
		tstyle.StandardFlags = pDrawing->Tables.Style[i].StandardFlags;
		tstyle.TextGenerationFlags = pDrawing->Tables.Style[i].TextGenerationFlags;
		tstyle.FixedTextHeight = pDrawing->Tables.Style[i].FixedTextHeight;
		tstyle.WidthFactor = pDrawing->Tables.Style[i].WidthFactor;
		tstyle.Height = pDrawing->Tables.Style[i].LastHeightUsed;
		tstyle.ObliqueAngle = pDrawing->Tables.Style[i].ObliqueAngle;

		dxfAddTextStyle(hDxf, &tstyle);
	}

	dxfTableTypeEnd(hDxf);

	//  DIMSTYLE table type ----------------------
	dxfTableTypeBegin(hDxf, TAB_DIMSTYLE);
	
	DXFDIMSTYLE	dimstyle;
	for(i=0; i<pDrawing->Tables.NumDimStyles; i++)
	{
		STYLE	Style;
		char*	pStyleName;

		Style.Objhandle = pDrawing->Tables.DimStyle[i].dimtxstyObjhandle;
		if(drwFindTableType(hDrawing, TAB_STYLE, FIND_BYHANDLE, &Style)>0)
			pStyleName = Style.Name;
		else
			pStyleName = NULL;

		strcpy(dimstyle.Name, pDrawing->Tables.DimStyle[i].Name);
		dimstyle.StandardFlags = pDrawing->Tables.DimStyle[i].StandardFlags;
		dimstyle.DIMCLRD = pDrawing->Tables.DimStyle[i].dimclrd;
		dimstyle.DIMDLE = pDrawing->Tables.DimStyle[i].dimdle;
		dimstyle.DIMCLRE = pDrawing->Tables.DimStyle[i].dimclre;
		dimstyle.DIMEXE = pDrawing->Tables.DimStyle[i].dimexe;
		dimstyle.DIMEXO = pDrawing->Tables.DimStyle[i].dimexo;
		strcpy(dimstyle.DIMBLK1, pDrawing->Tables.DimStyle[i].dimblk1);
		strcpy(dimstyle.DIMBLK2, pDrawing->Tables.DimStyle[i].dimblk2);
		dimstyle.DIMASZ = pDrawing->Tables.DimStyle[i].dimasz;
		strcpy(dimstyle.DIMTXSTY, pStyleName);
		dimstyle.DIMCLRT = pDrawing->Tables.DimStyle[i].dimclrt;
		dimstyle.DIMTXT = pDrawing->Tables.DimStyle[i].dimtxt;
		dimstyle.DIMTAD = pDrawing->Tables.DimStyle[i].dimtad;
		dimstyle.DIMGAP = pDrawing->Tables.DimStyle[i].dimgap;

	//	dxfAddDimStyle(hDxf, &dimstyle);
		dxfAddDimStyle_pri(hDxf, &dimstyle);
	}

	dxfTableTypeEnd(hDxf);

	dxfSectionEnd(hDxf);

	// Blocks Section ------------------------------------------
	dxfSectionBegin(hDxf, SEC_BLOCKS);

	BLOCKHEADER		BlockHeader;
	ENTITYHEADER	EntityHeader;
	char			EntityData[4096];

	if(drwFindBlock(hDrawing, FIND_FIRST, &BlockHeader)>0)
	{
		do{
			LAYER	Layer;
			LPCTSTR	pLayerName;
			DWORD	CurrentBlockNum;

			Layer.Objhandle = BlockHeader.LayerObjhandle;
			if(drwFindTableType(hDrawing, TAB_LAYER, FIND_BYHANDLE, &Layer)>0)
				pLayerName = Layer.Name;
			else
				pLayerName = NULL;
			dxfBlockBegin(hDxf, BlockHeader.Name, pLayerName, BlockHeader.BasePoint.x, BlockHeader.BasePoint.y, BlockHeader.Flags);

			CurrentBlockNum = pDrawing->CurrentBlock;
			if(drwFindEntity(hDrawing, BlockHeader.Name, &EntityHeader, &EntityData, FIND_FIRST)>0)
			{
				do{
					if(!EntityHeader.Deleted)
						WriteEntityDataToFile(hDrawing, hDxf, &EntityHeader, &EntityData);
				} while(drwFindEntity_Direct(pDrawing, BlockHeader.Name, &EntityHeader, &EntityData, FIND_NEXT)>0);
			}
			pDrawing->CurrentBlock = CurrentBlockNum;

			dxfBlockEnd(hDxf);
		} while(drwFindBlock(hDrawing, FIND_NEXT, &BlockHeader)>0);
	}
	//开始添加写块表内容
	dxfSectionEnd(hDxf);

	// Entities Section ----------------------------------------
	dxfSectionBegin(hDxf, SEC_ENTITIES);

	if(drwFindEntity(hDrawing, NULL, &EntityHeader, &EntityData, FIND_FIRST)>0)
	{
		do{
			if(!EntityHeader.Deleted)
				WriteEntityDataToFile(hDrawing, hDxf, &EntityHeader, &EntityData);
//			NotifySaveProgress();
		} while(drwFindEntity( hDrawing, NULL, &EntityHeader, &EntityData, FIND_NEXT )>0);
	}
	//在这里写标注项目


	dxfSectionEnd(hDxf);

	// Set Progress Percent to 100
	ProgPercent = 100;
	SendMessage(hWndProgress, WM_PROGRESS, ProgPercent, 0);

	// Close dxf file
	dxfCloseFile(hDxf);
	// UnInitilize pDrawing -----------------
	return UnInitilizePDRAWING(hDrawing);
}
BOOL CDrawing::dxfAddLayer_pri( HDXF hDxf, char* Name, int Color, char* Linetype,char standflay)
{
	PDXF	pDxf;
	BOOL	result;

	// Initialize pDxf ------------------
	if((pDxf = InitilizePDXF(hDxf))==NULL)
		return FALSE;

	// Check if current section is TABLES
	if(pDxf->Write.CurrentSection!=SEC_TABLES)
	{
		// Current section is not TABLES
		GlobalUnlock(hDxf);
		return FALSE;
	}

	// Check if current type is LAYER
	if(pDxf->Write.CurrentTableType!=TAB_LAYER)
	{
		// Current table type is not LAYER
		GlobalUnlock(hDxf);
		return FALSE;
	}

	// Write data to output file
	result = TRUE;
	result &= dxfWriteParamString(hDxf, 0, "LAYER"); // Entity type
	result &= dxfWriteParamString(hDxf, 2, Name);	 // Layer Name
	result &= dxfWriteParamInteger(hDxf, 70, standflay);	 // Standard flags
	result &= dxfWriteParamInteger(hDxf, 62, Color); // Layer Color
	result &= dxfWriteParamString(hDxf, 6, Linetype);// Linetype
	if(!result)
	{
		GlobalUnlock(hDxf);
		return FALSE;
	}
	
	// UnInitilize hDxf -----------------
	return UnInitilizePDXF(hDxf);
}


BOOL CDrawing::dxf_add_block_table(HDXF hDxf)
{
	BOOL	result = TRUE;
	result &= dxfWriteParamString(hDxf, 0, "BLOCK");						// DimStyle Name
	result &= dxfWriteParamString(hDxf, 8, "(null)");
	result &= dxfWriteParamString(hDxf, 2, block_name);	
	result &= dxfWriteParamString(hDxf, 70, "1");	
	result &= dxfWriteParamString(hDxf, 10, "0.0");	
	result &= dxfWriteParamString(hDxf, 20, "0.0");	
	result &= dxfWriteParamString(hDxf, 3, block_name);	
	result &= dxfWriteParamString(hDxf, 0, "ENDBLK");	

	return result;
}

BOOL CDrawing::dxfAddDimStyle_pri( HDXF hDxf, PDXFDIMSTYLE pDimStyle )
{
	PDXF		pDxf;
	DWORD		CurrentSize;
	DWORD		NeededSize;

	if(pDimStyle==NULL)
	{
		// pDimStyle shall not be NULL
		return FALSE;
	}

	// Initialize pDxf ------------------
	if((pDxf = InitilizePDXF(hDxf))==NULL)
		return FALSE;

	// Check if current section is TABLES
	if(pDxf->Write.CurrentSection!=SEC_TABLES)
	{
		// Current section is not TABLES
		GlobalUnlock(hDxf);
		return FALSE;
	}

	// Check if current type is DIMSTYLE
	if(pDxf->Write.CurrentTableType!=TAB_DIMSTYLE)
	{
		// Current table type is not DIMSTYLE
		GlobalUnlock(hDxf);
		return FALSE;
	}

	// Save data to momery for further use
	CurrentSize = GlobalSize(hDxf);
	NeededSize = pDxf->Size + sizeof(DXFDIMSTYLE);
	if(NeededSize>CurrentSize)
	{
		GlobalUnlock(hDxf);
		GlobalReAlloc(hDxf, CurrentSize+65535, GHND);
		pDxf = (PDXF)GlobalLock(hDxf);
		CurrentSize = GlobalSize(hDxf);
		if(NeededSize>CurrentSize)
		{
			// Low memory error
			GlobalUnlock(hDxf);
			return FALSE;
		}
	}

	CopyMemory((LPVOID)((DWORD)pDxf+pDxf->Size), pDimStyle, sizeof(DXFDIMSTYLE));

	pDxf->Size += sizeof(DXFDIMSTYLE);
	pDxf->Write.DimStylesNumber++;

	// Write data to output file
//	if(!WriteDimStyleData(pDxf, pDimStyle))
	if(!WriteDimStyleData_pri(hDxf, pDimStyle))
	{
		// Writing DimStyle data error
		GlobalUnlock(hDxf);
		return FALSE;
	}

	// UnInitilize hDxf -----------------
	return UnInitilizePDXF(hDxf);
}
BOOL CDrawing::WriteDimStyleData_pri( HDXF hDxf, PDXFDIMSTYLE pDimStyle )
{
	BOOL	result = TRUE;

	if(strcmp(pDimStyle->Name,g_baseling_dimstyle)==0){
		add_dxf_base_line(pDimStyle->Name,hDxf);
	}else{
		result &= dxfWriteParamString(hDxf, 0, "DIMSTYLE");						// DimStyle Name
		result &= dxfWriteParamString(hDxf, 2, pDimStyle->Name);				// Standard flag values
	//	result &= dxfWriteParamString(hDxf, 5, "A");				// Standard flag values
		//*****************************
		//缺少的键码
		result &= dxfWriteParamString(hDxf, 3, "");//mm 单位
		result &= dxfWriteParamString(hDxf, 4, "2");//指定用于所有标注类型（角度标注除外）的换算标注测量值的文字前缀或后缀
		result &= dxfWriteParamString(hDxf, 5, "9A");//箭头样式
		result &= dxfWriteParamString(hDxf, 6, "9A");
		result &= dxfWriteParamString(hDxf, 7, "9A");
		result &= dxfWriteParamString(hDxf, 40, "1");//线形比例
		result &= dxfWriteParamString(hDxf, 44, "1.25");//指定尺寸线超出尺寸界线的距离
		result &= dxfWriteParamString(hDxf, 45, "1.0");//将所有标注距离舍入到指定值
		result &= dxfWriteParamString(hDxf, 46, "1");//当使用小斜线代替箭头进行标注时，设置尺寸线超出尺寸界线的距离
		result &= dxfWriteParamString(hDxf, 47, "2");//设置标注文字的最大（上）公差极限（当DIMTOL 或 DIMLIM 设置为开时）
		result &= dxfWriteParamString(hDxf, 48, "2");//设置标注文字的最小（下）公差极限（当 DIMTOL 或 DIMLIM 设置为开时）
		result &= dxfWriteParamString(hDxf, 142, "1");//>0绘制小斜线替代箭头
		result &= dxfWriteParamString(hDxf, 144, "1");//设置线性标注测量值的比例因子
		result &= dxfWriteParamString(hDxf, 145, "1");//控制标注文字在尺寸线上方或下方的垂直位置
		result &= dxfWriteParamString(hDxf, 146, "1");//与通过 DIMTXT 系统变量设置一样，指定分数和公差值的文字高度相对于标注文字高度的比例因子
		result &= dxfWriteParamString(hDxf, 71, "0");//将公差附在标注文字之后。 将 DIMTOL 设置为开将会关闭 DIMLIM
		result &= dxfWriteParamString(hDxf, 72, "0");//生成标注界限作为默认文字。 将 DIMLIM 设置为"开"将会关闭 

		result &= dxfWriteParamString(hDxf, 75, "0");//DIMSE1控制是否禁止显示第一条尺寸界线
		result &= dxfWriteParamString(hDxf, 76, "0");
		
		result &= dxfWriteParamString(hDxf, 170, "0");//DIMALT控制标注中的换算单位的显示
		result &= dxfWriteParamString(hDxf, 173, "0");//控制尺寸线箭头块的显示
		result &= dxfWriteParamString(hDxf, 174, "1");//在尺寸界线之间绘制文字
		result &= dxfWriteParamString(hDxf, 175, "0");//收缩绘制到尺寸界线之外的尺寸线，关不压缩尺寸线
		result &= dxfWriteParamString(hDxf, 176, "0");//DIMCLRD为尺寸线、箭头和标注引线指定颜色
		result &= dxfWriteParamString(hDxf, 177, "0");//DIMCLRE为尺寸界线指定颜色
		result &= dxfWriteParamString(hDxf, 178, "0");//文字颜色
		//********************************
		result &= dxfWriteParamInteger(hDxf, 70, 0);	
		result &= dxfWriteParamDouble(hDxf, 41, 2.5);				// pDimStyle->DIMASZ Arrow size
		result &= dxfWriteParamDouble(hDxf, 42, 0.625);				//pDimStyle->DIMEXO Offset from origin
		result &= dxfWriteParamDouble(hDxf, 43, 3.75);				// Offset from origin
		result &= dxfWriteParamInteger(hDxf, 73, 0);	
		result &= dxfWriteParamInteger(hDxf, 74, 0);	
		result &= dxfWriteParamInteger(hDxf, 77, 1);			// pDimStyle->DIMTAD Vertical Text Placement
		result &= dxfWriteParamInteger(hDxf, 78, 8);	
		result &= dxfWriteParamDouble(hDxf, 140, pDimStyle->DIMTXT);			//pDimStyle->DIMTXT Text height
		result &= dxfWriteParamDouble(hDxf, 141, 2.5);		
		result &= dxfWriteParamDouble(hDxf, 143, 0.03937007874016);		
		result &= dxfWriteParamDouble(hDxf, 147, 0.625);			//pDimStyle->DIMGAP Offset from dimension line
		result &= dxfWriteParamInteger(hDxf, 171, 3);		
		result &= dxfWriteParamInteger(hDxf, 172, 1);	
		result &= dxfWriteParamInteger(hDxf, 271, 2);	
		result &= dxfWriteParamInteger(hDxf, 272, 2);	
		result &= dxfWriteParamInteger(hDxf, 274, 3);	
	//	result &= dxfWriteParamInteger(hDxf, 278, 44);	
		result &= dxfWriteParamInteger(hDxf, 283, 0);	
		result &= dxfWriteParamInteger(hDxf, 284, 8);	
		result &= dxfWriteParamInteger(hDxf, 340, 11);//pDimStyle->DIMTXSTYObjhandle Text style Object Handle
	//	result &= dxfWriteParamInteger(hDxf, 342, 87);	
		
	}

	return result;
}
BOOL CDrawing::add_dxf_base_line(LPCTSTR dim_style_name,HDXF hDxf)
{
	BOOL result = false;
	result &= dxfWriteParamString(hDxf, 0, "DIMSTYLE");						// DimStyle Name
	result &= dxfWriteParamString(hDxf, 2, dim_style_name);				// Standard flag values
//	result &= dxfWriteParamString(hDxf, 5, "A");				// Standard flag values
	//*****************************
	//缺少的键码
	result &= dxfWriteParamString(hDxf, 3, "");//mm 单位
	result &= dxfWriteParamString(hDxf, 4, "2");//指定用于所有标注类型（角度标注除外）的换算标注测量值的文字前缀或后缀
	result &= dxfWriteParamString(hDxf, 5, "9A");//箭头样式
	result &= dxfWriteParamString(hDxf, 6, "9A");
	result &= dxfWriteParamString(hDxf, 7, "9A");
	result &= dxfWriteParamString(hDxf, 40, "1");//线形比例
	result &= dxfWriteParamString(hDxf, 44, "1.25");//指定尺寸线超出尺寸界线的距离
	result &= dxfWriteParamString(hDxf, 45, "1.0");//将所有标注距离舍入到指定值
	result &= dxfWriteParamString(hDxf, 46, "1");//当使用小斜线代替箭头进行标注时，设置尺寸线超出尺寸界线的距离
	result &= dxfWriteParamString(hDxf, 47, "2");//设置标注文字的最大（上）公差极限（当DIMTOL 或 DIMLIM 设置为开时）
	result &= dxfWriteParamString(hDxf, 48, "2");//设置标注文字的最小（下）公差极限（当 DIMTOL 或 DIMLIM 设置为开时）
	result &= dxfWriteParamString(hDxf, 142, "1");//>0绘制小斜线替代箭头
	result &= dxfWriteParamString(hDxf, 144, "1");//设置线性标注测量值的比例因子
	result &= dxfWriteParamString(hDxf, 145, "1");//控制标注文字在尺寸线上方或下方的垂直位置
	result &= dxfWriteParamString(hDxf, 146, "1");//与通过 DIMTXT 系统变量设置一样，指定分数和公差值的文字高度相对于标注文字高度的比例因子
	result &= dxfWriteParamString(hDxf, 71, "0");//将公差附在标注文字之后。 将 DIMTOL 设置为开将会关闭 DIMLIM
	result &= dxfWriteParamString(hDxf, 72, "1");//生成标注界限作为默认文字。 将 DIMLIM 设置为"开"将会关闭 

	result &= dxfWriteParamString(hDxf, 75, "1");//DIMSE1控制是否禁止显示第一条尺寸界线
	result &= dxfWriteParamString(hDxf, 76, "0");
	
	result &= dxfWriteParamString(hDxf, 170, "0");//DIMALT控制标注中的换算单位的显示
	result &= dxfWriteParamString(hDxf, 173, "0");//控制尺寸线箭头块的显示
	result &= dxfWriteParamString(hDxf, 174, "1");//在尺寸界线之间绘制文字
	result &= dxfWriteParamString(hDxf, 175, "0");//收缩绘制到尺寸界线之外的尺寸线，关不压缩尺寸线
	result &= dxfWriteParamString(hDxf, 176, "222");//DIMCLRD为尺寸线、箭头和标注引线指定颜色
	result &= dxfWriteParamString(hDxf, 177, "1");//DIMCLRE为尺寸界线指定颜色
	result &= dxfWriteParamString(hDxf, 178, "1");
	//********************************
	result &= dxfWriteParamInteger(hDxf, 70, 0);	
	result &= dxfWriteParamDouble(hDxf, 41, 2.5);				// pDimStyle->DIMASZ Arrow size
	result &= dxfWriteParamDouble(hDxf, 42, 0.625);				//pDimStyle->DIMEXO Offset from origin
	result &= dxfWriteParamDouble(hDxf, 43, 3.75);				// Offset from origin
	result &= dxfWriteParamInteger(hDxf, 73, 0);	
	result &= dxfWriteParamInteger(hDxf, 74, 0);	
	result &= dxfWriteParamInteger(hDxf, 77, 1);			// pDimStyle->DIMTAD Vertical Text Placement
	result &= dxfWriteParamInteger(hDxf, 78, 8);	
	result &= dxfWriteParamDouble(hDxf, 140, 2.5);			//pDimStyle->DIMTXT Text height
	result &= dxfWriteParamDouble(hDxf, 141, 2.5);		
	result &= dxfWriteParamDouble(hDxf, 143, 0.03937007874016);		
	result &= dxfWriteParamDouble(hDxf, 147, 0.625);			//pDimStyle->DIMGAP Offset from dimension line
	result &= dxfWriteParamInteger(hDxf, 171, 3);		
	result &= dxfWriteParamInteger(hDxf, 172, 2);	////？改
	result &= dxfWriteParamInteger(hDxf, 271, 2);	
	result &= dxfWriteParamInteger(hDxf, 272, 2);	
	result &= dxfWriteParamInteger(hDxf, 274, 3);	
//	result &= dxfWriteParamInteger(hDxf, 278, 44);	
	result &= dxfWriteParamInteger(hDxf, 281, 1);	//DIMSD1控制是否禁止显示第一条尺寸线
	result &= dxfWriteParamInteger(hDxf, 282, 0);	//设置为开，将禁止显示第一条尺寸界线与文字之间的尺寸线和箭头
	
	result &= dxfWriteParamInteger(hDxf, 283, 0);	
	result &= dxfWriteParamInteger(hDxf, 284, 8);	
	result &= dxfWriteParamInteger(hDxf, 340, 11);//pDimStyle->DIMTXSTYObjhandle Text style Object Handle
//	result &= dxfWriteParamInteger(hDxf, 342, 87);	
	return result;
}
void CDrawing::WriteEntityDataToFile( HDRAWING hDrawing, HDXF hDxf, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	LAYER		Layer;
	LTYPE		LType;
	STYLE		Style;
	char*		pLayerName;
	char*		pLTypeName;
	char*		pStyleName;
	
	// Initialize LayerName & LineTypeName & Color
	Layer.Objhandle = pEntityHeader->LayerObjhandle;
	if(drwFindTableType(hDrawing, TAB_LAYER, FIND_BYHANDLE, &Layer)>0)
		pLayerName = Layer.Name;
	else
		pLayerName = NULL;

	LType.Objhandle = pEntityHeader->LTypeObjhandle;
	if(drwFindTableType(hDrawing, TAB_LTYPE, FIND_BYHANDLE, &LType)>0)
		pLTypeName = LType.Name;
	else
		pLTypeName = NULL;

	dxfSetCurrentLayer(hDxf, pLayerName, pLTypeName);
	dxfSetCurrentColor(hDxf, pEntityHeader->Color);

	// Write entities data to file
	switch(pEntityHeader->EntityType)
	{
	case ENT_LINE:
		dxfLine(
			hDxf, 
			((PENTLINE)pEntityData)->Point0.x,
			((PENTLINE)pEntityData)->Point0.y,
			((PENTLINE)pEntityData)->Point1.x,
			((PENTLINE)pEntityData)->Point1.y
		);
		break;

	case ENT_POINT:
		dxfPoint( 
			hDxf,
			((PENTPOINT)pEntityData)->Point0.x,
			((PENTPOINT)pEntityData)->Point0.y,
			pEntityHeader->Thickness
		);
		break;

	case ENT_CIRCLE:
		dxfCircle(
			hDxf,
			((PENTCIRCLE)pEntityData)->Point0.x,
			((PENTCIRCLE)pEntityData)->Point0.y,
			((PENTCIRCLE)pEntityData)->Radius
		);
		break;

/*	case ENT_ELLIPSE:
		dxfEllipse(
			hDxf, 
			((PENTELLIPSE)pEntityData)->CenterPoint.x,
			((PENTELLIPSE)pEntityData)->CenterPoint.y,
			((PENTELLIPSE)pEntityData)->MajorAxisEndPoint.x,
			((PENTELLIPSE)pEntityData)->MajorAxisEndPoint.y,
			((PENTELLIPSE)pEntityData)->MinorToMajorRatio,
			((PENTELLIPSE)pEntityData)->StartParam,
			((PENTELLIPSE)pEntityData)->EndParam
		);
		break;
*/
	case ENT_TEXT:
		// Find textstyle name
		Style.Objhandle = ((PENTTEXT)pEntityData)->TextData.TextStyleObjhandle;
		if(drwFindTableType(hDrawing, TAB_STYLE, FIND_BYHANDLE, &Style)>0)
			pStyleName = Style.Name;
		else
			pStyleName = NULL;

		dxfText( 
			hDxf,
			((PENTTEXT)pEntityData)->strText,
			((PENTTEXT)pEntityData)->Point0.x,
			((PENTTEXT)pEntityData)->Point0.y,
			((PENTTEXT)pEntityData)->TextData.SecondAlignmentPoint.x,
			((PENTTEXT)pEntityData)->TextData.SecondAlignmentPoint.y,
			((PENTTEXT)pEntityData)->TextData.Height,
			((PENTTEXT)pEntityData)->TextData.RotationAngle,
			((PENTTEXT)pEntityData)->TextData.Justification,
			((PENTTEXT)pEntityData)->TextData.WidthFactor,
			pStyleName
		);
		break;

	case ENT_ARC:
		dxfArc(
			hDxf,
			((PENTARC)pEntityData)->Point0.x,
			((PENTARC)pEntityData)->Point0.y,
			((PENTARC)pEntityData)->Radius,
			((PENTARC)pEntityData)->StartAngle,
			((PENTARC)pEntityData)->EndAngle,
			pEntityHeader->Thickness
		);
		break;

	case ENT_SOLID:
		dxfSolid( 
			hDxf,
			((PENTSOLID)pEntityData)->Point0,
			((PENTSOLID)pEntityData)->Point1,
			((PENTSOLID)pEntityData)->Point2,
			((PENTSOLID)pEntityData)->Point3
		);
		break;

	case ENT_INSERT:
		BLOCKHEADER	BlockHeader;
		BlockHeader.Objhandle = ((PENTINSERT)pEntityData)->BlockHeaderObjhandle;
		if(drwFindBlock(hDrawing, FIND_BYHANDLE, &BlockHeader)>0)
			dxfInsertBlock(
				hDxf,
				BlockHeader.Name,
				((PENTINSERT)pEntityData)->Point0.x,
				((PENTINSERT)pEntityData)->Point0.y,
				((PENTINSERT)pEntityData)->XScale,
				((PENTINSERT)pEntityData)->YScale,
				((PENTINSERT)pEntityData)->RotationAngle
			);
		break;

	case ENT_POLYLINE:
		dxfPolyLine(
			hDxf, 
			(PDXFENTVERTEX)((PENTPOLYLINE)pEntityData)->pVertex,
			((PENTPOLYLINE)pEntityData)->nVertex,
			((PENTPOLYLINE)pEntityData)->Flag
		);
		break;

	case ENT_DIMENSION:
/*
		pStyleName = NULL;
		pDimStyleName = NULL;
		// Find dimstyle name
		DimStyle.Objhandle = ((PENTDIMENSION)pEntityData)->DimStyleObjhandle;
		if(drwFindTableType(hDrawing, TAB_DIMSTYLE, FIND_BYHANDLE, &DimStyle)<=0)
			drwFindTableType(hDrawing, TAB_DIMSTYLE, FIND_FIRST, &DimStyle);
		if(DimStyle.dimtxstyObjhandle>0)
		{
			pDimStyleName = DimStyle.Name;
			// Find textstyle name of dimension
			Style.Objhandle = DimStyle.dimtxstyObjhandle;
			if(drwFindTableType(hDrawing, TAB_STYLE, FIND_BYHANDLE, &Style)>0)
				pStyleName = Style.Name;
		}

		dxfSetCurrentDimStyle(hDxf, pDimStyleName);
		dxfSetCurrentTextStyle(hDxf, pStyleName);

		dxfDimLinear(
			hDxf,
			((PENTDIMENSION)pEntityData)->DefPoint3.x,
			((PENTDIMENSION)pEntityData)->DefPoint3.y,
			((PENTDIMENSION)pEntityData)->DefPoint4.x,
			((PENTDIMENSION)pEntityData)->DefPoint4.y,
			((PENTDIMENSION)pEntityData)->DimLineDefPoint.x,
			((PENTDIMENSION)pEntityData)->DimLineDefPoint.y,
			((PENTDIMENSION)pEntityData)->DimRotationAngle,
			((PENTDIMENSION)pEntityData)->DimText
		);
*/
		break;
	}
}


BOOL CDrawing::LoadDXFFile( LPCTSTR FileName, HWND hWndProgress )
{
	ISLIBRARYLOADED();
	return drwLoadDataFromFile(m_hDrawing, NULL, 0, FileName, hWndProgress);
}
//09.2.5
BOOL CDrawing::LoadDXFFile( LPCTSTR FileName,dlhml::Database& database)
{
	ISLIBRARYLOADED();
	return drwLoadDataFromFile_db(m_hDrawing, NULL, 0, FileName, database);	
}

/*

BOOL CDrawing::deal_ents(PDRAWING pDrawing,HDRAWING hDrawing,PENTITYHEADER pEntityHeader, LPVOID pEntityData,dlhml::Database & database)
{
	BOOL	result=TRUE;
	Z_EntProperties entProp;
	//层
	LAYER layer;//
	get_layer(hDrawing,pEntityHeader,layer);
	strcpy(entProp.ch_layer,layer.Name);
//	pEntityHeader->
	//线形
	LTYPE ltype;//
	get_ltype(hDrawing,pEntityHeader,ltype);
	GetLtype(ltype.Name,entProp.ch_ltype);
	//颜色
	int iIndexColor = 0;
	iIndexColor = get_color(hDrawing,pEntityHeader,pEntityHeader->Color);
	entProp.color = GetColor(iIndexColor);


	//得到标注样式
	DIMSTYLE dim_style;
	get_dimstyle(pDrawing,hDrawing,pEntityHeader,pEntityData,dim_style);

	Ents_Dxf_In dxf_in;
	dxf_in.set_database(&database);
	dxf_in.set_hdrawing(hDrawing);
//	dxf_in.deal_ents(entProp,pEntityHeader,pEntityData);
	return result;
}*/



PDRAWING CDrawing::converse_hd_to_pd(HDRAWING hDrawing)
{
	PDRAWING pDrawing;

	if( hDrawing == NULL )
	{
		// hDrawing shall not be null
		return NULL;
	}

	pDrawing = (PDRAWING)GlobalLock(hDrawing);
	if(pDrawing==NULL)
	{
		// GlobalLock error
		return NULL;
	}

	return pDrawing;
}

//</Add>
//</Author>
//<Author>:zhong
//<Add>=Date:2007/11/19
BOOL CDrawing::save_dxf(LPCTSTR strFilePathName,dlhml::Database& database)
{
	ISLIBRARYLOADED();
	return save_dxf_ents(m_hDrawing,strFilePathName,database);

}

//</Add>
//</Author>



//把memdrw.cpp中的函数移动到此
OBJHANDLE CDrawing::drwFindEntity_Direct( PDRAWING pDrawing, LPCTSTR strBlockName, PENTITYHEADER pEntityHeader, LPVOID pEntityData, DWORD dwFindType, DWORD* pdwEntityPos )
{
	PENTITIES		pEntities;
	OBJHANDLE		result;

	if(pEntityHeader==NULL)
	{
		// pEntityHeader can not be NULL
		return 0;
	}

	if(pEntityData==NULL)
	{
		// pEntityData can not be NULL
		return 0;
	}

	if(strBlockName!=NULL)
	{ // Search for block name
		DWORD i = FindBlockPosByName( pDrawing, strBlockName );
		if(i<0)
		{
			// The block cannot be found
			return 0;
		}
		else
			pEntities = &pDrawing->Blocks[i].Entities;
	}
	else
		pEntities = &pDrawing->Entities;

	// Check number of entities
	if(pEntities->EntitiesNumber<1)
	{
		// There is no entity to find
		return 0;
	}

	result = 0;

	if(dwFindType & FIND_BYHANDLE)
	{
		ENTITYHEADER tempEntityHeader;
		char tempEntityData[4096];
		DWORD dwEntitySize;

		pEntities->CurrentEntityPos = 0;
		while(pEntities->CurrentEntityPos<pEntities->FreePos)
		{
			dwEntitySize = GetCurrentEntityData(pEntities, &tempEntityHeader, tempEntityData);
			if(pdwEntityPos!=NULL)
				*pdwEntityPos = pEntities->CurrentEntityPos;

			pEntities->CurrentEntityPos = tempEntityHeader.NextEntityPos;
			if(pEntityHeader->Objhandle==tempEntityHeader.Objhandle)
			{
				CopyMemory(pEntityHeader, &tempEntityHeader, sizeof(ENTITYHEADER));
				CopyMemory(pEntityData, tempEntityData, dwEntitySize);
				result = pEntityHeader->Objhandle;
				break;
			}
		}
	}
	else
	{
		if(dwFindType & FIND_FIRST)
		{
			pEntities->CurrentEntityPos = 0;
			GetCurrentEntityData(pEntities, pEntityHeader, pEntityData);
			if(pdwEntityPos!=NULL)
				*pdwEntityPos = pEntities->CurrentEntityPos;

			pEntities->CurrentEntityPos = pEntityHeader->NextEntityPos;
			result = pEntityHeader->Objhandle;
		}
		else if(dwFindType & FIND_LAST)
		{
			pEntities->CurrentEntityPos = pEntities->LastEntityPos;
			GetCurrentEntityData(pEntities, pEntityHeader, pEntityData);
			if(pdwEntityPos!=NULL)
				*pdwEntityPos = pEntities->CurrentEntityPos;

			pEntities->CurrentEntityPos = pEntities->FreePos;
			result = pEntityHeader->Objhandle;
		}
		else if(dwFindType & FIND_PREVIOUS)
		{
	//		if(pEntities->CurrentEntityPos<=0)
	//			break;
	//		GetCurrentEntityData(pEntities, pEntityHeader, pEntityData);
	//		if(pdwEntityPos!=NULL)
	//			*pdwEntityPos = pEntities->CurrentEntityPos;

	//		pEntities->CurrentEntityPos = pEntityHeader->PreviousEntityPos;
	//		GetCurrentEntityData(pEntities, pEntityHeader, pEntityData);
	//		result = pEntityHeader->Objhandle;
		}
		else if(dwFindType & FIND_NEXT)
		{
			if(pEntities->CurrentEntityPos<pEntities->FreePos)
			{
				GetCurrentEntityData(pEntities, pEntityHeader, pEntityData);
				if(pdwEntityPos!=NULL)
					*pdwEntityPos = pEntities->CurrentEntityPos;

				pEntities->CurrentEntityPos = pEntityHeader->NextEntityPos;
				result = pEntityHeader->Objhandle;
			}
		}
	}

	return result;
}
int CDrawing::FindBlockPosByName( PDRAWING pDrawing, LPCTSTR strBlockName )
{
	for(unsigned int i=0; i<pDrawing->BlocksNumber; i++)
		if( strcmp(pDrawing->Blocks[i].Name, strBlockName)==0 )
			return i;
	
	return -1;
}
DWORD CDrawing::GetCurrentEntityData( PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData )
{
	LPVOID	pEntitiesData;
	DWORD	EntityDataSize;

	// Initialize pEntitiesData ----------
	pEntitiesData = GlobalLock(pEntities->hEntities);
	if(pEntitiesData==NULL)
	{
		// GlobalLock error
		return 0;
	}

	CopyMemory(pEntityHeader, (LPVOID)((DWORD)pEntitiesData+pEntities->CurrentEntityPos), sizeof(ENTITYHEADER));

	EntityDataSize = pEntityHeader->NextEntityPos - (pEntities->CurrentEntityPos + sizeof(ENTITYHEADER));
	CopyMemory(pEntityData, (LPVOID)((DWORD)pEntitiesData+pEntities->CurrentEntityPos+sizeof(ENTITYHEADER)), EntityDataSize);

	return EntityDataSize;
}
