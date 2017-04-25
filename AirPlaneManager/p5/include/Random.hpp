#ifndef RANDOM_HPP_
#define RANDOM_HPP_
#include <stdlib.h>
#include <time.h>
// class Random {
// public:
// 	Random(bool pseudo=true);
// 	int Random_integer(int low,int high);
// 	double Random_real();
// 	int poisson(double mean);
//
// private:
// 	int reseed();
// 	int seed;
// 	int multiplier;
// 	int max_int;
// 	int add_on;
// };
class Random {
public:
	 Random(bool pseudo=true);
	 int possion(double);
	 double U_Random();
};
#endif
