#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class QueryType {
	NewBus, BusesForStop, StopsForBus, AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >>(istream &is, Query &q) {
	string operation_code;
	cin >> operation_code;
	if (operation_code == "NEW_BUS") {
		q.type = QueryType::NewBus;
		cin >> q.bus;
		int stop_count;
		cin >> stop_count;
		q.stops.resize(stop_count);
		for (string &stop : q.stops) {
			cin >> stop;
		}

	} else if (operation_code == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		cin >> q.stop;

	} else if (operation_code == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		cin >> q.bus;

	} else if (operation_code == "ALL_BUSES") {
		q.type = QueryType::AllBuses;

	}

	return is;
}

struct BusesForStopResponse {
	vector<string> buses_this_stop;
};

ostream& operator <<(ostream &os, const BusesForStopResponse &r) {
	if (r.buses_this_stop.size() == 0) {
		os << "No stop" << endl;
		return os;
	}
	for (const string &b : r.buses_this_stop) {
		os << b << " ";
	}
	return os;
}

struct StopsForBusResponse {
	vector<string> stops;
	map<string, vector<string>> interchanges;
};

ostream& operator <<(ostream &os, const StopsForBusResponse &r) {
	if (r.stops.size() == 0) {
		cout << "No bus";
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

struct AllBusesResponse {
	map<string, vector<string>> buses;
};

ostream& operator <<(ostream &os, const AllBusesResponse &r) {
	if (r.buses.empty()) {
		os << "No buses";
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

class BusManager {
public:
	void AddBus(const string &new_bus, const vector<string> &new_stops) {
		buses[new_bus] = new_stops;
		for (const string &stop : new_stops) {
			stops[stop].push_back(new_bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const {
		BusesForStopResponse res;
		if (stops.count(stop) == 1) {
			res.buses_this_stop = stops.at(stop);
		}
		return res;
	}

	StopsForBusResponse GetStopsForBus(const string &bus) const {
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

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse res;
		if (buses.size() == 0) {
			return res;
		}
		res.buses = buses;
		return res;
	}

private:
	map<string, vector<string>> buses;
	map<string, vector<string>> stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}

