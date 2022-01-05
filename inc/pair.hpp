#ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>

namespace ft {
	template <typename T1, typename T2>
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair() : first(first_type()), second(second_type()) {}
		template<typename U, typename V>
		pair(const pair<U,V>& src) : first(src.first), second(src.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& src) {
			first = src.first;
			second = src.second;
			return *this;
		}
		bool operator==(const pair<T1, T2> & rhs) const {
			if (first == rhs.first && second == rhs.second)
				return true;
			return false;
		}
		bool operator<(const pair<T1, T2> & rhs) const {
			if (first < rhs.first)
				return true;
			else if (rhs.first < rhs.first)
				return false;
			else if (second < rhs.second)
				return true;
			return false;
		}
	};
}

#endif