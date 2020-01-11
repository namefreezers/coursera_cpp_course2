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

void Database::Print(ostream &os) {
	for (const auto& [date, events] : db) {
		for (const string &event : events) {
			os << date << ' ' << event << '\n';
		}
	}
}

template<typename Pred>
int Database::RemoveIf(Pred pred) {
	int res;

	// clear db (linear). Elements order is preserved
	for (const auto& [date, events] : db) {
		auto end_not_removed = remove_if(events.begin(), events.end(), [&pred, &date](const string &event) {
			return pred(date, event);
		});
		res = events.end() - end_not_removed;
		events.erase(end_not_removed, events.end());
	}

	// clear db_if_contains (linear)
	for (const pair<Date, set<string>> &date_events_set : db_if_contains) {
		Date date = date_events_set.first;
		set<string> events_set = date_events_set.second;

		for (set<string>::const_iterator it_event_set = events_set.begin(); it_event_set != events_set.end();) {
			if (pred(date, *it_event_set)) {
				it_event_set = events_set.erase(it_event_set);
			} else {
				++it_event_set;
			}
		}
	}

	return res;
}

template<typename Pred>
vector<Entry<Date, string>> Database::FindIf(Pred pred) {
	vector<Entry<Date, string>> res;
	for (const auto& [date, events] : db) {
		auto end_not_removed = copy_if(events.begin(), events.end(), back_inserter(res),
				[&pred, &date](const string &event) {
			return pred(date, event);
		});
	}
}

Entry<Date, string> Database::Last(const Date& d) {
	auto it = db.upper_bound(d);
	if (it == db.begin()) {
		throw invalid_argument("");
	}
	--it;
	return Entry<Date, string>(it->first, it->second[it->second.size() - 1]);
}

