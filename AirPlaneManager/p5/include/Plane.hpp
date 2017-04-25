#ifndef PLANE_HPP_
#define PLANE_HPP_
#include <iostream>
using namespace std;
enum Plane_status {null,arriving, departing};
class Plane {
public:
  Plane();
  Plane(int flt, int time, Plane_status status, int _oil_left);
  void refuse() const;
  void land(int time) const;
  void fly(int time) const;
  int started() const;
  int oil() const;
  void set_oil();
  int flt_num;
private:

  int clock_start;
  Plane_status state;
  int oil_left;
};
#endif
