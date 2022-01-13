#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <functional>
# include <queue>
# include <math.h>
# include "enable_if.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"
# include "pair.hpp"
# include "make_pair.hpp"
# include "map_iterator.hpp"
# include "map_reverse_iterator.hpp"
# include "Node.hpp"
# include "BST.hpp"

namespace ft {
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
		private:
			typedef ft::Node<ft::pair<const Key, T> >	node;
			typedef node*								node_pointer;
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
			typedef ft::map_iterator<value_type>					iterator;
			typedef ft::map_iterator<const value_type>				const_iterator;
			typedef ft::map_reverse_iterator<iterator>				reverse_iterator;
			typedef ft::map_reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename Alloc::difference_type					difference_type;
			typedef typename Alloc::size_type						size_type;


			//		--> CONSTRUCTORS/DESTRUCTORS <--

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree(_comp, _alloc) {}
			template <class InputIterator>
			map (typename enable_if< (is_same<InputIterator, pointer>::value || is_same<InputIterator, const_pointer>::value || is_same<InputIterator, iterator>::value || is_same<InputIterator, const_iterator>::value), InputIterator>::type first
			, InputIterator last
			, const key_compare& comp = key_compare()
			, const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree(BST<value_type, key_type, key_compare, allocator_type>(first, last, _comp, _alloc)) {}
			map (const map& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}
			~map () {}


			//		--> ITERATORS <--

			iterator begin() { return _tree.begin(); }
			const_iterator begin() const { return _tree.begin(); }
			iterator end() { return _tree.end(); }
			const_iterator end() const { return _tree.end(); }
			reverse_iterator rbegin() { return reverse_iterator(_tree.end()); }
			const_reverse_iterator rbegin() const { return reverse_iterator(_tree.end()); }
			reverse_iterator rend() { return reverse_iterator(_tree.begin()); }
			const_reverse_iterator rend() const { return reverse_iterator(_tree.begin()); }


			//		--> MODIFIERS <--

			pair<iterator,bool> insert (const value_type& val) { return (_tree.insert(val)); }
			iterator insert (iterator position, const value_type& val) { 
				(void)position;
				return _tree.insert(val).first; 
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {
				while (first != last)
					insert(*(first++));
			}
			void erase (iterator position) { _tree.erase(position->first); }
			size_type erase (const key_type& k) { return _tree.erase(k); }
			void erase (iterator first, iterator last) {
				while (first != last)
					erase((first++)->first);
			}
			void clear () { return _tree.clear(); }
			void swap (map& x) { _tree.swap(x._tree); }


			//		--> CAPACITY <--

			bool empty() const { return _tree.empty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _alloc.max_size(); }


			//		--> OBSERVERS <--

			key_compare key_comp() const { return _comp; }
			class value_compare {
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					~value_compare() {};
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
			value_compare value_comp() const { return value_compare(_comp); }
			void print_tree() { return _tree.print_tree(); }


			//		--> OPERATIONS <--

			iterator find (const key_type& k) { return iterator(_tree.find(k)); }
			const_iterator find (const key_type& k) const { return const_iterator(_tree.find(k)); }
			size_type count (const key_type& k) const { return (_tree.find(k) == _tree.get_end() ? 0 : 1); }
			iterator lower_bound (const key_type& k) { return iterator(_tree.find_bound(k, 'l')); }
			const_iterator lower_bound (const key_type& k) const { return const_iterator(_tree.find_bound(k, 'l')); }
			iterator upper_bound (const key_type& k) { return iterator(_tree.find_bound(k, 'u')); }
			const_iterator upper_bound (const key_type& k) const { return const_iterator(_tree.find_bound(k, 'u')); }
			pair<iterator,iterator> equal_range (const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }


			//		--> ALLOCATOR <--

			allocator_type get_allocator() const { return _alloc; }


			//		--> OPERATORS <--

			mapped_type& operator[] (const key_type& k) {
				return (insert(make_pair(k, mapped_type())).first)->second;
			}
			map& operator=(const map& x) {
				_comp = x._comp;
				_alloc = x._alloc;
				_tree = x._tree;
				return *this;
			}
			friend bool operator==(const map& lhs, const map& rhs) { 
				if (lhs.empty() && rhs.empty())
					return true;
				else if (lhs.size() != rhs.size() )
					return false;
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
			friend bool operator!= (const map& lhs, const map& rhs) { return !(lhs == rhs); }
			friend bool operator<  (const map& lhs, const map& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool operator<= (const map& lhs, const map& rhs) { return ((lhs < rhs) || (lhs == rhs)); }
			friend bool operator>  (const map& lhs, const map& rhs) { return (!(lhs < rhs) && (lhs != rhs)); }
			friend bool operator>= (const map& lhs, const map& rhs) { return !(lhs < rhs); }


		protected :
			Compare									_comp;
			allocator_type							_alloc;
			BST<value_type, Key, Compare, Alloc>	_tree;

	};
}


#endif