#include <iostream>
#include <sstream>
using namespace std;

void first_task() {
	int first_num, amount_ops;
	cin >> first_num >> amount_ops;
	cout << string(amount_ops, '(') << first_num;
	for (int i = 0; i < amount_ops; i++) {
		char op;
		int num;
		cin >> op >> num;
		cout << ") " << op << " " << num;
	}
}

bool is_higher_priority(char prev_op, char op) {
	return (op == '*' || op == '/') && (prev_op == '+' || prev_op == '-');
}

void second_task() {
	int first_num, amount_ops;
	stringstream ss;
	cin >> first_num >> amount_ops;
	ss << first_num;

	int amount_brackets = 0;
	char prev_op, op;
	int num;
	cin >> op >> num;
	ss << " " << op << " " << num;
	prev_op = op;

	for (int i = 1; i < amount_ops; i++) {
		cin >> op >> num;
		if (is_higher_priority(prev_op, op)) {
			ss << ')';
			amount_brackets++;
		}
		ss << " " << op << " " << num;
		prev_op = op;
	}
	cout << string(amount_brackets, '(') << ss.str();
}

int main() {
//	first_task();
	second_task();
	return 0;
}
