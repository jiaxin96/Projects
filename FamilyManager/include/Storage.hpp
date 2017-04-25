#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <fstream>
#include <vector>
#include <string>
#include "Person.hpp"
#include "Date.hpp"
#include "Family_tree.hpp"
using namespace std;

class Storage {
private:
	vector<Family_tree> family_instance;
public:
	Storage();
	bool readFromFile(void);
	bool writeToFile(void);
	~Storage();
	void createFamily(const People & people);
	bool sync(void);
	vector<Family_tree>& get_family_instance();
	void set_family_instance(vector<Family_tree> &);
};
#endif#pragma once
