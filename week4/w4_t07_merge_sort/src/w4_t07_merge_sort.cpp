#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int len = range_end - range_begin;
	RandomIt range_mid = range_begin + len / 2;
	if (len <= 1) {
		return;
	}
	vector<typename RandomIt::value_type> part1(range_begin, range_mid), part2(range_mid, range_end); // or swap this and next
	MergeSort(part1.begin(), part1.end());															  // or swap this and prev
	MergeSort(part2.begin(), part2.end());
	merge(part1.begin(), part1.end(), part2.begin(), part2.end(), range_begin);
}

template<typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end) {
	int len = range_end - range_begin;
	RandomIt range_mid1 = range_begin + len / 3;
	RandomIt range_mid2 = range_mid1 + len / 3;
	if (len <= 1) {
		return;
	}
	vector<typename RandomIt::value_type> part1(range_begin, range_mid1), part2(range_mid1, range_mid2), part3(range_mid2, range_end); // or swap this and next
	MergeSort(part1.begin(), part1.end());															  // or swap this and prev
	MergeSort(part2.begin(), part2.end());
	MergeSort(part3.begin(), part3.end());

	vector<typename RandomIt::value_type> temp_part1_part2;
	merge(part1.begin(), part1.end(), part2.begin(), part2.end(), back_inserter(temp_part1_part2)); // merge part1 and part2
	merge(temp_part1_part2.begin(), temp_part1_part2.end(), part3.begin(), part3.end(), range_begin); // merge part1_part2 and part3
}

int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort3(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
