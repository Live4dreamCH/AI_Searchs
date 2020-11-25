#pragma once
#include "State.h"

class NineState_new :public State<NineState_new, unsigned int> {
protected:
    short int Nine[3][3], x, y;
    unsigned int code;
    unsigned long long int gx, hx;

    bool isAncestor(short int n[3][3]) const {
        NineState_new* curr = this->parent;
        while (curr != NULL) {
            if (*curr == n)
                return true;
            curr = curr->parent;
        }
        return false;
    }

    bool operator ==(short int n[3][3]) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (n[i][j] != Nine[i][j])
                    return false;
            }
        }
        return true;
    }

    void setHx(NineState_new* target) {
        this->hx = 0;
        if (target != NULL) {

        }
    }

public:
    NineState_new(short int n[3][3], short int x, short int y, NineState_new* p = NULL, NineState_new * target = NULL) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Nine[i][j] = n[i][j];
            }
        }
        this->x = x;
        this->y = y;
        this->code = 0;
        this->setParent(p);
        this->setHx(target);
        //std::cout << "构造了\n";
        //this->print();
    };


    NineState_new(const NineState_new& ano) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Nine[i][j] = ano.Nine[i][j];
            }
        }
        this->x = ano.x;
        this->y = ano.y;
        this->code = ano.code;
        this->setParent(ano.parent);
        this->hx = ano.hx;
        //std::cout << "拷贝构造了\n";
        //this->print();
    }

    //void test() {
    //    State* s = this->parent;
    //    NineState_new* ns = this;
    //    s = ns;
    //}

    ~NineState_new()
    {
        //std::cout << "析构了\n";
        //this->print();
    }

    void setParent(NineState_new* p) {
        this->parent = p;
        if (p == NULL)
            this->gx = 0;
        else
            this->gx = p->gx + 1;
    }

    //扩展当前Sn节点, 内容不是祖先的进入下一步(S::generate, S::isAncestor)
    //如果不在G中,new一个, 改Sn的child,加M,加G,del堆上的(S::<),M中设为false
    //如果在, 改Sn的child, 加M, M中设为true
    //有(非祖先的)子节点时, 返回true
    bool generate(std::vector<std::pair<NineState_new*, bool> >& M, std::map<unsigned int, NineState_new>& G, NineState_new* target) {
        short int temp[3][3];
        bool succ = false;
        NineState_new *son = NULL;
        std::pair<NineState_new*, bool> p2M;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[i][j] = Nine[i][j];
            }
        }
        if ((0 <= x && x < 3) && (0 <= y && y < 3)) {
            if (x > 0) {
                temp[x][y] = temp[x - 1][y];
                temp[x - 1][y] = 0;

                if (!isAncestor(temp)) {
                    son = new NineState_new(temp, x - 1, y, this, target);
                    auto it = G.find(son->getCode());
                    p2M.second = !(it == G.end());
                    if (!p2M.second) {
                        p2M.first = &(G.insert_or_assign(son->getCode(), *son).first->second);
                        delete son;
                    }
                    else {
                        p2M.first = &(it->second);
                    }
                    this->children.push_back(p2M.first);
                    M.push_back(p2M);
                    succ = true;
                }

                temp[x - 1][y] = temp[x][y];
                temp[x][y] = 0;
            }
            if (x < 2) {
                temp[x][y] = temp[x + 1][y];
                temp[x + 1][y] = 0;

                if (!isAncestor(temp)) {
                    son = new NineState_new(temp, x + 1, y, this, target);
                    auto it = G.find(son->getCode());
                    p2M.second = !(it == G.end());
                    if (!p2M.second) {
                        p2M.first = &(G.insert_or_assign(son->getCode(), *son).first->second);
                        delete son;
                    }
                    else {
                        p2M.first = &(it->second);
                    }
                    this->children.push_back(p2M.first);
                    M.push_back(p2M);
                    succ = true;
                }

                temp[x + 1][y] = temp[x][y];
                temp[x][y] = 0;
            }
            if (y > 0) {
                temp[x][y] = temp[x][y - 1];
                temp[x][y - 1] = 0;

                if (!isAncestor(temp)) {
                    son = new NineState_new(temp, x, y - 1, this, target);
                    auto it = G.find(son->getCode());
                    p2M.second = !(it == G.end());
                    if (!p2M.second) {
                        p2M.first = &(G.insert_or_assign(son->getCode(), *son).first->second);
                        delete son;
                    }
                    else {
                        p2M.first = &(it->second);
                    }
                    this->children.push_back(p2M.first);
                    M.push_back(p2M);
                    succ = true;
                }

                temp[x][y - 1] = temp[x][y];
                temp[x][y] = 0;
            }
            if (y < 2) {
                temp[x][y] = temp[x][y + 1];
                temp[x][y + 1] = 0;

                if (!isAncestor(temp)) {
                    son = new NineState_new(temp, x, y + 1, this, target);
                    auto it = G.find(son->getCode());
                    p2M.second = !(it == G.end());
                    if (!p2M.second) {
                        p2M.first = &(G.insert_or_assign(son->getCode(), *son).first->second);
                        delete son;
                    }
                    else {
                        p2M.first = &(it->second);
                    }
                    this->children.push_back(p2M.first);
                    M.push_back(p2M);
                    succ = true;
                }

                temp[x][y + 1] = temp[x][y];
                temp[x][y] = 0;
            }
        }
        return succ;
    }

    //懒加载code,需要才计算
    unsigned int getCode() {
        if (code != 0)
            return code;
        unsigned int ten = 1;
        for (int i = 2; i >= 0; i--) {
            for (int j = 2; j >= 0; j--) {
                code += Nine[i][j] * ten;
                ten *= 10;
            }
        }
        return code;
    }

    unsigned long long int getFx() {
        return this->gx + this->hx;
    }

    bool operator <(NineState_new ano) {
        return this->getCode() < ano.getCode();
    }

    void print() const {
        if (parent == NULL) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (Nine[i][j] != 0)
                        std::cout << Nine[i][j];
                    else
                        std::cout << ' ';
                    std::cout << ' ';
                }
                std::cout << "\n";
            }
        }
        else {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (Nine[i][j] != 0)
                        std::cout << Nine[i][j];
                    else
                        std::cout << ' ';
                    std::cout << ' ';
                }
                std::cout << " <- ";
                for (int j = 0; j < 3; j++) {
                    if (parent->Nine[i][j] != 0)
                        std::cout << parent->Nine[i][j];
                    else
                        std::cout << ' ';
                    std::cout << ' ';
                }
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }

};