#include<iostream>

#include "../include/Runway.hpp"

using namespace std;
Runway::Runway(int limit)
{
	queue_limit=limit;
	num_land_requests=num_takeoff_requests=0;
	num_landings=num_takeoffs=0;
	num_land_refused=num_takeoff_refused=0;
	num_land_accepted=num_takeoff_accepted=0;
	land_wait=takeoff_wait=idle_time=0;
	num_land_crashdown = 0;
}
Error_code Runway::can_land(const Plane &current)
{
	Error_code result;
	if(landing.size()<queue_limit) {
		Queue judge = landing;
		judge.append(current);
		judge.sort();
		bool is_ok = true;
		if (current.oil() != 1) {
			for (int i = 0; i < judge.size(); ++i) {
				if (judge.nth_plane(i).oil() < i + 1) {
					is_ok = false;
					break;
				}
			}
			if (is_ok)result=landing.append(current);
			else result = fail;
		} else {

			result = landing.apphead(current);
		}
	} else {
		result=fail;
	}
	num_land_requests++;
	if(result!=success)
		num_land_refused++;
	else
		num_land_accepted++;
	return result;
}
Error_code Runway::can_depart(const Plane &current)
{

    Error_code result;
	if(takeoff.size()<queue_limit)
		result=takeoff.append(current);
	else
		result=fail;
	num_takeoff_requests++;
	if(result!=success)
		num_takeoff_refused++;
	else
		num_takeoff_accepted++;
	return result;
}

//处理对跑道的访问
Runway_activity Runway::activity(int time,Plane &moving)
{
	Runway_activity in_progress;
	//若着陆队列非空，准备着陆的飞机进入着陆队列

	if(!landing.empty()){
		landing.sort();
		landing.retrieve(moving);
		if (moving.oil() <= 0) {
			// cout << moving.flt_num << ":" << moving.oil() << endl;
			num_land_crashdown++;
		} else {
			// cout << moving.flt_num << ":" << moving.oil() << endl;
			num_landings++;
		}
		land_wait+=time-moving.started();
		in_progress=land;
		landing.serve();
	}
	//若着陆队列为空而起飞队列非空，起飞队列队头飞机起飞
	else if(!takeoff.empty()){
    takeoff.retrieve(moving);
		takeoff_wait+=time-moving.started();
		num_takeoffs++;
		in_progress=take_off;
		takeoff.serve();
	}
	//两队列均空时，标记跑道空闲
	else{
		idle_time++;
		in_progress=idle;
	}
	return in_progress;
}

