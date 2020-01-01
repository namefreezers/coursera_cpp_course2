#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<class T>
ostream& operator <<(ostream &os, const vector<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class T>
ostream& operator <<(ostream &os, const set<T> &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template<class K, class V>
ostream& operator <<(ostream &os, const map<K, V> &m) {
	os << "{";
	bool first = true;
	for (const auto &kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = { }) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string &hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const string &test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception &e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a != 0) {
		double d = b * b - 4 * a * c;
		if (d < 0) {
			return 0;
		} else if (d == 0) {
			return 1;
		} else {
			return 2;
		}
	} else {
		if (b == 0) {
			return 0;
		} else {
			return 1;
		}
	}
}

void test_normal() {
	AssertEqual(GetDistinctRealRootCount(1, 4, 2), 2);
}

void test_d_0() {
	AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1);
}

void test_d_lt() {
	AssertEqual(GetDistinctRealRootCount(2, 3, 2), 0);
}

void test_lin_no() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0);
}

void test_lin_norm() {
	AssertEqual(GetDistinctRealRootCount(0, 3, 0), 1);
}

void test_lin_norm2() {
	AssertEqual(GetDistinctRealRootCount(0, 3, 2), 1);
}

int main() {
	TestRunner runner;
	runner.RunTest(test_normal, "test_normal");
	runner.RunTest(test_d_0, "test_d_0");
	runner.RunTest(test_d_lt, "test_d_lt");
	runner.RunTest(test_lin_no, "test_lin_no");
	runner.RunTest(test_lin_norm, "test_lin_norm");
	runner.RunTest(test_lin_norm2, "test_lin_norm2");
	return 0;
}
