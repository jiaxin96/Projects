#ifndef RUNWAY_HPP_
#define RUNWAY_HPP_
#include <string>
#include <iostream>
#include "queue.hpp"
#include "Plane.hpp"
using namespace std;
enum Runway_activity {idle,land,take_off};
class Runway {
public:
  Runway(int limit);
  Error_code can_land(const Plane & current);
  Error_code can_depart(const Plane & current);
  Runway_activity activity(int time, Plane & moving);
  void shut_down(int time) const;
private:
  Queue landing;
  Queue takeoff;
  int queue_limit;
  int num_land_requests;
  int num_takeoff_requests;
  int num_landings;
  int num_takeoffs;
  int num_land_accepted;
  int num_takeoff_accepted;
  int num_land_refused;
  int num_takeoff_refused;
  int land_wait;
  int takeoff_wait;
  int idle_time;
};
#endif
