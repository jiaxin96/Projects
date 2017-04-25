//  Person.hpp
//  Family Tree
//
//  Created by Yoshi Park 16/11/16.
//  Copyright  2016 Yoshi Park. All rights reserved.
//
#include <string>
#include "Date.hpp"
#ifndef PERSON_HPP
#define PERSON_HPP
using namespace std;
class People {
private:
	string name;
	string spouse_name;
	string father_name;
	string mother_name;
	int level;
	int sex;  // zero denote man, one denote woman
	bool marriage;
	bool live;
	Date birth;
	Date death;
public:
	People(string _father_name, string _mother_name, string _name, string _spouse_name, int _level, int _sex, bool _marriage, bool _live, const Date & _birth, const Date & _death);
	People(const People & _person);
	void set_name(string _name);
	string get_name() const;
	void set_spouse_name(string _name);
	string get_spouse_name() const;
	void set_father_name(string _name);
	string get_father_name() const;
	void set_mother_name(string _name);
	string get_mother_name() const;
	void set_level(int _level);
	int get_level() const;
	void set_sex(int _sex);
	int get_sex() const;
	void set_marriage(bool _marriage);
	bool get_marriage() const;
	void set_live(bool _live);
	bool get_live() const;
	void set_birth(const Date& _birth);
	Date get_birth() const;
	void set_death(const Date& _death);
	Date get_death() const;
};
struct Person {
	People person;
	Person* left;
	Person* right;
	Person(const People & _person, Person * _left = NULL, Person * _right = NULL) :person(_person), left(_left), right(_right) {}
};
#endif#pragma once
