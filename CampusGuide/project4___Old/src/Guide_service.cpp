#include "../include/Guide_service.hpp"
Guide_service::Guide_service() {}
Guide_service::~Guide_service() {}
void Guide_service::StartService() {
    instance.readFromFile();
    guide.handle(instance.get_edge(), instance.get_spot().size());
}
void Guide_service::QuitService() {
    instance.sync();
}
int Guide_service::QueryFootdis(int s, int e) {
    return guide.get_foot_distance(s, e);
}
int Guide_service::QueryCardis(int s, int e) {
    return guide.get_car_distance(s, e);
}
bool Guide_service::Addspot(const Spot & other) {
  vector<Spot> s = instance.get_spot();
  int len = s.size();
  for (int i = 0; i < len; ++i) {
    if (s[i].get_name() == other.get_name() || s[i].get_mark() == other.get_mark() || s[i].get_introduction() == other.get_introduction()) {
      return false;
    }
  }
  instance.addSpot(other);
  return true;
}
bool Guide_service::Deletespot(int mark) {
    vector<Spot> s = instance.get_spot();
    int len = s.size();
    if (mark < 0 || mark >= len) return false;
    instance.deleteSpot(mark);
    return true;
}
void Guide_service::SetGraph(const vector<Edge> & other) {
    instance.updataEdge(other);
    guide.init();
    guide.handle(instance.get_edge(), instance.get_spot().size());

}
string Guide_service::Num_2_Name(string order) {
  string result = "最佳路径推荐:";
  vector<Spot> s = instance.get_spot();
  int len = s.size();
  while (!order.empty()) {
    int mark = order[0] - '0';
    for (int i = 0; i < len; ++i) {
      if (s[i].get_mark() == mark) {
        result += s[i].get_name();
        break;
      }
    }
    order.erase(0, 1);
    if (order.length() != 0) {
      result += "->";
    } else {
      result += "\n";
    }
  }
  return result;
}
vector<string> Guide_service::Spotname() {
    vector<Spot> s = instance.get_spot();
    int len = s.size();
    vector<string> result;
    for (int i = 0; i < len; ++i) {
      string temp;
      char ch = (i + '1');
      temp +=  ch + s[i].get_name();
      result.push_back(temp);
    }
    return result;
}
string Guide_service::QueryFootpath(int s, int e) {
    string order = guide.get_foot_path(s, e);
    return Num_2_Name(order);
}
string Guide_service::Spotintroduction(int mark) {
  vector<Spot> s = instance.get_spot();
  int len = s.size();
  for (int i = 0; i < len; ++i) {
    if (s[i].get_mark() == mark) {
      return s[i].get_introduction();
    }
  }
  return "Unknown";
}
string Guide_service::QueryCarpath(int s, int e) {
    string order = guide.get_car_path(s, e);
    return Num_2_Name(order);
}
string Guide_service::QuerySpot(int mark) {
    vector<Spot> s = instance.get_spot();
    int len = s.size();
    for (int i = 0; i < len; ++i) {
      if (s[i].get_mark() == mark) {
        return s[i].get_introduction();
      }
    }
    return "Unknown";
}
