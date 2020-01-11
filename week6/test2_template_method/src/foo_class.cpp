#include <iostream>
using namespace std;

#include "foo_class.h"


template <typename T>
void Entry::f(T i) {
	cout << (i > 2) << endl;
}

template void Entry::f<int>(int);

