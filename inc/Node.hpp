#ifndef NODE_HPP
# define NODE_HPP

#include "pair.hpp"

namespace ft {
	template <typename T>
	struct Node {
		typedef T		value_type;

		T			data;	// data
		Node		*l;		// left child
		Node		*r;		// right child
		Node		*p;		// parent
		int			b;		// -1 = begin, 0 = node , 1 = end

		Node () : data(T()), l(NULL), r(NULL), p(NULL), b(0) {}
		Node (T const & val) : data(val), l(NULL), r(NULL), p(NULL), b(0) {}
		template <typename V>
		Node (Node<V> const & src) : data(src.data), l(src.l), r(src.l), p(src.p), b(0) {}
		~Node() {}

		Node & operator=(Node const & src) {
			data = src.data;
			l = src.l;
			r = src.r;
			p = src.p;
		}
	};
}

#endif