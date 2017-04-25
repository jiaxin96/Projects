#ifndef GRAPH_HPP
#define GRAPH_HPP
#define inf 99999
#include <string>
#include <string.h>
#include <vector>
using namespace std;
struct Edge{
    int s_pos;
    int e_pos;
    int weight;
    int type;
    Edge(int s, int e, int w, int t):s_pos(s), e_pos(e), weight(w), type(t){}
    bool operator ==(Edge & ot) {
        return (ot.s_pos == s_pos && ot.e_pos == e_pos);
    }
    void operator =(Edge & ot) {
        s_pos = ot.s_pos;
        e_pos = ot.e_pos;
        weight = ot.weight;
        type = ot.type;
    }
};
class Graph{
private:
    int car_edge[20][20], car_dis[20][20], car_book[20][20];
    int foot_edge[20][20], foot_dis[20][20], foot_book[20][20];
    int size;
    vector<vector<string> > car_path;
    vector<vector<string> > foot_path;
public:
    Graph();
    Graph(const vector<Edge> & other);
    void init();
    void handle(const vector<Edge> & other, int nowSize);
    void car_Dijkstra();
    void foot_Dijkstra();
    int get_car_distance(int start, int end);
    int get_foot_distance(int start, int end);
    string get_car_path(int start, int end);
    string get_foot_path(int start, int end);
};
#endif
