#include "Person.hpp"
People::People(string _father_name, string _mother_name, string _name, string _spouse_name, int _level, int _sex, bool _marriage, bool _live, const Date & _birth, const Date & _death) :birth(_birth), death(_death) {
	name = _name;
	spouse_name = _spouse_name;
	father_name = _father_name;
	mother_name = _mother_name;
	level = _level;
	sex = _sex;
	marriage = _marriage;
	live = _live;
}
People::People(const People & _person) {
	name = _person.name;
	spouse_name = _person.spouse_name;
	father_name = _person.father_name;
	mother_name = _person.mother_name;
	level = _person.level;
	sex = _person.sex;
	marriage = _person.marriage;
	live = _person.live;
	birth = _person.birth;
	death = _person.death;
}
void People::set_name(string _name) { name = _name; }
string People::get_name()  const { return name; }
void People::set_spouse_name(string _name) { spouse_name = _name; }
string People::get_spouse_name()  const { return spouse_name; }
void People::set_father_name(string _name) { father_name = _name; }
string People::get_father_name()  const { return father_name; }
void People::set_mother_name(string _name) { mother_name = _name; }
string People::get_mother_name()  const { return mother_name; }
void People::set_level(int _level) { level = _level; }
int People::get_level()  const { return level; }
void People::set_sex(int _sex) { sex = _sex; }
int People::get_sex()  const { return sex; }
void People::set_marriage(bool _marriage) { marriage = _marriage; }
bool People::get_marriage()  const { return marriage; }
void People::set_live(bool _live) { live = _live; }
bool People::get_live()  const { return live; }
void People::set_birth(const Date& _birth) { birth = _birth; }
Date People::get_birth()  const { return birth; }
void People::set_death(const Date& _death) { death = _death; }
Date People::get_death()  const { return death; }