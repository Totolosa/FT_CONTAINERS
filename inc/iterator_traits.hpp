#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft {
	
	template <class Iterator>
	class iterator_traits {
		public:
			typedef Iterator						value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T> class iterator_traits<T*>
	class iterator_traits {
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T> class iterator_traits<const T*>;
	class iterator_traits {
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
}

#endif