#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#include "database.h"
#include "date.h"

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

	// clear db (linear)
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
vector<pair<Date, string>> Database::FindIf(Pred pred) {

}

template<typename T1, typename T2>
Entry<T1, T2>::Entry(const T1 &new_v1, const T2 &new_v2) : v1(new_v1), v2(new_v2) { }

template<typename T1, typename T2>
T1 Entry<T1, T2>::Get_v1() const {
	return v1;
}

template<typename T1, typename T2>
T2 Entry<T1, T2>::Get_v2() const {
	return v2;
}

