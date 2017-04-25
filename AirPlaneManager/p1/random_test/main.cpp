#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
double U_Random();
double possion(double Lambda);


int main()
{
        srand( (unsigned)time( NULL ) );
        double u = U_Random();
        vector<double> num;
        for (int i = 0; i < 1000; ++i) {

          double p = possion(0.5);
          // printf("%f ",u);
          // printf("%d\n",p);
          num.push_back(p);
        }
        double ave = 0;
        for (int i = 0; i < num.size(); ++i) {
          printf("%lf\n", num[i]);
          ave += num[i];
        }
        ave = ave / 1000;
        printf("AVE:%lf\n", ave);
        return 0;



}

double possion(double Lambda)  /* 产生一个泊松分布的随机数，Lamda为总体平均数*/
{
        double k = 0;
        long double p = 1.0;
        long double l=exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
        printf("%.15Lf\n",l);
        while (p>=l)
        {
                double u = U_Random();
                p *= u;
                k++;
        }
        return k-1;
}

double U_Random()   /* 产生一个0~1之间的随机数 */
{
        double f;

        f = (float)(rand() % 100);
        /* printf("%f\n",f); */
        return f/100;
}
