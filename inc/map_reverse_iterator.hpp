#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <iostream>
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
			
			map_reverse_iterator() : it(NULL) {} ;
			map_reverse_iterator (iterator_type ite) : it(--ite) {}
			template <class Iter>
  			map_reverse_iterator (const map_reverse_iterator<Iter>& rev_it) : it(--rev_it.base()) {}

			iterator_type base() const { 
				iterator_type ret = it;
				return ++ret ; 
			}

			reference operator*() const { return it.operator*(); }	
			pointer operator->() const { return it.operator->(); }	
			map_reverse_iterator & operator++() {
				node_pointer tmp = it.getptr();
				if (tmp->left) {
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
					it = tmp;
				}
				else if (tmp->parent) {
					while (tmp == tmp->parent->left)
						tmp = tmp->parent;
					it = tmp->parent;
				}
				return *this;
			}
			map_reverse_iterator operator++(int) {
				map_reverse_iterator temp = *this;
				++*this;
				return temp;
			}
			map_reverse_iterator & operator--() {
				node_pointer tmp = it.getptr();
				if (tmp->right) {
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
					it = tmp;
				}
				else if (tmp->parent) {
					while (tmp == tmp->parent->right)
						tmp = tmp->parent;
					it = tmp->parent;
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
				it = reinterpret_cast<map_reverse_iterator::iterator_type>(rhs.base());
				// it = &*rhs;
				return *this;
			}
			// template <typename V>
			// bool operator==(map_reverse_iterator<V> const & rhs) { return it == rhs.it; }
			// template <typename V>
			// bool operator!=(map_reverse_iterator<V> const & rhs) { return it != rhs.it; }
			template <typename V, typename W>
			friend bool operator==(map_reverse_iterator<V> const & lhs, map_reverse_iterator<W> const & rhs) { return lhs.it == rhs.it; }
			template <typename V, typename W>
			friend bool operator!=(map_reverse_iterator<V> const & lhs, map_reverse_iterator<W> const & rhs) { return lhs.it != rhs.it; }
			// bool operator==(map_reverse_iterator const & lhs, map_reverse_iterator const & rhs) { return lhs.it == rhs.it; }
			// bool operator!=(map_reverse_iterator const & lhs, map_reverse_iterator const & rhs) { return lhs.it != rhs.it; }
			// bool operator==(map_reverse_iterator const & rhs) const { return it == rhs.it; }
			// bool operator!=(map_reverse_iterator const & rhs) const { return it != rhs.it; }

		protected:
			iterator_type it;
	};
}

#endif