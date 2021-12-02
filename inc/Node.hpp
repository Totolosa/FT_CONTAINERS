#ifndef NODE_HPP
# define NODE_HPP

#include "pair.hpp"

namespace ft {
	template <typename T>
	struct Node {
		T			data;	// data
		Node		*l;		// left child
		Node		*r;		// right child
		Node		*p;		// parent

		Node () : data(T()), l(NULL), r(NULL), p(NULL) {}
		Node (T const & val) : data(val), l(NULL), r(NULL), p(NULL) {}
		Node (Node const & src) : data(src.data), l(src.l), r(src.l), p(src.p) {}
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