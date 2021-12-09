#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <functional>
# include "pair.hpp"
# include "make_pair.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "Node.hpp"
# include "BST.hpp"
// # include <map>

template <typename C>
void print_map_inside(C & cont) {
	for (typename C::size_type i = 0; i < cont.size(); i++)
		std::cout << cont[i] << "|";
	std::cout << std::endl << "size = " << cont.size() << std::endl;
	std::cout << "capacity = " << cont.capacity() << std::endl << std::endl;
}

namespace ft {
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
		private:
			typedef ft::Node<ft::pair<const Key, T> >	node;
			typedef std::allocator<node>				node_all;

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
			typedef ft::map_iterator<ft::Node<value_type> >			iterator;
			typedef ft::map_iterator<ft::Node<const value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename Alloc::difference_type					difference_type;
			typedef typename Alloc::size_type						size_type;

			//		--> CONSTRUCTORS/DESTRUCTORS <--
			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree() {}

			//		--> ITERATORS <--

			iterator begin() { return _tree.begin(); }
			const_iterator begin() const { return _tree.begin(); }
			iterator end() { return _tree.end(); }
			const_iterator end() const { return _tree.end(); }

			// iterator end() { 
			// 	node *tmp = tree;
			// 	if (tmp)
			// 		while (tmp->r)
			// 			tmp = tmp->r;
			// 	return iterator(tmp->r);
			// }
			// const_iterator end() const {
			// 	node *tmp = tree;
			// 	if (tmp)
			// 		while (tmp->r)
			// 			tmp = tmp->r;
			// 	return iterator(tmp->r);
			// }

			//		--> MODIFIERS <--

			pair<iterator,bool> insert (const value_type& val) { return (_tree.insert(val)); }
			void erase (iterator position);
			size_type erase (const key_type& k) { return _tree.erase(k); }
			void erase (iterator first, iterator last);

			//		--> CAPACITY <--
			bool empty() const { return _tree.empty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _alloc.max_size(); }

			//		--> OPERATORS <--

			mapped_type& operator[] (const key_type& k) {
				return (insert(make_pair(k, mapped_type())).first)->second;
			}
		
		private :
			Compare									_comp;
			allocator_type							_alloc;
			BST<value_type, Key, Compare, Alloc>	_tree;

	};
}


#endif