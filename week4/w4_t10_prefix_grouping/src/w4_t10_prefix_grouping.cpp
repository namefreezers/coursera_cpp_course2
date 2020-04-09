#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	string lower_bound_str({ prefix }), upper_bound_str({ static_cast<char>(prefix + 1) });
	return make_pair(lower_bound(range_begin, range_end, lower_bound_str), lower_bound(range_begin, range_end, upper_bound_str));
}

template<typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
	string prefix_upper_bound = prefix;
	prefix_upper_bound[prefix_upper_bound.size() - 1]++; // can be "bz" -> "ca"
	return make_pair(lower_bound(range_begin, range_end, prefix), lower_bound(range_begin, range_end, prefix_upper_bound));
}

int main() {
    const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;

    cout << endl;

    const vector<string> sorted_strings_2 = { "moscow", "motovilikha", "murmansk" };

    const auto mo_result = FindStartsWith(begin(sorted_strings_2), end(sorted_strings_2), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result = FindStartsWith(begin(sorted_strings_2), end(sorted_strings_2), "mt");
    cout << (mt_result.first - begin(sorted_strings_2)) << " " << (mt_result.second - begin(sorted_strings_2)) << endl;

    const auto na_result = FindStartsWith(begin(sorted_strings_2), end(sorted_strings_2), "na");
    cout << (na_result.first - begin(sorted_strings_2)) << " " << (na_result.second - begin(sorted_strings_2)) << endl;

    return 0;
}

// moscow murmansk
// 2 2
// 3 3

// moscow motovilikha
// 2 2
// 3 3

