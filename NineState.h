#pragma once
//#include "State.h"
#include <vector>
#include <iostream>

class NineState
{
private:
    NineState* parent;//谁扩展了它(父节点)
    unsigned long long int num;//第几个进行扩展
    short int Nine[3][3], x, y, c = 0;
    NineState* children[4] = { 0,0,0,0 };

public:
    NineState(short int n[3][3], short int x, short int y, NineState* p = NULL) :parent(p),num(0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Nine[i][j] = n[i][j];
            }
        }
        this->x = -1;
        this->y = -1;
        if ((0 <= x && x < 3) && (0 <= y && y < 3)) {
            if (Nine[x][y] == 0) {
                this->x = x;
                this->y = y;
            }
        }
    }

    bool operator ==(short int n[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (n[i][j] != Nine[i][j])
                    return false;
            }
        }
        return true;
    }

    bool operator ==(NineState* ano) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (ano->Nine[i][j] != Nine[i][j])
                    return false;
            }
        }
        return true;
    }


    bool isAncestor(short int n[3][3]) {
        NineState* curr = this->parent;
        while (curr != NULL) {
            if (*curr == n)
                return true;
            curr = curr->parent;
        }
        return false;
    }

    NineState* getParent() {
        return parent;
    }

    void setNum(unsigned long long int n) {
        num = n;
    }

    void setParent(NineState* p) {
        parent = p;
    }

    bool generate(std::vector<NineState*>& M) {
        short int temp[3][3];
        bool succ = false;
        NineState* son = NULL;
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
                    son = new NineState(temp, x - 1, y, this);
                    M.push_back(son);
                    children[c]=son;
                    c++;
                    succ = true;
                }
                temp[x - 1][y] = temp[x][y];
                temp[x][y] = 0;
            }
            if (x < 2) {
                temp[x][y] = temp[x + 1][y];
                temp[x + 1][y] = 0;
                if (!isAncestor(temp)) {
                    son = new NineState(temp, x + 1, y, this);
                    M.push_back(son);
                    children[c] = son;
                    c++;
                    succ = true;
                }
                temp[x + 1][y] = temp[x][y];
                temp[x][y] = 0;
            }
            if (y > 0) {
                temp[x][y] = temp[x][y-1];
                temp[x][y-1] = 0;
                if (!isAncestor(temp)) {
                    son = new NineState(temp, x, y - 1, this);
                    M.push_back(son);
                    children[c] = son;
                    c++;
                    succ = true;
                }
                temp[x][y-1] = temp[x][y];
                temp[x][y] = 0;
            }
            if (y < 2) {
                temp[x][y] = temp[x][y+1];
                temp[x][y+1] = 0;
                if (!isAncestor(temp)) {
                    son = new NineState(temp, x, y + 1, this);
                    M.push_back(son);
                    children[c] = son;
                    c++;
                    succ = true;
                }
                temp[x][y+1] = temp[x][y];
                temp[x][y] = 0;
            }
        }
        return succ;
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