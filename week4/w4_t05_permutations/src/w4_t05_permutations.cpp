#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void print_v(const vector<T>& v) {
	for (const T& elem : v) {
		cout << elem << " ";
	}
	cout << '\n';
}

int main() {
	int amount;
	cin >> amount;
	vector<int> v;
	for (int i = 1; i <= amount; i++) {
		v.push_back(i);
	}

	prev_permutation(begin(v), end(v));
	print_v(v);
	while(prev_permutation(begin(v), end(v))) {
		print_v(v);
	}
	return 0;
}
