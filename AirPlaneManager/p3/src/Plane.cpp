#include<iostream>
#include<string>
#include"Plane.hpp"
using namespace std;
Plane::Plane()
{
	flt_num=-1;
	clock_start=-1;
	state=null;
}
Plane::Plane(int flt,int time,Plane_status status)
{
	flt_num=flt;
	clock_start=time;
	state=status;
	cout<<"      Plane number "<<flt<<" ready to ";
	if(status == arriving)
		cout<<"land."<<endl;
	else
		cout<<"take off."<<endl;
}

//拒绝飞机起飞或着陆
void Plane::refuse()const
{
	cout<<"      Plane number "<<flt_num;
	if(state==arriving)
		cout<<" directed to another airport"<<endl; //安排准备着陆的飞机转去另一机场
	else
		cout<<" told to try to take off again later"<<endl; //告知飞机当前不可立即起飞，须等待
}

//安排飞机进入起飞队列
void Plane::fly(int time)const
{
	int wait=time-clock_start;
	cout<<"   "<<time<<":Plane number "<<flt_num<<" took off after "
		<<wait<<" time unit"<<((wait==1)?"":"s")
		<<" in the takeoff queue."<<endl;
}

//安排飞机进入着陆队列
void Plane::land(int time)const
{
    int wait=time-clock_start;
	cout<<"   "<<time<<":Plane number "<<flt_num<<" landed after "
		<<wait<<" time unit"<<((wait==1)?"":"s")
		<<" in the landing queue."<<endl;
}

//沟通飞机的到达数据
int Plane::started()const
{
	return clock_start;
}
