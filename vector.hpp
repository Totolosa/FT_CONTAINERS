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
				return ("Pointer Null, iterator need to be assigned");
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
			
			template <typename U>
			class iter {
				public:
					typedef U				value_type;
					typedef std::ptrdiff_t	difference_type;
					typedef value_type*		pointer;
					typedef value_type&		reference;

					iter() : ptr(NULL) {} ;
					iter(value_type & ptr) : ptr(&ptr) {} ;

					
					reference & operator*() {
						if (ptr == NULL)
							throw ft::PointerNull();
						return *ptr;
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
						// return ++ptr;
					}
					bool operator==(const iter& rhs) const { return ptr == rhs.ptr; }
					bool operator!=(const iter& rhs) const { return ptr != rhs.ptr; }
					
				private:
					value_type *ptr;
			};

			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef typename Alloc::reference			reference;
			typedef typename Alloc::const_reference		const_reference;
			typedef typename Alloc::pointer				pointer;
			typedef typename Alloc::const_pointer		const_pointer;
			typedef iter<T>								iterator;
			typedef iter<const T>						const_iterator;

			vector() : _n(0), _capacity(0), _v(NULL) {}
			// vector(ft::vector<T> const & src) {}
			~vector() { delete [] _v; }
			
			
			// template <typename U>
			// class iter {
			// 	public:
			// 		typedef U			value_type;
			// 		typedef ptrdiff_t	difference_type;
			// 		typedef U*			pointer;
			// 		typedef U&			reference;

			// 		iter() : ptr(NULL) {} ;
			// 		iter(U & ptr) : ptr(&ptr) {} ;

					
			// 		value_type & operator*() {
			// 			if (this == NULL)
			// 				throw ft::PointerNull();
			// 			return *ptr;
			// }
					
			// 	private:
			// 		U *ptr;
			// };

			iter<T>		begin() { return iter<T>(_v[0]); }
			iter<T>		end() { return iter<T>(_v[_n]); }
			size_t		size() { return _n; }
			size_t		capacity() { return _capacity; }
			void		push_back (value_type const & val) {
				if (_n >= _capacity && _capacity != 0) {
					T *newV = _alloc.allocate(_capacity * 2, _v);
					for (size_t i = 0; i < _n; i++) {
						_alloc.construct(&newV[i], _v[i]);
						_alloc.destroy(&_v[i]);
					}
					_alloc.deallocate(_v, _capacity);
					_v = newV;
					_capacity *= 2;
				}
				else if (_capacity == 0)
					_v = _alloc.allocate(_capacity++);
				_alloc.construct(&_v[_n], val);
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