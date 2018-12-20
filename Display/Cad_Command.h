
#ifndef _TIAN_DISPLAY_CAD_COMMAND_H_
#define _TIAN_DISPLAY_CAD_COMMAND_H_


#include "vector"
#include "counter.h"

namespace dlhml
{

enum CADTYPE {CADCMD, ROTACMD, SCALECMD, STRECHCMD};

class Create_Entity;

class Matrix;
class Entity;
class Point;
class Line;

class Cad_Command 
{
public:
  Cad_Command();
  virtual ~Cad_Command();

public:
	void setcur(Create_Entity * c){cur_ = c;}

public:
//virtual void set_old(std::vector<Entity*>* myold){old_=myold;}
  virtual void set_xor(std::vector<Entity*>* myxor){xor_=myxor;}
  virtual void set_new(std::vector<Entity*>* mynew){new_=mynew;}
  
  virtual bool cad_cammand(const Line& ln)=0;
  
  virtual Point key_cammand(const Point& begin, const Point& end);
  virtual Point key_cammand(const Point& begin, const Point& way, double val);
  virtual LPCTSTR  endpt_cmd_out();
  //virtual void close()=0;
  virtual bool is_ortho(){return true;}
	virtual bool is_there_temp(){return false;}
	virtual bool is_keep_begin(){return false;}//	保持begin_不移动（否则begin_自动移动到end_）
	virtual bool is_reset_begin(){return false;}//	用于需要重新指定begin_

	virtual CADTYPE cadtype()const{return CADCMD;}

public:
	void count(int n){count_ = n;}

protected:
//std::vector<Entity*>* old_;
  std::vector<Entity*>* xor_;
  std::vector<Entity*>* new_;
	int count_;

	Create_Entity * cur_;					////当前命令指针，外部传入（Idle_Command）
	
private:
	MCT_DEF
};

}//namespace

#endif//FILE
