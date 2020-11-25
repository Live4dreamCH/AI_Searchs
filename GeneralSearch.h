#pragma once
#include <map>
#include <vector>
#include <stack>
#include <utility>

//#include "NineState_new.h"

//一般搜索类; S: 状态, O: Open表采用的数据结构类型, code:每个S的唯一标识
template <class S, class O, class Code>
class GeneralSearch
{
protected:
	O open;//open表
	std::map<Code, S> graph;//保存已扩展到的节点.
	std::map<Code, S*> close;
	unsigned long long int n;//被扩展过的节点数目
	S start, target;
	S* Sn;//起始节点, 目标节点, 当前节点
	std::vector<std::pair<S*, bool>> M;//扩展得到的子节点

	//把open中的第一个节点从open转移到close, 
	//并赋编号为n, (S::setNum)
	//将Sn指向它
	virtual void open2close() = 0;

	//清空M, 
	//扩展当前Sn节点, 内容不是祖先的进入下一步(S::generate, S::isAncestor)
	//如果不在G中,new一个, 改Sn的child,加M,加G,del堆上的(S::<)
	//如果在, 改Sn的child, 加M
	//有(非祖先的)子节点时, 返回true
	virtual bool generate() = 0;
	//处理M
	virtual void changeM() = 0;
	//对open表排序
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

	//查找全过程, 返回true表示找到, 否则查找失败
	//若成功, 将路径上从起始到目标的节点顺序写入states(包含首尾)
	virtual bool search(std::stack<S*> &states) = 0;

	//get n
	unsigned long long int getN() { return n; }
};

