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
		
		bool erase(key_type const & k) {
			if (_n == 0)
				return false;
			return _erase(_root, k);
		}

		void clear() {
			if (_n == 0)
				return ;
			iterator it = begin();
			while (it != end())
				erase((it++)->first);
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
			if (!src.empty())
				for (iterator it = src.begin(); it != src.end(); it++)
					insert(*it);
			return *this;
		}


		//		--> PRINT MAP <--

		void print_tree(int levelMax = 0) const {
			(void) levelMax;
			std::cout << " -- MyTree -- " << std::endl;
			print_node(this->_root, 0, levelMax);
			std::cout << " ------------ " << std::endl;
		}


	protected:

		//		--> INIT BEGIN / END <--

		void _init_limits () {
			_begin = _nal.allocate(1);
			_nal.construct(_begin, node());
			_end = _nal.allocate(1);
			_nal.construct(_end, node());
		}
		

		//		--> INSERT <--

		ft::pair< iterator, bool> _insert (node_pointer tmp, const value_type& val) {
			if (_comp(val.first, tmp->data.first)) {
				if (tmp->left == NULL || tmp->left == _begin) {
					_insert_node(tmp, 'l', val);
					ft::pair<iterator, bool> ret(iterator(tmp->left), true);
					_check_height(tmp);
					return ret;
				}
				else
					return _insert(tmp->left, val);
			}
			else if (_comp(tmp->data.first, val.first)) {
				if (tmp->right == NULL || tmp->right == _end) {
					_insert_node(tmp, 'r', val);
					ft::pair<iterator, bool> ret(iterator(tmp->right), true);
					_check_height(tmp);
					return ret;
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


		//		--> ERASE <--

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
				tmp = _delete_node(tmp);
				if (tmp != NULL)
					_check_height(tmp);
				_assign_limits();
				return true;
			}
		}

		node_pointer _delete_node(node_pointer tmp) {
			if (!tmp->left && !tmp->right)
				return _no_child(tmp);
			if (tmp->left && !tmp->right)
				return _one_child(tmp, tmp->left);
			if (tmp->right && !tmp->left)
				return _one_child(tmp, tmp->right);
			else
				return _two_child(tmp);
		}

		node_pointer _no_child(node_pointer to_erase) {
			node_pointer ret = to_erase->parent;
			if (to_erase != _root && to_erase->parent->left == to_erase)
				to_erase->parent->left = NULL;
			else if (to_erase != _root && to_erase->parent->right == to_erase)
				to_erase->parent->right = NULL;
			_erase_node(to_erase);
			return ret;
		}

		node_pointer _one_child(node_pointer to_erase, node_pointer subtree) {
			_moove_parent(to_erase, subtree);
			_erase_node(to_erase);
			return subtree->parent;
		}

		node_pointer _two_child(node_pointer to_erase) {
			node_pointer tmp = to_erase->right;
			while (tmp->left)
				tmp = tmp->left;
			if (tmp == to_erase->right) {
				tmp->left = to_erase->left;
				tmp->left->parent = tmp;
				tmp->height_l = to_erase->height_l;
				_moove_parent(to_erase, tmp);
				_erase_node(to_erase);
				return tmp;
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
				return parent;
			}
		}

		void _erase_node (node_pointer to_erase) {
			_nal.destroy(to_erase);
			_nal.deallocate(to_erase, 1);
			_n--;
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


		//		--> BALANCE TREE <--

		void _check_height (node_pointer tmp) {
			update_height(tmp);
			if (std::abs(tmp->height_l - tmp->height_r) > 1) {
				tmp = _balance_tree(tmp);
				return;
			}
			if (tmp == _root)
				return ;
			if (tmp == tmp->parent->left)
				_check_height(tmp->parent);
			else if (tmp == tmp->parent->right)
				_check_height(tmp->parent);
		}

		void update_height(node_pointer to_update) {
			if (!to_update->left || to_update->left == _begin)
				to_update->height_l = 0;
			else
				to_update->height_l = 1 + std::max(to_update->left->height_l, to_update->left->height_r);
			if (!to_update->right || to_update->right == _end)
				to_update->height_r = 0;
			else
				to_update->height_r = 1 + std::max(to_update->right->height_l, to_update->right->height_r);
		}

		node_pointer _balance_tree (node_pointer tmp) {
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
			_moove_parent(node, child);		// Moove parent of node to parent of child
			node->left = child->right;		// Moove child right-subtree to node left-subtree
			if (node->left)
				node->left->parent = node;
			node->parent = child;			// The parent of node become the child
			child->right = node;	
			update_height(node);			// Mofify height for all nodes
			update_height(child);
			return child;
		}
		node_pointer _left_right_balance (node_pointer node, node_pointer child, node_pointer gchild) {
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
			update_height(node);			// Mofify height for all nodes
			update_height(child);
			update_height(gchild);
			return gchild;
		}
		node_pointer _right_right_balance (node_pointer node, node_pointer child) {
			_moove_parent(node, child);		// Moove parent of node to parent of child
			node->right = child->left;		// Moove child left-subtree to node right-subtree
			if (node->right)
				node->right->parent = node;
			node->parent = child;			// The parent of node become the child
			child->left = node;
			update_height(node);			// Mofify height for all nodes
			update_height(child);
			return child;
		}
		node_pointer _right_left_balance (node_pointer node, node_pointer child, node_pointer gchild) {
			_moove_parent(node, gchild);	// Moove parent of node to parent of grandchild
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
			update_height(node);			// Mofify height for all nodes
			update_height(child);
			update_height(gchild);
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


		//		--> OTHER <--

		node_pointer _search_key(node_pointer tmp, key_type const & key) const {
			if (!tmp || tmp == _begin || tmp == _end)
				return _end;
			else if (_comp(key, tmp->data.first))
				return _search_key(tmp->left, key);
			else if (_comp(tmp->data.first, key))
				return _search_key(tmp->right, key);
			else
				return tmp;
		}

		void print_node(node_pointer tmp, int level, int levelMax) const {
			if (levelMax != 0 && level == levelMax)
				return;
			if (tmp)
			{
				print_node(tmp->right, level + 1, levelMax);
				for (int i = 0; i < level; i++)
					std::cout << "   ";
				if (tmp == _begin)
					std::cout << "BEGIN" << std::endl;
				else if (tmp == _end)
					std::cout << "END" << std::endl;
				else
					std::cout << tmp->data.first << std::endl;
				print_node(tmp->left, level + 1, levelMax);
			}
			else
			{
				if (levelMax != 0)
					print_node(NULL, level + 1, levelMax);
				for (int i = 0; i < level; i++)
					std::cout << "   ";
				std::cout << "..." << std::endl;
				if (levelMax != 0)
					print_node(NULL, level + 1, levelMax);
			}
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