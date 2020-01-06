#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Figure {
public:
	virtual string Name() = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
};

class Triangle: public Figure {
public:
	Triangle(double new_s1, double new_s2, double new_s3) :
			s1(new_s1), s2(new_s2), s3(new_s3) {
	}

	virtual string Name() override {
		return "TRIANGLE";
	}

	virtual double Perimeter() override {
		return s1 + s2 + s3;
	}

	virtual double Area() override {
		double p = Perimeter() / 2;
		return sqrt(p * (p - s1) * (p - s2) * (p - s3));
	}
private:
	const double s1, s2, s3;
};

class Rect: public Figure {
public:
	Rect(double new_s1, double new_s2) :
			s1(new_s1), s2(new_s2) {
	}

	virtual string Name() override {
		return "RECT";
	}

	virtual double Perimeter() override {
		return s1 + s2 + s1 + s2;
	}

	virtual double Area() override {
		return s1 * s2;
	}

private:
	const double s1, s2;
};

class Circle: public Figure {
public:
	Circle(double new_r) :
			r(new_r) {
	}

	virtual string Name() override {
		return "CIRCLE";
	}

	virtual double Perimeter() override {
		return 2 * pi * r;
	}

	virtual double Area() override {
		return pi * r * r;
	}

private:
	const double pi = 3.14;
	const double r;
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
	string figure_type;
	is >> figure_type;
	if (figure_type == "TRIANGLE") {
		int s1, s2, s3;
		is >> s1 >> s2 >> s3;
		return make_shared<Triangle>(s1, s2, s3);
	} else if (figure_type == "RECT") {
		int s1, s2;
		is >> s1 >> s2;
		return make_shared<Rect>(s1, s2);
	} else if (figure_type == "CIRCLE") {
		int r;
		is >> r;
		return make_shared<Circle>(r);
	} else {
		throw invalid_argument("");
	}
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line);) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto &current_figure : figures) {
				cout << fixed << setprecision(3) << current_figure->Name() << " " << current_figure->Perimeter() << " " << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
