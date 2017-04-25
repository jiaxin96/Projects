#ifndef GUIDE_SERVICE_HPP
#define GUIDE_SERVICE_HPP
#include "Storage.hpp"
#include <vector>
#include <string>
class Guide_service{
private:
    Storage instance;
    Graph guide;
    string Num_2_Name(string);
public:
    Guide_service();
    ~Guide_service();
    void StartService();
    void QuitService();
    void SetGraph(const vector<Edge> & other);
    bool Addspot(const Spot & other);
    bool Deletespot(int mark);
    vector<string> Spotname();
    string Spotintroduction(int mark);
    int QueryFootdis(int, int);
    int QueryCardis(int, int);
    string QueryFootpath(int, int);
    string QueryCarpath(int, int);
    string QuerySpot(int);
};
#endif
