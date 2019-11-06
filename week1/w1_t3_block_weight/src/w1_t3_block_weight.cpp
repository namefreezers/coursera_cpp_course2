#include <cstdint>
#include <iostream>
using namespace std;

int main() {
	cout << "A";

	int N;
	int R;
	cin >> N >> R;

	uint64_t res = 0;
	for (int i = 0; i < N; ++i) {
		int W, H, D;
		cin >> W >> H >> D;
		res += static_cast<uint64_t>(W) * H * D * R;
	}
	cout << res;

	return 0;
}
