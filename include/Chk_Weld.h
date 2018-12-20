#ifndef _CHK_WELD_H_
#define _CHK_WELD_H_
#include <vector>
class CModel;
class Chk_Weld{
	CModel* model_;
	public:
		Chk_Weld(CModel* model);
		void chk();
	private:
		int get_main_mem();
		void get_sub_mem(int main_index,std::vector<int>& indexs);
		void select_jnt_pl(int mem_index);
		void select_all(std::vector<int>& indexs);
		void select_all_jnt_pl(std::vector<int>& indexs);
		void clear_jnt_pls();
};
#endif