#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP

#include <cstddef>

namespace ft {

	template <class Category,			// iterator::iterator_category
		class T,		 				// iterator::value_type
		class Distance = ptrdiff_t,		// iterator::difference_type
		class Pointer = T*,				// iterator::pointer
		class Reference = T&			// iterator::reference
		>
	class iterator {
		public:
			iterator();
			iterator(iterator const& src);
			~iterator();

			iterator& operator=(iterator const& rhs);
		private:
			
	};

}

#endif