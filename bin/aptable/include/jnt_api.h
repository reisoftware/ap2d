#ifndef _JNT_API_H_
#define _JNT_API_H_

#ifdef JNTDLL
#define JNT_API __declspec(dllexport)
#else
#define JNT_API 
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "joint.h"

#define MAX_PARAMS 20

#define I_TYPE 0
#define F_TYPE 1
#define S_TYPE 2
#define B_TYPE 3
struct PARAM{
	int type;
	union{
		int i_val;
		double f_val;
		char s_val[MAX_BUFFER];
		};
	char name[MAX_BUFFER];
	char func_name[MAX_BUFFER];
};
struct PARAMS{
	int nums;
	char name[MAX_BUFFER];
	struct PARAM param[MAX_PARAMS];
};

typedef int(*CHANGE_PARAM)(struct PARAMS*,struct PARAM*,const char*);

JNT_API int is_store_ar(void* ar);
JNT_API void write_ar(void* buf,int max,void* ar);
JNT_API void read_ar(void* buf,int max,void* ar);
JNT_API void* create_mirror_xz();
JNT_API void del_xz(void* xz);
JNT_API struct Pt polarto(struct Pt pt,double l,void* norm);
JNT_API void double2int(double* d,int* i);
JNT_API struct PARAMS* get_params(struct PARAMS* params,int num,const char* name);
JNT_API struct PARAM* get_param(struct PARAMS* params,const char* name);
JNT_API void* get_member(int memno);
JNT_API double get_beta(void* member);
JNT_API int edit_param(struct PARAMS* params,int nums,struct JOINT* jnt,CHANGE_PARAM func);
//////////////////////////cjoint//////////////
JNT_API struct Pt get_jnt_base(void* jnt);


//GEPlate exported APIs////////////
JNT_API void cnt_add_pl(void* cnt,void* pl);
JNT_API void cnt_recal_pl(void* cnt,void* norm,struct Pt pt);

JNT_API void* create_pl();
JNT_API void delete_pl(void* pl);
JNT_API int pl_get_owner(void* ge_pl);
JNT_API void pl_set_owner(void* ge_pl,int index);
JNT_API void pl_get_name(void* ge_pl,char name[]);
JNT_API void pl_set_name(void* ge_pl,char name[]);
JNT_API void pl_get_prefix(void* ge_pl,char prefix[]);
JNT_API void pl_set_prefix(void* ge_pl,char prefix[]);
JNT_API void pl_get_material(void* ge_pl,char material[]);
JNT_API void pl_set_material(void* ge_pl,char material[]);
JNT_API void pl_get_custom(void* ge_pl,char custom[]);
JNT_API void pl_set_custom(void* ge_pl,char custom[]);
JNT_API void pl_get_guid(void* ge_pl,char guid[]);
JNT_API void pl_set_guid(void* ge_pl,char guid[]);
JNT_API double pl_get_w(void* ge_pl);
JNT_API double pl_get_h(void* ge_pl);
JNT_API double pl_get_t(void* ge_pl);
JNT_API void pl_set_w(void* ge_pl,double w);
JNT_API void pl_set_t(void* ge_pl,double t);
JNT_API void pl_set_h(void* ge_pl,double h);
JNT_API int pl_need_num(void* ge_pl);
JNT_API int pl_need_draw(void* ge_pl);
JNT_API void pl_set_set_need_num(void* ge_pl);
JNT_API void pl_set_set_need_draw(void* ge_pl);
JNT_API void pl_clear_need_draw(void* ge_pl);
JNT_API void pl_clear_need_num(void* ge_pl);
JNT_API void pl_Load(void* ge_pl,char* szPath);
JNT_API void pl_Save(void* ge_pl,char* szPath);
JNT_API int pl_UserEdit(void* ge_pl);
JNT_API double pl_get_thick(void* ge_pl);
JNT_API int pl_get_normal(void* ge_pl,struct Pt* norm);
JNT_API int pl_get_vertexs_size(void* ge_pl);
JNT_API void pl_AddVertex(void* ge_pl,struct Pt pt,int bArc);
JNT_API void pl_add_vertex(void* ge_pl,int begin,int end,struct Pt pt,int bArc); 
JNT_API void pl_del_vertex(void* ge_pl,int index);
JNT_API void pl_round_angle(void* ge_pl,int index,double r);
JNT_API void pl_bolt_angle(void* ge_pl,int index,double r);
JNT_API void pl_unround(void* ge_pl,int index);
JNT_API void pl_move_vertex(void* ge_pl,int index,struct Pt pt);
JNT_API struct Pt pl_get_near_pt(void* ge_pl,struct Pt pt,void* plane);
JNT_API void pl_enable_select(void* ge_pl,int bTrue);
JNT_API int pl_select_state(void* ge_pl);
JNT_API void pl_add_norm_cut(void* ge_pl,void* cut);
JNT_API void pl_clear_norm_cut(void* ge_pl);
JNT_API void pl_modify(void* ge_pl,struct Pt pt1,struct Pt pt2,struct Pt pt3);
JNT_API void pl_transform(void* pl,void* transform);

