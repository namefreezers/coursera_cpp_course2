#include <iostream>
using namespace std;

template<typename T1, typename T2>
class Entry {
public:
	Entry(T1 new_v1, T2 new_v2);

	T1 Get_v1() const;

	T2 Get_v2() const;

private:
	T1 v1;
	T2 v2;
};
