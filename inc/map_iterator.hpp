#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "Node.hpp"
// # include "BST.hpp"

namespace ft {
	template <typename T>
	class map_iterator {
		public :
			// typedef T								node;
			// typedef node*							node_pointer;
			// typedef typename T::value_type			value_type;
			typedef T 								value_type;
			typedef ft::Node<value_type>			node;
			typedef node*							node_pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			map_iterator() : ptr(NULL) {} ;
			// map_iterator(node_pointer * ptr_node) : ptr(reinterpret_cast<node_pointer>(ptr_node)) {}
			// template <typename V>
			// map_iterator(typename ft::enable_if<std::is_const<value_type>::value, ft::Node<V> >::type * ptr_node) : ptr(reinterpret_cast<node_pointer>(ptr_node)) {}

			template <typename V>
			map_iterator(ft::Node<V> * ptr_node) : ptr(reinterpret_cast<node_pointer>(ptr_node)) {}
			// map_iterator(typename ft::enable_if< !(!std::is_const<value_type>::value && std::is_const<typename Other::value_type>::value), Other * >::type ptr_node) : ptr(reinterpret_cast<node_pointer>(ptr_node)) {}
			// map_iterator(node_pointer const & ptr_node) : ptr(ptr_node) {}
			template <typename V>
			// map_iterator(map_iterator<typename ft::enable_if<(std::is_const<value_type>::value || !std::is_const<V>::value), V >::type> const & src) { *this = src; }
			map_iterator(map_iterator<V> const & src) { *this = src; }

			node_pointer getptr() const { return ptr; }

			reference operator*() const { return ptr->data; }	
			pointer operator->() const { return &(ptr->data); }	
			map_iterator & operator++() {
				node_pointer tmp = ptr;
				if (tmp->right) {
					tmp = tmp->right;
					while (tmp->left)
						tmp = tmp->left;
					ptr = tmp;
				}
				else if (tmp->parent) {
					while (tmp == tmp->parent->right)
						tmp = tmp->parent;
					ptr = tmp->parent;
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
				if (tmp->left) {
					tmp = tmp->left;
					while (tmp->right)
						tmp = tmp->right;
					ptr = tmp;
				}
				else if (tmp->parent) {
					while (tmp == tmp->parent->left)
						tmp = tmp->parent;
					ptr = tmp->parent;
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
			// template <typename V>
			// bool operator!=(map_iterator<V> const & rhs) { return ptr != rhs.ptr; }
			template <typename V, typename W>
			friend bool operator==(map_iterator<V> const & lhs, map_iterator<W> const & rhs) { return reinterpret_cast<map_iterator::node_pointer>(lhs.ptr) == reinterpret_cast<map_iterator::node_pointer>(rhs.ptr); }
			template <typename V, typename W>
			friend bool operator!=(map_iterator<V> const & lhs, map_iterator<W> const & rhs) { return reinterpret_cast<map_iterator::node_pointer>(lhs.ptr) != reinterpret_cast<map_iterator::node_pointer>(rhs.ptr); }
			// bool operator==(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			// bool operator!=(map_iterator const & lhs, map_iterator const & rhs) { return lhs.ptr != rhs.ptr; }
			// bool operator==(map_iterator const & rhs) const { return ptr == rhs.ptr; }
			// bool operator!=(map_iterator const & rhs) const { return ptr != rhs.ptr; }

		protected:
			node_pointer ptr;
	};
}

#endif