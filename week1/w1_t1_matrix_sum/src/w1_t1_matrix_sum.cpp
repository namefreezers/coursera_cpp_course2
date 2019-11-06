#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix() {
		Reset(0, 0);
	}

	Matrix(int new_n, int new_m) {
		Reset(new_n, new_m);
	}

	void Reset(int new_n, int new_m) {
		if (new_n < 0 || new_m < 0) {
			throw out_of_range("");
		}
		if (new_n == 0 || new_m == 0) {
			new_n = 0;
			new_m = 0;
		}

		n = new_n;
		m = new_m;
		arr.assign(n, vector<int>(m));

//		arr = vector<vector<int>>(n);
//		for (auto &row : arr) {
//			row = vector<int>(m);
//		}
	}

	int GetNumRows() const {
		return n;
	}

	int GetNumColumns() const {
		return m;
	}

	int At(int i, int j) const {
		if (i < 0 || i >= n || j < 0 || j >= m) {
			throw out_of_range("");
		}
		return arr[i][j];
	}

	int& At(int i, int j) {
		if (i < 0 || i >= n || j < 0 || j >= m) {
			throw out_of_range("");
		}
		return arr[i][j];
	}

private:
	int n, m;
	vector<vector<int>> arr;
};

istream& operator>>(istream &stream, Matrix& matr) {
	int n, m;
	stream >> n >> m;
	matr.Reset(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			stream >> matr.At(i, j);
		}
	}
	return stream;
}

ostream& operator<<(ostream &stream, const Matrix &matr) {

	stream << matr.GetNumRows() << " " << matr.GetNumColumns() << endl;

	for (int i = 0; i < matr.GetNumRows(); i++) {
		if (matr.GetNumColumns() > 0) {
			stream << matr.At(i, 0);
		}
		for (int j = 1; j < matr.GetNumColumns(); j++) {
			stream << " " << matr.At(i, j);
		}
		stream << endl;
	}
	return stream;
}

bool operator==(const Matrix &m1, const Matrix &m2) {
	if (m1.GetNumColumns() != m2.GetNumColumns()
			|| m1.GetNumRows() != m2.GetNumRows()) {
		return false;
	}
	for (int i = 0; i < m1.GetNumRows(); i++) {
		for (int j = 0; j < m1.GetNumColumns(); j++) {
			if (m1.At(i, j) != m2.At(i, j)) {
				return false;
			}
		}
	}
	return true;

}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
	if (m1.GetNumRows() != m2.GetNumRows()
			|| m1.GetNumColumns() != m2.GetNumColumns()) {
		throw invalid_argument("");
	}
	Matrix res(m1.GetNumRows(), m1.GetNumColumns());
	for (int i = 0; i < m1.GetNumRows(); i++) {
		for (int j = 0; j < m1.GetNumColumns(); j++) {
			res.At(i, j) = m1.At(i, j) + m2.At(i, j);
		}
	}
	return res;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << "a\n";
	cout << one + two << endl;
	cout << "a\n";
	return 0;
}
