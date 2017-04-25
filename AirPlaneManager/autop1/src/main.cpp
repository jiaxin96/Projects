#include<iostream>
#include<string>
#include <cmath>
#include <vector>
#include <fstream>
#include"Extended_queue.hpp"
#include"Random.hpp"
#include"Runway.hpp"
#include"Plane.hpp"
#include "Path.hpp"
using namespace std;
void write_to_file(void) {
  ofstream p1(Path::dataPath);
  double a_start = 0.0;
  double d_start = 0.0;
  for (int i = 0; i < 10; ++i) {
    a_start += 0.1;
		d_start = 0;
    for (int j = 0; j < 10; ++j) {
      d_start += 0.1;
      p1 << "5" << endl;
      p1 << "1000" << endl;
      p1 << a_start << endl;
      p1 << d_start << endl;
    }
  }
  p1.close();
}
void run_idle(int time)
{
	cout<<"   "<<time<<":Runway is idle."<<endl;
}
//主程序
int main() {
	vector<double> amax;
	vector<double> dmax;
	write_to_file();
	fstream p1(Path::dataPath);
	int num_count = 0;
	while (!p1.eof()) {
		int end_time;
		int queue_limit;
		int flight_number=0;
		double arrival_rate;
		double departure_rate;
		double ar = 0.0;
		double dr = 0.0;
		cout<<"This is program simulates an airport with only one runway."<<endl
		<<"One plane can land or depart in each unit of time."<<endl;
		cout<<"Up to what number of planes can be waiting to land"
			<<" or take off at any time?"<<flush;  //提示输入希望跑道能容纳的最大飞机数
		string queue_limit_str;
		getline(p1,queue_limit_str); //输入用户期望的跑道最大容纳量
		queue_limit = atoi(queue_limit_str.c_str());
		cout << queue_limit << endl;
		cout<<"How many units of time will the simulation run?"<<flush;  //提示输入用户期望的模拟时间
		string end_time_str;
		getline(p1,end_time_str);
		end_time = atoi(end_time_str.c_str());
		cout << end_time << endl;
		bool acceptable;
		do {
			cout<<"Expected number of arrivals  per unit time?"<<flush; //提示输入用户期望每时间单元平均到达的飞机数
			string arrival_rate_str;
			getline(p1,arrival_rate_str);
			arrival_rate = atof(arrival_rate_str.c_str());
			ar = arrival_rate;
			cout << arrival_rate << endl;
			cout<<"Expected number of departures  per unit time?"<<flush; //提示输入每时间单元平均起飞的飞机数
			string departure_rate_str;
			getline(p1,departure_rate_str);
			departure_rate = atof(departure_rate_str.c_str());
			dr = departure_rate;
			cout << departure_rate << endl;
			if(arrival_rate<0.0||departure_rate<0.0)
				cerr<<"These rates must  be nonnegative."<<endl;  //输入为负数时报错
			else
				acceptable=true;
			if(acceptable&&arrival_rate+departure_rate>1.0)
				cerr<<"Safety Warning:This airport will become saturated."<<endl;
		}while(!acceptable);
		Random variable;  //定义随机数变量
		Runway small_airport(queue_limit);
		//判断当前发出请求的飞机是否应该被接受或拒绝
		for(int current_time=0;current_time<end_time;current_time++){
			int number_arrivals= variable.possion(arrival_rate);
			for(int i=0;i<number_arrivals;i++){
				Plane current_plane(flight_number++,current_time,arriving);
				if(small_airport.can_land(current_plane) != success)
					current_plane.refuse();
			}
			int number_departures=variable.possion(departure_rate);
			for(int j=0;j<number_departures;j++){
				Plane current_plane(flight_number++,current_time,departing);
				if(small_airport.can_depart(current_plane)!=success)
					current_plane.refuse();
			}
			Plane moving_plane;
			//根据前面判断进行相关调度
			switch(small_airport.activity(current_time,moving_plane)){
			case land:
				moving_plane.land(current_time);
				break;
			case take_off:
				moving_plane.fly(current_time);
				break;
			case idle:
				run_idle(current_time);
			}
		}
		//结束模拟，打印调度过程
		small_airport.shut_down(end_time);
		if (small_airport.a_r() == false) amax.push_back(ar);
		if (small_airport.d_r() == false) dmax.push_back(dr);
		num_count++;
	}
	p1.close();
	cout << num_count << endl;
	cout << amax[amax.size() - 1] << endl;
	cout << dmax[dmax.size() - 1] << endl;
	return 0;
}
