#include <iostream>
#include <string>
#include <fstream>
#include "../include/Plane.hpp"

using namespace std;
Plane::Plane()
{
	flt_num=-1;
	clock_start=-1;
	state=null;
	oil_left = 0;
}
Plane::Plane(int flt,int _time,Plane_status status, int _oil_left)
{

	flt_num=flt;
	clock_start=_time;
	state=status;
	oil_left = _oil_left;
	cout<<"      Plane number "<<flt<<" ready to ";
	if(status == arriving)
		cout<<"land. "<< "Oil: " << oil_left << endl;
	else
		cout<<"take off."<<endl;
}

//拒绝飞机起飞或着陆
void Plane::refuse()const
{
	cout<<"      Plane number "<<flt_num;
	if(state==arriving)
		cout<<" directed to another airport"<<endl; //安排准备着陆的飞机转去另一跑道
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
		ofstream p2("Crashinfo.in",ios::app);
    int wait=time-clock_start;
		if (oil_left <= 0) {
			cout<<"   "<<time<<":Plane number "<<flt_num << " Oil left: " << oil_left;
			p2 << "   "<<time<<":Plane number "<<flt_num << " Oil left: " << oil_left;
			if(oil_left!= 0) {
				cout << ", so the plane crashed down before " <<  -oil_left << "s" << endl;
				p2 << ", so the plane crashed down before " <<  -oil_left << "s" << endl;
			} else {
				cout << ",now the plane start to crash down!" << endl;
				p2 << ",now the plane start to crash down!" << endl;
			}
		} else {
			cout<<"   "<<time<<":Plane number "<<flt_num<<" landed after "
				<<wait<<" time unit"<<((wait==1)?"":"s")
				<<" in the landing queue."<< "oil left: " << oil_left << endl;
		}
		p2.close();
}

//沟通飞机的到达数据
int Plane::started()const
{
	return clock_start;
}
int Plane::oil() const {
	return oil_left;
}
void Plane::set_oil() {
	oil_left--;
}