void Runway::shut_down(int time, bool flag)const
{
	cout<<endl<<endl
		<<"Simulation has conluded after "<<time<<" time units."<<endl //模拟在time时间单元后终止
	    <<"Total number of planes processed:  " //总共处理的飞机数
		<<(num_land_requests+num_takeoff_requests)<<endl
	    <<"Total number of planes asking to land:  " //总共要求着陆的飞机数
		<<num_land_requests<<endl
	    <<"Total number of planes asking to take off:  " //总共要求起飞的飞机数
		<<num_takeoff_requests<<endl
		<<"Total number of plane accepted for land:  " //总共接受着陆的飞机数
		<<num_land_accepted<<endl
		<<"Total number of planes accepted  for takeoff:  " //总共接受起飞的飞机数
		<<num_takeoff_accepted<<endl
		<<"Total number of planes refused  for landing:  " //总共拒绝着陆的飞机数
		<<num_land_refused<<endl
        <<"Total number of planes refused  for takeoff:  " //总共拒绝起飞的飞机数
		<<num_takeoff_refused<<endl
        <<"Total number of planes that landed:  " //总共着陆的飞机数
		<<num_landings<<endl
				<<"Total number of planes that crash down: " << num_land_crashdown << endl
        <<"Total number of planes that take off:  " //总共起飞的飞机数
		<<num_takeoffs<<endl
        <<"Total number of planes left in the landing queue:  " //总共留在着陆队列里的飞机数
		<<landing.size()<<endl
        <<"Total number of planes left in the takeoff queue:  " //总共留在起飞队列里的飞机数
		<<takeoff.size()<<endl;
	cout<<endl<<endl;
	cout<<"Percentage of time runway idle: " //飞机跑道空闲的时间百分比
		<<100.0*((float)idle_time)/((float)time)<<"%"<<endl;
	cout<<"Average wait in landing queue:  " //着陆队列里的平均等待
		<<((float)land_wait)/((float)num_landings)<<" time units.";
    if(num_takeoffs == 0)
    cout<<endl<<"  No plane took off!"<<endl;
	else
	cout<<endl<<"Average wait in takeoff queue:  " //起飞队列里的平均等待
        <<((float)takeoff_wait)/((float)num_takeoffs)
		<<" time units."<<endl;

	//期望着陆或起飞的飞机平均被观察率，它将与运行开始时设置的期望相
	//匹配，以证明随机数算法确实模拟了合适的Poisson分布
	cout<<"Average observed rate of planes wanting to land:  "
	    <<((float)num_land_requests)/((float)time)
		<<" per time unit"<<endl;
    cout<<"Average observed rate of planes wanting to takeoff:  "
	    <<((float)num_takeoff_requests)/((float)time)
		<<" per time unit"<<endl;
		if (flag == true) {
			ofstream p1("airport.in",ios::app);
			p1<<endl<<endl
				<<"Simulation has conluded after "<<time<<" time units."<<endl //模拟在time时间单元后终止
			    <<"Total number of planes processed:  " //总共处理的飞机数
				<<(num_land_requests+num_takeoff_requests)<<endl
			    <<"Total number of planes asking to land:  " //总共要求着陆的飞机数
				<<num_land_requests<<endl
			    <<"Total number of planes asking to take off:  " //总共要求起飞的飞机数
				<<num_takeoff_requests<<endl
				<<"Total number of plane accepted for land:  " //总共接受着陆的飞机数
				<<num_land_accepted<<endl
				<<"Total number of planes accepted  for takeoff:  " //总共接受起飞的飞机数
				<<num_takeoff_accepted<<endl
				<<"Total number of planes refused  for landing:  " //总共拒绝着陆的飞机数
				<<num_land_refused<<endl
		        <<"Total number of planes refused  for takeoff:  " //总共拒绝起飞的飞机数
				<<num_takeoff_refused<<endl
		        <<"Total number of planes that landed:  " //总共着陆的飞机数
				<<num_landings<<endl
						<<"Total number of planes that crash down: " << num_land_crashdown << endl
		        <<"Total number of planes that take off:  " //总共起飞的飞机数
				<<num_takeoffs<<endl
		        <<"Total number of planes left in the landing queue:  " //总共留在着陆队列里的飞机数
				<<landing.size()<<endl
		        <<"Total number of planes left in the takeoff queue:  " //总共留在起飞队列里的飞机数
				<<takeoff.size()<<endl;
			p1<<endl<<endl;
			p1<<"Percentage of time runway idle: " //飞机跑道空闲的时间百分比
				<<100.0*((float)idle_time)/((float)time)<<"%"<<endl;
			p1<<"Average wait in landing queue:  " //着陆队列里的平均等待
				<<((float)land_wait)/((float)num_landings)<<" time units.";
		    if(num_takeoffs == 0)
		    p1<<endl<<"  No plane took off!"<<endl;
			else
			p1<<endl<<"Average wait in takeoff queue:  " //起飞队列里的平均等待
		        <<((float)takeoff_wait)/((float)num_takeoffs)
				<<" time units."<<endl;

			//期望着陆或起飞的飞机平均被观察率，它将与运行开始时设置的期望相
			//匹配，以证明随机数算法确实模拟了合适的Poisson分布
			p1<<"Average observed rate of planes wanting to land:  "
			    <<((float)num_land_requests)/((float)time)
				<<" per time unit"<<endl;
		    p1<<"Average observed rate of planes wanting to takeoff:  "
			    <<((float)num_takeoff_requests)/((float)time)
				<<" per time unit"<<endl;
			p1.close();
		}
}
void Runway::suboil() {
		for (int i = 0; i < landing.size(); ++i) {
			// cout << landing.nth_plane(i).flt_num << ": " << landing.nth_plane(i).oil() << endl;
			landing.nth_plane(i).set_oil();
			// cout << landing.nth_plane(i).flt_num << ": " << landing.nth_plane(i).oil() << endl;
		}
}
