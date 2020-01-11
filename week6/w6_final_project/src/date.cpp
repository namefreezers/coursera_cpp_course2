#include <iomanip>
#include <iostream>
using namespace std;

#include "date.h"

Date::Date() { }

Date::Date(int new_year, int new_month, int new_day) {
	SetDate(new_year, new_month, new_day);
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

void Date::SetDate(int new_year, int new_month, int new_day) {
	if (new_month < 1 || new_month > 12) {
		throw invalid_argument("Month value is invalid: " + to_string(new_month));
	}
	if (new_day < 1 || new_day > 31) {
		throw invalid_argument("Day value is invalid: " + to_string(new_day));
	}
	year = new_year;
	month = new_month;
	day = new_day;
}

auto Date::GetComparable() const {
	return tie(year, month, day);
}

istream& operator>>(istream &stream, Date &d) {
	string date_str;
	stream >> date_str;

	stringstream ss(date_str);
	int year, month, day;
	if (!(ss >> year)) {
		throw runtime_error("Wrong date format: " + date_str);
	}
	if (ss.peek() != '-') {
		throw runtime_error("Wrong date format: " + date_str);
	}
	ss.ignore(1);
	if (!(ss >> month)) {
		throw runtime_error("Wrong date format: " + date_str);
	}
	if (ss.peek() != '-') {
		throw runtime_error("Wrong date format: " + date_str);
	}
	ss.ignore(1);
	if (!(ss >> day)) {
		throw runtime_error("Wrong date format: " + date_str);
	}
	string temp;
	if (ss >> temp) { // anything left
		throw runtime_error("Wrong date format: " + date_str);
	}

	d.SetDate(year, month, day);
	return stream;
}

ostream& operator<<(ostream &stream, const Date &d) {
	stream << setfill('0');
	return stream << setw(4) << d.GetYear() << '-' << setw(2) << d.GetMonth() << '-' << setw(2) << d.GetDay();
}

bool operator<(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() < rhs.GetComparable();
}

bool operator<=(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() <= rhs.GetComparable();
}

bool operator>(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() > rhs.GetComparable();
}

bool operator>=(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() >= rhs.GetComparable();
}

bool operator==(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() == rhs.GetComparable();
}

bool operator!=(const Date &lhs, const Date &rhs) {
	return lhs.GetComparable() != rhs.GetComparable();
}

Date ParseDate(istream &is) {
	Date d;
	is >> d;
	return d;
}
