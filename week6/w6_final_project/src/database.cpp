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

void Database::Print(ostream& os) {

}
