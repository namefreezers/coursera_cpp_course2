#include <string>
#include <vector>
using namespace std;

#include <bus_manager.h>

void BusManager::AddBus(const string &new_bus, const vector<string> &new_stops) {
	buses[new_bus] = new_stops;
	for (const string &stop : new_stops) {
		stops[stop].push_back(new_bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
	BusesForStopResponse res;
	if (stops.count(stop) == 1) {
		res.buses_this_stop = stops.at(stop);
	}
	return res;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
	StopsForBusResponse res;
	if (buses.count(bus) == 0) {
		return res;
	}
	res.stops = buses.at(bus);
	for (const string &stop : res.stops) {
		if (stops.at(stop).size() > 1) {
			for (const string &interchange_bus : stops.at(stop)) {
				if (interchange_bus != bus) {
					res.interchanges[stop].push_back(interchange_bus);
				}
			}
		}
	}
	return res;
}

AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse res;
	if (buses.size() == 0) {
		return res;
	}
	res.buses = buses;
	return res;
}

