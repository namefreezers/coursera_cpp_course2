#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name) : Name(name) { }

	virtual void Walk(const string& destination) const {
		cout << Who() << ": " << Name << " walks to: " << destination << '\n';
	}

	virtual string Who() const = 0;

	string GetName() const {
		return Name;
	}

protected:
	const string Name;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name), FavouriteSong(favouriteSong) { }

    string Who() const override {
    	return "Student";
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << '\n';
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << '\n';
    }

private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:

    Teacher(const string& name, const string& subject) : Person(name), Subject(subject) { }

	string Who() const override {
		return "Teacher";
	}

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name) { }

	string Who() const override {
		return "Policeman";
	}

    void Check(const Person& person) {
        cout << "Policeman: " << Name << " checks " << person.Who() << ". "<< person.Who() << "'s name is: " << person.GetName() << endl;
    }

};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
    	person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
