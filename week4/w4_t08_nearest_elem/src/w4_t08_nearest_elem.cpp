#include <iostream>
#include <set>
using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {
	auto it = numbers.lower_bound(border);
	if (it == begin(numbers) ||
			(it != end(numbers) && (*it - border) < (border - *prev(it)))) {
		return it;
	} else {
		return prev(it);  // if equal, then prev(it). Lower
	}
}

int main() {
	set<int> numbers = { 1, 4, 6 };
	cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " " << *FindNearestElement(numbers, 5) << " "
			<< *FindNearestElement(numbers, 6) << " " << *FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}

// 1 4 4 6 6
// 1