////////////cut_norm/////////////////////////

JNT_API void norm_cut_start(void* norm_cut);
JNT_API void norm_cut_end(void* norm_cut);
JNT_API void norm_cut_set(void* norm_cut,int start,int end,double a,int up);
JNT_API double norm_cut_get_len(void* norm_cut,void* ge_plate);
JNT_API int norm_cut_get_normal(void* norm_cut,void* normal,void* ge_plate);
JNT_API int norm_cut_is_up(void* norm_cut);
JNT_API void norm_cut_set_up(void* norm_cut,int up);
JNT_API int norm_cut_is_same(void* norm_cut,void* rhs);
JNT_API int norm_cut_is_reverse(void* norm_cut,void* rhs);
JNT_API void* norm_cut_create(void* norm_cut);
JNT_API void norm_cut_release(void* norm_cut);

////////////Ge_Norm/////////////////////////
JNT_API void* genorm_X();
JNT_API void* genorm_Y();
JNT_API void* genorm_Z();
JNT_API void* genorm_X1();
JNT_API void* genorm_Y1();
JNT_API void* genorm_Z1();
JNT_API void genorm_set(void* norm,struct Pt pt1,struct Pt pt2);
JNT_API double genorm_len(void* norm);
JNT_API double genorm_Angle2Norm(void* norm,void* norm_rhs);
JNT_API double genorm_Dot(void* norm,void* norm_rhs);
JNT_API int genorm_IsZero(void* norm);
JNT_API void genorm_normalize(void* norm);
JNT_API struct Pt genorm_get_pt(void* norm);
JNT_API void* genorm_create(double x,double y,double z);
JNT_API void genorm_release(void* norm);


