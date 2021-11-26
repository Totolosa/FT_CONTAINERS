#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;


			reverse_iterator() : _current(Iterator()) {}
			reverse_iterator (iterator_type it) : _current(it - 1) {}
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

			iterator_type base() const { return _current + 1; }

			reference operator*() const { return *_current; }
			pointer operator->() const { return &*_current; }
			reverse_iterator & operator++() {
				_current--;
				return *this;
			}
			reverse_iterator operator++(int) {
				reverse_iterator temp = *this;
				++*this;
				return temp;
			}
			reverse_iterator & operator--() {
				_current++;
				return *this; 
			}
			reverse_iterator operator--(int) {
				reverse_iterator temp = *this;
				--*this;
				return temp; 
			}
			reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n + 1); }
			reverse_iterator & operator+=(int const & val) {
				_current -= val;
				return (*this);
			}
			reverse_iterator operator-(int const & val) const { return reverse_iterator(_current + val + 1); }
			reverse_iterator & operator-=(int const & val) {
				_current += val;
				return (*this);
			}
			template <typename U>
			reverse_iterator & operator=(reverse_iterator<U> const & rhs) {
				_current = rhs.operator->();
				return *this;
			}
			reference operator[](int const & val) const { return *(_current - val); }
			friend bool operator==(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current == rhs._current; }
			friend bool operator!=(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current != rhs._current; }
			friend bool operator>(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current < rhs._current;  }
			friend bool operator>=(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current <= rhs._current; }
			friend bool operator<(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current > rhs._current;  }
			friend bool operator<=(reverse_iterator const & lhs, reverse_iterator const & rhs) { return lhs._current >= rhs._current; }
			friend reverse_iterator operator+(difference_type n, reverse_iterator const & rhs) { return reverse_iterator(rhs._current - n + 1); }
			friend difference_type operator-(reverse_iterator const & lhs, reverse_iterator const & rhs) { return rhs._current - lhs._current; }
		protected:
			iterator_type	_current;
	};
}

#endif