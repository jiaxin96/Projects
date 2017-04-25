#ifndef FAMILY_TREE_SERVICE_HPP
#define FAMILY_TREE_SERVICE_HPP
#include "Date.hpp"
#include "Family_tree.hpp"
#include "Person.hpp"
#include "Storage.hpp"
class Familytree_service {
private:
	Storage instance;
public:
	Familytree_service();
	~Familytree_service();
	void StartFamilytree();
	bool FamilyRegister(const People& ancestor);
	bool FamilyLogIn(string ancestor);
	void quitFamilytree();
	bool Addwife(string ancestor, string hunband_name, const People & wife);
	bool Addchild(string ancestor, string father_name, string mother_name, const People & child);
	bool DeletePerson(string ancestor, string person_name);
	bool SetLive(string ancestor, string people_name);
	bool SetMarriage(string ancestor, string people_name);
	void display_tree(string ancestor, void(*visite1)(Person*, int), void(*visite2)(Person*), void(*visite3)(int));
	bool QueryPerson(string ancestor, string person_name, void(*visite1)(Person*, int), void(*visite2)(Person*));
	bool judge_exist(string ancestor);
};
#endif