/////////////////////////////////
JNT_API void member_get_name(void* member, char* name);
JNT_API void member_get_no(void* member, char* no);
JNT_API void member_get_part_no(void* member, char* part_no);
JNT_API void member_get_custom_no(void* member, char* custom_no);
JNT_API void member_get_no_prefix(void* member, char* no_prefix);
JNT_API void member_get_part_prefix(void* member, char* part_prefix);
JNT_API void member_get_section_name(void* member, char* section);
JNT_API void member_get_material_name(void* member, char* material);
JNT_API void member_set_name(void* member, char* str);
JNT_API void member_set_no(void* member, char* str);
JNT_API void member_set_part_no(void* member, char* str);
JNT_API void member_set_custom_no(void* member, char* str);
JNT_API void member_set_no_prefix(void* member, char* str);
JNT_API void member_set_part_prefix(void* member, char* str);
JNT_API void member_set_section_name(void* member, char* str);
JNT_API void member_set_material_name(void* member, char* str);
JNT_API struct Pt member_get_offset(void* member, int index);
JNT_API void member_set_offset(void* member, int index,struct Pt offset);
JNT_API void* member_get_plates(void* member);
JNT_API float member_get_color(void* member, int index);
JNT_API void member_set_color(void* member, int index, float val);
// 很多类似函数似乎没必要
JNT_API void member_new(void* member);
JNT_API void member_copy(void* obj_member, void* ori_member);
JNT_API void member_draw_plates(void* member);
JNT_API struct Pt member_get_near_pt(void* member, struct Pt pt, void* plane);
JNT_API struct SECT member_get_section(void* member);
JNT_API struct Pt member_get_real_start(void* member);
JNT_API struct Pt member_get_real_end(void* member);
JNT_API void* member_GetStart(void* member, void* lpModel);
JNT_API void* member_GetEnd(void* member, void* lpModel);
JNT_API int member_SetStartWithND(void* member, void* node);
JNT_API int member_SetEndWithND(void* member, void* node);
JNT_API int member_is_cut(void* member);
JNT_API void member_set_modify(void* member, int modify);
JNT_API int member_edit_cut(void* member);
JNT_API void member_Divide(void* member, int nSeg, int bCut, void* lpNodeAry);
JNT_API void member_SetStartWithNo(void* member, int iNum);
JNT_API void member_SetEndWithNo(void* member, int iNum);
//JNT_API void member_GetMemCut(void* member, void* hBeam_Cut);
JNT_API int member_IsNormal(void* member, void* lpNode, void* lpNorm);
JNT_API int member_IsNormalZ(void* member, void* lpNode);
JNT_API void member_ModifyOffset(void* member, void* lpNode, void* lpPt3d);
JNT_API void member_set_cut(void* member, void* hBeam_Cut);
JNT_API void member_GetNorm(void* member, void* lpNode, void* lpGeNorm);
JNT_API struct Pt member_GetBase(void* member, void* lpNode);
JNT_API void member_AddNode(void* member);
JNT_API double member_GetSteelLen(void* member);
JNT_API void member_SetOffset(void* member, void* lpNode, void* lpPt3d);
JNT_API void member_mirror_plane(void* member, void* lpNorm, void* lpPt3d);
JNT_API void member_offset(void* member, double len, void* lpNormal);
JNT_API void member_move_nd(void* member, void* lpPt3d1, void* lpPt3d2);
JNT_API void member_Move(void* member, double len, void *lpNorm);
JNT_API int member_IsAssemble_Mem(void* member);
JNT_API int member_IsC_Mem(void* member);
JNT_API int member_IsP_Mem(void* member);
JNT_API int member_IsG_Mem(void* member);
JNT_API int member_IsB_Mem(void* member);
JNT_API int member_IsDP_Mem(void* member);
JNT_API int member_IsT_Mem(void* member);
JNT_API int member_IsS_Mem(void* member);
JNT_API int member_Is_COLUMN(void* member);
JNT_API int member_Is_BEAM(void* member);
JNT_API int member_Is_BRACE(void* member);
JNT_API void member_SetMemType_C(void* member);
JNT_API void member_SetMemType_P(void* member);
JNT_API void member_SetMemType_G(void* member);
JNT_API void member_SetMemType_B(void* member);
JNT_API void member_SetMemType_DP(void* member);
JNT_API void member_SetMemType_T(void* member);
JNT_API void member_SetMemType_S(void* member);
JNT_API void member_ClearMemType(void* member);
JNT_API void member_select_plate(void* member, int index);
JNT_API struct Pt bolt_get_cen(void* bolt);
JNT_API double bolt_get_len(void* bolt);
JNT_API void bolt_set_pt(void* bolt, void* lpPt3d, void* lpNorm);

JNT_API void bolt_draw_center(void* bolt, void* lpPlane, void* lpPt3ds);
JNT_API void bolt_draw_2d_cross(void* bolt, void* lpPlane, void* lpAxis);
JNT_API void bolt_draw_2d_c(void* bolt, void* lpPlane, void* lpAxis);
JNT_API void bolt_draw_2d_r(void* bolt, void* lpPlane, void* lpAxis);
JNT_API void bolt_new(void* lpNewBolt);
JNT_API void* bolt_get_polygon(void* bolt, void* lpAxis);
JNT_API void bolt_l2g(void* bolt, void* lpAxis);
JNT_API void bolt_g2l(void* bolt, void* lpAxis);
JNT_API void bolt_transform(void* bolt, void* lpTransform_base);
JNT_API void bolts_add_bolt(void* bolts, struct Pt startPt,double dia,double hole_d, char* type,int jnt_index);
JNT_API void bolts_add_bolt0(void* bolts, void* lpBolt);
JNT_API int bolts_bolts_size(void* bolts);
JNT_API void bolts_clear_bolts(void* bolts);
//JNT_API void GeBolts::transform(Transform_Base& transform_base);
JNT_API void bolts_transform(void* bolts, void* lpTransform_base);


#ifdef __cplusplus
}
#endif

#endif
