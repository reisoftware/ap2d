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
|  CadLib.h: The interface for CadIO.dll                              |
\*-------------------------------------------------------------------*/

#ifndef CADLIB_H
#define CADLIB_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "display_export.h"

#include "DXFDef.h"
#include "DrawingDef.h"

#include "MemDrw.h"
#include "Database.h"
#include "DXFBase.h"
#include "DXFRead.h"
#include "DXFWrite.h"
#include "DrwIO.h"
#include "counter.h"
// CDrawing class --------------------------------------------------
class DISPLAY_API CDrawing
{
public:
	// Initialization & UnInitialization
	CDrawing();
	~CDrawing();

	BOOL isOpen();
	// Construction & Destruction
	BOOL Create( );
	BOOL Destroy( );

	// Drawing View
	BOOL InitView( int x, int y, int nWidth, int nHeight );
	BOOL Paint( HDC hdc );
	double GetZoomLevel( );
	BOOL   SetZoomLevel(double ZoomLevel);
	BOOL GetViewProperties( PVIEW pView );
	BOOL SetViewProperties( PVIEW pView );
	BOOL GetDrawingBorder( PREALRECT pRect );
	BOOL ZoomExtents( );

	// Configuration
	BOOL SetLayer( LPCTSTR Name );
	BOOL SetLineType( LPCTSTR Name );
	BOOL SetTextStyle( LPCTSTR Name );
	BOOL SetDimStyle( LPCTSTR Name );
	BOOL SetColor( short Color );
	BOOL SetThickness( double Thickness );
	double SetLineTypeScale( double LineTypeScale );

	// TABLES section
	OBJHANDLE AddTableType( DWORD dwTableType, LPVOID pTableType );
	OBJHANDLE AddLayer( PLAYER pLayer );
	OBJHANDLE AddLinetype( PLTYPE pLineType );
	OBJHANDLE AddTextStyle( PSTYLE pTextStyle );
	OBJHANDLE AddDimStyle( PDIMSTYLE pDimStyle );
//	BOOL ChangeTableType( DWORD dwTableType, OBJHANDLE TableTypeObjhandle, LPVOID pTableType );
	BOOL DeleteTableType( DWORD dwTableType, OBJHANDLE TableTypeObjhandle );
	BOOL DeleteLayer( OBJHANDLE LayerObjhandle );
	BOOL DeleteLinetype( OBJHANDLE LineTypeObjhandle );
	BOOL DeleteTextStyle( OBJHANDLE TextStyleObjhandle );
	BOOL DeleteDimStyle( OBJHANDLE DimStyleObjhandle );
	OBJHANDLE FindTableType( DWORD dwTableType, DWORD dwFindType, LPVOID pTableType );

	// BLOCKS section
	OBJHANDLE AddBlock( PBLOCKHEADER pBlockHeader, LPCTSTR strFileName=NULL );
//	BOOL ChangeBlock( OBJHANDLE BlockObjhandle, PBLOCKHEADER pBlockHeader );
	BOOL DeleteBlock( OBJHANDLE BlockObjhandle );
	OBJHANDLE FindBlock( DWORD dwFindType, PBLOCKHEADER pBlockHeader );
	BOOL SetActiveBlock( OBJHANDLE ohBlock );
	BOOL SetActiveBlock( LPCTSTR strBlockName );
	OBJHANDLE GetActiveBlock( );

