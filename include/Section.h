#ifndef _SECTION_H_
#define _SECTION_H_
#include <vector>
#include "Rei_Sect.h"
class CGePlate;

class Section{
private:
  REISECT sect_;
  virtual void get_pls_imp(double len,std::vector<CGePlate>& pls) const = 0;
public:
  Section():sect_() {}
  virtual ~Section() = 0 {}
    REISECT get_reisect() const;
  void get_pls(double len,std::vector<CGePlate>& pls) const;	
  friend class Section_Factory;
};

class Section_Factory{
  static void get_number(CString& str,double num[]);
public:
  static Section* create_section(CString str);
};


class Tub_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class C_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class CG_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class L_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class M_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class P_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class H_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
class CT_Section:public Section{
private:
  void get_pls_imp(double len,std::vector<CGePlate>& pls) const;
};
#endif
