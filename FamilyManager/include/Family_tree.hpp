//  Family_tree.hpp
//  Family Tree
//
//  Created by Yoshi Park 16/11/16.
//  Copyright  2016 Yoshi Park. All rights reserved.
//
#ifndef FAMILY_TREE_HPP
#define FAMILY_TREE_HPP
#include <queue>
#include <vector>
#include "Date.hpp"
#include "Person.hpp"
using namespace std;
class Family_tree {
private:
	Person* root;
	Person* copyPerson(Person * oldPerson, Person * newPerson);
	Person* SearchPersonByname(Person* & _root, string _name);
	Person* find_wife(string husband_name, string wife_name);
	void show_wife(Person* & husband, void(*visite)(Person*, int));
	void show_child(Person* & husband, void(*visite)(Person*));
	void get_child(Person* & father, queue<Person*> & queue_node);
	void clear(Person* _root);
public:
	bool clean;
public:
	Family_tree();
	~Family_tree();
	Family_tree(const Family_tree & other);
	Family_tree(Person*  other);
	Family_tree(const vector<Person*>& preOrder, const vector<Person*>& inOrder);
	Person* getroot() const;
	bool AddWife(string husband_name, const People & wife);
	bool Addchild(string father_name, string mother_name, const People & child);
	bool DeletePerson(string person_name);
	bool SetLive(string people_name);
	bool SetMarriage(string people_name);
	void display_tree(void(*visite1)(Person*, int), void(*visite2)(Person*), void(*visite3)(int));
	bool QueryPerson(string person_name, void(*visite1)(Person*, int), void(*visite2)(Person*));
	static void PreOrder(vector<Person*> & Prevector, Person* _root);
	static void InOrder(vector<Person*> & Invector, Person* _root);
};
#endif