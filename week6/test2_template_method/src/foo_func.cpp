#include <iostream>
using namespace std;

#include "foo_func.h"

template <typename T>
void g(T arg) {
	cout << arg << endl;
}

template void g<int>(int);
