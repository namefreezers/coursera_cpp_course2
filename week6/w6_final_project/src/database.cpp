#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#include "database.h"
#include "date.h"
#include "entry.h"

void Database::Add(const Date &d, const string &event) {
	if (db_if_contains[d].count(event) != 0) {
		return;
	}
	db_if_contains[d].insert(event);
	db[d].push_back(event);
}

void Database::Print(ostream &os) const {
	for (const auto& [date, events] : db) {
		for (const string &event : events) {
			os << date << ' ' << event << '\n';
		}
	}
}

Entry<Date, string> Database::Last(const Date& d) const {
	auto it = db.upper_bound(d);
	if (it == db.begin()) {
		throw invalid_argument("");
	}
	--it;
	return Entry<Date, string>(it->first, it->second.back());
}

