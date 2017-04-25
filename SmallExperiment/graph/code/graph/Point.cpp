//
// Created by rjx on 16-11-17.
//
#ifndef POINT_CPP
#define POINT_CPP

#include <iostream>
#include <string>
#include <list>
using namespace std;

class Point
{
public:
	Point() {
		order = 0;
		weight = 0;
		data = "";
		next.clear();
	}
	void setOrder(int o) {
		order = o;
	}
	void setWeight(int w) {
		weight = w;
	}
	void setData(string d) {
		data = d;
	}
	void addNext(string nextData) {
		next.push_back(nextData);
//		cout << "@#@#@$@#$" <<next.size() <<endl;

	}
	list<string> getNext() const {
		return next;
	}

    // in this test do not use this fun
	bool deleteNext(string NextName) {
		for (list<string>::iterator it = next.begin(); it != next.end(); it++) {
			if (*it == NextName) {
				// next.remove(it);
				next.remove(*it);
				return true;
			}
		}
		return false;
	}
	int getOrder() const {
		return order;
	}
	int getWeight() const {
		return weight;
	}
	string getData() const {
		return data;
	}
	~Point() {}
private:
	int order;
	int weight;
	string data;
	list<string> next;
};

#endif