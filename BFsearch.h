#pragma once
#include "GeneralSearch.h"
#include <list>
#include <iostream>

//#include "NineState_new.h"


//�����������
template<class S, class Code>
class BFsearch : public GeneralSearch<S, std::list<S*>, Code>
{
public:
	BFsearch(S start, S target) :GeneralSearch<S, std::list<S*>, Code>(start, target) {}

	//��open�еĵ�һ���ڵ��openת�Ƶ�close, 
	//�������Ϊn, (S::setNum)
	//��Snָ����
	void open2close() override {
		this->Sn = this->open.front();
		this->open.pop_front();
		this->Sn->setNum(this->n);
		this->close[this->Sn->getCode()] = this->Sn;
		this->n++;
		//std::cout << "open--\n";
		//this->Sn->print();
	}

	//���M, 
	//��չ��ǰSn�ڵ�, ���ݲ������ȵĽ�����һ��(S::generate, S::isAncestor)
	//�������G��,newһ��, ��Sn��child,��M,��G,del���ϵ�(S::operator <),M����Ϊfalse
	//�����, ��Sn��child, ��M, M����Ϊtrue
	//��(�����ȵ�)�ӽڵ�ʱ, ����true
	bool generate() override {
		this->M.clear();
		return this->Sn->generate(this->M, this->graph);
	}
	//����M
	//�������G��,�Ͳ����κβ���;����G��,setParent�Ҽ���open��
	void changeM() override {
		//std::cout << "open++\n";
		for (auto it = this->M.begin(); it != this->M.end(); it++) {
			if (!(*it).second) {
				(*it).first->setParent(this->Sn);
				//this->open.remove(*it);
				this->open.push_back((*it).first);
			}
			//(*it)->print();
		}
	}
	//��open������
	void sortOpen() override {}
	//����ȫ����,����true��ʾ�ҵ�,�������ʧ��
	//���ɹ�, ��·���ϴ���ʼ��Ŀ��Ľڵ�˳��д��states(������β)
	bool search(std::stack<S*>& states) override {
		auto it = this->graph.insert({ this->start.getCode(),this->start }).first;
		this->open.push_front(&(it->second));
		while (true) {
			//std::cout << "-----------------------------------\n";
			if (this->open.empty())
				return false;
			//for (auto it = this->graph.begin(); it != this->graph.end(); it++) {
			//	it->second.print();
			//}
			//std::cout << "open = " << this->open.size() << '\n';
			//std::cout << "graph = " << this->graph.size() << '\n';
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

