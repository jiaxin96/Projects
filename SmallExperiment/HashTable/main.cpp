#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "hashTable.cpp"
using namespace std;


bool getoperation(int & op) {
	cout << "Please select your operation\n";
	cout << "1.insert 2.queryByName 3.delete 4.showAllStudent 5.Using data.txt to init 6.getSize 7.exit\n";
	cin >> op;
	if (op == 7) return false;
	if (op > 7 || op < 1) {
		cout << "Please input right number\n";
		return getoperation(op);
	}
	return true;
}

void excu(int op, hashTable & table) {
	if (op == 1) {
		int total = 0;
		cout << "Please input the total student number :";
		cin >> total;
		for (int i = 0; i < total; ++i)
		{
			cout << "No." << i + 1 << ":" << endl;
			string name, sid, tell, grend;
			cout << "Name:\n";
			cin >> name;
			cout << "Student id:\n";
			cin >> sid;
			cout << "Male or Famle\n";
			cin >> grend;
			cout << "Student tell number:\n";
			cin >> tell;
			if(table.insert(student(name, sid, grend, tell))) {
				cout << "insert " << name << " succeed\n";
			} else {
				cout << "insert " << name << " fail\n";
			}
		}
		cout << "Insert end\n";
	} else if (op == 2) {
		cout << "Please input the student's name:\n";
		string name;
		cin >> name;
		if (table.query(name) < 0) { 
			cout << "No this student\n";
		} else {
			cout << "The student's information is shown as" << ":\n" << table.getStu(table.query(name)).name << " " <<
			table.getStu(table.query(name)).sid << " "
			<< table.getStu(table.query(name)).grend << " " << table.getStu(table.query(name)).tell << endl;
			cout << "This query cost " << table.getQueryTimes() << " times compare\n";
		}
	} else if (op == 3) {
		cout << "Please input the student's name:";
		string name;
		cin >> name;
		if(table.deleteNode(name)) {
			cout << "Delete succeed\n";
		} else {
			cout << "Delete fail\n";
		}
	} else if (op == 4) {
		if (table.getSize()) {
			cout << "The student's information is shown as\n";
			table.show();
		} else {
			cout << "No student!!\n";
		}
	} else if (op == 5) {
		cout << "Start get data from file\n";
		ifstream input("data.txt");
		if (!input) {
			cout << "File con't be opened\n";
		}
		string data, name, sid, grend, tell;
		while (getline(input, data)) {
			istringstream istr (data);
			istr >> name >> sid >> grend >> tell;
			table.insert(student(name, sid, grend, tell));
		}
		input.close();
		cout << "File close\n";
	} else if (op == 6) {
		cout << "The total student number is " << table.getSize() << endl;
	}
}


void test() {
	cout << "Start test\n";
	int op;
	hashTable table;
	while (getoperation(op)) excu(op, table);
	cout << "test end\n";
}


int main(int argc, char const *argv[])
{
	
	test();

	return 0;
}