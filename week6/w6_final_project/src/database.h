#include <algorithm>
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
	int RemoveIf(Pred pred) {
		int res;

		// clear db (linear). Elements order is preserved
		for (auto& [date, events] : db) {
			auto end_not_removed = remove_if(events.begin(), events.end(), [&pred, &date](const string &event) {
				return pred(date, event);
			});
			res = events.end() - end_not_removed;
			events.erase(end_not_removed, events.end());
		}

		// clear db_if_contains (linear)
		for (pair<const Date, set<string>> &date_events_set : db_if_contains) { // todo
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
	vector<Entry<Date, string>> FindIf(Pred pred) {
		vector<Entry<Date, string>> res;
		for (const auto& [date, events] : db) {
			for (const string& event : events) {
				if (pred(date, event)) {
					res.push_back(Entry(date,event));
				}
			}
		}
		return res;
	}

	Entry<Date, string> Last(const Date& d);

private:
	map<Date, vector<string>> db;
	map<Date, set<string>> db_if_contains;
};
