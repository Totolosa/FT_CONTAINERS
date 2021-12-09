#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "Node.hpp"

namespace ft {
	template <typename T>
	class map_iterator {
		public :
			typedef T								node;
			typedef node*							node_pointer;
			typedef typename T::value_type			value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			map_iterator() : ptr(NULL) {} ;
			map_iterator(node_pointer const & ptr_node) : ptr(ptr_node) {}
			template <typename V>
			map_iterator(map_iterator<V> const & src) { *this = src; }

			
			reference operator*() const { return ptr->data; }	
			pointer operator->() const { return &(ptr->data); }	
			map_iterator & operator++() {
				node_pointer tmp = ptr;
				if (tmp->r) {
					tmp = tmp->r;
					while (tmp->l)
						tmp = tmp->l;
					ptr = tmp;
				}
				else if (tmp->p)
					ptr = tmp->p;
				return *this;
			}
			map_iterator operator++(int) {
				map_iterator temp = *this;
				++*this;
				return temp;
			}
			map_iterator & operator--() {
				node_pointer tmp = ptr;
				if (tmp->l) {
					tmp = tmp->l;
					while (tmp->r)
						tmp = tmp->r;
					ptr = tmp;
				}
				else if (tmp->p)
					ptr = tmp->p;
				return *this;
			}
			map_iterator operator--(int) {
				map_iterator temp = *this;
				--*this;
				return temp; 
			}
			template <typename V>
			map_iterator & operator=(map_iterator<V> const & rhs) {
				ptr = rhs.ptr;
				return *this;
			}
			// template <typename V>
			// bool operator==(map_iterator<V> const & rhs) { return ptr == rhs.ptr; }
			// template <typename V, typename W>
			// friend bool operator==(map_iterator<V> const & lhs, map_iterator<W> const & rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator==(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator!=(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr != rhs.ptr; }

		protected:
			node_pointer ptr;
	};
}

#endif