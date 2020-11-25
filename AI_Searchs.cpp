// AI_Searchs.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//#include <vector>
//#include <map>
//#include <queue>

#include "BFsearch.h"
#include "NineState_new.h"
#include <stack>


int main()
{
    //std::vector<int> v{1, 2, 4, 8, 16};
    //for (auto i = v.begin(); i != v.end(); i++)
    //    std::cout << *i << "\n";
    //std::map<int*, bool> signal;
    //int* x = new int;
    //*x = -1;
    //signal[x] = true;
    //for (auto i = signal.begin(); i != signal.end(); i++) {
    //    delete i->first;
    //}

    //std::map<int, bool> g;
    //auto it = g.begin();
    //std::vector<std::map<int, bool>::iterator> m;
    //m.push_back(it);
    //std::queue<std::map<int, bool>::iterator> o;
    //o.push(*(m.begin()));
    //std::map<int, bool>::iterator sn = o.front();
    //sn->second = true;

    short int s0[3][3] = { {1,2,3}, {4,0,8}, {7,6,5} }, se[3][3] = { {1,2,3}, {8,0,4}, {7,6,5} };
    int x0 = 1, y0 = 1, xe = 1, ye = 1;
    NineState_new start(s0, x0, y0, NULL), target(se, xe, ye);
    BFsearch<NineState_new, unsigned int> bfs(start, target);

    std::cout << "从:\n";
    start.print();
    std::cout << "到:\n";
    target.print();
    std::cout << "开始搜索:\n";

    std::stack<NineState_new*> result;
    if (bfs.search(result)) {
        std::cout << "扩展次数:"<< bfs.getN() <<"答案是\n";
        while (!result.empty())
        {
            result.top()->print();
            result.pop();
        }
    }
    else {
        std::cout << "无解! 可达状态数:" << bfs.getN();
    }
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
