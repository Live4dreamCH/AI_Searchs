#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <utility>
//#include "NineState_new.h"

//节点类的基类. 在解决不同问题的时候, 继承并修改它, 以处理不同的状态空间和算符
//C是子类的类型
template <class C, class Code>
class State
{
private:
	//应当实现, 但是参数是具体内容
	bool isAncestor(State* test) {
		//State* curr = this->parent;
		//while (curr != NULL) {
		//	if (curr == test)
		//		return true;
		//	curr = curr->parent;
		//}
		//return false;
	}

	//应当实现, 但广度和单调A*中似乎都不用,先放一放
	bool getChild(std::vector<C*> &ch){}

protected:
	C* parent;//谁扩展了它(父节点)
	unsigned long long int num;//第几个被扩展
	std::vector<C*> children;//扩展得到的所有非祖先子节点
	Code code;//唯一标识符

public:
	State(C* p = NULL) :parent(p), num(0), code(0) {}
	virtual bool generate(std::vector<std::pair<C*,bool> >& M, std::map<Code, C>& G) = 0;
	void setNum(unsigned long long int n){
		num = n;
	}
	void setParent(C* p) {
		parent = p;
	}
	C* getParent() const{
		return parent;
	}

	virtual Code getCode() = 0;

	//virtual bool operator <(C ano) = 0;

	virtual void print()const = 0;
};

