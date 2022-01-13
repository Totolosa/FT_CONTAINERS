#ifndef NODE_HPP
# define NODE_HPP

#include "pair.hpp"

namespace ft {
	template <typename T>
	struct Node {
		typedef T			value_type;

		T			data;		// data
		Node		*left;		// left child
		Node		*right;		// right child
		Node		*parent;	// parent
		int			height_l;	// height left subtree
		int			height_r;	// height right subtree

		Node () : data(T()), left(NULL), right(NULL), parent(NULL), height_l(0), height_r(0) {}
		Node (T const & val) : data(val), left(NULL), right(NULL), parent(NULL), height_l(0), height_r(0) {}
		template <typename V>
		Node (Node<V> const & src) : data(src.data), left(NULL), right(NULL), parent(NULL), height_l(0), height_r(0) {}
		// Node (Node<V> const & src) : data(src.data), left(src.left), right(src.left), parent(src.parent), b(0) {}
		template <typename V>
		Node (Node<V> const * ptr) : data(ptr->data), left(NULL), right(NULL), parent(NULL), height_l(0), height_r(0) {}
		~Node() {}

		int getKey() const {return data.first; }

		Node & operator=(Node const & src) { data = src.data; }
	};
}

#endif