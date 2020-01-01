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

bool IsPalindrom(const string &str) {
	for (size_t i = 0; i < str.size() / 2; i++) {
		if (str[i] != str[str.size() - 1 - i]) {
			return false;
		}
	}
	return true;
}

void test1_true() {
	AssertEqual(IsPalindrom("madam"), true, "1111111111");
	AssertEqual(IsPalindrom("a"), true, "22222222222");
	AssertEqual(IsPalindrom(" "), true, "333333333333");
	AssertEqual(IsPalindrom("maddam"), true, "44444444444");
	AssertEqual(IsPalindrom("mm"), true, "5555555555555");
	AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "66666666666666");
}

void test2_false() {
	AssertEqual(IsPalindrom("amadam"), false);
	AssertEqual(IsPalindrom("madama"), false);
	AssertEqual(IsPalindrom("ma dam"), false);
	AssertEqual(IsPalindrom("mmdamm"), false);
	AssertEqual(IsPalindrom("mmdaamm"), false);
	AssertEqual(IsPalindrom("  madam"), false);
	AssertEqual(IsPalindrom(" madam"), false);
	AssertEqual(IsPalindrom("madam "), false);
}

int main() {
	TestRunner runner;
	runner.RunTest(test1_true, "test1_true");
	runner.RunTest(test2_false, "test2_false");
	return 0;
}
