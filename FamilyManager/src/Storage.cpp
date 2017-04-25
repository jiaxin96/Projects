#include "Storage.hpp"
Storage::Storage()  {}
bool Storage::readFromFile(void) {
	std::ifstream familytreein("data/users.txt");
	if (familytreein.fail()) return false;
	if (!familytreein.good()) return false;
	string person_info;
	vector<Person*> preorder;
	vector<Person*> inorder;
	bool is_pre = true;
	bool next_family = false;
	while (!familytreein.eof()) {
		getline(familytreein, person_info);
		if (person_info == "*") {
			is_pre = false;
		}
		else if (person_info == "#") {
			Family_tree instance(preorder, inorder);
			family_instance.push_back(instance);
			preorder.clear();
			inorder.clear();
		}
		else {
			string name, spouse_name, father_name, mother_name;
			int level = 0, sex = 0;
			bool marriage = false, live = false;
			Date birth, death;
			string temp;
			int count = 0;
			while (!person_info.empty()) {
				if (person_info[0] != ' ') {
					temp += person_info[0];
				}
				else {
					if (count == 0) {
						name = temp;
					}
					else if (count == 1) {
						spouse_name = temp;
					}
					else if (count == 2) {
						father_name = temp;
					}
					else if (count == 3) {
						mother_name = temp;
					}
					else if (count == 4) {
						level = stoi(temp);
					}
					else if (count == 5) {
						sex = stoi(temp);
					}
					else if (count == 6) {
						if (stoi(temp) == 1) {
							marriage = true;
						}
						else {
							marriage = false;
						}
					}
					else if (count == 7) {
						if (stoi(temp) == 1) {
							live = true;
						}
						else {
							live = false;
						}
					}
					else if (count == 8) {
						birth = Date::stringToDate(temp);
					}
					else {
						death = Date::stringToDate(temp);
					}
					count++;
					temp.clear();
				}
				person_info.erase(0, 1);
			}
			death = Date::stringToDate(temp);
			People people(father_name, mother_name, name, spouse_name, level, sex, marriage, live, birth, death);
			Person* _temp = new Person(people);
			if (is_pre) {
				preorder.push_back(_temp);
			}
			else {
				inorder.push_back(_temp);
			}
		}
	}
}
bool Storage::writeToFile(void) {
	std::ofstream familytreeout("data/users.txt");
	if (!familytreeout.good()) return false;
	if (familytreeout.fail()) return false;
	auto len = family_instance.size();
	for (auto i = 0; i < len; ++i) {
		vector<Person*> preorder;
		Family_tree::PreOrder(preorder, family_instance[i].getroot());
		auto pre_len = preorder.size();
		for (auto i = 0; i < pre_len; ++i) {
			familytreeout << preorder[i]->person.get_name() << " ";
			familytreeout << preorder[i]->person.get_spouse_name() << " ";
			familytreeout << preorder[i]->person.get_father_name() << " ";
			familytreeout << preorder[i]->person.get_mother_name() << " ";
			familytreeout << preorder[i]->person.get_level() << " ";
			familytreeout << preorder[i]->person.get_sex() << " ";
			familytreeout << preorder[i]->person.get_marriage() << " ";
			familytreeout << preorder[i]->person.get_live() << " ";
			familytreeout << Date::dateToString(preorder[i]->person.get_birth()) << " ";
			familytreeout << Date::dateToString(preorder[i]->person.get_death()) << "\n";
		}
		familytreeout << "*\n";
		vector<Person*> inorder;
		Family_tree::InOrder(inorder, family_instance[i].getroot());
		auto in_len = inorder.size();
		for (auto i = 0; i < pre_len; ++i) {
			familytreeout << inorder[i]->person.get_name() << " ";
			familytreeout << inorder[i]->person.get_spouse_name() << " ";
			familytreeout << inorder[i]->person.get_father_name() << " ";
			familytreeout << inorder[i]->person.get_mother_name() << " ";
			familytreeout << inorder[i]->person.get_level() << " ";
			familytreeout << inorder[i]->person.get_sex() << " ";
			familytreeout << inorder[i]->person.get_marriage() << " ";
			familytreeout << inorder[i]->person.get_live() << " ";
			familytreeout << Date::dateToString(inorder[i]->person.get_birth()) << " ";
			familytreeout << Date::dateToString(inorder[i]->person.get_death()) << "\n";
		}
		familytreeout << "#\n";
	}
	familytreeout.close();
	return true;
}
Storage::~Storage() {}
void Storage::createFamily(const People & people) {
	Person* temp = new Person(people);
	Family_tree current(temp);
	family_instance.push_back(current);
}
bool Storage::sync(void) {
	return writeToFile();
}
vector<Family_tree>& Storage::get_family_instance() {
	return family_instance;
}
void Storage::set_family_instance(vector<Family_tree> & newvec) {
	if (!family_instance.empty()) {
		family_instance.clear();
	}
	for (auto i = 0; i < newvec.size(); ++i) {
		if (newvec[i].clean == false) {
			family_instance.push_back(newvec[i]);
		}
	}
}