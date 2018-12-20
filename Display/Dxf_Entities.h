#ifndef _DXF_ENTITIES_H_
#define _DXF_ENTITIES_H_
#include "counter.h"
////////////////////////////////////////////////////////////
typedef struct D_DIMSTYLE {
public:
	D_DIMSTYLE()MCT_INIT1("D_DIMSTYLE"){;}
	D_DIMSTYLE(DIMSTYLE dim)MCT_INIT1("D_DIMSTYLE"){
		init(dim);
	}
	void operator= (DIMSTYLE dim){
		init(dim);		
	}
	void init(DIMSTYLE dim){
		Objhandle = dim.Objhandle;
		strcpy(Name, dim.Name);
		StandardFlags = dim.StandardFlags;
		dimasz = dim.dimasz;
		strcpy(dimblk1, dim.dimblk1);
		strcpy(dimblk2, dim.dimblk2);
		dimclrd = dim.dimclrd;
		dimclre = dim.dimclre;
		dimclrt = dim.dimclrt;
		dimdle = dim.dimdle;
		dimexe = dim.dimexe;
		dimexo = dim.dimexo;
		dimgap = dim.dimgap;
		dimtxt = dim.dimtxt;
		dimtad = dim.dimtad;
		dimtxstyObjhandle = dim.dimtxstyObjhandle;
	}
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// name of dimension style
	char	StandardFlags;			// Standard flag values
	double	dimasz;					// Arrow size
//	OBJHANDLE dimblk1Objhandle;		// 1st Arrow head
//	OBJHANDLE dimblk2Objhandle;		// 2nd Arrow head
	char	dimblk1[16];			// 1st Arrow head
	char	dimblk2[16];			// 2nd Arrow head
	short	dimclrd;				// Dimension line & Arrow heads color
	short	dimclre;				// Extension line color
	short	dimclrt;				// Text color
	double	dimdle;					// Dimension line size after Extensionline
	double	dimexe;					// Extension line size after Dimline
	double	dimexo;					// Offset from origin
	double	dimgap;					// Offset from dimension line
	double	dimtxt;					// Text height
	char	dimtad;					// Vertical Text Placement
	OBJHANDLE dimtxstyObjhandle;	// Text style handle
private:
	MCT_DEF
} D_DIMSTYLE, *PD_DIMSTYLE;

////////////////////////////////////////////////////////////
typedef struct D_LAYER {
	D_LAYER()MCT_INIT1("D_LAYER"){;}
	D_LAYER(LAYER layer)MCT_INIT1("D_LAYER"){
		init(layer);
	}
	void operator= (LAYER layer){
		init(layer);		
	}
	void init(LAYER layer){
		Objhandle = layer.Objhandle;
		strcpy(Name, layer.Name);
		StandardFlags = layer.StandardFlags;
		Color = layer.Color;
		LineTypeObjhandle = layer.LineTypeObjhandle;
		LineWeight = layer.LineWeight;
		PlotFlag = layer.PlotFlag;
		PlotStyleObjhandle = layer.PlotStyleObjhandle;
	}
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Layer Name
	char	StandardFlags;			// Standard flags
	short	Color; 					// Layer Color (if negative, layer is Off)
	OBJHANDLE LineTypeObjhandle;	// Handle of linetype for this layer
	short	LineWeight;				// Layer's Line Weight                      (*2000*)
	BOOL	PlotFlag;				// TRUE=Plot this layer                     (*2000*)
	OBJHANDLE PlotStyleObjhandle;	// handle of PlotStyleName object           (*2000*)
private:
	MCT_DEF
} D_LAYER, *D_PLAYER;

////////////////////////////////////////////////////////////
typedef struct D_LTYPE {
	D_LTYPE()MCT_INIT1("D_LTYPE"){;}
	D_LTYPE(LTYPE ltype)MCT_INIT1("D_LTYPE"){
		init(ltype);
	}
	void operator= (LTYPE ltype){
		init(ltype);		
	}
	void init(LTYPE ltype){
		Objhandle = ltype.Objhandle;
		strcpy(Name, ltype.Name);
		StandardFlags = ltype.StandardFlags;
		strcpy(DescriptiveText, ltype.DescriptiveText);
		ElementsNumber = ltype.ElementsNumber;
		Elements[30] = ltype.Elements[30];
		PatternLength = ltype.PatternLength;
	}
	bool operator== (LTYPE ltype){
		if(ltype.Objhandle == Objhandle)
			return true;
		return false;		
	}
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Line Type Name
	char	StandardFlags;			// Standard flags
	char	DescriptiveText[512];	// Descriptive Text
	short	ElementsNumber;			// Line Elements Number
	double	Elements[30];			// Line Elements (Max=30)
	double	PatternLength;          // Length of linetype pattern
private:
	MCT_DEF
} D_LTYPE, *PD_LTYPE;

////////////////////////////////////////////////////////////
typedef struct D_STYLE {
	D_STYLE()MCT_INIT1("D_STYLE"){;}
	D_STYLE(STYLE style)MCT_INIT1("D_STYLE"){
		init(style);
	}
	void operator= (STYLE style){
		init(style);		
	}
	void init(STYLE style){
		Objhandle = style.Objhandle;
		strcpy(Name, style.Name);
		StandardFlags = style.StandardFlags;
		TextGenerationFlags = style.TextGenerationFlags;
		strcpy(PrimaryFontFilename, style.PrimaryFontFilename);
		strcpy(BigFontFilename, style.BigFontFilename);
		ObliqueAngle = style.ObliqueAngle;
		FixedTextHeight = style.FixedTextHeight;
		WidthFactor = style.WidthFactor;
		LastHeightUsed = style.LastHeightUsed;
	}
	OBJHANDLE Objhandle;			// Handle
	char	Name[MAX_STRLEN];		// Style Name
	char	StandardFlags;			// Standard flag values -> 4=Vertical text
	char	TextGenerationFlags;	// Text generation flags -> 2=Text is backward  4=Text is upside down
	char	PrimaryFontFilename[256];// Primary Font Filename
	char	BigFontFilename[256];	// Big font filename
	double	ObliqueAngle;			// Oblique angle
	double	FixedTextHeight;		// Fixed text height
	double	WidthFactor;			// Width Factor
	double	LastHeightUsed;			// Height
private:
	MCT_DEF
} D_STYLE, *PD_STYLE;

typedef std::vector<D_DIMSTYLE> DimStyles;//文本样式的集合
typedef std::vector<D_LAYER> Layers;//文本样式的集合
typedef std::vector<D_LTYPE> LTypes;//文本样式的集合
typedef std::vector<D_STYLE> Styles;//txt style gather



#endif