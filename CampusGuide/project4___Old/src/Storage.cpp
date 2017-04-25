#include "../include/Storage.hpp"
#include <sstream>
#include <vector>
using namespace std;
Storage::Storage() {}
bool Storage::readFromFile(void) {
  return (readSpot() && readEdge());
}
bool Storage::readSpot() {
  std::ifstream guidein("data/map");
  if (guidein.fail()) return false;
  if (!guidein.good()) return false;
  string spot_info;
  while (!guidein.eof()) {
    getline(guidein, spot_info);
    if (spot_info == "") break;
    string name, introduction;
    int mark;
    istringstream istr(spot_info);
    istr >> name >> mark >> introduction;
    spot.push_back(Spot(name, mark, introduction));
    // int mark, count = 0;
    // while (!spot_info.empty()) {
    //   if (spot_info[0] != ' ') {
    //     temp += spot_info[0];
    //   } else {
    //     if (count == 0) {
    //       name = temp;
    //     }
    //     else if (count == 1) {
    //       mark = atoi(temp.c_str());
    //     } else {
    //       introduction = temp;
    //     }
    //     count++;
    //     temp.clear();
    //   }
    //   spot_info.erase(0, 1);
    // }
    // Spot examle(name, mark, introduction);
    // spot.push_back(examle);
  }
  guidein.close();
  return true;
}
bool Storage::readEdge() {
  std::ifstream guidein("data/edge");
  if (guidein.fail()) return false;
  if (!guidein.good()) return false;
  string edge_info;
  while (!guidein.eof()) {
    getline(guidein, edge_info);
    if (edge_info == "") break;
    int startP, endP, edgeWeirht, edgeType;
    istringstream istr(edge_info);
    istr >> startP >> endP >> edgeWeirht >> edgeType;
    mapEdge.push_back(Edge(startP, endP, edgeWeirht, edgeType));
  }
  guidein.close();
  return true;
}
bool Storage::writeToFile(void) {
  return (writeSpot() && writeEdge());
}

bool Storage::writeSpot() {
  std::ofstream guideout("data/map");
  if (!guideout.good()) return false;
  if (guideout.fail()) return false;
  int len = spot.size();
  for (int i = 0; i < len; ++i) {
    guideout << spot[i].get_name() << " " << spot[i].get_mark() << " "
    << spot[i].get_introduction() << endl;
  }
  guideout.close();
  return true;
}
bool Storage::writeEdge() {
  std::ofstream guideout("data/edge");
  if (!guideout.good()) return false;
  if (guideout.fail()) return false;
  int len = mapEdge.size();
  for (int i = 0; i < len; ++i) {
    guideout << mapEdge[i].s_pos << " " << mapEdge[i].e_pos << " "
    << mapEdge[i].weight << " " << mapEdge[i].type << endl;
  }
  guideout.close();
  return true;
}

std::vector<Edge> Storage::get_edge() const {
  return mapEdge;
}


Storage::~Storage() {}
bool Storage::sync(void) {
  return writeToFile();
}
vector<Spot> Storage::get_spot() const {
  return spot;
}
void Storage::addSpot(const Spot & other) {
  spot.push_back(other);
}

void Storage::updataEdge(std::vector<Edge> other) {
  for (int i = 0; i < other.size(); ++i)
  {
    int findEdge = false;
    for (int j = 0; j < mapEdge.size(); ++j)
    {
      if (mapEdge[j] == other[i]) {
        mapEdge[j] = other[i];
        findEdge = true;
      }
    }
    if (!findEdge) {
      mapEdge.push_back(other[i]);
    }
  }
}

void Storage::deleteSpot(int mark) {
  if (mark < 0 || mark >= spot.size()) return;
  int count = 0;
  vector<Spot>::iterator iter = spot.begin();
  while (iter != spot.end()) {
    if (count == mark) {
      iter = spot.erase(iter);
      break;
    } else {
      count++;
    }
  }
}
