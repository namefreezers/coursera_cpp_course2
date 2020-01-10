#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#include "date.h"

class Database {
public:
	void Add(const Date &d, const string &event);

	void Print(ostream &os);

	template<typename Pred>
	int RemoveIf(Pred pred);

	template<typename Pred>
	vector<pair<Date, string>> FindIf(Pred pred);

private:
	map<Date, vector<string>> db;
	map<Date, set<string>> db_if_contains;
};

template<typename T1, typename T2>
class Entry {
public:
	Entry(const T1 &new_v1, const T2 &new_v2);

	T1 Get_v1() const;

	T2 Get_v2() const;

private:
	T1 v1;
	T2 v2;
};
