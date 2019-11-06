#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

const auto& getComparable(const Region &r) {
	return tie(r.std_name, r.parent_std_name, r.names, r.population);
}

bool operator<(const Region &r1, const Region &r2) {
	return getComparable(r1) < getComparable(r2);
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
	map<Region, int> count;
	for (const Region &r : regions) {
		count[r]++;
	}

	int max = 0;
	for (const auto& [r, c] : count) {
		if (c > max) {
			max = c;
		}
	}
	return max;
}

int main() {
	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
	}) << endl;

	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Toulouse",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  31
	  },
	}) << endl;

    return 0;
}
