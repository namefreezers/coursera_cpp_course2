#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements){
	sort(begin(elements), end(elements));
	auto end_unique_it = unique(begin(elements), end(elements));
	elements.erase(end_unique_it, end(elements));
}

// long
//template <typename T>
//void RemoveDuplicates(vector<T>& elements){
//	set<T> s(begin(elements), end(elements));
//	elements.assign(begin(s), end(s));
//}

int main() {
  vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
  RemoveDuplicates(v1);
  for (int x : v1) {
    cout << x << " ";
  }
  cout << endl;

  vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
  RemoveDuplicates(v2);
  for (const string& s : v2) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}

// 6 4 7 0 1
// C++ C