	// ENTITIES section
	OBJHANDLE AddEntity( OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	BOOL ChangeEntity( PENTITYHEADER pEntityHeader, LPVOID pEntityData, LPCTSTR strBlockName=NULL );
	BOOL DeleteEntity( LPCTSTR strBlockName, OBJHANDLE EntityObjhandle );
	OBJHANDLE FindEntity( DWORD dwFindType, PENTITYHEADER pEntityHeader, LPVOID pEntityData, LPCTSTR strBlockName=NULL );
	OBJHANDLE Arc( double cx, double cy, double r, double StartAngle, double EndAngle );
	OBJHANDLE Circle( double cx, double cy, double r );
//	OBJHANDLE Ellipse( double cx, double cy, double ex, double ey, double Ratio, double StartParam=0.0, double EndParam=2*PI );
	OBJHANDLE DimLinear( double x1, double y1, double x2, double y2, double x3, double y3, double angle,
		LPCTSTR text=NULL);
	OBJHANDLE DimLinear( double x1, double y1, double x2, double y2, double x3, double y3, double angle,
		LPCTSTR text,LPCTSTR dim_kind,double dimline_angle,double angle_dim_x1, double angle_dim_y1//2.22 add
		);
	OBJHANDLE InsertBlock( OBJHANDLE BlockObjhandle, double x, double y, double xScale=1, double yScale=1, double Rotation=0 );
	OBJHANDLE InsertBlock( LPCTSTR BlockName, double x, double y, double xScale=1, double yScale=1, double Rotation=0 );
	OBJHANDLE Line( double x1, double y1, double x2, double y2 );
	OBJHANDLE Solid( REALPOINT &Point0, REALPOINT &Point1, REALPOINT &Point2, REALPOINT &Point3 );
	OBJHANDLE Text( LPCTSTR Text, double x1, double y1, double x2, double y2, double Height, short Justification, double Rotation=0, double WidthFactor=0 );
	OBJHANDLE Text( LPCTSTR Text, double x, double y, double Height, double Rotation=0, double WidthFactor=0 );
	OBJHANDLE PolyLine( PENTVERTEX pVertex, int nVertex, unsigned short Flag=0 );

	// Datafile data-exchange
	BOOL SaveDXFFile( LPCTSTR FileName, HWND hWndProgress=NULL );
	BOOL LoadDXFFile( LPCTSTR FileName, HWND hWndProgress=NULL );

	HDRAWING get_hdrawing(){return m_hDrawing;}
	BOOL dxf_add_block_table(HDXF hDxf);


	BOOL save_dxf(LPCTSTR strFilePathName,dlhml::Database& database);
	BOOL LoadDXFFile( LPCTSTR FileName,dlhml::Database& database);



	OBJHANDLE drwAddTableType_pri( HDRAWING hDrawing, DWORD dwTableType, LPVOID pTableType );

protected:
	HINSTANCE		hinstCadIO;
	HDRAWING		m_hDrawing;
	bool			isLibraryLoaded;
	OBJHANDLE		CurrentLayerObjhandle;
	OBJHANDLE		CurrentLTypeObjhandle;
	OBJHANDLE		CurrentDimStyleObjhandle;
	OBJHANDLE		CurrentStyleObjhandle;
	short			CurrentColor;
	double			CurrentThickness;
	OBJHANDLE		ActiveBlockObjhandle;
	ENTITYHEADER	m_EntityHeader;


private:
	HDRAWING (*drwCreate)( );
	BOOL (*drwDestroy)( HDRAWING hDrawing );

	OBJHANDLE (*drwAddTableType)( HDRAWING hDrawing, DWORD dwTableType, LPVOID pTableType );
	BOOL (*drwDeleteTableType)( HDRAWING hDrawing, DWORD dwTableType, OBJHANDLE TableTypeObjhandle );
	OBJHANDLE (*drwFindTableType)( HDRAWING hDrawing, DWORD dwTableType, DWORD dwFindType, LPVOID pTableType );

	OBJHANDLE (*drwAddBlock)( HDRAWING hDrawing, PBLOCKHEADER pBlockHeader );
	BOOL (*drwDeleteBlock)( HDRAWING hDrawing, OBJHANDLE BlockObjhandle );
	OBJHANDLE (*drwFindBlock)( HDRAWING hDrawing, DWORD dwFindType, PBLOCKHEADER pBlockHeader );

	OBJHANDLE (*drwAddEntity)( HDRAWING hDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	BOOL (*drwDeleteEntity)( HDRAWING hDrawing, LPCTSTR strBlockName, OBJHANDLE EntityHandle );
	BOOL (*drwChangeEntity)( HDRAWING hDrawing, LPCTSTR strBlockName, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	OBJHANDLE (*drwFindEntity)( HDRAWING hDrawing, LPCTSTR strBlockName, PENTITYHEADER pEntityHeader, LPVOID pEntityData, DWORD dwFindType );

	BOOL (*drwSaveDataToFile)( HDRAWING hDrawing, DWORD Reserved, LPCTSTR strFileName, HWND hWndProgress );
	BOOL (*drwLoadDataFromFile)( HDRAWING hDrawing, OBJHANDLE BlockObjhandle, DWORD Reserved, LPCTSTR strFileName, HWND hWndProgress );

	BOOL (*drwInitView)( HDRAWING hDrawing, int x, int y, int Width, int Height );
	BOOL (*drwPaint)( HDRAWING hDrawing, HDC hdc );
	BOOL (*drwGetViewProperties)( HDRAWING hDrawing, PVIEW pView );
	BOOL (*drwSetViewProperties)( HDRAWING hDrawing, PVIEW pView );
	BOOL (*drwGetDrawingBorder)( HDRAWING hDrawing, PREALRECT pRect);
	BOOL (*drwZoomExtents)( HDRAWING hDrawing );

	BOOL (*drw_get_ents)(HDRAWING hDrawing,dlhml::Database& database);
	BOOL (*save_dxf_ents)(HDRAWING hDrawing,LPCTSTR strFilePathName,dlhml::Database& database);
	BOOL (*drwLoadDataFromFile_db)( HDRAWING hDrawing, OBJHANDLE BlockObjhandle, DWORD Reserved, LPCTSTR strFileName, dlhml::Database& database);

	PDRAWING converse_hd_to_pd(HDRAWING hDrawing);

	
	//把memdrw.cpp中的函数移动到此
	OBJHANDLE drwFindEntity_Direct( PDRAWING pDrawing, LPCTSTR strBlockName, PENTITYHEADER pEntityHeader, LPVOID pEntityData, DWORD dwFindType, DWORD* pdwEntityPos=NULL);
	int FindBlockPosByName( PDRAWING pDrawing, LPCTSTR strBlockName );
	DWORD GetCurrentEntityData( PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData );


	//重要的操作，需要修改的操作
	BOOL drwSaveDataToFile_pri( HDRAWING hDrawing, DWORD Reserved, LPCTSTR strFileName, HWND hWndProgress );



	//2.22
	void WriteEntityDataToFile( HDRAWING hDrawing, HDXF hDxf, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	BOOL dxfAddDimStyle_pri( HDXF hDxf, PDXFDIMSTYLE pDimStyle );
	BOOL WriteDimStyleData_pri( HDXF hDxf, PDXFDIMSTYLE pDimStyle );

	OBJHANDLE drwAddEntity_pri( HDRAWING hDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	OBJHANDLE drwAddEntity_Direct( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	int FindBlockPosByHandle( PDRAWING pDrawing, OBJHANDLE BlockObjhandle );
	BOOL AddEntity( PDRAWING pDrawing, PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData );
	BOOL AddToEntitiesList(PENTITIES pEntities, PENTITYHEADER pEntityHeader, LPVOID pEntityData, WORD EntitySize);
	BOOL DimLinear_pri( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pDimHeader, PENTDIMENSION pDimension, PDIMSTYLE pDimStyle );
	BOOL dimDrawArrowHead( PDRAWING pDrawing, OBJHANDLE BlockObjhandle, PENTITYHEADER pHeader, double cx, double cy, double Angle, double ArrowSize, LPCTSTR ArrowHeadName, int BLKNum );

	BOOL dxfAddLayer_pri( HDXF hDxf, char* Name, int Color, char* Linetype,char standflay='0');

  BOOL add_dxf_base_line(LPCTSTR dim_style_name,HDXF hDxf);

private:
	MCT_DEF
};

#endif // CADLIB_H
