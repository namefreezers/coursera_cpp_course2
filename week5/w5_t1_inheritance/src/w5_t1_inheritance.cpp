#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	Animal(const string& new_name) : Name(new_name) {

	}

    const string Name;
};


class Dog : public Animal {
public:
    Dog(const string& new_name) : Animal(new_name) {

    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};


int main() {
	Dog d("abc");
	d.Bark();
	return 0;
}
