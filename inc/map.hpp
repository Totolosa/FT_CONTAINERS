#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <functional>
# include "pair.hpp"
# include "make_pair.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

template <typename C>
void print_vec_inside(C & cont) {
	for (typename C::size_type i = 0; i < cont.size(); i++)
		std::cout << cont[i] << "|";
	std::cout << std::endl << "size = " << cont.size() << std::endl;
	std::cout << "capacity = " << cont.capacity() << std::endl << std::endl;
}

namespace ft {
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const Key, T>							value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename Alloc::reference						reference;
			typedef typename Alloc::const_reference					const_reference;
			typedef typename Alloc::pointer							pointer;
			typedef typename Alloc::const_pointer					const_pointer;
			typedef ft::map_iterator<value_type>			iterator;
			typedef ft::map_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename Alloc::difference_type					difference_type;
			typedef typename Alloc::size_type						size_type;

			//		--> CONSTRUCTORS/DESTRUCTORS <--
			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _n(0), _comp(comp), _alloc(alloc), tree(NULL) {}

			//		--> ITERATORS <--

			iterator begin() { return iterator()}
			const_iterator begin() const;

			//		--> MODIFIERS <--

			pair<iterator,bool> insert (const value_type& val) {
				for (iterator it = tree.begin())
			}

			//		--> CAPACITY <--
			bool empty() const { return _n == 0; }

			//		--> OPERATORS <--

			mapped_type& operator[] (const key_type& k) {
				return (*((this->insert(make_pair(k,mapped_type()))).first)).second
			}
		
		private :
			typedef struct Node_s {
				value_type	data;
				Node_s		*left;
				Node_s		*right;
			} Node;
			size_type		_n;
			Compare			_comp;
			allocator_type	_alloc;
			Node			*tree;

			value_type & _min() {
				if (tree == NULL)
					return 

			} 
	};
}


#endif