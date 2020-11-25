#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <utility>
//#include "NineState_new.h"

//�ڵ���Ļ���. �ڽ����ͬ�����ʱ��, �̳в��޸���, �Դ���ͬ��״̬�ռ�����
//C�����������
template <class C, class Code>
class State
{
private:
	//Ӧ��ʵ��, ���ǲ����Ǿ�������
	bool isAncestor(State* test) {
		//State* curr = this->parent;
		//while (curr != NULL) {
		//	if (curr == test)
		//		return true;
		//	curr = curr->parent;
		//}
		//return false;
	}

	//Ӧ��ʵ��, ����Ⱥ͵���A*���ƺ�������,�ȷ�һ��
	bool getChild(std::vector<C*> &ch){}

protected:
	C* parent;//˭��չ����(���ڵ�)
	unsigned long long int num;//�ڼ�������չ
	std::vector<C*> children;//��չ�õ������з������ӽڵ�
	Code code;//Ψһ��ʶ��

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

