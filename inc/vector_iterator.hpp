#ifndef vector_iterator_HPP
# define vector_iterator_HPP

#include <iostream>

namespace ft {
	template <typename U>
	class vector_iterator {
		public:
			typedef U								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::random_access_iterator_tag	iterator_category;

			vector_iterator() : ptr(NULL) {}
			vector_iterator(pointer const & ptr) : ptr(ptr) {}
			template <typename V>
			vector_iterator(vector_iterator<V> const & src) { *this = src; }
			~vector_iterator() {}
			
			reference operator*() const { return *ptr; }	
			pointer operator->() const { return ptr; }	
			vector_iterator & operator++() {
				ptr++;
				return *this;
			}
			vector_iterator operator++(int) {
				vector_iterator temp = *this;
				++*this;
				return temp; 
			}
			vector_iterator & operator--() {
				ptr--;
				return *this; 
			}
			vector_iterator operator--(int) {
				vector_iterator temp = *this;
				--*this;
				return temp; 
			}
			vector_iterator operator+(int const & val) const {
				vector_iterator tmp(ptr + val);
				return (tmp); 
			}
			vector_iterator & operator+=(int const & val) {
				ptr += val;
				return (*this);
			}
			difference_type operator-(vector_iterator const & rhs) const {
			
			return ptr - rhs.operator->(); 
			}
			vector_iterator operator-(int const & val) const {
				vector_iterator tmp(ptr - val);
				return (tmp); 
			}
			vector_iterator & operator-=(int const & val) {
				ptr -= val;
				return (*this);
			}
			template <typename V>
			vector_iterator & operator=(vector_iterator<V> const & rhs) {
				ptr = rhs.operator->();
				return *this;
			}
			reference operator[](int const & val) { return *(ptr + val); }
			template <typename V, typename W>
			friend bool operator==(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr == rhs.ptr; }
			// friend bool operator==(vector_iterator const & lhs, vector_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			template <typename V, typename W>
			friend bool operator!=(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr != rhs.ptr; }
			template <typename V, typename W>
			friend bool operator>(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr > rhs.ptr;  }
			template <typename V, typename W>
			friend bool operator>=(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr >= rhs.ptr; }
			template <typename V, typename W>
			friend bool operator<(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr < rhs.ptr;  }
			template <typename V, typename W>
			friend bool operator<=(vector_iterator<V> const & lhs, vector_iterator<W> const & rhs) { return lhs.ptr <= rhs.ptr; }
			friend vector_iterator operator+(difference_type n, vector_iterator const & rhs) { return vector_iterator(rhs.ptr + n); }

		protected:
			pointer ptr;
	};
}

#endif