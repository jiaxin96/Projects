#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Solution.hpp"
int main() {
	ifstream f1("../data/sort_data.txt");
	ofstream f2("../data/nswer.txt");
	string temp;
	while (!f1.eof()) {
		getline(f1, temp);
		vector<int> train_carriage;
		string tempData = "";
		for (unsigned int i = 0; i < temp.length(); ++i) {
			if (temp[i] != ' ') {
				tempData += temp[i];
			} else {
				istringstream iss(tempData);
				int carriage_num;
				iss >> carriage_num;
				train_carriage.push_back(carriage_num);
				tempData = "";
			}
		}
		for (unsigned int i = 1; i <= temp.length(); ++i) {
			Solution s(train_carriage, i);
			string result = s.simulate_stack();
			if (result != "No Answer!\n") {
				cout << result << endl;
				f2 << temp << endl << result << endl;
				break;
			}
		}
	}
	return 0;
}
