#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "Node.hpp"
# include "pair.hpp"
# include "map_iterator.hpp"

template <typename T, typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<T> >
class _Tree {
	public:
		typedef T												value_type;
		typedef Key												key_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef ft::Node<T>										node;
		typedef typename Alloc::template rebind<node>::other	node_alloc;

		_Tree(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _n(0), _tree(NULL), _nal(node_alloc()), _comp(comp), _tal(alloc) {}

		ft::pair< *node, bool> insert (const value_type& val) {
			return _insert(_tree, val);
		}
		

	private:
		ft::pair< *node, bool> _insert (node *tmp, const value_type& val) {
			if (!_tree) {
				_tree = _nal.allocate(1);
				_nal.construct(_tree, node(val));
				_n++;
				return (ft::make_pair(_tree, true));
			}
			if (_comp(val.first, tmp->data.first))
				_insert(tmp->l, val);
			else if (tmp->data.first < val.first)
				_insert(tmp->r, val);
			// 		tmp = tmp->l;
			// 	else if (tmp->data.first < val.first)
			// 		tmp = tmp->r;
			// 	else
			// 		return (ft::make_pair(tmp, false));
			// node *tmp = _tree;
			// while (tmp != NULL) {
			// 	if (val.first < tmp->data.first)
			// 		tmp = tmp->l;
			// 	else if (tmp->data.first < val.first)
			// 		tmp = tmp->r;
			// 	else
			// 		return (ft::make_pair(tmp, false));
			// }
			// tmp = _nal.allocate(1);
			// _nal.construct(tmp, node(val));
			// _n++;
			// return (ft::make_pair(tmp, true));
		}

		size_t			_n;
		node			*_tree;
		node_alloc		_nal;
		Compare			_comp;
		allocator_type	_tal;
};

#endif