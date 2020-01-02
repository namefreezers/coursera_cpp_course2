#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include <phone_number.h>

PhoneNumber::PhoneNumber(const string &international_number) {
	stringstream ss(international_number);
	if (ss.get() != '+') {
		throw invalid_argument("");
	}
	if (!getline(ss, country_code_, '-')) {
		throw invalid_argument("");
	}
	if (!getline(ss, city_code_, '-')) {
		throw invalid_argument("");
	}
	if (!getline(ss, local_number_)) {
		throw invalid_argument("");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

//int main() {
//	PhoneNumber pn1("+7-495-111-22-33");
//	PhoneNumber pn2("+7-495-1112233");
//	PhoneNumber pn3("+323-22-460002");
//	PhoneNumber pn4("+1-2-coursera-cpp");
//	for (PhoneNumber pn : {pn1, pn2, pn3, pn4}) {
//		cout << pn.GetCountryCode() << " " << pn.GetCityCode() << " " << pn.GetLocalNumber() << " " << pn.GetInternationalNumber() << endl;
//	}
//
////	PhoneNumber pn5("1-2-333");
////	PhoneNumber pn5("+7-1233");
//}
