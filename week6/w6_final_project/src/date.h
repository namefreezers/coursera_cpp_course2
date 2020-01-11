#pragma once

#include <iomanip>
#include <iostream>
using namespace std;

class Date {
public:
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	void SetDate(int new_year, int new_month, int new_day);

	auto GetComparable() const;

private:
	int year;
	int month;
	int day;
};

istream& operator>>(istream &stream, Date &d);
ostream& operator<<(ostream &stream, const Date &d);

bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);

Date ParseDate(istream &is);
