#ifndef STORAGE_HPP
#define STORAGE_HPP
#include "Spot.hpp"
#include "Graph.hpp"
#include <fstream>
#include <vector>
class Storage {
private:
    vector<Spot> spot;
    std::vector<Edge> mapEdge;
public:
  Storage();
  bool readFromFile(void);
  bool readSpot(void);
  bool readEdge(void);
  bool writeToFile(void);
  ~Storage();
  bool sync(void);
  vector<Spot> get_spot() const;
  void addSpot(const Spot & other);
  void deleteSpot(int mark);
  bool writeSpot();
  bool writeEdge();
  void updataEdge(std::vector<Edge>);
  vector<Edge> get_edge() const;
};
#endif
