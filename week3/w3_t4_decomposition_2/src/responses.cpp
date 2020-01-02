#include <iostream>
#include <string>
using namespace std;

#include <responses.h>

ostream& operator <<(ostream &os, const BusesForStopResponse &r) {
	if (r.buses_this_stop.size() == 0) {
		os << "No stop" << endl;
		return os;
	}
	for (const string &b : r.buses_this_stop) {
		os << b << " ";
	}
	os << endl;
	return os;
}


ostream& operator <<(ostream &os, const StopsForBusResponse &r) {
	if (r.stops.size() == 0) {
		os << "No bus" << endl;
		return os;
	}
	for (const string &stop : r.stops) {
		os << "Stop " << stop << ": ";
		if (r.interchanges.count(stop) == 0) {
			os << "no interchange";
		} else {
			for (const string &other_bus : r.interchanges.at(stop)) {
				os << other_bus << " ";
			}
		}
		os << endl;
	}
	return os;
}


ostream& operator <<(ostream &os, const AllBusesResponse &r) {
	if (r.buses.empty()) {
		os << "No buses" << endl;
		return os;
	}

	for (const auto& [bus, stops] : r.buses) {
		os << "Bus " << bus << ": ";
		for (const string &stop : stops) {
			os << stop << " ";
		}
		os << endl;
	}

	return os;
}
