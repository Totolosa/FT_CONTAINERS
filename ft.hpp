#ifndef FT_HPP
# define FT_HPP

# include <iostream>

namespace ft {

	template <typename T, typename Alloc = allocator<T> >
	class vector {
		public:
			typedef typename T						value_type;
			typedef typename Alloc					allocator_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			// typedef typename 	iterator;

			vector::vector(const allocator_type& alloc = allocator_type());
			vector::vector();
	};
}

#endif