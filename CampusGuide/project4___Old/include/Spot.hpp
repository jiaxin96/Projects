#ifndef SPOT_HPP
#define SPOT_HPP
#include <string>
using namespace std;
class Spot {
private:
    string name;
    int mark;
    string introduction;
public:
    Spot();
    Spot(string n, int m, string i);
    string get_name() const;
    int get_mark() const;
    string get_introduction() const;
};
#endif
