/*-------------------------------------------------------------------*\
|  CadLib Version 2.1                                                 |
|  Written by Omid Shahabi <omid_shahabi@hotmail.com>                 |
|  Copyright © 2002-2004                                              |
|  Pars Technology Development Co.                                    |
|                                                                     |
|  This software is distributed on an "AS IS" basis, WITHOUT WARRANTY |
|  OF ANY KIND, either express or implied.                            |
|                                                                     |
|                                                                     |
|  DREntities.h                                                       |
\*-------------------------------------------------------------------*/

#ifndef DRENTITIES_H
#define DRENTITIES_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DXFBase.h"

//---------------------------------------------------------------------------
// Exported Functions
//---------------------------------------------------------------------------
BOOL dxfReadEntityData( 
	HDXF				hDxf,			// handle to the openning DXF file structure
	PDXFENTITYHEADER	pEntityHeader,	// pointer to entity data header
	LPVOID				pEntityData		// pointer to entity data structure to read
);

BOOL dxfReadEntityData_Direct(
	PDXF				pDxf,			// pointer to the openning DXF file structure
	PDXFENTITYHEADER	pEntityHeader,	// pointer to entity data header
	LPVOID				pEntityData		// pointer to entity data structure to read
);
BOOL ReadLineData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTLINE pLine );
BOOL ReadPointData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTPOINT pPoint );
BOOL ReadCircleData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTCIRCLE pCircle );
BOOL ReadEllipseData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTELLIPSE pEllipse );
BOOL ReadTextData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTTEXT pText );
BOOL ReadArcData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTARC pArc );
BOOL ReadSolidData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTSOLID pSolid );
BOOL ReadInsertData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTINSERT pInsert );
BOOL ReadPolyLineData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTPOLYLINE pPolyLine );
BOOL ReadDimensionData( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTDIMENSION pDimension );
void SetEntityHeaderDefaultValues( PDXFENTITYHEADER pEntityHeader );

#endif // DRENTITIES_H
