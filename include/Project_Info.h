#ifndef PROJECT_INFO_H_
#define PROJECT_INFO_H_
class AFX_EXT_CLASS Project_Info  
{
	bool need_save_;
	CString name_;
	CString alias_;
	CString paint_kind_1_;
	CString paint_kind_2_;
	CString group_name_;
	CString lable_1_;
	CString lable_2_;
	double weld_;
	public:
	Project_Info();
	LPCTSTR get_name() const;
	LPCTSTR get_alias() const;
	LPCTSTR get_paint_1() const;
	LPCTSTR get_paint_2() const;
	LPCTSTR get_group_name() const;
	LPCTSTR get_lable_1() const;
	LPCTSTR get_lable_2() const;
	double get_weld() const;

	void set_name(LPCTSTR name);
	void set_alias(LPCTSTR alias);
	void set_paint_1(LPCTSTR paint_kind);
	void set_paint_2(LPCTSTR paint_kind);
	void set_group_name(LPCTSTR group_name);
	void set_lable_1(LPCTSTR lable);
	void set_lable_2(LPCTSTR lable);
	void set_weld(double weld);

	void save(LPCTSTR path) const;
	void load(LPCTSTR path);

	void disable_need_save();
	bool is_need_save() const;
};
#endif