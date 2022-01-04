#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <iostream>
// # include "Node.hpp"
// # include "BST.hpp"
# include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class map_reverse_iterator {
		public :
			typedef Iterator													iterator_type;
			typedef typename iterator_type::node								node;
			typedef node*														node_pointer;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			
			map_reverse_iterator() : ptr(NULL) {} ;
			map_reverse_iterator (iterator_type it) : ptr(it - 1) {}
			template <class Iter>
  			map_reverse_iterator (const map_reverse_iterator<Iter>& rev_it) : ptr(rev_it.base()) {}

			node_pointer getptr() const { return ptr; }
			iterator_type base() const { return ptr + 1; }

			reference operator*() const { return ptr->data; }	
			pointer operator->() const { return &(ptr->data); }	
			map_reverse_iterator & operator++() {
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
			map_reverse_iterator operator++(int) {
				map_reverse_iterator temp = *this;
				++*this;
				return temp;
			}
			map_reverse_iterator & operator--() {
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
			map_reverse_iterator operator--(int) {
				map_reverse_iterator temp = *this;
				--*this;
				return temp; 
			}
			template <typename V>
			map_reverse_iterator & operator=(map_reverse_iterator<V> const & rhs) {
				ptr = reinterpret_cast<map_reverse_iterator::node_pointer>(rhs.getptr());
				// ptr = &*rhs;
				return *this;
			}
			// template <typename V>
			// bool operator==(map_reverse_iterator<V> const & rhs) { return ptr == rhs.ptr; }
			// template <typename V>
			// bool operator!=(map_reverse_iterator<V> const & rhs) { return ptr != rhs.ptr; }
			template <typename V, typename W>
			friend bool operator==(map_reverse_iterator<V> const & lhs, map_reverse_iterator<W> const & rhs) { return reinterpret_cast<map_reverse_iterator::node_pointer>(lhs.ptr) == reinterpret_cast<map_reverse_iterator::node_pointer>(rhs.ptr); }
			template <typename V, typename W>
			friend bool operator!=(map_reverse_iterator<V> const & lhs, map_reverse_iterator<W> const & rhs) { return reinterpret_cast<map_reverse_iterator::node_pointer>(lhs.ptr) != reinterpret_cast<map_reverse_iterator::node_pointer>(rhs.ptr); }
			// bool operator==(map_reverse_iterator const & lhs, map_reverse_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			// bool operator!=(map_reverse_iterator const & lhs, map_reverse_iterator const & rhs) { return lhs.ptr != rhs.ptr; }
			// bool operator==(map_reverse_iterator const & rhs) const { return ptr == rhs.ptr; }
			// bool operator!=(map_reverse_iterator const & rhs) const { return ptr != rhs.ptr; }

		protected:
			node_pointer ptr;
	};
}

#endif