//
// Created by rjx on 16-11-17.
//
#ifndef MATRIX_CPP
#define MATRIX_CPP
#define MAX_SIZE 100
#include "Point.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;
class MatrixG
{
public:
	MatrixG() {
		initGraph();
	}
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
		if (o1 != -1 && o2 != -1) {
			matrix[o1][o2] = 1;

			matrix[o2][o1] = 1;

			return true;
		}
		else {
			return false;
		}
	}
	void initVisited() {
		memset(visited, 0, sizeof(visited));
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
	int getPointOrderByData(string data) {
		for (int i = 0; i < order; ++i) {
			if(point[i].getData() == data) return i;
		}
		return -1;
	}
	~MatrixG() {}
private:
	void initGraph() {
		order = 0;
		memset(matrix, 0, sizeof(matrix));
	}
	void DFS(int num, int part) {
		if (allVisited() || num >= order) return;
		if (!visited[num]) {
			visited[num] = 1;
			cout << point[num].getData();
			for (int i = 0; i < order; ++i) {
				if (i == num) continue;
				if (matrix[num][i] == 1 && !visited[i]) DFS(i, part);
			}
		}
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
				cout << point[f].getData();
				visited[f] = 1;
				q.pop();
				for (int i = f + 1; i < order; ++i) {
					if (!visited[i] && matrix[f][i]) {
                        visited[i] = 1;
                        q.push(i);
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
};

#endif