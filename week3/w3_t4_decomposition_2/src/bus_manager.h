#pragma once

#include <map>
#include <string>
#include <vector>
using namespace std;

#include <responses.h>

class BusManager {
public:
	void AddBus(const string &new_bus, const vector<string> &new_stops);

	BusesForStopResponse GetBusesForStop(const string &stop) const;

	StopsForBusResponse GetStopsForBus(const string &bus) const;

	AllBusesResponse GetAllBuses() const;

private:
	map<string, vector<string>> buses;
	map<string, vector<string>> stops;
};
