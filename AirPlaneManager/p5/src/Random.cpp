#include <iostream>
#include "../include/Random.hpp"
#include"math.h"
#include "time.h"
#include <limits.h>
// int Random::reseed()
// {
// 	seed=seed*multiplier+add_on;
// 	return seed;
// }
// Random::Random(bool pseudo)
// {
// 	if(pseudo) seed=1;
// 	else seed=time(NULL)%max_int;
// 	multiplier= 2743;
// 	add_on= 5923;
// }
// double Random::Random_real()
// {
// 	double max=max_int+1.0;
// 	double temp=reseed();
// 	if (temp<0) temp=temp+max;
// 	return temp/max;
// }
// int Random::Random_integer(int low,int high)
// {
// 	if(low>high) return Random_integer(high,low);
// 	else return ((int)((high-low+1)*Random_real()))+low;
// }
// int Random::poisson(double mean)
// {
// 	double limit=exp(-mean);
// 	double product=Random_real();
// 	int count=0;
// 	while(product>limit){
// 		count++;
// 		product*=Random_real();
// 	}
// 	return count;
// }
Random::Random(bool pseudo) {
	srand( (unsigned)time( NULL ) );
}
int Random::possion(double Lambda)  /* 产生一个泊松分布的随机数，Lamda为总体平均数*/
{
        int k = 0;
        long double p = 1.0;
        long double l=exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
        // printf("%.15Lf\n",l);
        while (p>=l)
        {
                double u = U_Random();
                p *= u;
                k++;
        }
        return k-1;
}
double Random::U_Random()   /* 产生一个0~1之间的随机数 */
{
        double f;

        f = (float)(rand() % 100);
        /* printf("%f\n",f); */
        return f/100;
}
