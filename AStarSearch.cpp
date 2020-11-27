#include "GeneralSearch.h"
#include <algorithm>

#include "NineState_new.h"

template<class S>
static bool cmp(const S* a, const S* b) {
	return a->getFx() > b->getFx();
}

//保证了单调性后的A*算法, F是fx返回的类型
template<class S, class Code, class F>
class AStarSearch : public GeneralSearch<S, std::vector<S*>, Code>
{
public:
	AStarSearch(S start, S target):GeneralSearch<S, std::vector<S*>, Code>(start, target) {}
	
	//把open中的第一个节点从open转移到close, 
	//并赋编号为n, (S::setNum)
	//将Sn指向它
	void open2close() override {
		std::pop_heap(this->open.begin(), this->open.end(), cmp<S>);
		this->Sn = this->open.back();
		this->open.pop_back();
		this->Sn->setNum(this->n);
		this->close[this->Sn->getCode()] = this->Sn;
		this->n++;
	}

	//清空M, 
	//扩展当前Sn节点, 内容不是祖先的进入下一步(S::generate, S::isAncestor)
	//如果不在G中,new一个, 改Sn的child,加M,加G,del堆上的(S::operator <),M中设为false
	//如果在, 改Sn的child, 加M, M中设为true
	//有(非祖先的)子节点时, 返回true
	bool generate() override {
		this->M.clear();
		return this->Sn->generate(this->M, this->graph, &(this->target));
	}

	//处理M
	//如果在open中, 比较哪个父亲最优, 设置父亲并且修改gx值
	//如果它在close里,就不做任何操作;
	//不在G里,setParent且加入open中
	bool changeM() override {
		//std::cout << "open++\n";
		bool open_sort = false;
		for (auto it = this->M.begin(); it != this->M.end(); it++) {
			//不在G里,setParent且加入open中
			if (!(*it).second) {
				(*it).first->setParent(this->Sn);
				//this->open.remove(*it);
				this->open.push_back((*it).first);
				std::push_heap(this->open.begin(), this->open.end(), cmp<S>);
			}
			//如果在open中, 比较哪个父亲最优, 设置父亲并且修改gx值
			else if( this->close.find( (*it).first->getCode() ) == this->close.end()){
				if ((*it).first->changeParent(this->Sn))
					open_sort = true;
			}
			//(*it)->print();
		}
		return open_sort;
	}

	//对open表排序
	void sortOpen() override {
		std::make_heap(this->open.begin(), this->open.end(), cmp<S>);
	}

	//查找全过程,返回true表示找到,否则查找失败
	//若成功, 将路径上从起始到目标的节点顺序写入states(包含首尾)
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