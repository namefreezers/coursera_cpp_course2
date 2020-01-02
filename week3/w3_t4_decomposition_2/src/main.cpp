#include <iostream>
using namespace std;

#include <bus_manager.h>
#include <query.h>

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
			cout << bm.GetBusesForStop(q.stop);
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus);
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses();
			break;
		}
	}

	return 0;
}

