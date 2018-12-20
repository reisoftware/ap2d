
#ifndef TIAN_DISPLAY_PAINT_ENTITY_TOOLS_H_
#define TIAN_DISPLAY_PAINT_ENTITY_TOOLS_H_

#include "../object/Circle.h"
#include "display_export.h"

#include "Line.h"
#include "RArc.h"
#include "Scene_d.h"
#include "Three_Pt_Dimension.h"
#include "Three_Pt_Dimension_Block.h"
#include "Ln_Dim.h"
#include "Ln_Dim_Block.h"
#include "Angle_Dimension.h"
#include "Radius_Dimension.h"

#include "TPlaneGeometry.h"
#include "TPt3D.h"
#include "TGlobal.h"


//using namespace TIAN_GA_BETTER;

namespace dlhml{
const int TGC_INT_DIM_TEXT_MAXSIZE = 512;
const COLORREF TGC_CR_CROSS = RGB(255,0,255);
const COLORREF TGC_CR_EXTLN = RGB(255,200,0);
const COLORREF TGC_CR_SELED = RGB(0,200,200);

const char TGC_STR_EXC_DIM[] = "exit size dimension\0";

enum EEditDo	
{
	DO_NULL					,
	DO_MOVE_DIM			,
	DO_MOVE_BLOCK		,
	DO_LAYOUT_BLOCK	,
	DO_ADD_DIM			,
	DO_DEL_DIM			,
	DO_LAYOUT_BASE	,
	DO_RESET0       ,
	DO_MOVE_TEXT		
};

typedef TIAN_GA_BETTER::CPt3D_Pri				TPoint;
typedef TIAN_GA_BETTER::CGeNorm					TNormal;
typedef TIAN_GA_BETTER::TLine						TLine;
typedef TIAN_GA_BETTER::TRayLine				TRayLine;
typedef TIAN_GA_BETTER::TSegLine				TSegLine;
typedef TIAN_GA_BETTER::TArc						TArc;

const double T_PI = TIAN_GA_BETTER::PI_R;

typedef TIAN_GA_BETTER::CPt3D_Pri  CPt3D_Pri;

class Point;

class DISPLAY_API Paint_Entity_Tools  
{
public:
	Paint_Entity_Tools(Scene& scene);
	virtual ~Paint_Entity_Tools();

public:
	static TPoint PointToPt3D_Pri(const Point& pt);
	static Point Pt3D_PriToPoint(const TPoint& pt);
	static TPoint  GetPt3D(const Point& pt);
	static Point GetPoint(const TPoint & pt);

	static Point TPoint2LPoint(const TPoint & pt);
	static TPoint LPoint2TPoint(const Point& pt);
	static Line TLine2LLine(const TLine & line);
	static TLine LLine2TLine(const Line & line);
	static TRayLine LLine2TRayLine(const Line & line);
	static TSegLine LLine2TSegLine(const Line & line);

	static RArc TArc2Larc(const TArc & tArc);
	static TArc LArc2Tarc(const RArc & lArc);

	static Line LineParallel(Line lnBase, Point ptExt);
	static Line LinePedal(Line lnBase, Point ptExt);
	static Point PointPedal(Point ptExt, Line lnBase);

	static TNormal Normal2TNormal(Normal nm);
	static Normal TNormal2Normal(TNormal nm);

	static Normal LNormalFromAngle(double angle);

	static Circle Arc2Circle(RArc myarc);
	static RArc LArcFrom3LPoint(Point pt1, Point pt2, Point pt3);

	static bool GetRectFrom3Point(Point& ptExtBegin, Point& ptExtEnd, 
		Point ptBegin, Point ptEnd, Point ptExt);
	static bool GetRectFrom3PointAndExtAngle(Point& ptExtBegin, Point& ptExtEnd, 
		Point ptBegin, Point ptEnd, Point ptExt, double dExtAngle);
	static bool GetRectFrom3PointAndDimAngle(Point& ptExtBegin, Point& ptExtEnd, 
		Point ptBegin, Point ptEnd, Point ptExt, double dDimAngle);
	static bool GetRectFrom4PointAndAngle(Point& ptExtBegin, Point& ptExtEnd, 
		Point ptBegin, Point ptEnd, Point ptExt1, Point ptExt2, double dDimAngle);
	static bool GetLineBaseFromPtAndExtAngle(Line& lnBase,
		Point pt, double dExtAngle);
	static bool GetLineBaseFromPtAndDimAngle(Line& lnBase,
		Point pt, double dDimAngle);

