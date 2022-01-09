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
		}
		ft::pair< iterator, bool> _insert (node_pointer tmp, const value_type& val) {
			// std::cout << "debut _insert : val = " << val.first << ", tmp = " << tmp->data.first << std::endl;
			if (_comp(val.first, tmp->data.first)) {
				if (tmp->left == NULL || tmp->left == _begin) {
					_insert_node(tmp, 'l', val);
					// ft::pair<iterator, bool> ret(iterator(tmp->left), true);
					check_height(tmp, 'l');
					// return ret;
					return (ft::make_pair(iterator(tmp->left), true));
				}
				else
					return _insert(tmp->left, val);
			}
			else if (_comp(tmp->data.first, val.first)) {
				if (tmp->right == NULL || tmp->right == _end) {
					_insert_node(tmp, 'r', val);
					// ft::pair<iterator, bool> ret(iterator(tmp->right), true);
					check_height(tmp, 'r');
					// return ret;
					return (ft::make_pair(iterator(tmp->right), true));
				}
				else
					return _insert(tmp->right, val);
			}
			else
				return (ft::make_pair(iterator(tmp), false));
		}

		// void my_print() {
		// 	std::cout << "MY PRINT :" << std::endl;
		// 	for (iterator it = begin(); it != end(); ++it)
		// 		std::cout << it->first << "|" << std::flush << it->second << " " << std::flush;
		// 	std::cout << std::endl
		// 		<< "size = " << size() << std::endl;
		// }

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

		void check_height (node_pointer tmp, char orientation) {
			// std::cout << "start check height : tmp = " << tmp->data.first << ", height_left = " << tmp->height_l << ", height_right = " << tmp->height_r << std::endl;
			// if (orientation == 'l')
			// 	tmp->height_l++;
			// else if (orientation == 'r')
			// 	tmp->height_r++;
			update_height(tmp, orientation);
			if (std::abs(tmp->height_l - tmp->height_r) > 1) {
				tmp = balance_tree(tmp);
				return;
			}
			// if ((tmp->left && tmp->right) || tmp== _root)
			if (tmp == _root)
				return ;
			if (tmp == tmp->parent->left)
				check_height(tmp->parent, 'l');
			else if (tmp == tmp->parent->right)
				check_height(tmp->parent, 'r');
		}

		void update_height (node_pointer tmp, char orientation) {
			// int height_child_left;
			// int height_child_right;
			// if (tmp->left)
			// 	height_child_left = std::max(tmp->left->height_l, tmp->left->height_r)
			// else
			// 	height_child_left = 0;
			// if (tmp->right)
			// 	height_child_right = std::max(tmp->right->height_l, tmp->right->height_r)
			// else
			// 	height_child_right = 0;
			if (orientation == 'l')
				tmp->height_l = 1 + std::max(tmp->left->height_l, tmp->left->height_r);
			else if (orientation == 'r')
				tmp->height_r = 1 + std::max(tmp->right->height_l, tmp->right->height_r);
		}

		node_pointer balance_tree (node_pointer tmp) {
			// std::cout << "start balance_tree : tmp = " << tmp->data.first << ", height_left = " << tmp->height_l << ", height_right = " << tmp->height_r << std::endl;
			if (tmp->height_l > tmp->height_r) {
				if (tmp->left->height_l > tmp->left->height_r)
					return left_left_balance(tmp, tmp->left);
				else
					return left_right_balance(tmp, tmp->left, tmp->left->right);
			}
			else {
				if (tmp->right->height_r > tmp->right->height_l)
					return right_right_balance(tmp, tmp->right);
				else
					return right_left_balance(tmp, tmp->right, tmp->right->left);
			}
		}

		node_pointer left_left_balance (node_pointer node, node_pointer child) {
			// std::cout << "start LL rotation" << std::endl;
			// std::cout << "node = " << node->data.first << ", child = " << child->data.first << ", gchild = " << child->left->data.first << std::endl;
			moove_parent(node, child);		// Moove parent of node to parent of child
			node->left = child->right;		// Moove child right-subtree to node left-subtree
			if (node->left)
				node->left->parent = node;
			node->parent = child;			// The parent of node become the child
			child->right = node;	
			child->height_r++;				// Mofify height for all nodes
			node->height_l -= 2;
			return child;
		}
		node_pointer left_right_balance (node_pointer node, node_pointer child, node_pointer gchild) {
			// std::cout << "start LR rotation" << std::endl;
			moove_parent(node, gchild);	// Moove parent of node to parent of grandchild
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
			gchild->height_l++;				// Mofify height for all nodes
			gchild->height_r++;
			child->height_r--;
			node->height_l -= 2;
			return gchild;
		}
		node_pointer right_right_balance (node_pointer node, node_pointer child) {
			// std::cout << "start RR rotation" << std::endl;
			moove_parent(node, child);		// Moove parent of node to parent of child
			node->right = child->left;		// Moove child left-subtree to node right-subtree
			if (node->right)
				node->right->parent = node;
			node->parent = child;			// The parent of node become the child
			child->left = node;
			child->height_l++;				// Mofify height for all nodes
			node->height_r -= 2;
			return child;
		}
		node_pointer right_left_balance (node_pointer node, node_pointer child, node_pointer gchild) {
			// std::cout << "start RL rotation" << std::endl;
			moove_parent(node, gchild);		// Moove parent of node to parent of grandchild
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
			gchild->height_r++;				// Mofify height for all nodes
			gchild->height_l++;
			child->height_l--;
			node->height_r -= 2;
			return gchild;
		}

		void moove_parent (node_pointer oldtop, node_pointer newtop) {
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


		// ft::pair< iterator, bool> insert (const value_type& val) { 
		// 	if (!_root) {
		// 		node_pointer newnode = _nal.allocate(1);
		// 		_nal.construct(newnode, node(val));
		// 		_root = newnode;
		// 		newnode->parent = NULL;
		// 		newnode->left = _begin;
		// 		_begin->parent = newnode;
		// 		newnode->right = _end;
		// 		_end->parent = newnode;
		// 		_n++;
		// 		return (ft::make_pair(iterator(_root), false));
		// 	}
		// 	else {
		// 		node_pointer tmp = _root;
		// 		node_pointer parent = NULL;
		// 		char last;
		// 		while (tmp && tmp != _begin && tmp != _end) {
		// 			parent = tmp;
		// 			if (_comp(val.first, tmp->data.first)) {
		// 				// std::cout << "insert <" << std::endl;
		// 				tmp = tmp->left;
		// 				last = 'l';
		// 			}
		// 			else if (_comp(tmp->data.first, val.first)) {
		// 				// std::cout << "insert >" << std::endl;
		// 				tmp = tmp->right;
		// 				last = 'r';
		// 			}
		// 			else
		// 				return (ft::make_pair(iterator(tmp), false));
		// 		}
		// 		// std::cout << "ICI, _n = " << _n << std::endl;
		// 		node_pointer newnode = _nal.allocate(1);
		// 		_nal.construct(newnode, node(val));
		// 		if (!tmp) {
		// 			// std::cout << "!tmp" << std::endl;
		// 			newnode->parent = parent;
		// 			if (last == 'l')
		// 				parent->left = newnode;
		// 			else if (last == 'r')
		// 				parent->right = newnode;
		// 			// _insert_node(newnode, parent);
		// 		}
		// 		else if (tmp == _begin) {
		// 			// std::cout << "tmp == begin" << std::endl;
		// 			_set_begin(newnode, tmp->parent);
		// 		}
		// 		else if (tmp == _end) {
		// 			// std::cout << "tmp == end" << std::endl;
		// 			_set_end(newnode, tmp->parent);
		// 		}
		// 		_n++;
		// 		return (ft::make_pair(iterator(newnode), true));
		// 	}
		// 	// return _insert(_root, val); 
		// }
		bool erase(key_type const & k, iterator it) {
			node_pointer tmp;
			if (it == end())
				tmp = _search_key(_root, k);
			else
				tmp = it.getptr();
			if (tmp == _end) {
				// std::cout << "number to erase not fount" << std::endl;
				return false;
			}
			if (_n == 1) {
				_begin->parent = NULL;
				_end->parent = NULL;
			}
			else if (tmp->left == _begin) {
				// std::cout << "tmp->left = _begin" << std::endl;
				if (tmp->right) {
					tmp->right->parent = tmp->parent;
					tmp->parent->left = tmp->right;
					_begin->parent = tmp->right;
					tmp->right->left = _begin;
				}
				else {
					_begin->parent = tmp->parent;
					tmp->parent->left = _begin;
				}
			}
			else if (tmp->right == _end) {
				// std::cout << "tmp->right = _end" << std::endl;
				if (tmp->left) {
					tmp->left->parent = tmp->parent;
					tmp->parent->right = tmp->left;
					_end->parent = tmp->left;
					tmp->left->right = _end;
				}
				else {
					_end->parent = tmp->parent;
					tmp->parent->right = _end;
				}
			}
			else if (tmp->right && tmp->left) {
				node_pointer tmp2 = tmp->right;
				while (tmp2->left)
					tmp2 = tmp2->left;
				if (tmp->right->left) {
					tmp2->parent->left = tmp2->right;
					if (tmp2->right)
						tmp2->right->parent = tmp2->parent;
				}
				tmp2->parent = tmp->parent;
				tmp2->left = tmp->left;
				if (tmp2->left)
					tmp2->left->parent = tmp2;
				tmp->parent->right = tmp2;
				tmp2->right = tmp->right;
			}
			else if (tmp->left) {
				if (tmp == tmp->parent->right)
					tmp->parent->right = tmp->left;
				else
					tmp->parent->left = tmp->left;
				// tmp->parent->left = tmp->left;
				tmp->left->parent = tmp->parent;
			}
			else if (tmp->right) {
				if (tmp == tmp->parent->right)
					tmp->parent->right = tmp->right;
				else
					tmp->parent->left = tmp->right;
				// tmp->parent->right = tmp->right;
				tmp->right->parent = tmp->parent;
			}
			else {
				if (tmp == tmp->parent->right)
					tmp->parent->right = NULL;
				else
					tmp->parent->left = NULL;
			}
			_nal.destroy(tmp);
			_nal.deallocate(tmp, 1);
			_n--;
			return true;

		}
		// void erase(iterator & start, iterator & end) {
		// 	iterator tmp = _search_key();
		// }
		void clear() {
			if (_n == 0)
				return ;
			iterator it = iterator(_begin->parent);
			iterator end = iterator(_end);
			while (it != end)
				_erase_node((it++).getptr());
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
		
		void _erase_node (node_pointer to_erase) {
			_nal.destroy(to_erase);
			_nal.deallocate(to_erase, 1);
		}
		void _set_begin(node_pointer newnode, node_pointer parent) {
			parent->left = newnode;
			newnode->parent = parent;
			newnode->left = _begin;
			_begin->parent = newnode;
		}
		void _set_end(node_pointer newnode, node_pointer parent) {
			parent->right = newnode;
			newnode->parent = parent;
			newnode->right = _end;
			_end->parent = newnode;
		}
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