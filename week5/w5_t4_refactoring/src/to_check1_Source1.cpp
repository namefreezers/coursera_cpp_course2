#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string& type, const string& name) : type_(type), name_(name) {}

	string Type_Name() const {
		return type_ + ": " + name_;
	}

	virtual void Walk(string destination) const {
		cout << Type_Name() << " walks to: " << destination << endl;
	}

	string GetName() const {
		return name_;
	}

	string GetType() const {
		return type_;
	}
private:
	const string type_;
	const string name_;
};

class Student : public Human{
public:
	Student(const string& name, const string& favouriteSong) : Human("Student", name), favourite_song_(favouriteSong) {}

	void Learn() const{
		cout << Type_Name() << " learns" << endl;
	}

	void Walk(string destination) const override{
		cout << Type_Name() << " walks to: " << destination << endl;
		SingSong();
	}

	void SingSong() const {
		cout << Type_Name() << " sings a song: " << favourite_song_ << endl;
	}

private:
	const string favourite_song_;
};


class Teacher : public Human{
public:

	Teacher(const string& name, const string& subject) : Human("Teacher", name), subject_(subject) {}

	void Teach() const {
		cout << Type_Name() << " teaches: " << subject_ << endl;
	}

public:
	const string subject_;
};


class Policeman : public Human{
public:
	Policeman(const string& name) : Human("Policeman", name) {}

	void Check(Human& h) const {
		cout << Type_Name() << " checks " << h.GetType() << ". " << h.GetType() << "'s name is: " << h.GetName() << endl;
	}
};


void VisitPlaces(Human& h, vector<string> places) {
	for (auto p : places) {
		h.Walk(p);
	}
}

int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });

	return 0;
}