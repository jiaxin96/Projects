#include "../include/Spot.hpp"
Spot::Spot():name("unknown"), mark(-1), introduction("unknown") {}
Spot::Spot(string n, int m, string i):name(n), mark(m), introduction(i) {}
string Spot::get_name() const { return name; }
int Spot::get_mark() const { return mark; }
string Spot::get_introduction() const{ return introduction;}
