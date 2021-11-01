#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
// # include <iterator>
# include <stdexcept>
# include <memory>

namespace ft {

	class PointerNull : public std::exception {
		public :
			virtual const char* what() const throw () {
				return ("Pointer Null, ipossible to derive it");
			}
	};

	template <typename T, typename Alloc = std::allocator<T> >
	class vector {
		private:
			size_t	_n;
			size_t	_capacity;
			Alloc	_alloc;
			T		*_v;

		public:
			typedef T						value_type;
			typedef Alloc					allocator_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			// typedef typename iterator iterator;

			vector() : _n(0), _capacity(0), _v(nullptr) {}
			// vector(ft::vector<T> const & src) {}
			~vector() { delete [] _v; }
			
			class iterator {
				public:
					typedef T			value_type;
					typedef ptrdiff_t	difference_type;
					typedef T*			pointer;
					typedef T&			reference;

					iterator() : ptr(nullptr) {} ;
					iterator(T & ptr) : ptr(&ptr) {} ;

					
					value_type & operator*() {
						if (this == nullptr)
							throw ft::PointerNull();
						return *ptr;
			}
					
				private:
					T *ptr;
			};

			iterator	begin() { return iterator(_v[0]); }
			iterator	end() { return iterator(_v[_n]); }
			size_t		size() { return _n; }
			size_t		capacity() { return _capacity; }
			void		push_back (value_type const & val) {
				if (_n >= _capacity && _capacity != 0) {
					T *newV = _alloc.allocate(_capacity * 2, _v);
					for (size_t i = 0; i < _n; i++) {
						newV[i] = _v[i];
						_alloc.destroy(&_v[i]);
					}
					_alloc.deallocate(_v, _capacity);
					_v = newV;
					_capacity *= 2;
				}
				else if (_capacity == 0)
					_v = _alloc.allocate(_capacity++);
				_v[_n] = val;
				_n++;
			}

			value_type & operator[](size_t i) {
				if (i < 0 || i >= _n)
					throw std::out_of_range("Wrong index of vector<T>::operator[]");
				return _v[i];
			}

	};
}


#endif