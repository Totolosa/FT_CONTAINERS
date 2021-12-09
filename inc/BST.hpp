#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "Node.hpp"
# include "pair.hpp"
# include "map_iterator.hpp"

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
		typedef ft::map_iterator<ft::Node<value_type> >			iterator;
		typedef ft::map_iterator<ft::Node<const value_type> >	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		BST(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _n(), _root(NULL), _nal(), _comp(comp), _tal(alloc) {
				_begin = _nal.allocate(1);
				_nal.construct(_begin, node());
				_end = _nal.allocate(1);
				_nal.construct(_end, node());
			}
		// ~BST() { }

		//		--> MODIFIERS <--

		ft::pair< iterator, bool> insert (const value_type& val) { return _insert(_root, val); }
		bool erase(key_type const & k) {
			node_pointer tmp = _search_key(_root, k);
			if (tmp == _end)
				return false;
			if (tmp->r && tmp->l) {
				node_pointer tmp2 = tmp->r;
				while (tmp2->l)
					tmp2 = tmp->l;
				tmp2->p = tmp->p;
				tmp2->r = tmp->r;
				tmp2->l = tmp->l;
			}
			else if (tmp->l) {
				tmp->p->l = tmp->l;
				tmp->l->p = tmp->p;
			}
			else if (tmp->r) {
				tmp->p->r = tmp->r;
				tmp->r->p = tmp->p;
			}
			// else {
				_nal.destroy(&(tmp->data));
				_nal.deallocate(tmp, 1);
			// }
			return true;

		}
		// void erase(iterator & start, iterator & end) {
		// 	iterator tmp = _search_key();
		// }
		
		//		--> CAPACITY <--

		bool empty() const { return _n == 0; }
		size_t size() const { return _n; }

		//		--> ACCESSORS <--

		iterator begin() { return ++iterator(_begin); }
		const_iterator begin() const {return ++iterator(_begin); }
		iterator end() { return iterator(_end); }
		const_iterator end() const {return iterator(_end); }
		

	private:
		ft::pair< iterator, bool> _insert (node_pointer &tmp, const value_type& val) {
			if (!tmp || tmp == _begin || tmp == _end) {
				node_pointer newnode = _nal.allocate(1);
				_nal.construct(newnode, node(val));
				if (!tmp) {
					// std::cout << "!tmp" << std::endl;
					_insert_node(newnode, tmp);
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
				// std::cout << "ICI, _n = " << _n << std::endl;
				return (ft::make_pair(iterator(newnode), true));
			}
			else if (_comp(val.first, tmp->data.first)) {
				// std::cout << "insert <" << std::endl;
				return _insert(tmp->l, val);
			}
			else if (_comp(tmp->data.first, val.first)) {
				// std::cout << "insert >" << std::endl;
				return _insert(tmp->r, val);
			}
			else {
				return (ft::make_pair(iterator(tmp), false));
			}
		}
		void _insert_node(node_pointer &newnode, node_pointer &parent) {
			newnode->p = parent;
			parent = newnode;
			if (_n == 0) {
				newnode->l = _begin;
				_begin->p = newnode;
				newnode->r = _end;
				_end->p = newnode;
			}
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
		node_pointer _search_key(node_pointer &tmp, key_type const & key) {
			if (!tmp || tmp == _begin || tmp == _end)
				return _end;
			else if (key == tmp->data.first)
				return tmp;
			else if (_comp(key, tmp->data.first))
				return _search_key(tmp->l, key);
			else if (_comp(tmp->data.first, key))
				return _search_key(tmp->r, key);
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