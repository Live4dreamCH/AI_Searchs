#include "GeneralSearch.h"
#include <algorithm>

#include "NineState_new.h"

template<class S>
static bool cmp(const S* a, const S* b) {
	return a->getFx() > b->getFx();
}

//��֤�˵����Ժ��A*�㷨, F��fx���ص�����
template<class S, class Code, class F>
class AStarSearch : public GeneralSearch<S, std::vector<S*>, Code>
{
public:
	AStarSearch(S start, S target):GeneralSearch<S, std::vector<S*>, Code>(start, target) {}
	
	//��open�еĵ�һ���ڵ��openת�Ƶ�close, 
	//�������Ϊn, (S::setNum)
	//��Snָ����
	void open2close() override {
		std::pop_heap(this->open.begin(), this->open.end(), cmp<S>);
		this->Sn = this->open.back();
		this->open.pop_back();
		this->Sn->setNum(this->n);
		this->close[this->Sn->getCode()] = this->Sn;
		this->n++;
	}

	//���M, 
	//��չ��ǰSn�ڵ�, ���ݲ������ȵĽ�����һ��(S::generate, S::isAncestor)
	//�������G��,newһ��, ��Sn��child,��M,��G,del���ϵ�(S::operator <),M����Ϊfalse
	//�����, ��Sn��child, ��M, M����Ϊtrue
	//��(�����ȵ�)�ӽڵ�ʱ, ����true
	bool generate() override {
		this->M.clear();
		return this->Sn->generate(this->M, this->graph, &(this->target));
	}

	//����M
	//�����open��, �Ƚ��ĸ���������, ���ø��ײ����޸�gxֵ
	//�������close��,�Ͳ����κβ���;
	//����G��,setParent�Ҽ���open��
	bool changeM() override {
		//std::cout << "open++\n";
		bool open_sort = false;
		for (auto it = this->M.begin(); it != this->M.end(); it++) {
			//����G��,setParent�Ҽ���open��
			if (!(*it).second) {
				(*it).first->setParent(this->Sn);
				//this->open.remove(*it);
				this->open.push_back((*it).first);
				std::push_heap(this->open.begin(), this->open.end(), cmp<S>);
			}
			//�����open��, �Ƚ��ĸ���������, ���ø��ײ����޸�gxֵ
			else if( this->close.find( (*it).first->getCode() ) == this->close.end()){
				if ((*it).first->changeParent(this->Sn))
					open_sort = true;
			}
			//(*it)->print();
		}
		return open_sort;
	}

	//��open������
	void sortOpen() override {
		std::make_heap(this->open.begin(), this->open.end(), cmp<S>);
	}

	//����ȫ����,����true��ʾ�ҵ�,�������ʧ��
	//���ɹ�, ��·���ϴ���ʼ��Ŀ��Ľڵ�˳��д��states(������β)
	bool search(std::stack<S*>& states) override {
		auto it = this->graph.insert({ this->start.getCode(),this->start }).first;
		this->open.push_back(&(it->second));
		std::make_heap(this->open.begin(), this->open.end(), cmp<S>);
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
			if (this->generate()) {
				if (this->changeM())
					this->sortOpen();
			}
		}
	}

};