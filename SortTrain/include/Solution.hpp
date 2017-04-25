#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_
#include <string>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;
class Solution {
public:
  Solution(vector<int>,int);
  ~Solution();
  string simulate_stack();

private:
  string result;
  vector<stack<int>> track;
  vector<int> train_carriage;
  int track_num;
};
#endif // SOLUTION_HPP_
