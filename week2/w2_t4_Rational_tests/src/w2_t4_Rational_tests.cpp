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

//class Rational {
//public:
//	Rational() {
//		num = 0;
//		denom = 1;
//	}
//
//	Rational(int numerator, int denominator) {
//		change(numerator, denominator);
//	}
//
//	int Numerator() const {
//		return num;
//	}
//
//	int Denominator() const {
//		return denom;
//	}
//
//private:
//	void change(int numerator, int denominator) {
//		int gcd = GCD_euclid(numerator, denominator);
//		numerator /= gcd;
//		denominator /= gcd;
//		if (denominator < 0) {
//			numerator = -numerator;
//			denominator = -denominator;
//		}
//		num = numerator;
//		denom = denominator;
//	}
//
//	int GCD_euclid(int a, int b) {
//		a = abs(a);
//		b = abs(b);
//		while (a > 0 && b > 0) {
//			if (a > b) {
//				a = a % b;
//			} else {
//				b = b % a;
//			}
//		}
//		return a + b;
//	}
//
//	int num;
//	int denom;
//};

void test1_default_constr() {
	Rational r;
	AssertEqual(r.Numerator(), 0);
	AssertEqual(r.Denominator(), 1);
}

void test2_fraction_reduction() {
	Rational r(2, 1), r2(6, 3);
	AssertEqual(r.Numerator(), 2);
	AssertEqual(r.Denominator(), 1);
	AssertEqual(r2.Numerator(), 2);
	AssertEqual(r2.Denominator(), 1);
}

void test3_positive_denom() {
	Rational r(-2, 1), r2(2, -1), r3(6, -3), r4(-6, 3);
	AssertEqual(r.Numerator(), -2);
	AssertEqual(r.Denominator(), 1);
	AssertEqual(r2.Numerator(), -2);
	AssertEqual(r2.Denominator(), 1);
	AssertEqual(r3.Numerator(), -2);
	AssertEqual(r3.Denominator(), 1);
	AssertEqual(r4.Numerator(), -2);
	AssertEqual(r4.Denominator(), 1);
}

void test4_positive_nom_denom() {
	Rational r(-2, -1), r2(-6, -3);
	AssertEqual(r.Numerator(), 2);
	AssertEqual(r.Denominator(), 1);
	AssertEqual(r2.Numerator(), 2);
	AssertEqual(r2.Denominator(), 1);
}

void test5_nom_0_denom_1() {
	Rational r(0, -5), r2(0, 2), r3(0, 1);
	AssertEqual(r.Numerator(), 0);
	AssertEqual(r.Denominator(), 1);
	AssertEqual(r2.Numerator(), 0);
	AssertEqual(r2.Denominator(), 1);
	AssertEqual(r3.Numerator(), 0);
	AssertEqual(r3.Denominator(), 1);
}

int main() {
	TestRunner runner;
	runner.RunTest(test1_default_constr, "test1_default_constr");
	runner.RunTest(test2_fraction_reduction, "test2_fraction_reduction");
	runner.RunTest(test3_positive_denom, "test3_positive_denom");
	runner.RunTest(test4_positive_nom_denom, "test4_positive_nom_denom");
	runner.RunTest(test5_nom_0_denom_1, "test5_nom_0_denom_1");
	return 0;
}
