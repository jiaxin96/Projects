#include <vector>
#include <string>
#include <list>
#include <iostream>
/**
*哈希函数为 
*(名字拼音的末尾的字母表序号*10+开头的字母序号) mod Table_SIZE.
*
*
*
*/
using namespace std;

struct student
{
	string name;
	string sid;
	string grend;
	string tell;
	student(string n = "#", string s = "#", string g="#", string t="#") :
	name(n), sid(s), grend(g), tell(t) {}
};
#define TABLE_SIZE 100

class hashTable
{
public:
	hashTable() {
		currentSize = 0;
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			storage.push_back(student());
		}
	}
	~hashTable() {}
	hashTable(std::vector<student> v) {
		currentSize = 0;
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			storage.push_back(student());
		}
		for (int i = 0; i < v.size(); ++i)
		{
			insert(v[i]);
		}
	}

	bool insert(student stu) {
		string name = stu.name;
		if (name == "" || currentSize + 1 >= TABLE_SIZE) return false;
		char s = name[0];
		char e = name[name.length() - 1];
		int addr = haseFun(s, e);
		if (query(name) >= 0) return false;
		
		while (storage[addr].name != "#") addr = (addr+1)%TABLE_SIZE;
		storage[addr] = stu;
		currentSize++;
		return true;
	}

	int query(string name) {
		querytimes = 0;
		if (name == "") return -1;
		int initAdd = haseFun(name[0], name[name.length() - 1]);
		if (storage[initAdd].name == name) {
			querytimes++;
			return initAdd;
		}
		int tempAdd = (initAdd + 1) % TABLE_SIZE;
		while(tempAdd != initAdd) {
			if (storage[tempAdd].name == name) {
				querytimes++;
				return tempAdd;
			}
			querytimes++;
		    tempAdd = (tempAdd + 1) % TABLE_SIZE;
		}
		return -1;
	}

	student getStu(int pos) {
		return storage[pos];
	}

	bool deleteNode(string name) {
		if (query(name) < -1) return false;
		storage[query(name)] = student();     
		currentSize--;
		return true;
	}

	void show() {
		int num = 1;
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			if (storage[i].name != "#") 	{
				cout << (num++) << ": " << storage[i].name << " " <<
				storage[i].sid << " "
				<< storage[i].grend << " " << storage[i].tell << endl;
			}
		}
	}
	int getSize() {
		return currentSize;
	}
	int getQueryTimes() {
		return querytimes;
	}
private:
	std::vector<student> storage;
	int currentSize;
	int querytimes;
	int haseFun(char s, char e) {
		if (s >= 'A' && s <= 'Z') s = 'a' + s - 'A';
		
		if (e >= 'A' && e <= 'Z') s = 'a' + e - 'A';
		
		int ep = (e-'a')*10;
		int sp = (s-'a');

		return (ep+sp)%TABLE_SIZE;
	}
};