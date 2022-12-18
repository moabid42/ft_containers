/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:27:47 by moabid            #+#    #+#             */
/*   Updated: 2022/12/09 18:00:59 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility.hpp"
# include "TreeIterator.hpp"
# include "../algorithm.hpp"

namespace ft
{
	//TREE IMPLEMENTATION
	template<class T, class Compare, class Allocator>
	class tree {
	public:
		typedef T																	value_type;
		typedef Node<value_type>													node_type;
		typedef node_type*															pointer;
		typedef Compare																value_compare;
		typedef Allocator															allocator_type;
		typedef typename Allocator::template rebind<node_type>::other				node_allocator;
		typedef typename allocator_type::size_type									size_type;
		typedef typename ft::TreeIterator<value_type, node_type*, tree> 			iterator;
		typedef typename ft::TreeIterator<const value_type, const node_type*, tree>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename std::ptrdiff_t												difference_type;
	
	protected:
		allocator_type			_alloc;
		node_allocator			_node_alloc;
		value_compare			_compare;
		pointer					_root;
		pointer					_head;
		pointer					_nil;
		size_type				_size;
	
	public:
		//  CONSTRUCTORS AND DESTRUCTOR
		tree(const value_compare& compare = value_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _node_alloc(alloc), _compare(compare), _root(_null_leaf_alloc()),
				_head(nullptr), _nil(_null_leaf_alloc()), _size(0) { }
		tree (const tree& x) :	_alloc(x._alloc), _node_alloc(x._node_alloc), _compare(x._compare),
								_root(_null_leaf_alloc()), _head(nullptr), _nil(_null_leaf_alloc()), _size(0) {
			_copy_tree(x._head);
			_root->left = _head;
		}
		~tree() {
			clear();
			_node_alloc.deallocate(_root, 1);
			_node_alloc.deallocate(_nil, 1);
		}
		tree& operator= (const tree& x) {
			if (this != &x) {
				_alloc = x._alloc;
				_node_alloc = x._node_alloc;
				_compare = x._compare;
				clear();
				_copy_tree(x._head);
				_root->left = _head;
			}
			return *this;
		}
	
		size_type	max_size () const { return _node_alloc.max_size(); }
		size_type	size () const { return _size; }
		// 1)Insertion of single element
		ft::pair<iterator, bool> insert(const value_type& val) {
			if (_head == nullptr) {
				_head = _nallocate(val);
				_head->red = false;
				_head->parent = _root;
				_root->left = _head;
				_size++;
				return ft::make_pair(iterator(_head), true);
			}
			for ( pointer tmp = _head; tmp != nullptr; ) {
				if (!_compare(tmp->value, val)) {
					if (!_compare(val, tmp->value))
						return ft::make_pair(iterator(tmp), false);
					if (tmp->left == nullptr) {
						tmp->left = _nallocate(val);
						tmp->left->parent = tmp;
						tmp = tmp->left;
						_ins_balance(tmp);
						_size++;
						return ft::make_pair(iterator(tmp), true);
					}
					tmp = tmp->left;
				}
				else {
					if (tmp->right == nullptr) {
						tmp->right = _nallocate(val);
						tmp->right->parent = tmp;
						tmp = tmp->right;
						_ins_balance(tmp);
						_size++;
						return ft::make_pair(iterator(tmp), true);
					}
					tmp = tmp->right;
				}
			}
			return (ft::make_pair(iterator(_root), false));
		}
		iterator begin () {
			if (_head == nullptr)
				return iterator(_root);
			return iterator(node_minimum(_head)); 
		}
		const_iterator begin () const {
			if (_head == nullptr)
				return const_iterator(_root);
			return const_iterator(node_minimum(_head)); 
		}
		iterator end () { return iterator(_root); }
		const_iterator end () const { return const_iterator(_root);	}
		// Checks if tree is empty
		bool empty () const {
			if (_size == 0)
				return true;
			return false;
		}
		// 2) Find
		pointer find(const value_type& key) const {
			for ( pointer tmp = _head; tmp != nullptr; ) {
				if (!_compare(tmp->value, key)) {
					if (!_compare(key, tmp->value))
						return tmp;
					if (tmp->left == nullptr)
						return nullptr;
					tmp = tmp->left;
				}
				else {
					if (tmp->right == nullptr) {
						return nullptr;
					}
					tmp = tmp->right;
				}
			}
			return nullptr;
		}
			// for iterator
		pointer iter_find(const value_type& key) const {
			for ( pointer tmp = _head; tmp != nullptr; ) {
				if (!_compare(tmp->value, key)) {
					if (!_compare(key, tmp->value))
						return tmp;
					if (tmp->left == nullptr)
						return _root;
					tmp = tmp->left;
				}
				else {
					if (tmp->right == nullptr) {
						return _root;
					}
					tmp = tmp->right;
				}
			}
			return _root;
		}
		// 3) Deletion
		void	erase (pointer pos) {
			if (pos == nullptr || pos == _root)
				return ;
			if (_size == 1 && pos == _head) {
				_del_node(pos);
				_head = nullptr;
				_root->left = nullptr;
				return ;
			}
			_rb_deletion(pos);
		}
		size_type erase (const value_type& k) {
			pointer pos = find(k);
			if (pos == nullptr)
				return 0;
			_rb_deletion(pos);
			return 1;
		}
		void	clear() {
			_clear(_head);
			_head = nullptr;
		}
		void	_clear(pointer head) {
			if (head == nullptr)
				return ;
			_clear(head->left);
			_clear(head->right);
			_del_node(head);
		}
		// 4) Swap
		void swap (tree& x) {
			ft::swap(_root, x._root);
			ft::swap(_head, x._head);
			ft::swap(_node_alloc, x._node_alloc);
			ft::swap(_alloc, x._alloc);
			ft::swap(_compare, x._compare);
			ft::swap(_size, x._size);
		}
		// 5) Count
		size_type count (const value_type& k) const {
			if (find(k) == nullptr)
				return 0;
			return 1;
		}
		// 6) lower/upper bound
		iterator lower_bound (const value_type& k) {
			iterator it = begin();
			iterator last = end();
			while (it != last && _compare(*it, k))
				it++;
			return it;
		}
		const_iterator lower_bound (const value_type& k) const {
			const_iterator it = begin();
			const_iterator last = end();
			while (it != last && _compare(*it, k))
				it++;
			return it;
		}
		// 5) Return iterator to upper bound
		iterator upper_bound (const value_type& k) {
			iterator it = end();
			iterator first = begin();
			for (iterator tmp = it; it != first; it--) {
				tmp--;
				if (!_compare(k, *tmp))
					return it;
			}
			return it;
		}
		const_iterator upper_bound (const value_type& k) const {
			const_iterator it = end();
			const_iterator first = begin();
			for (const_iterator tmp = it; it != first; it--) {
				tmp--;
				if (!_compare(k, *tmp))
					return it;
			}
			return it;
		}
		// Min/Max search functions
		pointer	node_maximum (pointer current) const {
			if (current == nullptr)
				return current;
			while (current->right != nullptr)
				current = current->right;
			return current;
		}
		pointer	node_minimum (pointer current) const {
			if (current == nullptr)
				return current;
			while (current->left != nullptr)
				current = current->left;
			return current;	
		}
		// Predecessor/successor functions
		pointer	successor (pointer current) const {
			if (current->right != nullptr)
				return node_minimum(current->right);
			pointer	Par = current->parent;
			while (Par != _root && current == Par->right) {
				current = Par;
				Par = Par->parent;
			}
			return Par;
		}
		pointer	predecessor (pointer current) const {
			if (current->left != nullptr)
				return node_maximum(current->left);
			pointer	Par = current->parent;
			while (Par != _root && current == Par->left) {
				current = Par;
				Par = Par->parent;
			}
			return Par;
		}
	private:
		//TREE MANIPULATION
			//1)Left Rotation
		void	rotate_left(pointer x) {
			pointer y = x->right;
	
			if (y) {
				x->right = y->left;
				if (y->left)
					y->left->parent = x;
				y->left = x;
				y->parent = x->parent;
				if (x->parent != _root) {
					if (x->parent->left == x)
						x->parent->left = y;
					else
						x->parent->right = y;
				}
				else {
					_head = y;
					_root->left = _head;
				}
				x->parent = y;
			}
		}
			//2)Right Rotation
		void	rotate_right(pointer x) {
			pointer y = x->left;
	
			if (y) {
				x->left = y->right;
				if (y->right)
					y->right->parent = x;
				y->right = x;
				y->parent = x->parent;
				if (x->parent != _root) {
					if (x->parent->left == x)
						x->parent->left = y;
					else
						x->parent->right = y;
				}
				else {
					_head = y;
					_root->left = _head;
				}
				x->parent = y;
			}
		}
			//3)Recolour
		void	recolor_node(const node_type& x) {
			if (x.red == true)
				x.red = false;
			else
				x.red = true;
		}
		// UTILS
			// 1) Node Allocation
				// a) red node allocation
		pointer	_nallocate (const value_type& val) {
			pointer new_node = _node_alloc.allocate(1);
			try	{
				_alloc.construct(&(new_node->value), val);
			}
			catch(...) {
				_node_alloc.deallocate(new_node, 1);
			}
			new_node->red = true; new_node->left = nullptr;
			new_node->right = nullptr; new_node->parent = nullptr;
			return new_node;
		}
				// b) Null leaf allocation
		pointer	_null_leaf_alloc() {
			pointer new_node = _node_alloc.allocate(1);
			new_node->red = false; new_node->left = nullptr;
			new_node->right = nullptr; new_node->parent = nullptr;
			return new_node;
		}
			// 2) Deallocate Node
		void	_del_node (pointer pos) {
			try	{
				_alloc.destroy(&(pos->value));
			}
			catch(...) {
				_node_alloc.deallocate(pos, 1);
			}
			_node_alloc.deallocate(pos, 1);
			_size--;
		}
			// 3) Balance Tree after Insertion
		void	_ins_balance (pointer Kid) {
			for (pointer Uncle = nullptr; Kid != _head && Kid->parent->red == true; ) {
				if (Kid->parent == Kid->parent->parent->left) {
					Uncle = Kid->parent->parent->right;
					if (Uncle && Uncle->red == true)
						Kid = _ins_balance_case1(Kid, Uncle);	
					else {
						if (Kid == Kid->parent->right) {
							Kid = Kid->parent;
							rotate_left(Kid);
						}
						_ins_balance_case3(Kid);
					}				
				}
				else {
					Uncle = Kid->parent->parent->left;
					if (Uncle && Uncle->red == true)
						Kid = _ins_balance_case1(Kid, Uncle);
					else {
						if (Kid == Kid->parent->left) {
							Kid = Kid->parent;
							rotate_right(Kid);
						}
						_ins_balance_case2(Kid);
					}
				}
			}
			_head->red = false;
		}
		// 4) Balncing insertion cases
			 // If Uncle is red colour -> colors to be flipped -> Uncle and Parent become black, Grandparent red
		pointer	_ins_balance_case1(pointer Kid, pointer Uncle) {
			Kid->parent->red = false;
			Uncle->red = false;
			if (Kid->parent->parent != _root)
				Kid->parent->parent->red = true;
			return Kid->parent->parent;
		}
			 //b) Uncle is black, Parent is right child and kid is right child
		void	_ins_balance_case2(pointer Kid) {
			Kid->parent->red = false;
			Kid->parent->parent->red = true;
			rotate_left(Kid->parent->parent);
		}
			 //c) Uncle is black, Parent is right child and kid is left child
		void	_ins_balance_case3(pointer Kid) {
			Kid->parent->red = false;
			Kid->parent->parent->red = true;
			rotate_right(Kid->parent->parent);
		}
		// 5) Deleting Node from tree
		void	_rb_deletion(pointer z) {
			bool	is_red = z->red;
			pointer x;
			pointer y = z;
	
			if (z->left == nullptr) {
				if (z->right == nullptr && is_red == false) {
					z->right = _nil;
					z->right->parent = z;
				}
				x = z->right;
				_del_changenodes(z, z->right);
			}
			else if (z->right == nullptr) {
				x = z->left;
				_del_changenodes(z, z->left);
			}
			else {
				y = node_maximum(z->left);
				is_red = y->red;
				if (y->left == nullptr && is_red == false) {
					y->left = _nil;
					y->left->parent = y;
				}
				x = y->left;
				if (y->parent == z) {
					x->parent = y;
				}
				else {
					_del_changenodes(y, y->left);
					y->left = z->left;
					y->left->parent = y;
				}
				_del_changenodes(z, y);
				y->right = z->right;
				y->right->parent = y;
				y->red = z->red;
			}		
			_del_node(z);
			if (is_red == false)
				_del_rebalance(x);
			_remove_nill_leaf();
		}
			 // a) Rebalancing tree after deletion
		void _del_rebalance(pointer x) {
			for (pointer s = nullptr; x != _head && x->red == false;) {
				if (x == x->parent->left) {
					s = x->parent->right;
					if (s->red == true) {
						s->red = false;
						x->parent->red = true;
						rotate_left(x->parent);
						s = x->parent->right;
					}
					if ((s->left == nullptr || s->left->red == false) && (s->right == nullptr || s->right->red == false)) {
						s->red = true;
						x = x->parent;
					}
					else {
						if (s->right == nullptr || s->right->red == false) {
							s->left->red = false;
							s->red = true;
							rotate_right(s);
							s = x->parent->right;
						}
						s->red = x->parent->red;
						s->parent->red = false;
						s->right->red = false;
						rotate_left(x->parent);
						x = _head;
					}
				}
				else {
					s = x->parent->left;
					if (s->red == true) {
						s->red = false;
						x->parent->red = true;
						rotate_right(x->parent);
						s = x->parent->left;
					}
					if ((s->left == nullptr || s->left->red == false) && (s->right == nullptr || s->right->red == false)) {
						s->red = true;
						x = x->parent;
					}
					else {
						if (s->left == nullptr || s->left->red == false) {
							s->right->red = false;
							s->red = true;
							rotate_left(s);
							s = x->parent->left;
						}
						s->red = x->parent->red;
						x->parent->red = false;
						s->left->red = false;
						rotate_right(x->parent);
						x = _head;
					}
				}
			}
			x->red = false;
		}
		// Replaces node 'pos' with a node 'other_pos'
		void _del_changenodes(pointer pos, pointer other_pos) {
			if (pos->parent == _root) {
				_head = other_pos;
				_root->left = _head;
			}
			else if (pos == pos->parent->left)
				pos->parent->left = other_pos;
			else
				pos->parent->right = other_pos;
			if (other_pos)
				other_pos->parent = pos->parent;
		}
	
		void _remove_nill_leaf() {
			if (_nil->parent) {
				if (_nil->parent->left == _nil)
					_nil->parent->left = nullptr;
				else
					_nil->parent->right =nullptr;
				_nil->parent = nullptr;
			}
			if (_head == _nil)
				_head = nullptr;
		}
		void	_copy_tree(pointer other_head) {
			if (other_head == nullptr)
				return ;
			insert(other_head->value);
			_copy_tree(other_head->left);
			_copy_tree(other_head->right);
		}
	};
}
