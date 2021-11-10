#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator>
# include <stdexcept>
# include <memory>

namespace ft {

	class PointerNull : public std::exception {
		public :
			virtual const char* what() const throw () {
				return ("Pointer Null, iterator need to be assigned");
			}
	};
	class VectorEmpty : public std::exception {
		public :
			virtual const char* what() const throw () {
				return ("Vector empty, it need elements to use it");
			}
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {

		public:
			template <typename U> class iter;

			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef typename Alloc::reference			reference;
			typedef typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer				pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef iter<T>								iterator;
			typedef iter<const T>						const_iterator;
			typedef typename Alloc::difference_type		difference_type;
			typedef typename Alloc::difference_type		size_type;

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
					iter(iter const & src) { *this = src; } ;
					// iter(const_iterator const & src) { *this = src; } ;
					
					reference operator*() const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return *ptr;
					}	
					pointer operator->() const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr;
					}	
					iter & operator++() {
						if (ptr == NULL)
							throw ft::PointerNull();
						ptr++;
						return *this;
					}
					iter operator++(int) {
						if (ptr == NULL)
							throw ft::PointerNull();
						iter temp = *this;
						++*this;
						return temp;
					}
					iter & operator--() {
						if (ptr == NULL)
							throw ft::PointerNull();
						ptr--;
						return *this;
					}
					iter operator--(int) {
						if (ptr == NULL)
							throw ft::PointerNull();
						iter temp = *this;
						--*this;
						return temp;
					}
					iter operator+(int const & val) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						iter tmp(ptr + val);
						return (tmp);
					}
					iter & operator+=(int const & val) {
						if (ptr == NULL)
							throw ft::PointerNull();
						ptr += val;
						return (*this);
					}
					difference_type operator-(iter const & rhs) const {
						if (ptr == NULL || rhs.ptr == NULL)
							throw ft::PointerNull();
						return ptr - rhs.ptr;
					}
					iter operator-(int const & val) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						iter tmp(ptr - val);
						return (tmp);
					}
					iter & operator-=(int const & val) {
						if (ptr == NULL)
							throw ft::PointerNull();
						ptr -= val;
						return (*this);
					}
					iter & operator=(iter const & rhs) {
						ptr = rhs.ptr;
						return *this;
					}
					bool operator==(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr == rhs.ptr;
					}
					bool operator!=(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr != rhs.ptr;
					}
					bool operator>(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr > rhs.ptr; 
					}
					bool operator>=(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr >= rhs.ptr;
					}
					bool operator<(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr < rhs.ptr; 
					}
					bool operator<=(iter const & rhs) const {
						if (ptr == NULL)
							throw ft::PointerNull();
						return ptr <= rhs.ptr;
					}
					
				private:
					value_type *ptr;
			};

			vector() : _n(0), _capacity(0), _v(NULL) {}
			// explicit vector(const allocator_type& alloc = allocator_type()) : _n(0), _capacity(0), _v(NULL) {}
			vector(ft::vector<T> const & src) : _n(0), _capacity(0), _v(NULL) { *this = src; }
			~vector() { 
				for (size_type i = 0; i < _n; i++)
					_alloc.destroy(&_v[i]);
				_alloc.deallocate(_v, _capacity);
			}

			iterator		begin() {
				if (_v == NULL)
					throw VectorEmpty();
				return iter<T>(&_v[0]);
			}
			const_iterator	begin() const {
				if (_v == NULL)
					throw VectorEmpty();
				return iter<T>(&_v[0]);
			}
			iterator		end() {
				if (_v == NULL)
					throw VectorEmpty();
				return iter<T>(&_v[_n]);
			}
			const_iterator	end() const {
				if (_v == NULL)
					throw VectorEmpty();
				return iter<T>(&_v[_n]);
			}
			
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

			void		push_back (value_type const & val) {
				if (_n >= _capacity && _capacity != 0)
					_realloc_capacity(_capacity * 2);
				else if (_capacity == 0)
					_v = _alloc.allocate(_capacity++);
				_alloc.construct(&_v[_n], val);
				_n++;
			}

			value_type & operator[](size_type i) {
				if (i < 0 || i >= _n)
					throw std::out_of_range("Wrong index of vector<T>::operator[]");
				return _v[i];
			}
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

		private:
			size_type	_n;
			size_type	_capacity;
			Alloc		_alloc;
			T			*_v;

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
	};
}

#endif