#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#include "date.h"
#include "entry.h"

class Database {
public:
	void Add(const Date &d, const string &event);

	void Print(ostream &os);

	template<typename Pred>
	int RemoveIf(Pred pred);

	template<typename Pred>
	vector<Entry<Date, string>> FindIf(Pred pred);

	Entry<Date, string> Last(const Date& d);

private:
	map<Date, vector<string>> db;
	map<Date, set<string>> db_if_contains;
};
