#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& profession) : name(name), profession(profession) {};

    string GetName() const {
        return name;
    }

    string GetProfession() const {
        return profession;
    }

    virtual void Walk(const string& destination) const {
        cout << GetProfession() << ": " << GetName() << " walks to: " << destination << endl;
    };

private:
    const string name;
    const string profession;
};


class Student : public Human {
public:

    Student(const string& name, const string& favourite_song) : Human(name, "Student"), favourite_song(favourite_song) {};

    void Learn() const {
        cout << "Student: " << GetName() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << GetName() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << GetName() << " sings a song: " << favourite_song << endl;
    }

private:
    const string favourite_song;
};


class Teacher : public Human {
public:
    Teacher(const string& name, const string& subject) : Human(name, "Teacher"), subject(subject) {}

    void Teach() const {
        cout << "Teacher: " << GetName() << " teaches: " << subject << endl;
    }

private:
    const string subject;
};


class Policeman : public Human {
public:
    explicit Policeman(const string& name) : Human(name, "Policeman") {};

    void Check(const Human& human) const {
        cout << "Policeman: " << GetName() << " checks " << human.GetProfession() << ". "
            << human.GetProfession() << "'s name is: " << human.GetName() << endl;
    }

};

void VisitPlaces(const Human& human, const vector<string>& places) {
    for (const auto& place : places) {
        human.Walk(place);
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