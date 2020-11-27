#pragma once
#include "State.h"

static unsigned int myabs(int num) {
    return (num >= 0 ? num : -num);
}

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
            //��һ��hx: this��target��ͬ�ĸ���������2, ������A*�Ļ���Ҫ���Լ�������
            //����2��Ϊ�����㵥������Ҫ
            //���ڳ���2�����ָ�����, ���������ٶȼ���, ���ұȽ�ʱҲ�п��ܻ��������
            //�����ڴ˴�������2, �෴, ��ÿ������״̬����ʱ��c(x1, x2)��1��Ϊ2 (��this->setParent��)
            
            //for (int i = 0; i < 3; i++) {
            //    for (int j = 0; j < 3; j++) {
            //        if (this->Nine[i][j] != target->Nine[i][j]) {
            //            this->hx++;
            //        }
            //    }
            //}

            //�ڶ���hx: this��target������ͬ����֮�����̾���֮�ͳ���2, ͬ������A*�Ļ���Ҫ���Լ�������
            //���ڵڶ���hx >= ��һ��hx, �����ٶȿ��ܻ����

            bool brk = false;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (this->Nine[i][j] != target->Nine[i][j]) {
                        brk = false;
                        for (int xx = 0; xx < 3; xx++) {
                            for (int yy = 0; yy < 3; yy++) {
                                if (this->Nine[i][j] == target->Nine[xx][yy]) {
                                    this->hx += myabs(xx - i) + myabs(yy - j);
                                    brk = true;
                                    break;
                                }
                            }
                            if (brk)
                                break;
                        }
                    }
                }
            }

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
        //std::cout << "������\n";
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
        //std::cout << "����������\n";
        //this->print();
    }

    //void test() {
    //    State* s = this->parent;
    //    NineState_new* ns = this;
    //    s = ns;
    //}

    ~NineState_new()
    {
        //std::cout << "������\n";
        //this->print();
    }

    void setParent(NineState_new* p) {
        this->parent = p;
        if (p == NULL)
            this->gx = 0;
        else
            this->gx = p->gx + 2;
    }

    bool changeParent(NineState_new* p) {
        if (p->gx + 2 < this->gx) {
            this->setParent(p);
            return true;
        }
        return false;
    }

    //��չ��ǰSn�ڵ�, ���ݲ������ȵĽ�����һ��(S::generate, S::isAncestor)
    //�������G��,newһ��, ��Sn��child,��M,��G,del���ϵ�(S::<),M����Ϊfalse
    //�����, ��Sn��child, ��M, M����Ϊtrue
    //��(�����ȵ�)�ӽڵ�ʱ, ����true
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

    //������code,��Ҫ�ż���
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

    unsigned long long int getFx() const {
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