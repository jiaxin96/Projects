#include "Family_tree_UI.hpp"
static auto interface = 0;
Familytree_UI::Familytree_UI() {
	StartFamilytree();
	m_familytreeService.StartFamilytree();
}
void Familytree_UI::StartFamilytree() {
	cout << endl << endl << endl;
	if (interface == 0) {
		cout << "-------------------- Familytree -----------------------" << endl;
		cout << "Action :" << endl;
		cout << "l    - log in Familytree by user name" << endl;
		cout << "r    - register an Familytree account" << endl;
		cout << "q    - quit Familytree" << endl;
		cout << "---------------------------------------------------" << endl << endl;
		cout << "Familytree :  ~#";
	}
	else {
		cout << "-------------------- Familytree --------------------" << endl;
		cout << "Action :" << endl;
		cout << "o   - log out Familytree account" << endl;
		cout << "dp  - delete person" << endl;
		cout << "dt  - display family tree" << endl;
		cout << "gm  - get married" << endl;
		cout << "bm  - break marriage" << endl;
		cout << "ac  - add child" << endl;
		cout << "sp  - show person infomation" << endl;
		cout << "------------------------------------------------" << "\n\n";
		cout << "Familytree@" << m_userName << " :  ";
	}
}
string Familytree_UI::getOperation() {
	string selection;
	cin >> selection;
	return selection;
}
void Familytree_UI::OperationLoop(void) {
	executeOperation(getOperation());
}
bool Familytree_UI::executeOperation(string op) {
	if (interface == 0) {
		if (op == "l") { FamilyLogIn(); }
		else if (op == "r") { FamilyRegister(); }
		else if (op == "q") { quitFamilytree(); }
		else {
			cout << "Wrong Selection!\n";
			StartFamilytree();
			OperationLoop();
		}
	}
	else {
		if (op == "o") { FamilyLogOut(); }
		else if (op == "dp") { DeletePerson(); }
		else if (op == "dt") { display_tree(); }
		else if (op == "gm") { get_married(); }
		else if (op == "bm") { break_marriage(); }
		else if (op == "ac") { addchild(); }
		else if (op == "sp") { QueryPerson(); }
		else {
			cout << "Wrong Selection!\n";
			StartFamilytree();
			OperationLoop();
		}
	}
	return true;
}
void Familytree_UI::FamilyLogIn() {
	cout << endl;
	cout << "[log in] [user name]" << endl;
	cout << "[log in] ";
	cin >> m_userName;
	if (m_familytreeService.FamilyLogIn(m_userName)) {
		cout << "[log in] succeed!" << endl;
		interface = 1;
	}
	else {
		cout << "[log in] log in fail!" << endl;
		interface = 0;
	}
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::FamilyRegister() {
	string username, birthday, deathday;
	bool live = false;
	int _live;
	cout << endl;
	cout << "[register] [user name] [user birthday] [user live]" << endl;
	cout << "[register] ";
	cin >> username;
	cin >> birthday;
	cin >> _live;
	if (_live == 0) {
		cout << "[register] [user deathday]" << endl;
		cout << "[register] ";
		cin >> deathday;
		live = false;
	}
	else {
		live = true;
	}
	Date birth = Date::stringToDate(birthday);
	Date death = Date::stringToDate(deathday);
	People newUser("unknown", "unknown", username, "unknown", 0, 0, false, live, birth, death);
	if (m_familytreeService.FamilyRegister(newUser)) {
		cout << "[register] succeed!\n";
	}
	else {
		cout << "[register] register fail!\n";
	}
	interface = 0;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::quitFamilytree() {
	m_familytreeService.quitFamilytree();
}
void Familytree_UI::FamilyLogOut() {
	cout << endl;
	cout << "[Log Out]:succeed!\n";
	interface = 0;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::DeletePerson() {
	string peoplename;
	cout << "[Delete Person] [peoplename] " << endl;
	cout << "[Delete Person] ";
	cin >> peoplename;
	if (m_familytreeService.DeletePerson(m_userName, peoplename)) {
		cout << endl;
		cout << "[Delete Person]:Delete Person succeed!\n";
	}
	else {
		cout << endl;
		cout << "[Delete Person]:Delete Person failed!\n";
	}
	interface = m_familytreeService.judge_exist(m_userName) ? 1 : 0;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::get_married() {
	string wife_name, spouse_name, father_name, mother_name, birthday, deathday;
	int _live;
	bool live = false;
	cout << "[Get Married] [wife name] [husband name] [wife's father name] [wife's mother name] [wife's birthday] [wife's live]" << endl;
	cout << "[Get Married] ";
	cin >> wife_name;
	cin >> spouse_name;
	cin >> father_name;
	cin >> mother_name;
	cin >> birthday;
	cin >> _live;
	Date birth = Date::stringToDate(birthday);
	Date death;
	if (_live == 0) {
		cout << "[Get Married] [wife's deathday]" << endl;
		cout << "[Get Married] ";
		cin >> deathday;
		death = Date::stringToDate(deathday);
		live = false;
	}
	else {
		live = true;
	}
	People wife(father_name, mother_name, wife_name, spouse_name, 0, 1, false, live, birth, death);
	if (m_familytreeService.Addwife(m_userName, spouse_name, wife)) {
		cout << endl;
		cout << "[Get Married] Get Married Succeed!" << endl;
	}
	else {
		cout << endl;
		cout << "[Get Married] Get Married Failed!" << endl;
	}
	interface = 1;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::break_marriage() {
	string husband_name;
	cout << "[Break Marriage] [husband_name]" << endl;
	cout << "[Break Marriage] ";
	cin >> husband_name;
	if (m_familytreeService.SetMarriage(m_userName, husband_name)) {
		cout << endl;
		cout << "[Break Married] Break Married Succeed!" << endl;
	}
	else {
		cout << endl;
		cout << "[Break Married] Break Married Failed!" << endl;
	}
	interface = 1;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::addchild() {
	string child_name, father_name, mother_name, birthday, deathday;
	int sex, _live;
	bool live = false;
	Date death;
	cout << "[Add Child] [child name] [father name] [mother name] [birthday] [sex] [live]" << endl;
	cout << "[Add Child] ";
	cin >> child_name;
	cin >> father_name;
	cin >> mother_name;
	cin >> birthday;
	cin >> sex;
	cin >> _live;
	if (_live == 0) {
		live = false;
		cout << "[Add Child] [deathday]" << endl;
		cout << "[Add Child] ";
		cin >> deathday;
		death = Date::stringToDate(deathday);
	}
	Date birth = Date::stringToDate(birthday);
	People child(father_name, mother_name, child_name, "unknown", 0, sex, false, live, birth, death);
	if (m_familytreeService.Addchild(m_userName, father_name, mother_name, child)) {
		cout << endl;
		cout << "[Add Child] Add Child Succeed!" << endl;
	}
	else {
		cout << endl;
		cout << "[Add Child] Add Child Failed!" << endl;
	}
	interface = 1;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::visit_wife(Person* wife, int present) {
	if (present == 1) {
		cout << "The present wife:[";
	}
	else {
		cout << "The former wife:[";
	}
	cout << "name:" << wife->person.get_name() << ",";
	cout << "husband name:" << wife->person.get_spouse_name() << ", ";
	cout << "Father name:" << wife->person.get_father_name() << ", ";
	cout << "Mother name:" << wife->person.get_mother_name() << ", ";
	cout << "Genaration:" << wife->person.get_level() << ", ";
	cout << "Sex:" << wife->person.get_sex() << ", ";
	cout << "Marriage:" << ((wife->person.get_marriage() == true) ? 'T' : 'F') << ", ";
	cout << "Live:" << ((wife->person.get_live() == true) ? 'T' : 'F') << ", ";
	cout << "Birthday:" << Date::dateToString(wife->person.get_birth());
	if (wife->person.get_live() == false) {
		cout << ", ";
		cout << "Deathday:" << Date::dateToString(wife->person.get_death());
	}
	cout << "]\n";
}
void Familytree_UI::visit_child(Person* child) {
	cout << "man:[";
	cout << "name:" << child->person.get_name() << ",";
	cout << "spouse name:" << child->person.get_spouse_name() << ", ";
	cout << "Father name:" << child->person.get_father_name() << ", ";
	cout << "Mother name:" << child->person.get_mother_name() << ", ";
	cout << "Genaration:" << child->person.get_level() << ", ";
	cout << "Sex:" << child->person.get_sex() << ", ";
	cout << "Marriage:" << ((child->person.get_marriage() == true) ? 'T' : 'F') << ", ";
	cout << "Live:" << ((child->person.get_live() == true) ? 'T' : 'F') << ", ";
	cout << "Birthday:" << Date::dateToString(child->person.get_birth());
	if (child->person.get_live() == false) {
		cout << ", ";
		cout << "Deathday:" << Date::dateToString(child->person.get_death());
	}
	cout << "]\n";
}
void Familytree_UI::divide_genetation(int generation) {
	cout << "------------------------------------------------------------" << endl;
	cout << "The Genaration of " << generation << ": " << endl;
}
void Familytree_UI::display_tree() {
	m_familytreeService.display_tree(m_userName, Familytree_UI::visit_wife, Familytree_UI::visit_child, Familytree_UI::divide_genetation);
	interface = 1;
	StartFamilytree();
	OperationLoop();
}
void Familytree_UI::QueryPerson() {
	string person;
	cout << "[Query Person]: [person name]" << endl;
	cout << "[Query Person]: ";
	cin >> person;
	if (!m_familytreeService.QueryPerson(m_userName, person, Familytree_UI::visit_wife, Familytree_UI::visit_child)) {
		cout << "[Query Person]: Query Person failed!" << endl;
	}
	interface = 1;
	StartFamilytree();
	OperationLoop();
}