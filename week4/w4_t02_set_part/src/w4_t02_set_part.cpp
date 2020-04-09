#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
	return { elements.upper_bound(border), elements.end() };
}

//template<typename T>
//vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
//	vector<T> res;
//	copy(elements.upper_bound(border), elements.end(), back_inserter(res));
//	return res;
//}

int main() {
	for (int x : FindGreaterElements(set<int> { 1, 5, 7, 8 }, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string> { "C", "C++" }, to_find).size() << endl;
	return 0;
}
