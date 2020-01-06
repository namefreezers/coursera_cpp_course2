#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> SplitIntoWords(const string &s) {
	vector<string> res;
	auto begin_cur_it = begin(s);
	while (begin_cur_it != end(s)) {
		auto end_cur_it = find(begin_cur_it, end(s), ' ');

		res.push_back(string(begin_cur_it, end_cur_it));

		if (end_cur_it == end(s)) {
			break;
		}
		// else
		begin_cur_it = next(end_cur_it);
	}
	return res;
}

int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	// 4 С/Cpp/Java/Python

	return 0;
}
