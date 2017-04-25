#include "Family_tree_service.hpp"
Familytree_service::Familytree_service() {}
Familytree_service::~Familytree_service() {}
void Familytree_service::StartFamilytree() {
	instance.readFromFile();
}
void Familytree_service::quitFamilytree() {
	instance.sync();
}
bool Familytree_service::Addwife(string ancestor, string hunband_name, const People & wife) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].AddWife(hunband_name, wife)) {
				instance.set_family_instance(family_tree);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
bool Familytree_service::Addchild(string ancestor, string father_name, string mother_name, const People & child) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].Addchild(father_name, mother_name, child)) {
				instance.set_family_instance(family_tree);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
bool Familytree_service::DeletePerson(string ancestor, string person_name) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].DeletePerson(person_name)) {
				instance.set_family_instance(family_tree);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
bool Familytree_service::judge_exist(string ancestor) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) return true;
	}
	return false;
}
bool Familytree_service::SetLive(string ancestor, string people_name) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].SetLive(people_name)) {
				instance.set_family_instance(family_tree);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
bool Familytree_service::SetMarriage(string ancestor, string people_name) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].SetMarriage(people_name)) {
				instance.set_family_instance(family_tree);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
bool Familytree_service::QueryPerson(string ancestor, string person_name, void(*visite1)(Person*, int), void(*visite2)(Person*)) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			if (family_tree[i].QueryPerson(person_name, visite1, visite2)) return true;
			else return false;
		}
	}
	return false;
}
void Familytree_service::display_tree(string ancestor, void(*visite1)(Person*, int), void(*visite2)(Person*), void(*visite3)(int)) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			family_tree[i].display_tree(visite1, visite2, visite3);
			break;
		}
	}
}
bool Familytree_service::FamilyLogIn(string ancestor) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor) {
			return true;
		}
	}
	return false;
}
bool Familytree_service::FamilyRegister(const People& ancestor) {
	auto family_tree = instance.get_family_instance();
	auto len = family_tree.size();
	for (auto i = 0; i < len; ++i) {
		if (family_tree[i].getroot()->person.get_name() == ancestor.get_name()) {
			return false;
		}
	}
	Person* newPerson = new Person(ancestor);
	Family_tree newFamily(newPerson);
	family_tree.push_back(newFamily);
	instance.set_family_instance(family_tree);
	return true;
}