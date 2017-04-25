#include "Family_tree.hpp"
Family_tree::Family_tree() :root(NULL), clean(false) {}
Family_tree::Family_tree(const Family_tree & other) {
	if (this != &other) {
		root = NULL;
		root = copyPerson(other.getroot(), root);
	}
	clean = false;
}
Family_tree::Family_tree(Person*  other) {
	if (other != NULL) {
		root = copyPerson(other, root);
	}
	clean = false;
}


Person* recursionBuild(const vector<Person*>& preorder,
	unsigned long preLeft,
	unsigned long preRight,
	const vector<Person*>& inorder,
	unsigned long inLeft,
	unsigned long inRight) {
	if (preLeft > preRight || preRight == preorder.size() ||
		inLeft > inRight || inRight == inorder.size())
		return NULL;

	unsigned long i = 0;

	Person* node = new Person(preorder[preLeft]->person);

	for (i = inLeft; i <= inRight; i++) {
		if (inorder[i]->person.get_name() == node->person.get_name()) {
			break;
		}
	}

	node->left = recursionBuild(preorder,
		preLeft + 1, preLeft + i - inLeft,
		inorder,
		inLeft, i - 1);
	node->right = recursionBuild(preorder,
		preLeft + i - inLeft + 1, preRight,
		inorder,
		i + 1, inRight);

	return node;
}
Family_tree::Family_tree(const vector<Person*>& preorder, const vector<Person*>& inorder) {
	root = NULL;
	clean = false;
	unsigned long preSize = preorder.size();
	unsigned long inSize = inorder.size();
	if (preSize == 0 || preSize != inSize) {
		return;
	}
	root = recursionBuild(preorder, 0, preSize - 1,
		inorder, 0, inSize - 1);
}
Family_tree::~Family_tree() {
	clear(getroot());
}
Person* Family_tree::copyPerson(Person * oldPerson, Person * newPerson) {
	if (oldPerson == NULL) {
		newPerson = NULL;
		return newPerson;
	}
	newPerson = new Person(oldPerson->person);
	newPerson->left = copyPerson(oldPerson->left, newPerson->left);
	newPerson->right = copyPerson(oldPerson->right, oldPerson->right);
	return newPerson;
}
Person* Family_tree::getroot() const { return root; }
void Family_tree::clear(Person* _root) {
	if (clean == false) {
		std::queue<Person*> queue;
		if (_root != NULL) {
			queue.push(_root);
		}
		while (!queue.empty()) {
			Person * temp = queue.front();
			queue.pop();
			if (temp->left != NULL)
				queue.push(temp->left);
			if (temp->right != NULL)
				queue.push(temp->right);
			delete temp;
		}
		if (_root == root) clean = true;
	}
}
Person* Family_tree::SearchPersonByname(Person* & _root, string _name) {
	if (_root != NULL) {
		if (_root->person.get_name() == _name) {
			return _root;
		}
		else {
			Person* search_left = NULL;
			Person* search_right = NULL;
			if (_root->left != NULL) search_left = SearchPersonByname(_root->left, _name);
			if (_root->right != NULL) search_right = SearchPersonByname(_root->right, _name);
			return (search_left == NULL) ? search_right : search_left;
		}
	}
	else {
		return NULL;
	}
}
bool Family_tree::AddWife(string husband_name, const People & wife) {
	People m_wife = wife;
	Person* husband = SearchPersonByname(root, husband_name);
	if (husband == NULL) {
		return false;
	}
	else {
		if (husband->person.get_marriage() == true || m_wife.get_birth() > husband->person.get_death()) {
			return false;
		}
		else {
			Person* current = husband;
			while (current->left != NULL) {
				current = current->left;
				if (current->person.get_name() == wife.get_name()) return false;
			}
			m_wife.set_level(husband->person.get_level());
			m_wife.set_marriage(true);
			current->left = new Person(m_wife);
			current->left->person.set_spouse_name(husband_name);
			husband->person.set_spouse_name(m_wife.get_name());
			husband->person.set_marriage(true);
			return true;
		}
	}
}
Person* Family_tree::find_wife(string husband_name, string wife_name) {
	Person* husband = SearchPersonByname(root, husband_name);
	if (husband == NULL || husband->person.get_marriage() == false) {
		return NULL;
	}
	else {
		Person* current = husband->left;
		while (current != NULL) {
			if (current->person.get_name() == wife_name) return current;
			current = current->left;
		}
		return NULL;
	}
}
bool Family_tree::Addchild(string father_name, string mother_name, const People & child) {
	People children = child;
	Person* mother = find_wife(father_name, mother_name);
	if (mother == NULL) {
		return false;
	}
	else {
		Person* current = mother;
		while (current->right != NULL) {
			current = current->right;
			if (current->person.get_name() == child.get_name()) return false;
		}
		children.set_level(mother->person.get_level() + 1);
		current->right = new Person(children);
		return true;
	}
}
bool Family_tree::SetLive(string people_name) {
	Person* people = SearchPersonByname(root, people_name);
	if (people == NULL) {
		return false;
	}
	else {
		people->person.set_live(false);
		return true;
	}
}
bool Family_tree::SetMarriage(string people_name) {
	Person* people = SearchPersonByname(root, people_name);
	if (people == NULL || people->left == NULL) {
		return false;
	}
	else {
		people->person.set_marriage(false);
		people->person.set_spouse_name("unknown");
		Person* wife = people->left;
		while (wife != NULL) {
			wife->person.set_marriage(false);
			wife->person.set_spouse_name("unknown");
			wife = wife->left;
		}
		return true;
	}
}
void Family_tree::show_wife(Person* & husband, void(*visite)(Person*, int)) {
	if (husband != NULL) {
		Person* current = husband->left;
		while (current != NULL && current->left != NULL) {
			visite(current, 0);
			current = current->left;
		}
		if (current != NULL) {
			if (husband->person.get_marriage() == true && husband->person.get_live() == true) {
				visite(current, 1);
			}
			else {
				visite(current, 0);
			}
		}
	}
}
void Family_tree::get_child(Person* & father, queue<Person*> & queue_node) {
	Person* current = father->left;
	while (current != NULL) {
		Person* start = current->right;
		while (start != NULL) {
			queue_node.push(start);
			start = start->right;
		}
		current = current->left;
	}
}
void Family_tree::show_child(Person* & husband, void(*visite)(Person*)) {
	Person* wife = husband->left;
	while (wife != NULL) {
		Person* child = wife->right;
		while (child != NULL) {
			visite(child);
			child = child->right;
		}
		wife = wife->left;
	}
}
void Family_tree::display_tree(void(*visite1)(Person*, int), void(*visite2)(Person*), void(*visite3)(int)) {
	if (getroot() == NULL) {
		return;
	}
	else {
		int generation = 0;
		visite3(generation);
		Person* ancestor = getroot();
		queue<Person*> queue_node;
		queue_node.push(ancestor);
		while (!queue_node.empty()) {
			Person* current = queue_node.front();
			if (current->person.get_level() != generation) {
				generation = current->person.get_level();
				visite3(generation);
			}
			visite2(current);
			queue_node.pop();
			show_wife(current, visite1);
			get_child(current, queue_node);
		}
	}
}
bool Family_tree::QueryPerson(string person_name, void(*visite1)(Person*, int), void(*visite2)(Person*)) {
	Person* person = SearchPersonByname(root, person_name);
	if (person == NULL) {
		return false;
	}
	else {
		visite2(person);
		show_wife(person, visite1);
		show_child(person, visite2);
		return true;
	}
}

bool Family_tree::DeletePerson(string person_name) {
	Person* child = SearchPersonByname(root, person_name);
	Person* mother = SearchPersonByname(root, child->person.get_mother_name());
	if (mother == NULL) {
		if (child == NULL) return false;
		else {
			clear(getroot());
			return true;
		}
	}
	else {
		Person* child = mother->right;
		Person* prev = mother;
		while (child != NULL) {
			if (child->person.get_name() == person_name) {
				Person* delete_person = child;
				prev->right = child->right;
				delete_person->right = NULL;
				clear(delete_person);
				return true;
			}
			else {
				child = child->right;
				prev = prev->right;
			}
		}
		return false;
	}
}
void Family_tree::PreOrder(vector<Person*> & Prevector, Person* _root) {
	if (_root != NULL) {
		Prevector.push_back(_root);
		PreOrder(Prevector, _root->left);
		PreOrder(Prevector, _root->right);
	}
}
void Family_tree::InOrder(vector<Person*> & Invector, Person* _root) {
	if (_root != NULL) {
		InOrder(Invector, _root->left);
		Invector.push_back(_root);
		InOrder(Invector, _root->right);
	}
}