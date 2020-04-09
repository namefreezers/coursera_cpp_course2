#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& profession) : Name(name), Profession(profession) {}
    const string& GetProfession() const { return Profession; }
    const string& GetName() const { return Name; }
    // Этот метод объявлен константным, поскольку фактически выполняемая им работа не меняет состояние объекта.
    // В настоящем коде, скорее всего, такой метод не был бы константным.
    virtual void Walk(const string& destination) const {
        cout << Profession << ": " << Name << " walks to: " << destination << endl;
    }
protected:
    const string Name;
    const string Profession;
};


class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong)
      : Human(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << Profession << ": " << Name << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Profession << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }
protected:
    const string FavouriteSong;
};


class Teacher : public Human {
public:
    Teacher(const string& name, const string& subject)
      : Human(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << Profession << ": " << Name << " teaches: " << Subject << endl;
    }
protected:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman") {}

    void Check(const Human& h) const {
        cout << Profession << ": " << Name << " checks " << h.GetProfession() << ". "
             << h.GetProfession() << "'s name is: " << h.GetName() << endl;
    }
};


void VisitPlaces(Human& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    t.Teach();
    return 0;
}
