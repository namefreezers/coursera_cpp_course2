#pragma once

#include <memory>
#include <string>
using namespace std;

#include "date.h"

enum Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum LogicalOperation {
	And,
	Or,
};

class Node {
public:
	virtual bool Evaluate(const Date &d, const string &e) = 0;
};

class EmptyNode: public Node {
public:
	virtual bool Evaluate(const Date &d, const string &e) override;
};

class LogicalOperationNode: public Node {
public:
	LogicalOperationNode(LogicalOperation new_l_op, shared_ptr<Node> new_left, shared_ptr<Node> new_right);

	virtual bool Evaluate(const Date &d, const string &e) override;

private:
	LogicalOperation l_op;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
};


class ComparisonNode : public Node {
public:
	ComparisonNode(Comparison new_comp);

	template <typename T>
	bool compareWith(T in_value, T saved_value);

private:
	const Comparison comp;
};

class DateComparisonNode : public ComparisonNode {
public:
	DateComparisonNode(Comparison new_comp, const Date& new_d);

	virtual bool Evaluate(const Date &d, const string &e) override;

private:
	const Date d_cmp_with;
};

class EventComparisonNode : public ComparisonNode {
public:
	EventComparisonNode(Comparison new_comp, const string& new_e);

	virtual bool Evaluate(const Date &d, const string &e) override;

private:
	const string e_cmp_with;
};
