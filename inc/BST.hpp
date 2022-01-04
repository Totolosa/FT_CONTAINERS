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
			if (!_root) {
				node_pointer newnode = _nal.allocate(1);
				_nal.construct(newnode, node(val));
				_root = newnode;
				newnode->p = NULL;
				newnode->l = _begin;
				_begin->p = newnode;
				newnode->r = _end;
				_end->p = newnode;
				_n++;
				return (ft::make_pair(iterator(_root), false));
			}
			else {
				node_pointer tmp = _root;
				node_pointer parent = NULL;
				char last;
				while (tmp && tmp != _begin && tmp != _end) {
					parent = tmp;
					if (_comp(val.first, tmp->data.first)) {
						// std::cout << "insert <" << std::endl;
						tmp = tmp->l;
						last = 'l';
					}
					else if (_comp(tmp->data.first, val.first)) {
						// std::cout << "insert >" << std::endl;
						tmp = tmp->r;
						last = 'r';
					}
					else
						return (ft::make_pair(iterator(tmp), false));
				}
				// std::cout << "ICI, _n = " << _n << std::endl;
				node_pointer newnode = _nal.allocate(1);
				_nal.construct(newnode, node(val));
				if (!tmp) {
					// std::cout << "!tmp" << std::endl;
					newnode->p = parent;
					if (last == 'l')
						parent->l = newnode;
					else if (last == 'r')
						parent->r = newnode;
					// _insert_node(newnode, parent);
				}
				else if (tmp == _begin) {
					// std::cout << "tmp == begin" << std::endl;
					_set_begin(newnode, tmp->p);
				}
				else if (tmp == _end) {
					// std::cout << "tmp == end" << std::endl;
					_set_end(newnode, tmp->p);
				}
				_n++;
				return (ft::make_pair(iterator(newnode), true));
			}
			// return _insert(_root, val); 
		}
		// void erase_it (iterator position) {
		// 	_nal.destroy(position->getptr());
		// 	_nal.deallocate(position->getptr());
		// 	// position->getptr()
		// }
		bool erase(key_type const & k) {
			node_pointer tmp = _search_key(_root, k);
			if (tmp == _end) {
				// std::cout << "number to erase not fount" << std::endl;
				return false;
			}
			if (_n == 1) {
				_begin->p = NULL;
				_end->p = NULL;
			}
			else if (tmp->l == _begin) {
				// std::cout << "tmp->l = _begin" << std::endl;
				if (tmp->r) {
					tmp->r->p = tmp->p;
					tmp->p->l = tmp->r;
					_begin->p = tmp->r;
					tmp->r->l = _begin;
				}
				else {
					_begin->p = tmp->p;
					tmp->p->l = _begin;
				}
			}
			else if (tmp->r == _end) {
				// std::cout << "tmp->r = _end" << std::endl;
				if (tmp->l) {
					tmp->l->p = tmp->p;
					tmp->p->r = tmp->l;
					_end->p = tmp->l;
					tmp->l->r = _end;
				}
				else {
					_end->p = tmp->p;
					tmp->p->r = _end;
				}
			}
			else if (tmp->r && tmp->l) {
				node_pointer tmp2 = tmp->r;
				while (tmp2->l)
					tmp2 = tmp2->l;
				if (tmp->r->l) {
					tmp2->p->l = tmp2->r;
					if (tmp2->r)
						tmp2->r->p = tmp2->p;
				}
				tmp2->p = tmp->p;
				tmp2->l = tmp->l;
				if (tmp2->l)
					tmp2->l->p = tmp2;
				tmp->p->r = tmp2;
				tmp2->r = tmp->r;
			}
			else if (tmp->l) {
				if (tmp == tmp->p->r)
					tmp->p->r = tmp->l;
				else
					tmp->p->l = tmp->l;
				// tmp->p->l = tmp->l;
				tmp->l->p = tmp->p;
			}
			else if (tmp->r) {
				if (tmp == tmp->p->r)
					tmp->p->r = tmp->r;
				else
					tmp->p->l = tmp->r;
				// tmp->p->r = tmp->r;
				tmp->r->p = tmp->p;
			}
			else {
				if (tmp == tmp->p->r)
					tmp->p->r = NULL;
				else
					tmp->p->l = NULL;
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
			iterator it = iterator(_begin->p);
			iterator end = iterator(_end);
			while (it != end)
				_erase_node((it++).getptr());
			_root = NULL;
			_begin->p = NULL;
			_end->p = NULL;
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
			if (node->l == 0 && node->r == 0)
				return 1;
			else if (node->r == 0)
				return 1 + height(node->l);
			else if (node->l == 0)
				return 1 + height(node->r);
			else
				return 1 + std::max(height(node->l), height(node->r));
		}
		node_alloc get_allocator() const { return _nal; }

	private:
		void _init_limits () {
			_begin = _nal.allocate(1);
			_nal.construct(_begin, node());
			_begin->b = -1;
			_end = _nal.allocate(1);
			_nal.construct(_end, node());
			_end->b = 1;
		}
		void _insert_node(node_pointer &newnode, node_pointer &parent) {
			newnode->p = parent;
			parent = newnode;
		}
		void _set_begin(node_pointer &newnode, node_pointer &parent) {
			parent->l = newnode;
			newnode->p = parent;
			newnode->l = _begin;
			_begin->p = newnode;
		}
		void _set_end(node_pointer &newnode, node_pointer &parent) {
			parent->r = newnode;
			newnode->p = parent;
			newnode->r = _end;
			_end->p = newnode;
		}
		void _erase_node (node_pointer to_erase) {
			_nal.destroy(to_erase);
			_nal.deallocate(to_erase, 1);
		}
		node_pointer _search_key(node_pointer tmp, key_type const & key) const {
			// std::cout << "key = " << key << ", tmp->key = " << tmp->data.first << std::endl;
			if (!tmp || tmp == _begin || tmp == _end)
				return _end;
			else if (_comp(key, tmp->data.first))
				return _search_key(tmp->l, key);
			else if (_comp(tmp->data.first, key))
				return _search_key(tmp->r, key);
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