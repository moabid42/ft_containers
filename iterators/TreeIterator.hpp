/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:28:24 by moabid            #+#    #+#             */
/*   Updated: 2022/12/09 00:28:53 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"

namespace ft
{
	//NODE STRUCT
	template <typename T>
	struct Node
	{
		T			value;
		Node*		left;
		Node*		right;
		Node*		parent;
		bool		red;
	};
	//MAP ITERATORS
	template <class T, class TNode, class Tree>
	class TreeIterator {
	public:
		typedef T															value_type;
		typedef	TNode														node_type;
		typedef T*															pointer;
		typedef T&															reference;
    	typedef ptrdiff_t													difference_type;
		typedef typename ft::bidirectional_iterator_tag						iterator_category;
		typedef size_t														size_type;

	// CONSTRUCTORS
		// 1) Default
		TreeIterator() : _ptr() { }
		// 2) Initialization
		TreeIterator(const node_type& ptr) : _ptr(ptr) { }
		// 3) Copy
		TreeIterator ( const TreeIterator<typename Tree::value_type, typename Tree::node_type *, Tree> & x ) :_ptr(x.base()) { }
	// ASSIGN OPERATOR
		TreeIterator& operator=( const TreeIterator& x ) {
			if (*this != x)
				_ptr = x.base();
			return	*this;
		}
	// DESTRUCTOR
		~TreeIterator() { }
	// MEMBER FUNCTIONS
		// Base - returns base iterator
		node_type	base() const {
			return _ptr;
		}
		// Pre-increment iterator position
		TreeIterator&	operator++() {
			if (_ptr->right != nullptr) {
				_ptr = _ptr->right;
				while (_ptr->left != nullptr)
					_ptr = _ptr->left;
				return *this;
			}
			node_type par = _ptr->parent;
			while (par->parent != nullptr && _ptr == par->right) {
				_ptr = par;
				par = par->parent;
			}
			_ptr = par;
			return *this;
		}
		// Post-increment iterator position
		TreeIterator	operator++(int) {
			TreeIterator temp = *this;
			++(*this);
			return temp;
		}
		// Dereference iterator
		reference	operator*() const {
			return _ptr->value;
		}
		reference	operator*() {
			return _ptr->value;
		}
		// Dereference iterator
		pointer operator->() const {
			return &(_ptr->value);
		}
		pointer operator->() {
			return &(_ptr->value);
		}
		// Pre-decrement iterator position
		TreeIterator&	operator--() {
			if (_ptr->left != nullptr) {
				_ptr = _ptr->left;
				while (_ptr->right != nullptr)
					_ptr = _ptr->right;
				return *this;
			}
			node_type par = _ptr->parent;
			while (par->parent != nullptr && _ptr == par->left) {
				_ptr = par;
				par = par->parent;
			}
			_ptr = par;
			return *this;
		}
		// Post-decrement iterator position
		TreeIterator	operator--(int) {
			TreeIterator temp = *this;
			--(*this);
			return temp;
		}
		// Addition operator
		TreeIterator	operator+ (difference_type n) const {
			TreeIterator temp = *this;
			for (size_type i = 0; i < n; i++)
				temp++;
			return temp;
		}
		// Subtraction operator
		TreeIterator	operator- (difference_type n) const {
			TreeIterator temp = *this;
			for (size_type i = 0; i < n; i++)
				temp--;
			return temp;
		}
		bool operator==(const TreeIterator& x) const {
			return _ptr == x._ptr;
		}
		bool operator!=(const TreeIterator& x) const {
			return !(_ptr == x._ptr);
		}
	protected:
		node_type		_ptr;
	};

	//RELATIONAL OPERATORS 
	template <class T, class T2, class tree>
	bool operator==(const TreeIterator<T, T2, tree>& lhs, const TreeIterator<T, T2, tree>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T, class T1, class tree, class T2, class T12, class tree2>
	bool operator==(const TreeIterator<T, T2, tree>& lhs, const TreeIterator<T1, T12, tree2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T, class T2, class tree>
	bool operator!=(const TreeIterator<T, T2, tree>& lhs, const TreeIterator<T, T2, tree>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T, class T1, class tree, class T2, class T12, class tree2>
	bool operator!=(const TreeIterator<T, T2, tree>& lhs, const TreeIterator<T1, T12, tree2>& rhs) {
		return lhs.base() != rhs.base();
	}
}
