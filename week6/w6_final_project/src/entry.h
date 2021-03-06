#pragma once

template<typename T1, typename T2>
class Entry {
public:
	Entry(const T1 &new_v1, const T2 &new_v2) : v1(new_v1), v2(new_v2) { }

	T1 Get_v1() const {
		return v1;
	}


	T2 Get_v2() const {
		return v2;
	}

private:
	const T1 v1;
	const T2 v2;
};

template<typename T1, typename T2>
ostream& operator<<(ostream &stream, const Entry<T1, T2> &d) {
	return stream << d.Get_v1() << " " << d.Get_v2();
}

template<typename T1, typename T2>
bool operator==(const Entry<T1, T2>& lhs, const Entry<T1, T2>& rhs) {
	return lhs.Get_v1() == rhs.Get_v1() && lhs.Get_v2() == rhs.Get_v2();
}

template<typename T1, typename T2, typename T3, typename T4>
bool operator!=(const Entry<T1, T2>& lhs, const Entry<T3, T4>& rhs) {
	return lhs.Get_v1() != rhs.Get_v1() || lhs.Get_v2() != rhs.Get_v2();
}