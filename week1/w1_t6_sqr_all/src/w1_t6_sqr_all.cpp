#include <iostream>
#include <map>
#include <vector>
using namespace std;

template<typename T>
T Sqr(const T &to_sqr);

template<typename T>
vector<T> Sqr(const vector<T> &to_sqr);

template<typename K, typename V>
map<K, V> Sqr(const map<K, V> &to_sqr);

template<typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2> &to_sqr);

template<typename T>
T Sqr(const T &to_sqr) {
	return to_sqr * to_sqr;
}

template<typename T>
vector<T> Sqr(const vector<T> &to_sqr) {
	vector<T> res;
	for (const T &item : to_sqr) {
		res.push_back(Sqr(item));
	}
	return res;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V> &to_sqr) {
	map<K, V> res;
	for (const auto& [k, v] : to_sqr) {
		res[k] = Sqr(v);
	}
	return res;
}

template<typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2> &to_sqr) {
	return {Sqr(to_sqr.first), Sqr(to_sqr.second)};
}

int main() {
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = { { 4, { 2, 2 } }, { 7, { 4, 3 } } };
	cout << "map of pairs:" << endl;
	for (const auto &x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second
				<< endl;
	}
	return 0;
}
