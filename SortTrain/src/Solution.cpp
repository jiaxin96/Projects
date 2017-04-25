#include "Solution.hpp"
string int_2_string(int number) {
	string result;
	stringstream ss;
	ss << number;
	ss >> result;
	return result;
}
Solution::Solution(vector<int> train_carriage_,int track_num_):train_carriage(train_carriage_),track_num(track_num_) {
	for (auto i = 0; i < track_num; ++i) {
		stack<int> temp;
		track.push_back(temp);
	}
}
string Solution::simulate_stack() {
	int used_track = 0, pop_number = 1;
	bool init = false;
	while (!train_carriage.empty()) {
		int train_pop = train_carriage.back();
		train_carriage.pop_back();
		if (train_pop == pop_number) {
			result += "The No." + int_2_string(train_pop) + " carriage go straight to the destination\n";
			pop_number++;
			auto traversal = 0;
			while (traversal < used_track) {
				while (!track[traversal].empty()) {
					int stack_pop_num = track[traversal].top();
					if (stack_pop_num == pop_number) {
						track[traversal].pop();
						result += "The No." + int_2_string(stack_pop_num) + " carriage go to the destination from No." + int_2_string(traversal) + " track\n";
						pop_number++;
						traversal = 0;
					}
					else
					{
						break;
					}
				}
				traversal++;
			}
		}
		else
		{
			if (init == false) {
				used_track++;
				init = true;
			}
			auto Traversal = 0;
			bool need_expand = true;
			for (Traversal = 0; Traversal < used_track; ++Traversal) {
				if (track[Traversal].empty()) {
					track[Traversal].push(train_pop);
					result += "The No." + int_2_string(train_pop) + " carriage go to No." + int_2_string(Traversal) + " track\n";
					need_expand = false;
					break;
				}
				else if (!track[Traversal].empty() && track[Traversal].top() > train_pop) {
					track[Traversal].push(train_pop);
					result += "The No." + int_2_string(train_pop) + " carriage go to No." + int_2_string(Traversal) + " track\n";
					need_expand = false;
					break;
				}
			}
			if (need_expand == true && used_track == track_num) {
				result = "No Answer!\n";
				return result;
			}
			else if (need_expand == true && used_track < track_num) {
				used_track++;
				track[used_track-1].push(train_pop);
				result += "The No." + int_2_string(train_pop) + " carriage go to No." + int_2_string(Traversal) + " track\n";
			}
		}
		auto traversal = 0;
		while (traversal < used_track) {
			while (!track[traversal].empty()) {
				int stack_pop_num = track[traversal].top();
				if (stack_pop_num == pop_number) {
					track[traversal].pop();
					result += "The No." + int_2_string(stack_pop_num) + " carriage go to the destination from No." + int_2_string(traversal) + " track\n";
					pop_number++;
					traversal = 0;
				}
				else
				{
					break;
				}
			}
			traversal++;
		}
	}
	result += "So it need " + int_2_string(used_track) + " track to accomplish the work!\n";
	return result;
}
Solution::~Solution() {}
