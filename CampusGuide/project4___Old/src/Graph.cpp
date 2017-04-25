#include "../include/Graph.hpp"
Graph::Graph() {
    init();
}
Graph::Graph(const vector<Edge> & other) {
    init();
    handle(other, other.size());
}
void Graph::init() {
  memset(car_edge, inf, sizeof(car_edge));
  memset(foot_edge, inf, sizeof(foot_edge));
  memset(car_dis, inf, sizeof(car_dis));
  memset(foot_dis, inf, sizeof(foot_dis));
  memset(car_book, 0, sizeof(car_book));
  memset(foot_book, 0, sizeof(foot_book));
  size = 0;
  for (int i = 0; i < 20; ++i) {
    vector<string> vec_string;
    car_path.push_back(vec_string);
    foot_path.push_back(vec_string);
    for (int j = 0; j < 20; ++j) {
      char ch = i + '0';
      string temp;
      temp += ch;
      car_path[i].push_back(temp);
      foot_path[i].push_back(temp);
    }
  }
}
void Graph::handle(const vector<Edge> & other, int nowSize) {
  int len = other.size();
  size = nowSize;
  for (int i = 0; i < len; ++i) {
    if (other[i].type == 1) {
      car_edge[other[i].s_pos][other[i].e_pos] = other[i].weight;
      car_edge[other[i].e_pos][other[i].s_pos] = other[i].weight;
      car_path[other[i].s_pos][other[i].e_pos] += other[i].e_pos + '0';
      car_path[other[i].e_pos][other[i].s_pos] += other[i].s_pos + '0';
      car_dis[other[i].s_pos][other[i].e_pos] = car_edge[other[i].s_pos][other[i].e_pos];
      car_dis[other[i].e_pos][other[i].s_pos] = car_edge[other[i].e_pos][other[i].s_pos];
    }
    foot_edge[other[i].s_pos][other[i].e_pos] = other[i].weight;
    foot_edge[other[i].e_pos][other[i].s_pos] = other[i].weight;
    foot_path[other[i].s_pos][other[i].e_pos] += other[i].e_pos + '0';
    foot_path[other[i].e_pos][other[i].s_pos] += other[i].s_pos + '0';
    foot_dis[other[i].s_pos][other[i].e_pos] = foot_edge[other[i].s_pos][other[i].e_pos];
    foot_dis[other[i].e_pos][other[i].s_pos] = foot_edge[other[i].e_pos][other[i].s_pos];
  }
  foot_Dijkstra();
  car_Dijkstra();
  
}
void Graph::car_Dijkstra() {
    for (int i = 1; i <= size; ++i) {
      car_book[i][i] = 1;
      for (int j = 1; j <= size; ++j) {
        int min = inf, small;
        for (int k = 1; k <= size; ++k) {
          if (car_book[i][k] == 0 && car_dis[i][k] < min) {
            min = car_dis[i][k];
            small = k;
          }
        }
        car_book[i][small] = 1;
        for (int k = 1; k <= size; ++k) {
          if (car_edge[small][k] < inf) {
            if (car_dis[i][k] > car_edge[small][k]) {
              car_dis[i][k] = car_dis[i][small] + car_edge[small][k];
              car_path[i][k] = car_path[i][k].substr(0, car_path[i][k].length() - 1);
              car_path[i][k] += (small + '0') + (k + '0');
            }
          }
        }
      }
    }
}
void Graph::foot_Dijkstra() {
  for (int i = 1; i <= size; ++i) {
    foot_book[i][i] = 1;
    for (int j = 1; j <= size; ++j) {
      int min = inf, small;
      for (int k = 1; k <= size; ++k) {
        if (foot_book[i][k] == 0 && foot_dis[i][k] < min) {
          min = foot_dis[i][k];
          small = k;
        }
      }
      foot_book[i][small] = 1;
      for (int k = 1; k <= size; ++k) {
        if (foot_edge[small][k] < inf) {
          if (foot_dis[i][k] > foot_edge[small][k]) {
            foot_dis[i][k] = foot_dis[i][small] + foot_edge[small][k];
            foot_path[i][k] = foot_path[i][k].substr(0, foot_path[i][k].length() - 1);
            foot_path[i][k] += (small + '0') + (k + '0');
          }
        }
      }
    }
  }
}
int Graph::get_car_distance(int start, int end) {
    return car_dis[start][end];
}
int Graph::get_foot_distance(int start, int end) {
    return foot_dis[start][end];
}
string Graph::get_car_path(int start, int end) {
    return car_path[start][end];
}
string Graph::get_foot_path(int start, int end) {
    return foot_path[start][end];
}
