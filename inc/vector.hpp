#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include <stdexcept>
# include <memory>
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"

template <typename C>
void print_vec_inside(C & cont) {
	for (typename C::size_type i = 0; i < cont.size(); i++)
		std::cout << cont[i] << "|";
	std::cout << std::endl << "size = " << cont.size() << std::endl;
	std::cout << "capacity = " << cont.capacity() << std::endl << std::endl;
}

namespace ft {

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {

		public:
			template <typename U> class iter;

			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::const_reference			const_reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef iter<T>									iterator;
			typedef iter<const T>							const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename Alloc::difference_type			difference_type;
			typedef typename Alloc::difference_type			size_type;

			template <typename U>
			class iter {
				public:
					typedef U								value_type;
					typedef std::ptrdiff_t					difference_type;
					typedef value_type*						pointer;
					typedef value_type&						reference;
					typedef std::random_access_iterator_tag	iterator_category;

					iter() : ptr(NULL) {} ;
					iter(pointer const & ptr) : ptr(ptr) {} ;
					// iter(const_pointer const & ptr) : ptr(ptr) {} ;
					iter(iterator const & src) { *this = src; } ;
					iter(const_iterator const & src) { *this = src; } ;
					
					reference operator*() const { return *ptr; }	
					pointer operator->() const { return ptr; }	
					iter & operator++() {
						ptr++;
						return *this;
					}
					iter operator++(int) {
						iter temp = *this;
						++*this;
						return temp; 
					}
					iter & operator--() {
						ptr--;
						return *this; 
					}
					iter operator--(int) {
						iter temp = *this;
						--*this;
						return temp; 
					}
					iter operator+(int const & val) const {
						iter tmp(ptr + val);
						return (tmp); 
					}
					iter & operator+=(int const & val) {
						ptr += val;
						return (*this);
					}
					difference_type operator-(iter const & rhs) const {
					
					return ptr - rhs.operator->(); 
					}
					iter operator-(int const & val) const {
						iter tmp(ptr - val);
						return (tmp); 
					}
					iter & operator-=(int const & val) {
						ptr -= val;
						return (*this);
					}
					iter & operator=(iter const & rhs) {
						ptr = rhs.operator->();
						return *this;
					}
					reference operator[](int const & val) { return *(ptr + val); }
					friend bool operator==(iter const & lhs, iter const & rhs) { return lhs.ptr == rhs.ptr; }
					friend bool operator!=(iter const & lhs, iter const & rhs) { return lhs.ptr != rhs.ptr; }
					friend bool operator>(iter const & lhs, iter const & rhs) { return lhs.ptr > rhs.ptr;  }
					friend bool operator>=(iter const & lhs, iter const & rhs) { return lhs.ptr >= rhs.ptr; }
					friend bool operator<(iter const & lhs, iter const & rhs) { return lhs.ptr < rhs.ptr;  }
					friend bool operator<=(iter const & lhs, iter const & rhs) { return lhs.ptr <= rhs.ptr; }
					friend iter operator+(difference_type n, iter const & rhs) { return iter(rhs.ptr + n); }
					// friend difference_type operator-(iter const & lhs, iter const & rhs) { return rhs.ptr - lhs._current; }

				protected:
					pointer ptr;
			};

			//		--> CONSTRUCTORS/DESTRUCTORS <--

			explicit vector(const allocator_type& alloc = allocator_type()) : _n(0), _capacity(0), _alloc(alloc), _v(NULL) {}
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : _n(n), _capacity(n), _alloc(alloc) ,_v(NULL) {
				_v = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _n; i++)
					_alloc.construct(&_v[i], val);
			}
			vector(ft::vector<T> const & src) : _n(0), _capacity(0), _v(NULL) { *this = src; }
			template <class InputIterator>
			vector (typename enable_if< (is_same<InputIterator, pointer>::value || is_same<InputIterator, const_pointer>::value || is_same<InputIterator, iterator>::value || is_same<InputIterator, const_iterator>::value), InputIterator>::type first
			, InputIterator last
			, const allocator_type& alloc = allocator_type()) : _n(last - first), _capacity(_n), _alloc(alloc), _v(NULL) {
				_v = _alloc.allocate(_capacity);
					for (InputIterator it = first; it != last; it++)
						_alloc.construct(&_v[it - first], *it);
			}
			~vector() { 
				for (size_type i = 0; i < _n; i++)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);
			}

			//		--> ITERATORS <--

			iterator		begin() { return iterator(&_v[0]); }
			const_iterator	begin() const { return const_iterator(&_v[0]); }
			iterator		end() { return iterator(&_v[_n]); }
			const_iterator	end() const { return const_iterator(&_v[_n]); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
			
			//		--> CAPACITY <--

			size_type	size() const { return _n; }
			size_type	capacity() const { return _capacity; }
			size_type	max_size() const { return _alloc.max_size(); }
			bool		empty() const { return (_n == 0); }
			void		reserve (size_type n) {
				if (n > _capacity)
					_realloc_capacity(n);
			}
			void		resize (size_type n, value_type val = value_type()) {
				if (n < _n)
					for (size_type i = n; i < _n; i++)
						_alloc.destroy(&_v[i]);
				else if (n > _n) {
					while (n > _capacity) 
						_realloc_capacity(_capacity * 2);
					for (size_type i = _n; i < n; i++)
						_alloc.construct(&_v[i], val);
				}
				_n = n;
			}

			//		--> MODIFIERS <--

			void push_back(const value_type& val) {
				if (_n >= _capacity && _capacity != 0)
					_realloc_capacity(_capacity * 2);
				else if (_capacity == 0)
					_v = _alloc.allocate(_capacity++);
				_alloc.construct(&_v[_n], val);
				_n++;
			}
			void pop_back(){
				_alloc.destroy(&_v[_n - 1]);
				_n--;
			}
			iterator insert(iterator position, const value_type& val) {
				difference_type offset = position - begin();
				if (_capacity == 0)
					_v = _alloc.allocate(_capacity++);
				if (_n == _capacity)
					_realloc_capacity(_capacity * 2);
				for (difference_type i = _n; i > offset; i--) {
					if (i != _n)
						_alloc.destroy(&_v[i]);
					_alloc.construct(&_v[i], _v[i - 1]);
				}
				_alloc.destroy(&_v[offset]);
				_alloc.construct(&_v[offset], val);
				_n++;
				return begin() + offset;
			}
			iterator insert(iterator position, size_type n, const value_type& val) {
				difference_type offset = position - begin();
				if (n + _n > _capacity * 2)
					_realloc_capacity(_capacity + n);
				else if (n + _n > _capacity)
					_realloc_capacity(_capacity * 2);
				for (difference_type i = _n + n - 1; i >= offset + n; i--) {
					if (i < _n)
						_alloc.destroy(&_v[i]);
					_alloc.construct(&_v[i], _v[i - n]);
				}
				for (difference_type i = offset + n - 1; i >= offset; i--) {
					if (i < _n)
						_alloc.destroy(&_v[i]);
					_alloc.construct(&_v[i], val);
				}
				_n += n;
				return begin() + offset;
			}
			// template <class InputIterator>
			// 	void insert(iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position) {
				moove(position - begin(), _n - 1, 1);
				destroy(_n - 1);
				return begin() + (position - begin());
			}
			iterator erase (iterator first, iterator last) {
				moove(first - begin(), _n - (last - first), last - first);
				destroy(_n - (last - first), _n);
				return begin() + (first - begin());
			}
			void swap (vector& x) {
				std::swap(_v, x._v);
				std::swap(_n, x._n);
				std::swap(_capacity, x._capacity);
				std::swap(_alloc, x._alloc);
			}
			void clear() { destroy(0, _n); }

			//		--> ACCESS <--

			reference at (size_type n) {
				if (n >= _n || n < 0)
					throw std::out_of_range("vector");
				return _v[n];
			}
			const_reference at (size_type n) const {
				if (n >= _n || n < 0)
					throw std::out_of_range("vector");
				return _v[n];
			}
			reference front() { return _v[0]; }
			const_reference front() const { return _v[0]; }
			reference back() { return _v[_n - 1]; }
			const_reference back() const { return _v[_n - 1]; }

			//		--> ALLOCATOR <--
			allocator_type get_allocator() const { return _alloc; }

			//		--> OPERATORS <--

			reference operator[](size_type n) { return _v[n]; }
			const_reference operator[] (size_type n) const { return _v[n]; };
			vector<T> & operator=(vector<T> const & rhs) {
				if (_v) {
					for (size_type i = 0; i < _n; i++)
						_alloc.destroy(&_v[i]);
					_alloc.deallocate(_v, _capacity);
				}
				_n = rhs.size();
				if (_capacity < rhs.capacity())
					_capacity = _n;
				_v = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _n; i++)
					_alloc.construct(&_v[i], rhs._v[i]);
				return *this;
			}

			friend bool operator== (const vector& lhs, const vector& rhs) { 
				if (lhs.empty() && rhs.empty())
					return true;
				else if (lhs.size() != rhs.size() )
					return false;
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
			friend bool operator!= (const vector& lhs, const vector& rhs) { return !(lhs == rhs); }
			friend bool operator<  (const vector& lhs, const vector& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool operator<= (const vector& lhs, const vector& rhs) { return ((lhs < rhs) || (lhs == rhs)); }
			friend bool operator>  (const vector& lhs, const vector& rhs) { return (!(lhs < rhs) && (lhs != rhs)); }
			friend bool operator>= (const vector& lhs, const vector& rhs) { return !(lhs < rhs); }

			friend void swap(vector & x, vector & y) { x.swap(y); }

		private:
			size_type		_n;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_v;

			void	_realloc_capacity(size_type new_capa) {
				T *newV = _alloc.allocate(new_capa, _v);
				for (size_type i = 0; i < _n; i++) {
					_alloc.construct(&newV[i], _v[i]);
					_alloc.destroy(&_v[i]);
				}
				_alloc.deallocate(_v, _capacity);
				_v = newV;
				_capacity = new_capa;
			}
			void destroy(size_type start, size_type end) {
				for (size_type i = start; i < end; i++)
					_alloc.destroy(&_v[i]);
				_n -= end - start;
			}
			void destroy(size_type position) {
				_alloc.destroy(&_v[position]);
				_n -= 1;
			}
			void moove(size_type start, size_type end, size_type offset) {
				for (size_type i = start; i < end; i++)
					_v[i] = _v[i + offset];
			}
	};
}

#endif