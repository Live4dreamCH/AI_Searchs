#pragma once
#include <map>
#include <vector>
#include <stack>
#include <utility>

//#include "NineState_new.h"

//һ��������; S: ״̬, O: Open����õ����ݽṹ����, code:ÿ��S��Ψһ��ʶ
template <class S, class O, class Code>
class GeneralSearch
{
protected:
	O open;//open��
	std::map<Code, S> graph;//��������չ���Ľڵ�.
	std::map<Code, S*> close;
	unsigned long long int n;//����չ���Ľڵ���Ŀ
	S start, target;
	S* Sn;//��ʼ�ڵ�, Ŀ��ڵ�, ��ǰ�ڵ�
	std::vector<std::pair<S*, bool>> M;//��չ�õ����ӽڵ�

	//��open�еĵ�һ���ڵ��openת�Ƶ�close, 
	//�������Ϊn, (S::setNum)
	//��Snָ����
	virtual void open2close() = 0;

	//���M, 
	//��չ��ǰSn�ڵ�, ���ݲ������ȵĽ�����һ��(S::generate, S::isAncestor)
	//�������G��,newһ��, ��Sn��child,��M,��G,del���ϵ�(S::<)
	//�����, ��Sn��child, ��M
	//��(�����ȵ�)�ӽڵ�ʱ, ����true
	virtual bool generate() = 0;
	//����M
	virtual void changeM() = 0;
	//��open������
	virtual void sortOpen() = 0;

public:
	GeneralSearch(S start, S target) :start(start), target(target) {
		this->n = 0;
	}
	~GeneralSearch() {
		//for (auto i = this->graph.begin(); i != this->graph.end(); i++) {
		//	if (i->first != start) {
		//		delete i->first;
		//	}
		//}
	}

	//����ȫ����, ����true��ʾ�ҵ�, �������ʧ��
	//���ɹ�, ��·���ϴ���ʼ��Ŀ��Ľڵ�˳��д��states(������β)
	virtual bool search(std::stack<S*> &states) = 0;

	//get n
	unsigned long long int getN() { return n; }
};

