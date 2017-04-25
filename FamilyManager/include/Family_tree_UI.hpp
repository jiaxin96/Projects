#ifndef FAMILY_TREE_UI_HPP
#define FAMILY_TREE_UI_HPP
#include <string>
#include <iostream>
#include "Family_tree_service.hpp"
using namespace std;
class Familytree_UI {
private:
	string m_userName;
	Familytree_service m_familytreeService;
public:
	Familytree_UI();
	void StartFamilytree();
	void OperationLoop(void);
private:
	bool executeOperation(string t_operation);
	string getOperation();
	void FamilyLogIn();
	void FamilyRegister();
	void quitFamilytree();
	void FamilyLogOut();
	void DeletePerson();
	void get_married();
	void break_marriage();
	void addchild();
	void display_tree();
	void QueryPerson();
	static void visit_wife(Person*, int);
	static void visit_child(Person*);
	static void divide_genetation(int);
};
#endif