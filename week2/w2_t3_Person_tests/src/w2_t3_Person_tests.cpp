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

class Person {
public:
	void ChangeFirstName(int year, const string &first_name) {
		first_names[year] = first_name;
	}

	void ChangeLastName(int year, const string &last_name) {
		last_names[year] = last_name;
	}

	string GetFullName(int year) {
		string first = get_last(first_names, year);
		string last = get_last(last_names, year);
		if (first == "" && last == "") {
			return "Incognito";
		} else if (first != "" && last != "") {
			return first + " " + last;
		} else if (first != "") {
			return first + " with unknown last name";
		} else { // if (last != "")
			return last + " with unknown first name";
		}
	}

private:
	string get_last(const map<int, string> &names, const int &searched_year) {
		string name = "";
		for (const auto& [y, n] : names) {
			if (y <= searched_year) {
				name = n;
			} else {
				break;
			}
		}
		return name;
	}

	map<int, string> first_names;
	map<int, string> last_names;
};

void test1() {
	Person p;
	p.ChangeFirstName(2000, "f_name1");
	p.ChangeFirstName(2001, "f_name2");
	p.ChangeLastName(2002, "l_name1");
	p.ChangeLastName(2003, "l_name2");
	AssertEqual(p.GetFullName(1999), "Incognito");
	AssertEqual(p.GetFullName(2000), "f_name1 with unknown last name");
	AssertEqual(p.GetFullName(2001), "f_name2 with unknown last name");
	AssertEqual(p.GetFullName(2002), "f_name2 l_name1");
	AssertEqual(p.GetFullName(2003), "f_name2 l_name2");
}

void test11() {
	Person p;
	p.ChangeLastName(2000, "l_name1");
	p.ChangeLastName(2001, "l_name2");
	p.ChangeFirstName(2002, "f_name1");
	p.ChangeFirstName(2003, "f_name2");
	AssertEqual(p.GetFullName(1999), "Incognito");
	AssertEqual(p.GetFullName(2000), "l_name1 with unknown first name");
	AssertEqual(p.GetFullName(2001), "l_name2 with unknown first name");
	AssertEqual(p.GetFullName(2002), "f_name1 l_name2");
	AssertEqual(p.GetFullName(2003), "f_name2 l_name2");
}

void test2() {
	Person p;
	AssertEqual(p.GetFullName(2000), "Incognito");
	p.ChangeFirstName(2000, "f_name1");
	AssertEqual(p.GetFullName(1999), "Incognito");
	AssertEqual(p.GetFullName(2000), "f_name1 with unknown last name");
	p.ChangeLastName(2000, "l_name1");
	AssertEqual(p.GetFullName(1999), "Incognito");
	AssertEqual(p.GetFullName(2000), "f_name1 l_name1");
}

void test3() {
	Person p;
	AssertEqual(p.GetFullName(2000), "Incognito");
	p.ChangeFirstName(2001, "f_name1");
	AssertEqual(p.GetFullName(2000), "Incognito");
	p.ChangeFirstName(1998, "f_name2");
	AssertEqual(p.GetFullName(2000), "f_name2 with unknown last name");
	p.ChangeFirstName(1999, "f_name3");
	AssertEqual(p.GetFullName(2000), "f_name3 with unknown last name");
	p.ChangeFirstName(1997, "f_name4");
	AssertEqual(p.GetFullName(2000), "f_name3 with unknown last name");
}

void test32() {
	Person p;
	AssertEqual(p.GetFullName(2000), "Incognito");
	p.ChangeLastName(2001, "l_name1");
	AssertEqual(p.GetFullName(2000), "Incognito");
	p.ChangeLastName(1998, "l_name2");
	AssertEqual(p.GetFullName(2000), "l_name2 with unknown first name");
	p.ChangeLastName(1999, "l_name3");
	AssertEqual(p.GetFullName(2000), "l_name3 with unknown first name");
	p.ChangeLastName(1997, "l_name4");
	AssertEqual(p.GetFullName(2000), "l_name3 with unknown first name");
}

int main() {
	TestRunner runner;
	runner.RunTest(test1, "test1");
	runner.RunTest(test11, "test11");
	runner.RunTest(test2, "test2");
	runner.RunTest(test3, "test3");
	runner.RunTest(test32, "test32");
	return 0;
}
