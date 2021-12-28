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

			node_pointer getptr() const { return ptr; }

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
				else if (tmp->p) {
					while (tmp == tmp->p->r)
						tmp = tmp->p;
					ptr = tmp->p;
				}
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
				else if (tmp->p) {
					while (tmp == tmp->p->l)
						tmp = tmp->p;
					ptr = tmp->p;
				}
				return *this;
			}
			map_iterator operator--(int) {
				map_iterator temp = *this;
				--*this;
				return temp; 
			}
			template <typename V>
			map_iterator & operator=(map_iterator<V> const & rhs) {
				ptr = reinterpret_cast<map_iterator::node_pointer>(rhs.getptr());
				// ptr = &*rhs;
				return *this;
			}
			// template <typename V>
			// bool operator==(map_iterator<V> const & rhs) { return ptr == rhs.ptr; }
			template <typename V, typename W>
			friend bool operator==(map_iterator<V> const & lhs, map_iterator<W> const & rhs) { return lhs.ptr == reinterpret_cast<map_iterator::node_pointer>(rhs.getptr()); }
			template <typename V, typename W>
			friend bool operator!=(map_iterator<V> const & lhs, map_iterator<W> const & rhs) { return lhs.ptr != reinterpret_cast<map_iterator::node_pointer>(rhs.getptr()); }
			// bool operator==(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			// bool operator!=(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr != rhs.ptr; }
			// bool operator==(map_iterator const & rhs) const { return ptr == rhs.ptr; }
			// bool operator!=(map_iterator const & rhs) const { return ptr != rhs.ptr; }

		protected:
			node_pointer ptr;
	};
}

#endif