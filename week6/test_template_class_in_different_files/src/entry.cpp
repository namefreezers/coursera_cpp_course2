#include <iostream>
using namespace std;

#include "entry.h"

template<typename T1, typename T2>
Entry<T1, T2>::Entry(T1 new_v1, T2 new_v2) : v1(new_v1), v2(new_v2) { }

template<typename T1, typename T2>
T1 Entry<T1, T2>::Get_v1() const {
	return v1;
}

template<typename T1, typename T2>
T2 Entry<T1, T2>::Get_v2() const {
	return v2;
}

template class Entry<int, int>;
