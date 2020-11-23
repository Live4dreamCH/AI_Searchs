#pragma once
#include "GeneralSearch.h"
#include <queue>
//#include <iostream>

//#include "NineState_new.h"


//�����������
template<class S, class Code>
class BFsearch : public GeneralSearch<S, std::queue<S*>, Code>
{
public:
	BFsearch(S start, S target) :GeneralSearch<S, std::queue<S*>, Code>(start, target) {}

	//��open�еĵ�һ���ڵ��openת�Ƶ�close, 
	//�������Ϊn, (S::setNum)
	//��Snָ����
	void open2close() override {
		this->Sn = this->open.front();
		this->open.pop();
		this->Sn->setNum(this->n);
		this->close[this->Sn->getCode()] = this->Sn;
		this->n++;
	}

	//���M, 
	//��չ��ǰSn�ڵ�, ���ݲ������ȵĽ�����һ��(S::generate, S::isAncestor)
	//�������G��,newһ��, ��Sn��child,��M,��G,del���ϵ�(S::<)
	//�����, ��Sn��child, ��M
	//��(�����ȵ�)�ӽڵ�ʱ, ����true
	bool generate() override {
		this->M.clear();
		return this->Sn->generate(this->M, this->graph);
	}
	//����M
	void changeM() override {
		for (auto i = this->M.begin(); i != this->M.end(); i++) {
			//(*i)->setParent(this->Sn);
			this->open.push(*i);
			//(*i)->print();
		}
	}
	//��open������
	void sortOpen() override {}
	//����ȫ����,����true��ʾ�ҵ�,�������ʧ��
	//���ɹ�, ��·���ϴ���ʼ��Ŀ��Ľڵ�˳��д��states(������β)
	bool search(std::stack<S*>& states) override {
		auto it = this->graph.insert({ this->start.getCode(),this->start }).first;
		this->open.push(&(it->second));
		while (true) {
			//std::cout << "-----------------------------------\n";
			if (this->open.empty())
				return false;
			this->open2close();
			if (this->Sn->getCode() == this->target.getCode()) {
				S* curr = this->Sn;
				while (curr != NULL)
				{
					states.push(curr);
					curr = curr->getParent();
				}
				return true;
			}
			if (this->generate())
				this->changeM();
		}
	}
};

