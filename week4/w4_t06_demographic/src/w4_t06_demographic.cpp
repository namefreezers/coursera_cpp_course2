#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//enum class Gender {
//	FEMALE, MALE
//};
//
//struct Person {
//	int age;  // возраст
//	Gender gender;  // пол
//	bool is_employed;  // имеет ли работу
//};

template<typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

//template<typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
//	size_t n = (range_end - range_begin) / 2;
//	nth_element(range_begin, range_begin + n, range_end, [](Person p1, Person p2) {return p1.age < p2.age;});
//	return (range_begin + n)->age;
//}

bool all_people(const Person &p) {
	return true;
}

bool all_women(const Person &p) {
	return p.gender == Gender::FEMALE;
}

bool all_men(const Person &p) {
	return p.gender == Gender::MALE;
}

bool all_employed_women(const Person &p) {
	return p.gender == Gender::FEMALE && p.is_employed;
}

bool all_unemployed_women(const Person &p) {
	return p.gender == Gender::FEMALE && !p.is_employed;
}

bool all_employed_men(const Person &p) {
	return p.gender == Gender::MALE && p.is_employed;
}

bool all_unemployed_men(const Person &p) {
	return p.gender == Gender::MALE && !p.is_employed;
}

void PrintStats(vector<Person> persons) {

	vector<pair<function<bool(const Person&)>, string>> preds_strings = {
			{ all_people, "Median age = " },
			{ all_women, "Median age for females = " },
			{ all_men, "Median age for males = " },
			{ all_employed_women, "Median age for employed females = " },
			{ all_unemployed_women, "Median age for unemployed females = " },
			{ all_employed_men, "Median age for employed males = " },
			{ all_unemployed_men, "Median age for unemployed males = " } };

	for (auto [pred, descr] : preds_strings) {

		auto end_partitioned_it = partition(begin(persons), end(persons), pred);
		cout << descr << ComputeMedianAge(begin(persons), end_partitioned_it) << '\n';

	}
}

int main() {
	vector<Person> persons = {
			{ 31, Gender::MALE, false },
			{ 40, Gender::FEMALE, true },
			{ 24, Gender::MALE, true },
			{ 20, Gender::FEMALE, true },
			{ 80, Gender::FEMALE, false },
			{ 78, Gender::MALE, false },
			{ 10, Gender::FEMALE, false },
			{ 55, Gender::MALE, true }
	};
	PrintStats(persons);
	return 0;
}
