#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include <iostream>

namespace ft {
	template <typename U>
	class random_access_iterator {
		public:
			typedef U								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::random_access_iterator_tag	iterator_category;

			random_access_iterator() : ptr(NULL) {} ;
			random_access_iterator(pointer const & ptr) : ptr(ptr) {} ;
			template <typename V>
			random_access_iterator(random_access_iterator<V> const & src) { *this = src; } ;
			
			reference operator*() const { return *ptr; }	
			pointer operator->() const { return ptr; }	
			random_access_iterator & operator++() {
				ptr++;
				return *this;
			}
			random_access_iterator operator++(int) {
				random_access_iterator temp = *this;
				++*this;
				return temp; 
			}
			random_access_iterator & operator--() {
				ptr--;
				return *this; 
			}
			random_access_iterator operator--(int) {
				random_access_iterator temp = *this;
				--*this;
				return temp; 
			}
			random_access_iterator operator+(int const & val) const {
				random_access_iterator tmp(ptr + val);
				return (tmp); 
			}
			random_access_iterator & operator+=(int const & val) {
				ptr += val;
				return (*this);
			}
			difference_type operator-(random_access_iterator const & rhs) const {
			
			return ptr - rhs.operator->(); 
			}
			random_access_iterator operator-(int const & val) const {
				random_access_iterator tmp(ptr - val);
				return (tmp); 
			}
			random_access_iterator & operator-=(int const & val) {
				ptr -= val;
				return (*this);
			}
			template <typename V>
			random_access_iterator & operator=(random_access_iterator<V> const & rhs) {
				ptr = rhs.operator->();
				return *this;
			}
			reference operator[](int const & val) { return *(ptr + val); }
			friend bool operator==(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator!=(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr != rhs.ptr; }
			friend bool operator>(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr > rhs.ptr;  }
			friend bool operator>=(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr >= rhs.ptr; }
			friend bool operator<(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr < rhs.ptr;  }
			friend bool operator<=(random_access_iterator const & lhs, random_access_iterator const & rhs) { return lhs.ptr <= rhs.ptr; }
			friend random_access_iterator operator+(difference_type n, random_access_iterator const & rhs) { return random_access_iterator(rhs.ptr + n); }

		protected:
			pointer ptr;
	};
}

#endif