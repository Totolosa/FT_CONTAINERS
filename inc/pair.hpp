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
		template<class U, class V>
		pair(const pair<U,V>& src) : first(src.first), second(src.second) {}
		// pair(const pair& src) : first(src.first), second(src.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& src) {
			first = src.first;
			second = src.second;
		}
	};
}

#endif