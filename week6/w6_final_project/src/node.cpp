#include "date.h"
#include "node.h"

#include <memory>
#include <string>
using namespace std;


bool EmptyNode::Evaluate(const Date &d, const string &e) const {
	return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation new_l_op, shared_ptr<Node> new_left, shared_ptr<Node> new_right) :
		l_op(new_l_op), left(new_left), right(new_right) { }

bool LogicalOperationNode::Evaluate(const Date &d, const string &e) const {
	if (l_op == LogicalOperation::And) {
		return left->Evaluate(d, e) && right->Evaluate(d, e);
	} else if (l_op == LogicalOperation::Or) {
		return left->Evaluate(d, e) || right->Evaluate(d, e);
	} else {
		throw logic_error("");
	}
}

ComparisonNode::ComparisonNode(Comparison new_comp) : comp(new_comp) { }

template <typename T>
bool ComparisonNode::compareWith(T in_value, T saved_value) const {
	if (comp == Comparison::Less) {
		return in_value < saved_value;
	} else if (comp == Comparison::LessOrEqual) {
		return in_value <= saved_value;
	} else if (comp == Comparison::Greater) {
		return in_value > saved_value;
	} else if (comp == Comparison::GreaterOrEqual) {
		return in_value >= saved_value;
	} else if (comp == Comparison::Equal) {
		return in_value == saved_value;
	} else if (comp == Comparison::NotEqual) {
		return in_value != saved_value;
	} else {
		throw logic_error("");
	}
}

DateComparisonNode::DateComparisonNode(Comparison new_comp, const Date& new_d) : ComparisonNode(new_comp), d_cmp_with(new_d) { }

bool DateComparisonNode::Evaluate(const Date &d, const string &e) const {
	return compareWith(d, d_cmp_with);
}

EventComparisonNode::EventComparisonNode(Comparison new_comp, const string& new_e) : ComparisonNode(new_comp), e_cmp_with(new_e) { }

bool EventComparisonNode::Evaluate(const Date &d, const string &e) const {
	return compareWith(e, e_cmp_with);
}
