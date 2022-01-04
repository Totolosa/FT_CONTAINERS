#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class vector_reverse_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;


			vector_reverse_iterator() : ptr(Iterator()) {}
			vector_reverse_iterator (iterator_type it) : ptr(it - 1) {}
			template <class Iter>
  			vector_reverse_iterator (const vector_reverse_iterator<Iter>& rev_it) : ptr(rev_it.base()) {}

			iterator_type base() const { return ptr + 1; }

			// reference operator*() const { return const_cast<reference>(*ptr); }
			// pointer operator->() const { return const_cast<pointer>(&*ptr); }
			reference operator*() const { return *ptr; }
			pointer operator->() const { return &*ptr; }
			vector_reverse_iterator & operator++() {
				ptr--;
				return *this;
			}
			vector_reverse_iterator operator++(int) {
				vector_reverse_iterator temp = *this;
				++*this;
				return temp;
			}
			vector_reverse_iterator & operator--() {
				ptr++;
				return *this; 
			}
			vector_reverse_iterator operator--(int) {
				vector_reverse_iterator temp = *this;
				--*this;
				return temp; 
			}
			vector_reverse_iterator operator+(difference_type n) const { return vector_reverse_iterator(ptr - n + 1); }
			vector_reverse_iterator & operator+=(int const & val) {
				ptr -= val;
				return (*this);
			}
			vector_reverse_iterator operator-(int const & val) const { return vector_reverse_iterator(ptr + val + 1); }
			vector_reverse_iterator & operator-=(int const & val) {
				ptr += val;
				return (*this);
			}
			template <typename U>
			vector_reverse_iterator & operator=(vector_reverse_iterator<U> const & rhs) {
				ptr = rhs.operator->();
				return *this;
			}
			reference operator[](int const & val) const { return *(ptr - val); }
			friend bool operator==(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator!=(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr != rhs.ptr; }
			friend bool operator>(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr < rhs.ptr;  }
			friend bool operator>=(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr <= rhs.ptr; }
			friend bool operator<(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr > rhs.ptr;  }
			friend bool operator<=(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return lhs.ptr >= rhs.ptr; }
			friend vector_reverse_iterator operator+(difference_type n, vector_reverse_iterator const & rhs) { return vector_reverse_iterator(rhs.ptr - n + 1); }
			friend difference_type operator-(vector_reverse_iterator const & lhs, vector_reverse_iterator const & rhs) { return rhs.ptr - lhs.ptr; }
		protected:
			iterator_type	ptr;
	};
}

#endif