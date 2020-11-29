// AI_Searchs.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

//#include <vector>
//#include <map>
//#include <queue>
//#include <algorithm>

#include "BFsearch.h"
#include "AStarSearch.cpp"
#include "NineState_new.h"
#include <stack>


//bool cmp(const int& a,const int& b){
//    return a > b;
//}

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

    //std::vector<int> test = { 3,7,11,2,4,1 };
    //std::make_heap(test.begin(), test.end(), cmp);

    short int s0[3][3] = { {1,2,3}, {8,0,4}, {7,6,5} }, se[3][3] = { {0,5,7}, {6,2,8}, {3,4,1} };
    int x0 = 1, y0 = 1, xe = 0, ye = 0;

    std::string re;
    std::cout << "是否需要输入起止格局? (y:输入, N:不输入, 采用默认值)\n";
    std::cin >> re;
    if (re == "y" || re == "Y") {
        std::cout << "请输入起始格局:(空格以0代替)\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cin >> s0[i][j];
                if (s0[i][j] == 0) {
                    x0 = i;
                    y0 = j;
                }
            }
        }
        std::cout << "请输入目标格局:(空格以0代替)\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cin >> se[i][j];
                if (se[i][j] == 0) {
                    xe = i;
                    ye = j;
                }
            }
        }
    }

    NineState_new target(se, xe, ye);
    NineState_new start(s0, x0, y0, NULL, &target);

    std::cout << "\n是否使用DFS?(y/N): ";
    std::cin >> re;
    if (re == "y" || re == "Y") {
        BFsearch<NineState_new, unsigned int> bfs(start, target);

        std::cout << "\n从:\n";
        start.print();
        std::cout << "到:\n";
        target.print();
        std::cout << "DFS开始搜索:\n";

        std::stack<NineState_new*> result;
        if (bfs.search(result)) {
            int temp = result.size()-1;
            std::cout << "搜索成功!具体路径为:\n";
            while (!result.empty())
            {
                result.top()->print();
                result.pop();
            }
            std::cout << "扩展次数:" << bfs.getN() << "\n路径长度:" << temp << "\n\n";
        }
        else {
            std::cout << "无解! 可达状态数:" << bfs.getN()<<"\n\n";
        }
    }

    std::cout << "\n是否使用A*?(y/N): ";
    std::cin >> re;
    if (re == "y" || re == "Y") {
        AStarSearch<NineState_new, unsigned int, unsigned long long int> ass(start, target);

        std::cout << "\n从:\n";
        start.print();
        std::cout << "到:\n";
        target.print();
        std::cout << "A*开始搜索:\n";

        std::stack<NineState_new*> result2;
        if (ass.search(result2)) {
            int temp = result2.size()-1;
            std::cout << "搜索成功!具体路径为:\n";
            while (!result2.empty())
            {
                result2.top()->print();
                result2.pop();
            }
            std::cout << "扩展次数:" << ass.getN() << "\n路径长度:" << temp << "\n\n";
        }
        else {
            std::cout << "无解! 可达状态数:" << ass.getN()<<"\n\n";
        }
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