	static double Radian(Point pt, Point ptOrg = Point(0,0,0));
	static double Length(Line ln);

	static bool PtOrtho(Point& pt, Line lnBase, Point ptBase);
	static bool PtOrtho(Point& pt, Line lnBase);

	static Point get_mid_point(const Point& ptStart,const Point& ptEnd);

public:
	static double DisPtByNormal(Point pt1, Point pt2, Normal nm);
	static double DisPtToLineByNormal(Point pt, Line ln, Normal nm);
	static double DisPtToLine(Point pt, Line ln);
	//int add_dim_text_pos_layer(int iLayer);

public:
	static void xor_draw_circle(
		Scene& scene,
		Circle mycircle,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_arc(
		Scene& scene,
		RArc myarc,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_dim(
		Scene& scene,
		Angle_Dimension* pdim,
		bool xor = true,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_dim(
		Scene& scene,
		Three_Pt_Dimension * pdim,
		bool xor = true,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_dim(
		Scene& scene,
		Ln_Dim * pdim,
		bool xor = true,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_dim(
		Scene& scene,
		Radius_Dimension* pdim,
		bool xor = true,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_line(
		Scene& scene,
		Point pt1,
		Point pt2,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_line(
		Scene& scene,
		Line ln,
		COLORREF cr = RGB(255,255,255)
		);
	static void xor_draw_line(
		Scene& scene,
		Line ln,
		bool xor,
		COLORREF cr = RGB(255,255,255)
		);
	static void draw_dim_block(
		Scene& scene,
		Three_Pt_Dimension_Block& dimBlock);
	static void draw_dim_block(
		Scene& scene,
		Ln_Dim_Block& dimBlock);
	static void xor_draw_dim_block(
		Scene& scene,
		Three_Pt_Dimension_Block& dimBlock,
		bool xor = true);
	static void xor_draw_dim_block(
		Scene& scene,
		Ln_Dim_Block& dimBlock,
		bool xor = true);
	static void xor_draw_pt4(
		Scene& scene,
		const Point (&pt)[4], 
		COLORREF rolor = RGB(255,255,255)
		);
	static void xor_draw_rect(
		Scene& scene,
		const Rect& rect, 
		COLORREF rolor = RGB(255,255,255)
		);
	static void xor_draw_hint_dim(
		Scene& scene,
		const Rect& rect 
		);
	static void xor_draw_hint_txt(
		Scene& scene,
		const Rect& rect 
		);
	static void xor_draw_hint_add(
		Scene& scene,
		const Rect& rect 
		);
	static void xor_draw_hint_l(
		Scene& scene,
		const Rect& rect 
		);
	static void xor_draw_hint_r(
		Scene& scene,
		const Rect& rect 
		);
	static Point world_to_screen(Scene& scene,const Point& pt);

	static Line LineFromPointAndAngle(Point pt, double dAngle);
  
	static void Normal2TopOrLeft(Normal& nm);

public:
	////
	////圆心点+箭尾点+半径 ==》 箭头点
	static Point dim_arrow_head(Point c, Point tail, double r);
	////调整起始点及终止点的位置和顺序(保证起点、终点在弧线上同时小于平角)
	static void dim_angle_pt(Point& st, Point& ed, Point cen, Point dim);


	static void dim_angle_pt(Angle_Dimension& dim);
	////设置一个正向0点为显示，若无正向时显示负向
	//static void block_dim_show0(Ln_Dim_Block* pblock);
	////引出线方向
	static Normal LNormalExtFromDim(Ln_Dim* pDim);
	////标注方向
	static Normal LNormalFromDim(Ln_Dim* pDim);
	////标注方向+-,true为正序，false为逆序(以block为标准)
	static bool is_dim_order(Ln_Dim* pDim,
							Ln_Dim_Block* pBlock);
	static void dim_order_recal(Ln_Dim& dim,
							Ln_Dim_Block* pBlock);
	////判断标注是否为0
	static bool is_dim_0(Three_Pt_Dimension* pDim);
	static bool is_dim_0(Ln_Dim* pDim);
	static bool is_dim_0(Angle_Dimension* pDim);
	static bool is_dim_0(Radius_Dimension* pDim);
	////使得标注归0
	static void dim_re0(Three_Pt_Dimension* pDim);
	static void dim_re0(Ln_Dim* pDim);
	static void dim_re0(Angle_Dimension* pDim);
	static void dim_re0(Radius_Dimension* pDim);
	////求标注文本4点
	static void dim_text_4pt(Point (&pt)[4], Three_Pt_Dimension* pDim);
	static void dim_text_4pt_closed(Point (&pt)[4], Ln_Dim* pDim);
	static void dim_text1_4pt(Point (&pt)[4], Ln_Dim* pDim);
	static void dim_text2_4pt(Point (&pt)[4], Ln_Dim* pDim);
	////求标注文本宽度
	static double dim_text_height(Three_Pt_Dimension* pDim);
	static double dim_text_height_closed(Ln_Dim* pDim);
	static double dim_text_width(Three_Pt_Dimension* pDim);
	static double dim_text1_height(Ln_Dim* pDim);
	static double dim_text1_width(Ln_Dim* pDim);
	static double dim_text2_height(Ln_Dim* pDim);
	static double dim_text2_width(Ln_Dim* pDim);
	////获得/设置 标注文本所在层(线上为0,1，线下为-1,-2)，只改变文本基准点
	static int  get_dim_text_pos_layer(Three_Pt_Dimension * pDim);
	static int  get_dim_text_pos_layer_closed(Ln_Dim * pDim);
	static int  get_dim_text_pos_layer(Ln_Dim * pDim);
	static void set_dim_text_pos_layer(Three_Pt_Dimension * pDim, int iLayer);
	static void set_dim_text_pos_layer_closed(Ln_Dim * pDim, int iLayer);
	static void set_dim_text_pos_layer(Ln_Dim * pDim, int iLayer);
	////增加标注文本所在层号
	static void add_dim_text_pos_layer(Three_Pt_Dimension * pDim);
	static void add_dim_text_pos_layer_closed(Ln_Dim * pDim);
	static void add_dim_text_pos_layer(Ln_Dim * pDim);
	static int  add_dim_text_pos_layer(int iLayer);
	////标注层归0
	static void re0_dim_text_pos_layer(Three_Pt_Dimension * pDim);
	static void re0_dim_text_pos_layer_closed(Ln_Dim * pDim);
	static void re0_dim_text_pos_layer(Ln_Dim * pDim);

	////是否干涉
	static bool is_intervene(Three_Pt_Dimension* pDim1, 
							 Three_Pt_Dimension* pDim2);
	static bool is_intervene_closed(Ln_Dim* pDim1, Ln_Dim* pDim2);
	static bool is_intervene(Ln_Dim* pDim1, 
							 Ln_Dim* pDim2);
	static bool is_intervene(Ln_Dim* pDim);
	////bet ?   
	static bool is_intervene(Angle_Dimension* pDim1, 
							 Angle_Dimension* pDim2);

  static bool is_0_position(Ln_Dim_Block * block_1, 
                            Ln_Dim_Block * block_2);
  ////重新计算块
  static void recal_dim_block(Ln_Dim_Block& dimBlock);
  static void repos_dim_block(Ln_Dim_Block& dimBlock);
  static void recal_dim_block_pt(Ln_Dim_Block& dimBlock);
  static void recal_dim_block_txt(Ln_Dim_Block& dimBlock);
  static void recal_dim_block_txtpos(Ln_Dim_Block& dimBlock);
  static void recal_dim_block_show0(Ln_Dim_Block& dimBlock);
  ////
  static void recal_block_order(Ln_Dim_Block& dimBlock);
  static void recal_block_text(Ln_Dim_Block& dimBlock);
  static void recal_block_text_closed(Ln_Dim_Block& dimBlock);
  ////重新计算s点
  static void recal_dim_spt(Ln_Dim_Block& dimBlock);
	////重置标注文本高度层
	static void reset_dim_text_pos_layer(Three_Pt_Dimension_Block& dimBlock);
	static void reset_dim_text_pos_layer_closed(Ln_Dim_Block& dimBlock);
	static void reset_dim_text_pos_layer(Ln_Dim_Block& dimBlock);

	////求标注基线
	static Line LineBaseFromDim(Three_Pt_Dimension* pDim);
	static Line LineBaseFromDim(Ln_Dim* pDim);
	////标注线
	static Line LineDimFromDim(Three_Pt_Dimension* pDim);
	static Line LineDim1FromDim(Ln_Dim* pDim);
	static Line LineDim2FromDim(Ln_Dim* pDim);
	////引出线
	static Line LineExt1FromDim(Three_Pt_Dimension* pDim);
	static Line LineExt1FromDim(Ln_Dim* pDim);
	static Line LineExt2FromDim(Three_Pt_Dimension* pDim);
	static Line LineExt2FromDim(Ln_Dim* pDim);
	////引出线
	static bool LineExtFromDim(Line& lnExt1, Line& lnExt2, 
		Three_Pt_Dimension* pDim);
	static bool LineExtFromDim(Line& lnExt1, Line& lnExt2, 
		Ln_Dim* pDim);
	////标注的宽度
	static double WideFromDim(Three_Pt_Dimension* pDim);
	static double WideFromDim(Ln_Dim* pDim);
	static double AngleFromDim(Angle_Dimension* pDim);
	static double LenFromDim(Radius_Dimension* pDim);
	static RArc ArcFromDim(Angle_Dimension* pDim);
	static void DimSetByArc(Angle_Dimension& dim, RArc ar);
	static void DimSet(Angle_Dimension& dim, 
		                 const Point& ptCen, 
                     const Point& ptSrt, 
                     const Point& ptEnd, 
                     const Point& ptDim);
	////通过两点获得normal和dis（引出线方向）
	static void dim_get_namal_dis(Three_Pt_Dimension* pDim, Point bg, Point ed
									, Normal& nm, double& dis);
	static void dim_get_namal_dis(Ln_Dim* pDim, Point bg, Point ed
									, Normal& nm, double& dis);

	static void dim_txt_get_namal_dis(Three_Pt_Dimension* pDim, Point bg, Point ed
									, Normal& nm, double& dis);
	////获得标注点
	static Point dim_pt(Ln_Dim* pDim, int pos);
	////移动标注（沿角度引出线方向）
	static void dim_move(Angle_Dimension* pDim, Point bg, Point ed,
		Line lnExt1, Line lnExt2);
	static void dim_move(Angle_Dimension* pDim, Point bg, Point ed);
	static void dim_move(Angle_Dimension* pDim, Point ed);
	static void dim_move(Angle_Dimension* pDim, Point ed,
		Line lnExt1, Line lnExt2);
	static void dim_move(Angle_Dimension* pDim, Normal nm, double dis);
	static void dim_move(Radius_Dimension* pDim, Point ptArrowTail);
	////移动标注（沿引出线方向）
	static void dim_move(Three_Pt_Dimension* pDim, Point bg, Point ed);
	static void dim_move(Three_Pt_Dimension* pDim, Normal nm, double dis);
	////基线标注不移动0点（0点单独移动）
	static void dim_move(Ln_Dim* pDim, Point ptMoveTo, int pos);
	static void dim_move(Ln_Dim* pDim, Normal nm, double dis, int pos);
	static void dim_move1(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/);
	static void dim_move1(Ln_Dim* pDim, Normal nm, double dis);
	static void dim_move2(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/);
	static void dim_move2(Ln_Dim* pDim, Normal nm, double dis);
	//static void dim_move2by0(Ln_Dim* pDim, Normal nm, double dis);
	//static void dim_move3(Ln_Dim* pDim, Point ptMoveTo/*, int pos*/);
	//static void dim_move3(Ln_Dim* pDim, Normal nm, double dis);
	//static void dim_move3by0(Ln_Dim* pDim, Normal nm, double dis);
	////移动整块全部0点
	static void dim_move_all0(Ln_Dim_Block* pblock, Point ptMoveTo);

	static void dim_txt_move(Three_Pt_Dimension* pDim, Point bg, Point ed);
	static void dim_txt_move(Three_Pt_Dimension* pDim, Normal nm, double dis);

	static void dim_init(Three_Pt_Dimension& dim);
	////重算引出线角度
	static void dim_extend_angle_recal(Three_Pt_Dimension& dim);

	////重新计算标注文本相关信息
	static void dim_text_recal(Three_Pt_Dimension& dim);
	static void dim_text_recal_closed(Ln_Dim& dim);
	static void dim_text_recal(Ln_Dim& dim/*, Scene* scene = NULL*/);
	static void dim_text_recal(Angle_Dimension& dim);
	static void dim_text_recal(Radius_Dimension& dim);
	////计算标注文本内容
	static void dim_text_content(Three_Pt_Dimension& dim);
	static void dim_text_content_closed(Ln_Dim& dim);
	static void dim_text_content(Ln_Dim& dim);
	static void dim_text_content(Angle_Dimension& dim);
	static void dim_text_content(Radius_Dimension& dim);
	////计算标注文本位置
	static void dim_text_position(Three_Pt_Dimension& dim);
	//static void dim_text_position_closed(Ln_Dim& dim);
	static void dim_text_position(Ln_Dim& dim);
	static void dim_text_position(Angle_Dimension& dim);
	static void dim_text_position(Radius_Dimension& dim);
	////计算标注文本角度
	static void dim_text_rotation(Three_Pt_Dimension& dim);
	static void dim_text_rotation(Ln_Dim& dim);
	static void dim_text_rotation(Angle_Dimension& dim);
	static void dim_text_rotation(Radius_Dimension& dim);
	////计算标注文本对齐方式
	static void dim_text_alignpt(Three_Pt_Dimension& dim);
	static void dim_text_alignpt(Ln_Dim& dim);
	static void dim_text_alignpt(Angle_Dimension& dim);
	static void dim_text_alignpt(Radius_Dimension& dim);

	static void dim_copy(Three_Pt_Dimension& dimD, 
						const Three_Pt_Dimension& dimS);
	static void dim_copy(Ln_Dim& dimD, 
						const Ln_Dim& dimS);
	static void dim_copy(Angle_Dimension& dimD, 
						const Angle_Dimension& dimS);
//08.11.24
//	static void dim_copy(Radius_Dimension& dimD, 
//						const Radius_Dimension& dimS);
	////复制block
	static void dim_block_copy( Three_Pt_Dimension_Block& blockD,
						                  Three_Pt_Dimension_Block& blockS);
	static void dim_block_copy( Ln_Dim_Block& blockD,
						                  Ln_Dim_Block& blockS);
	static void dim_block_copy(Angle_Dimension& blockD,
						Angle_Dimension& blockS);
	////复制出blockOld中（从bg到ed的部分），形成blockNew；
	static void dim_block_split(Three_Pt_Dimension_Block& blockOld, 
						Three_Pt_Dimension_Block& blockNew,
						Three_Pt_Dimension * pdimSlipt);

	////block中iterator的+-操作
	static void block_it_move_pre(Ln_Dim** ppdim,
							Ln_Dim_Block* pblock, int pos);
	static void block_it_move_pre_or_to_first(Ln_Dim** ppdim,
							Ln_Dim_Block* pblock, int pos);

	static bool is_line_superpositon(Line ln1, Line ln2);



public:
	static double GetAngle(const Point& ptStart,const Point& ptEnd);
	static void GetLineKAndB(Point ptStart,Point ptEnd,float& k,float& b);
private:
	static float GetTwoPointSlope(const Point& ptStart,const Point& ptEnd);

protected:
  Scene& scene_;

	
private:
	MCT_DEF
};


//namespace
}
#endif // !defined(AFX_PAINT_ENTITY_TOOLS_H__02FFD82F_0189_413C_A9A2_605E43D76BF6__INCLUDED_)
