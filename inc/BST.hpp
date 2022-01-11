#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "Node.hpp"
# include "pair.hpp"
# include "enable_if.hpp"
# include "equal.hpp"
# include "map_iterator.hpp"
# include "map_reverse_iterator.hpp"

template <typename T, typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<T> >
class BST {
	public:
		typedef T												value_type;
		typedef Key												key_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef ft::Node<value_type>							node;
		typedef node*											node_pointer;
		typedef typename Alloc::template rebind<node>::other	node_alloc;
		// typedef ft::map_iterator<ft::Node<value_type> >			iterator;
		// typedef ft::map_iterator<ft::Node<const value_type> >	const_iterator;
		typedef ft::map_iterator<value_type>					iterator;
		typedef ft::map_iterator<const value_type>				const_iterator;
		typedef ft::map_reverse_iterator<iterator>				reverse_iterator;
		typedef ft::map_reverse_iterator<const_iterator>		const_reverse_iterator;

		//		--> CONSTRUCTORS / DESTRUCTORS <--

		BST (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _n(0), _root(NULL), _nal(), _comp(comp), _tal(alloc) {
			_init_limits();
		}
		template <class InputIterator>
		BST (typename ft::enable_if< (ft::is_same<InputIterator, iterator>::value || ft::is_same<InputIterator, const_iterator>::value || ft::is_same<InputIterator, reverse_iterator>::value || ft::is_same<InputIterator, const_reverse_iterator>::value), InputIterator>::type first
			, InputIterator last
			, const key_compare& comp = key_compare()
			, const allocator_type& alloc = allocator_type()) : _n(0), _root(NULL), _nal(), _comp(comp), _tal(alloc) {
			_init_limits();
			for (iterator it = first; it != last; it++)
				insert(*it);
		}
		BST (const BST & src) : _n(0), _root(NULL), _nal(src._nal), _comp(src._comp), _tal(src._tal) {
			_init_limits();
			*this = src;
		}
		~BST() { 
			clear();
			_erase_node(_begin);
			_erase_node(_end);
		}

		//		--> GETERS <--

		node_pointer get_root () const { return _root; }
		node_pointer get_begin () const { return _begin; }
		node_pointer get_end () const { return _end; }

		//		--> MODIFIERS <--

		ft::pair< iterator, bool> insert (const value_type& val) {
			if (_n == 0) {
				_root = _nal.allocate(1);
				_nal.construct(_root, node(val));
				_begin->parent = _root;
				_root->left = _begin;
				_end->parent = _root;
				_root->right = _end;
				_n++;
				return ft::make_pair(iterator(_root), true);
			}
			else
				return _insert(_root, val); 
			// else {
				// std::cout << "test" << std::endl;
				// ft::pair< iterator, bool> ret = _insert(_root, val);
				// std::cout << ret.first << std::endl;
				// return ret;
			// }
		}
		
		bool erase(key_type const & k) {
			if (_n == 0)
				return false;
			return _erase(_root, k);
		}

		bool _erase(node_pointer tmp, key_type const & k) {
			if (_comp(k, tmp->data.first)) {
				if (tmp->left == NULL || tmp->left == _begin)
					return false;
				else
					return _erase(tmp->left, k);
			}
			else if (_comp(tmp->data.first, k)) {
				if (tmp->right == NULL || tmp->right == _end)
					return false;
				else
					return _erase(tmp->right, k);
			}
			else {
				ft::pair<node_pointer, char> ret = _delete_node(tmp);
				// tmp = _delete_node(tmp);
				// if (tmp != NULL)
				if (ret.first != NULL)
					_check_height(ret.first, ret.second);
				_assign_limits();
				return true;
			}
		}

		ft::pair<node_pointer, char> _delete_node(node_pointer tmp) {
			if (!tmp->left && !tmp->right)
				return _no_child(tmp);
			if (tmp->left && !tmp->right)
				return _left_child(tmp);
			if (tmp->right && !tmp->left)
				return _right_child(tmp);
			else
				return _two_child(tmp);
		}

		ft::pair<node_pointer, char> _no_child(node_pointer to_erase) {
			ft::pair<node_pointer, char> ret = pair_delete(to_erase, to_erase->parent);
			if (to_erase != _root && to_erase->parent->left == to_erase)
				to_erase->parent->left = NULL;
			else if (to_erase != _root && to_erase->parent->right == to_erase)
				to_erase->parent->right = NULL;
			_erase_node(to_erase);
			return ret;
		}

		ft::pair<node_pointer, char> _left_child(node_pointer to_erase) {
			// if (to_erase != _root && to_erase->parent->left == to_erase)
			// 	to_erase->parent->left = to_erase->left;
			// else if (to_erase != _root && to_erase->parent->right == to_erase)
			// 	to_erase->parent->right = to_erase->left;
			// if (to_erase == _root)
			// 	_root = to_erase->left;
			// to_erase->left->parent = to_erase->parent;
			// node_pointer ret = to_erase->parent;
			ft::pair<node_pointer, char> ret = pair_delete(to_erase, to_erase->parent);
			_moove_parent(to_erase, to_erase->left);
			_erase_node(to_erase);
			return ret;
		}

		ft::pair<node_pointer, char> _right_child(node_pointer to_erase) {
			// if (to_erase != _root && to_erase->parent->left == to_erase)
			// 	to_erase->parent->left = to_erase->left;
			// else if (to_erase != _root && to_erase->parent->right == to_erase)
			// 	to_erase->parent->right = to_erase->left;
			// if (to_erase == _root)
			// 	_root = to_erase->left;
			// to_erase->left->parent = to_erase->parent;
			// node_pointer ret = to_erase->parent;
			ft::pair<node_pointer, char> ret = pair_delete(to_erase, to_erase->parent);
			_moove_parent(to_erase, to_erase->right);
			_erase_node(to_erase);
			return ret;
		}

		ft::pair<node_pointer, char> _two_child(node_pointer to_erase) {
			node_pointer tmp = to_erase->right;
			while (tmp->left)
				tmp = tmp->left;
			if (tmp == to_erase->right) {
				// ft::pair<node_pointer, char> ret = pair_delete(to_erase, tmp);
				tmp->left = to_erase->left;
				tmp->left->parent = tmp;
				tmp->height_l = to_erase->height_l;
				_moove_parent(to_erase, tmp);
				_erase_node(to_erase);
				// return tmp;
				return ft::make_pair(tmp, 'l');
			}
			else {
				tmp->parent->left = tmp->right;
				if (tmp->right)
					tmp->right->parent = tmp->parent;
				tmp->left = to_erase->left;
				tmp->left->parent = tmp;
				tmp->right = to_erase->right;
				tmp->right->parent = tmp;
				tmp->height_l = to_erase->height_l;
				node_pointer parent = tmp->parent;
				_moove_parent(to_erase, tmp);
				_erase_node(to_erase);
				// return ret;
				return ft::make_pair(parent, 'l');
			}
		}

		ft::pair<node_pointer, char> pair_delete(node_pointer to_erase, node_pointer pointer) {
			char orientation;
			if (to_erase != _root && to_erase->parent->left == to_erase)
				orientation = 'l';
			if (to_erase != _root && to_erase->parent->right == to_erase)
				orientation = 'r';
			return ft::make_pair(pointer, orientation);
		}

		void _erase_node (node_pointer to_erase) {
			// node_pointer parent = to_erase->parent;
			// if (parent && parent->left == to_erase)
			// 	parent->left = NULL;
			// else if (parent && parent->right == to_erase)
			// 	parent->right = NULL;
			_nal.destroy(to_erase);
			_nal.deallocate(to_erase, 1);
			_n--;
			// return parent;
		}

		void _assign_limits() {
			node_pointer tmp = _root;
			if (_n == 0) {
				_begin->parent = NULL;
				_begin->left = NULL;
				_begin->right = NULL;
				_end->parent = NULL;
				_end->left = NULL;
				_end->right = NULL;
				_root = NULL;
				return ;
			}
			while (tmp->left && tmp->left != _begin)
				tmp = tmp->left;
			_begin->parent->left = NULL;
			_begin->parent = tmp;
			tmp->left = _begin;
			tmp = _root;
			while (tmp->right && tmp->right != _end)
				tmp = tmp->right;
			_end->parent->right = NULL;
			_end->parent = tmp;
			tmp->right = _end;
		}

		// bool erase(key_type const & k, iterator it) {
		// 	node_pointer tmp;
		// 	if (it == end())
		// 		tmp = _search_key(_root, k);
		// 	else
		// 		tmp = it.getptr();
		// 	if (tmp == _end) {
		// 		// std::cout << "number to erase not fount" << std::endl;
		// 		return false;
		// 	}
		// 	if (_n == 1) {
		// 		_begin->parent = NULL;
		// 		_end->parent = NULL;
		// 	}
		// 	else if (tmp->left == _begin) {
		// 		// std::cout << "tmp->left = _begin" << std::endl;
		// 		if (tmp->right) {
		// 			tmp->right->parent = tmp->parent;
		// 			tmp->parent->left = tmp->right;
		// 			_begin->parent = tmp->right;
		// 			tmp->right->left = _begin;
		// 		}
		// 		else {
		// 			_begin->parent = tmp->parent;
		// 			tmp->parent->left = _begin;
		// 		}
		// 	}
		// 	else if (tmp->right == _end) {
		// 		// std::cout << "tmp->right = _end" << std::endl;
		// 		if (tmp->left) {
		// 			tmp->left->parent = tmp->parent;
		// 			tmp->parent->right = tmp->left;
		// 			_end->parent = tmp->left;
		// 			tmp->left->right = _end;
		// 		}
		// 		else {
		// 			_end->parent = tmp->parent;
		// 			tmp->parent->right = _end;
		// 		}
		// 	}
		// 	else if (tmp->right && tmp->left) {
		// 		node_pointer tmp2 = tmp->right;
		// 		while (tmp2->left)
		// 			tmp2 = tmp2->left;
		// 		if (tmp->right->left) {
		// 			tmp2->parent->left = tmp2->right;
		// 			if (tmp2->right)
		// 				tmp2->right->parent = tmp2->parent;
		// 		}
		// 		tmp2->parent = tmp->parent;
		// 		tmp2->left = tmp->left;
		// 		if (tmp2->left)
		// 			tmp2->left->parent = tmp2;
		// 		tmp->parent->right = tmp2;
		// 		tmp2->right = tmp->right;
		// 	}
		// 	else if (tmp->left) {
		// 		if (tmp == tmp->parent->right)
		// 			tmp->parent->right = tmp->left;
		// 		else
		// 			tmp->parent->left = tmp->left;
		// 		// tmp->parent->left = tmp->left;
		// 		tmp->left->parent = tmp->parent;
		// 	}
		// 	else if (tmp->right) {
		// 		if (tmp == tmp->parent->right)
		// 			tmp->parent->right = tmp->right;
		// 		else
		// 			tmp->parent->left = tmp->right;
		// 		// tmp->parent->right = tmp->right;
		// 		tmp->right->parent = tmp->parent;
		// 	}
		// 	else {
		// 		if (tmp == tmp->parent->right)
		// 			tmp->parent->right = NULL;
		// 		else
		// 			tmp->parent->left = NULL;
		// 	}
		// 	_nal.destroy(tmp);
		// 	_nal.deallocate(tmp, 1);
		// 	_n--;
		// 	return true;

		// }

		void clear() {
			if (_n == 0)
				return ;
			iterator it = begin();
			while (it != end())
				erase((it++)->first);
			_root = NULL;
			_begin->parent = NULL;
			_end->parent = NULL;
			_n = 0;
		}
		void swap (BST& x) {
			std::swap(_n, x._n);
			std::swap(_root, x._root);
			std::swap(_begin, x._begin);
			std::swap(_end, x._end);
			std::swap(_nal, x._nal);
			std::swap(_comp, x._comp);
			std::swap(_tal, x._tal);
		}
		
		//		--> CAPACITY <--

		bool empty() const { return _n == 0; }
		size_t size() const { return _n; }


		//		--> ACCESSORS <--

		iterator begin() { return ++iterator(_begin); }
		const_iterator begin() const {return ++iterator(_begin); }
		iterator end() { return iterator(_end); }
		const_iterator end() const {return iterator(_end); }
		node_pointer find (const key_type& k) const { return _search_key(_root, k); }
		iterator find_bound(const key_type& key, char bound) const { 
			iterator it = begin();
			while (_comp(it->first, key) && it != end())
				it++;
			if (!_comp(key, it->first) && bound == 'u')
				return (++it);
			return it;
		}
		
		//		--> OPERATORS <--

		BST & operator=(BST const & src) {
			if (_begin == NULL && _end == NULL) 
				_init_limits();
			if (_n > 0)
				clear();
			_nal = src._nal;
			_comp = src._comp;
			_tal = src._tal;
			for (iterator it = src.begin(); it != src.end(); it++)
				insert(*it);
			return *this;
		}

		//		--> TO PRINT MAP <--

		int height(node_pointer node) {
			if (node->left == 0 && node->right == 0)
				return 1;
			else if (node->right == 0)
				return 1 + height(node->left);
			else if (node->left == 0)
				return 1 + height(node->right);
			else
				return 1 + std::max(height(node->left), height(node->right));
		}
		node_alloc get_allocator() const { return _nal; }


	private:
		void _init_limits () {
			_begin = _nal.allocate(1);
			_nal.construct(_begin, node());
			// _begin->b = -1;
			_end = _nal.allocate(1);
			_nal.construct(_end, node());
			// _end->b = 1;
		}
		
		//		--> INSERT <--

		ft::pair< iterator, bool> _insert (node_pointer tmp, const value_type& val) {
			// std::cout << "debut _insert : val = " << val.first << ", tmp = " << tmp->data.first << std::endl;
			if (_comp(val.first, tmp->data.first)) {
				if (tmp->left == NULL || tmp->left == _begin) {
					_insert_node(tmp, 'l', val);
					ft::pair<iterator, bool> ret(iterator(tmp->left), true);
					_check_height(tmp, 'l');
					return ret;
					// return (ft::make_pair(iterator(tmp->left), true));
				}
				else
					return _insert(tmp->left, val);
			}
			else if (_comp(tmp->data.first, val.first)) {
				if (tmp->right == NULL || tmp->right == _end) {
					_insert_node(tmp, 'r', val);
					ft::pair<iterator, bool> ret(iterator(tmp->right), true);
					_check_height(tmp, 'r');
					return ret;
					// return (ft::make_pair(iterator(tmp->right), true));
				}
				else
					return _insert(tmp->right, val);
			}
			else
				return (ft::make_pair(iterator(tmp), false));
		}

		void _insert_node(node_pointer parent, char orientation, const value_type &val) {
			node_pointer newnode = _nal.allocate(1);
			_nal.construct(newnode, node(val));
			if (parent->left == _begin && orientation == 'l') {
				newnode->left = _begin;
				_begin->parent = newnode;
			}
			else if (parent->right == _end && orientation == 'r') {
				newnode->right = _end;
				_end->parent = newnode;
			}
			newnode->parent = parent;
			if (orientation == 'l')
				parent->left = newnode;
			else if (orientation == 'r')
				parent->right = newnode;
			_n++;
		}

		void _check_height (node_pointer tmp, char orientation) {
			// std::cout << "start check height : tmp = " << tmp->data.first << ", height_left = " << tmp->height_l << ", height_right = " << tmp->height_r << std::endl;
			// if (orientation == 'l')
			// 	tmp->height_l = 1 + std::max(tmp->left->height_l, tmp->left->height_r);
			// else if (orientation == 'r')
			// 	tmp->height_r = 1 + std::max(tmp->right->height_l, tmp->right->height_r);
			update_height(tmp, orientation);
			// (void)orientation;
			// std::cout << "check height height updated : tmp = " << tmp->data.first << ", height_left = " << tmp->height_l << ", height_right = " << tmp->height_r << std::endl;
			if (std::abs(tmp->height_l - tmp->height_r) > 1) {
				tmp = _balance_tree(tmp);
				return;
			}
			if (tmp == _root)
				return ;
			if (tmp == tmp->parent->left)
				_check_height(tmp->parent, 'l');
			else if (tmp == tmp->parent->right)
				_check_height(tmp->parent, 'r');
		}

		void update_height(node_pointer to_update, char orientation) {
			(void)orientation;
			// if (orientation == 'l') {
				if (!to_update->left || to_update->left == _begin)
					to_update->height_l = 0;
				else
					to_update->height_l = 1 + std::max(to_update->left->height_l, to_update->left->height_r);
			// }
			// else if (orientation == 'r') {
				if (!to_update->right || to_update->right == _end)
					to_update->height_r = 0;
				else
					to_update->height_r = 1 + std::max(to_update->right->height_l, to_update->right->height_r);
			// }
		}

		node_pointer _balance_tree (node_pointer tmp) {
			// std::cout << "start _balance_tree : tmp = " << tmp->data.first << ", height_left = " << tmp->height_l << ", height_right = " << tmp->height_r << std::endl;
			if (tmp->height_l > tmp->height_r) {
				if (tmp->left->height_l > tmp->left->height_r)
					return _left_left_balance(tmp, tmp->left);
				else
					return _left_right_balance(tmp, tmp->left, tmp->left->right);
			}
			else {
				if (tmp->right->height_r > tmp->right->height_l)
					return _right_right_balance(tmp, tmp->right);
				else
					return _right_left_balance(tmp, tmp->right, tmp->right->left);
			}
		}

		node_pointer _left_left_balance (node_pointer node, node_pointer child) {
			// std::cout << "start LL rotation" << std::endl;
			// std::cout << "node = " << node->data.first << ", child = " << child->data.first << ", gchild = " << child->left->data.first << std::endl;
			_moove_parent(node, child);		// Moove parent of node to parent of child
			node->left = child->right;		// Moove child right-subtree to node left-subtree
			if (node->left)
				node->left->parent = node;
			node->parent = child;			// The parent of node become the child
			child->right = node;	
			// child->height_r++;				// Mofify height for all nodes
			// node->height_l -= 2;
			update_height(node, 'l');
			update_height(child, 'l');
			return child;
		}
		node_pointer _left_right_balance (node_pointer node, node_pointer child, node_pointer gchild) {
			// std::cout << "start LR rotation" << std::endl;
			_moove_parent(node, gchild);	// Moove parent of node to parent of grandchild
			child->right = gchild->left;	// Moove grandchild left-subtree to child right-subtree
			if (child->right)
				child->right->parent = child;
			node->left = gchild->right;		// Moove grandchild right-subtree to node left-subtree
			if (node->left)
				node->left->parent = node;
			child->parent = gchild;			// The parent of child become the grandchild
			gchild->left = child;
			node->parent = gchild;			// The parent of node become the grandchild
			gchild->right = node;
			// gchild->height_l++;				// Mofify height for all nodes
			// gchild->height_r++;
			// child->height_r--;
			// node->height_l -= 2;
			update_height(node, 'l');
			update_height(child, 'l');
			update_height(gchild, 'l');
			return gchild;
		}
		node_pointer _right_right_balance (node_pointer node, node_pointer child) {
			// std::cout << "start RR rotation" << std::endl;
			_moove_parent(node, child);		// Moove parent of node to parent of child
			node->right = child->left;		// Moove child left-subtree to node right-subtree
			if (node->right)
				node->right->parent = node;
			node->parent = child;			// The parent of node become the child
			child->left = node;
			// child->height_l++;				// Mofify height for all nodes
			// node->height_r -= 2;
			update_height(node, 'l');
			update_height(child, 'l');
			return child;
		}
		node_pointer _right_left_balance (node_pointer node, node_pointer child, node_pointer gchild) {
			// std::cout << "start RL rotation" << std::endl;
			_moove_parent(node, gchild);		// Moove parent of node to parent of grandchild
			child->left = gchild->right;	// Moove grandchild right-subtree to child left-subtree
			if (child->left)
				child->left->parent = child;
			node->right = gchild->left;		// Moove grandchild left-subtree to node right-subtree
			if (node->right)
				node->right->parent = node;
			child->parent = gchild;			// The parent of child become the grandchild
			gchild->right = child;
			node->parent = gchild;			// The parent of node become the grandchild
			gchild->left = node;
			// gchild->height_r++;				// Mofify height for all nodes
			// gchild->height_l++;
			// child->height_l--;
			// node->height_r -= 2;
			update_height(node, 'l');
			update_height(child, 'l');
			update_height(gchild, 'l');
			return gchild;
		}

		void _moove_parent (node_pointer oldtop, node_pointer newtop) {
			if (oldtop->parent == NULL) {
				newtop->parent = NULL;
				_root = newtop;
			}
			else {
				newtop->parent = oldtop->parent;
				if (oldtop == oldtop->parent->left)
					newtop->parent->left = newtop;
				else
					newtop->parent->right = newtop;
			}
		}

		//		--> ERASE <--


		// void _set_begin(node_pointer newnode, node_pointer parent) {
		// 	parent->left = newnode;
		// 	newnode->parent = parent;
		// 	newnode->left = _begin;
		// 	_begin->parent = newnode;
		// }
		// void _set_end(node_pointer newnode, node_pointer parent) {
		// 	parent->right = newnode;
		// 	newnode->parent = parent;
		// 	newnode->right = _end;
		// 	_end->parent = newnode;
		// }
		node_pointer _search_key(node_pointer tmp, key_type const & key) const {
			// std::cout << "key = " << key << ", tmp->key = " << tmp->data.first << std::endl;
			if (!tmp || tmp == _begin || tmp == _end)
				return _end;
			else if (_comp(key, tmp->data.first))
				return _search_key(tmp->left, key);
			else if (_comp(tmp->data.first, key))
				return _search_key(tmp->right, key);
			else
				return tmp;
		}

		size_t			_n;
		node			*_root;
		node			*_begin;
		node			*_end;
		node_alloc		_nal;
		Compare			_comp;
		allocator_type	_tal;
};

#endif