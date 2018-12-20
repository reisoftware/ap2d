#ifndef _selector_h_
#define _selector_h_

namespace gelib{
class Selector{
protected:
	~Selector() {}
public:
	int select(CPoint pt,double width,double height,bool single_select);
private:
	void process_hits(GLint hits,GLuint buffer[]);
	void send_select_num_2_mainwnd();
};
}
#endif