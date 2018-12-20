#ifndef _NODES_H_
#define _NODES_H_
#pragma warning(disable: 4786)

#include <map>
#include "Node.h"

class AFX_EXT_CLASS Nodes
{
typedef std::map<int,NODE> NODES;
	mutable NODES nodes_;
public:
	typedef NODES::iterator iterator;
private:
	mutable iterator it_;
	mutable int index_;
public:
	iterator begin() const;

	iterator end() const;

	NODE& operator[](iterator it) const;
	NODE& operator[](int index) const;
	NODE& Add(NODE& t);
	
	NODE* get(iterator it) const;
	NODE* get(int key) const;
	int GetSize() const;
	void RemoveAll();
	void erase(int key);
	
};
#endif