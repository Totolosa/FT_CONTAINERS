#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "Node.hpp"

namespace ft {
	template <typename T>
	class map_iterator {
		public :
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			map_iterator() : ptr(NULL) {} ;
			map_iterator(pointer const & ptr_node) : ptr(ptr_node) {}
			template <typename V>
			map_iterator(map_iterator<V> const & src) { *this = src; }
			
			reference operator*() const { return (*ptr).data; }	
			// pointer operator->() const { return ; }	
			// map_iterator & operator++() {
			// 	ptr = ptr++;
			// 	return *this;
			// }
			// map_iterator operator++(int) {
			// 	map_iterator temp = *this;
			// 	++*this;
			// 	return temp;
			// }
			// map_iterator & operator--() {
			// 	ptr--;
			// 	return *this;
			// }
			// map_iterator operator--(int) {
			// 	map_iterator temp = *this;
			// 	--*this;
			// 	return temp; 
			// }
			// template <typename V>
			// map_iterator & operator=(map_iterator<V> const & rhs) {
			// 	ptr = rhs.operator->();
			// 	return *this;
			// }
			// friend bool operator==(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			// friend bool operator!=(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr != rhs.ptr; }

		protected:
			pointer ptr;

	};
}

#endif