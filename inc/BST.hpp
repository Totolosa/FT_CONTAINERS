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

		ft::pair< iterator, bool> insert (const value_type& val) {
			return _insert(_root, val);
		}
		bool empty() const { return _n == 0; }
		bool size() const { return _n; }

		iterator begin() { 
			return iterator(_begin)++;
		}
		const_iterator begin() const {
			return iterator(_begin)++;
		}
		iterator end() { 
			return iterator(_end);
		}
		const_iterator end() const {
			return iterator(_end);
		}
		

	private:
		ft::pair< iterator, bool> _insert (node_pointer &tmp, const value_type& val) {
			if (!tmp || tmp == _begin || tmp == _end) {
				node_pointer newnode = _nal.allocate(1);
				_nal.construct(newnode, node(val));
				if (!tmp)
					_insert_node(newnode, tmp);
				else if (tmp == _begin)
					_set_begin(newnode, tmp->p);
				else if (tmp == _end)
					_set_end(newnode, tmp->p);
				_n++;
				return (ft::make_pair(iterator(newnode), true));
			}
			else if (_comp(val.first, tmp->data.first))
				return _insert(tmp->l, val);
			else if (tmp->data.first < val.first)
				return _insert(tmp->r, val);
			else
				return (ft::make_pair(iterator(tmp), false));
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

		size_t			_n;
		node			*_root;
		node			*_begin;
		node			*_end;
		node_alloc		_nal;
		Compare			_comp;
		allocator_type	_tal;
};

#endif