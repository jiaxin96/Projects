#include<iostream>
#include<string>
#include <cmath>
#include"Extended_queue.hpp"
#include"Random.hpp"
#include"Runway.hpp"
#include"Plane.hpp"
using namespace std;

void run_idle(int time)
{
	cout<<"   "<<time<<":Runway is idle."<<endl;
}

//初始化程序
void initialize(int &end_time,int &queue_limit,double &arrival_rate,double &departure_rate){
	cout<<"This is program simulates an airport with two runways."<<endl
	<<"One plane can land or depart in each unit of time."<<endl;
	cout<<"Up to what number of planes can be waiting to land"
		<<" or take off at any time?"<<flush;  //提示输入希望跑道能容纳的最大飞机数
	cin>>queue_limit;    //输入用户期望的跑道最大容纳量
	cout<<"How many units of time will the simulation run?"<<flush;  //提示输入用户期望的模拟时间
	cin>>end_time;
	bool acceptable;
	do {
		cout<<"Expected number of arrivals  per unit time?"<<flush; //提示输入用户期望每时间单元平均到达的飞机数
		cin>>arrival_rate;
		cout<<"Expected number of departures  per unit time?"<<flush; //提示输入每时间单元平均起飞的飞机数
		cin>>departure_rate;
		if(arrival_rate<0.0||departure_rate<0.0)
			cerr<<"These rates must  be nonnegative."<<endl;  //输入为负数时报错
		else
			acceptable=true;
		if(acceptable&&arrival_rate+departure_rate>1.0)
			cerr<<"Safety Warning:This airport will become saturated."<<endl;
	}while(!acceptable);
}

//主程序
int main() {
	int end_time;
	int queue_limit;
	int flight_number=0;
	double arrival_rate;
	double departure_rate;
	initialize(end_time,queue_limit,arrival_rate,departure_rate);  //初始化跑道信息
	Random variable;  //定义随机数变量
	Runway small_airport_land(queue_limit);
	Runway small_airport_takeoff(queue_limit);
	//判断当前发出请求的飞机是否应该被接受或拒绝
	for(int current_time=0;current_time<end_time;current_time++){
		int number_arrivals= variable.possion(arrival_rate);
		for(int i=0;i<number_arrivals;i++){
			Plane current_plane(flight_number++,current_time,arriving);
			if(small_airport_land.can_land(current_plane) != success)
				current_plane.refuse();
		}
		int number_departures=variable.possion(departure_rate);
		for(int j=0;j<number_departures;j++){
			Plane current_plane(flight_number++,current_time,departing);
			if(small_airport_takeoff.can_depart(current_plane)!=success)
				current_plane.refuse();
		}
		Plane moving_plane;
		//根据前面判断进行相关调度
		switch(small_airport_land.activity(current_time,moving_plane)){
		case land:
			moving_plane.land(current_time);
			break;
		case take_off:
			moving_plane.fly(current_time);
			break;
		case idle:
			run_idle(current_time);
		}
		switch(small_airport_takeoff.activity(current_time,moving_plane)){
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
	small_airport_land.shut_down(end_time);
	small_airport_takeoff.shut_down(end_time);
	return 0;
}
