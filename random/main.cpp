#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
int result=0;
srand(time(0));//用时间作种子，使每次随即的数字不一样
for (int i = 0; i < 100; ++i) {
  result = rand()%10;
  cout << result << " ";
  if (i % 10 == 0) cout << endl;
}
cout << endl;
return 0;
}
