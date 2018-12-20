// Dxf_Read.h: interface for the Dxf_Read class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXF_READ_H__2A39AFE0_5624_47A4_A481_B3C86A0EEB5E__INCLUDED_)
#define AFX_DXF_READ_H__2A39AFE0_5624_47A4_A481_B3C86A0EEB5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CadLib.h"
#include "Dxf_Entities.h"

namespace dlhml
{
	class Scene;
}
class DISPLAY_API Dxf_Read  
{
public:
	Dxf_Read();
	virtual ~Dxf_Read();

	BOOL read(std::string file,dlhml::Scene* scene);

	void set_text_scale(double scale){reduce_scale_  = scale;};
	std::vector<dlhml::Entity*> ents_;
private:
	bool open_drawing(CDrawing& drawing);

	BOOL read_tables();
	BOOL read_dimstyles();
	BOOL read_layers();
	BOOL read_ltypes();
	BOOL read_styles();

	BOOL read_entities(PDXF pDxf);
	void get_ent_header(const DXFENTITYHEADER &DxfEntityHeader,ENTITYHEADER	&EntityHeader,Z_EntProperties& entProp);
	COLORREF get_color(int color);

	void line_add_db(const Z_EntProperties& entProp,PDXFENTLINE li);
	BOOL point_add_db(const Z_EntProperties& entProp,PDXFENTPOINT pt);
	BOOL circle_add_db(const Z_EntProperties& entProp,PDXFENTCIRCLE circle);
	BOOL arc_add_db(const Z_EntProperties& entProp,PDXFENTARC arc);
	void text_add_db(const Z_EntProperties& entProp,PDXFENTTEXT txt);
	BOOL txt_style_add_db(DXFSTYLE &style);

	
	bool get_ltype(OBJHANDLE obj_handle,LTYPE & ltype);
	void get_ltype(char* ch_ltype_old,char* ch_ltype);
	BOOL layer_add_db(LAYER &layer);
	BOOL ltype_add_db(LTYPE &ltype);
	BOOL style_add_db(STYLE &style);
	BOOL ltype_add_db(DXFLTYPE &ltype);

	//从cadio中添加
	BOOL dxfReadEntityData_Direct( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, LPVOID pEntityData );
	BOOL ReadPointData_pri( PDXF pDxf, PDXFENTITYHEADER pEntityHeader, PDXFENTPOINT pPoint );


private:
	PDRAWING	pDrawing_;
	HDRAWING hDrawing_;
	HDXF hDxf_;
	Layers layers_;
	LTypes ltypes_;	
	Styles styles_;

	//固定颜色
	COLORREF color_in_;

	dlhml::Scene* scene_;

	int cur_num_;

	double reduce_scale_;

private:
	MCT_DEF
};

#endif // !defined(AFX_DXF_READ_H__2A39AFE0_5624_47A4_A481_B3C86A0EEB5E__INCLUDED_)
