//
// Created by rjx on 16-11-18.
//
#ifndef LIST_CPP
#define LIST_CPP

#include "Point.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#define MAX_SIZE 100
using namespace std;

class ListG {
private:
    int getPointOrderByData(string data) {
        for (int i = 0; i < order; ++i) {
            if(point[i].getData() == data) return i;
        }
        return -1;
    }
    void initVisited() {
        memset(visited, 0, sizeof(visited));
    }
    void initGraph() {
        order = 0;
        memset(matrix, 0, sizeof(matrix));
    }

    // part 代表图的第几部分
    void DFS(int num, int part) {
        if (allVisited() || num >= order) return;
        if (!visited[num]) {
            visited[num] = 1;
            cout << point[num].getData();
            list<string> fNext = point[num].getNext();
            for (list<string>::iterator it = fNext.begin(); it != fNext.end(); ++it) {
                int temp = getPointOrderByData(*it);
                if (!visited[temp]) DFS(temp,part);
            }
        }
        // 实现不连通图的遍历
        if (part == num && !allVisited()) {
            DFS(num+1, part+1);
        }
    }
    bool allVisited() {
        for (int i = 0; i < order; ++i) {
            if (visited[i] == 0) return false;
        }
        return true;
    }
    void BFS(int num) {
        queue<int> q;
        q.push(num);
        while (!allVisited()) {
            while(q.size()) {
                int f = q.front();
                list<string> fNext = point[f].getNext();
//                cout <<"###" << fNext.size() << "+++" << f << endl;
                cout << point[f].getData();
                visited[f] = 1;
//                cout << "POP" << point[f].getData() << "Fne" << fNext.size() << endl;
                q.pop();
                for (list<string>::iterator it = fNext.begin(); it != fNext.end(); ++it) {
                    int temp = getPointOrderByData(*it);
//                    cout << "Get data" << *it << "GET temp=" << temp << endl;
                    if (!visited[temp]) {
                        visited[temp] = 1;
//                        cout << "PUSH" << point[temp].getData() << endl;
                        q.push(temp);
                    }
                }
            }
            for (int i = 0; i < order; ++i) {
                if (visited[i] == false) q.push(i);
            }
        }
    }
    bool visited[MAX_SIZE];
    Point point[MAX_SIZE];
    int matrix[MAX_SIZE][MAX_SIZE];
    int order;
public:
    ListG() {
        initGraph();
    }
    ~ListG() {}
    bool addPoint(Point p) {
        if(order + 1  <= MAX_SIZE) {
            p.setOrder(order);
            point[order++] = p;
            return true;
        } else {
            return false;
        }
    }
    bool createrAnEdge(string p1, string p2) {
        int o1 = getPointOrderByData(p1);
        int o2 = getPointOrderByData(p2);
        if (o1 == -1 || o2 == -1) return false;
        point[o1].addNext(p2);
        point[o2].addNext(p1);
        return true;
    }
    void travel(string op) {
        if (op == "D") {
            initVisited();
            DFS(0,0);
        } else {
            initVisited();
            BFS(0);
        }
    }
};

#endif
