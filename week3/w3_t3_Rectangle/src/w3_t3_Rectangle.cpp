#include <rectangle.h>

Rectangle::Rectangle(int width, int height) :
		width_(width), height_(height) {
}

int Rectangle::GetArea() const {
	return width_ * height_;
}

int Rectangle::GetPerimeter() const {
	return 2 * (width_ + height_);
}

int Rectangle::GetWidth() const {
	return width_;
}
int Rectangle::GetHeight() const {
	return height_;
}

int main() {
	Rectangle a(2, 3);
	cout << a.GetHeight() << " " << a.GetWidth() << " " << a.GetPerimeter() << " " << a.GetArea() << endl;
}
