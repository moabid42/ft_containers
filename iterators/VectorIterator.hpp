/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:28:44 by moabid            #+#    #+#             */
/*   Updated: 2022/12/09 00:29:04 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "iterator.hpp"

namespace ft
{
	//VECTOR ITERATORS
	template <class T>
	class VectorIterator {
	public:
		typedef	T*															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
    	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	// CONSTRUCTORS
		// 1) Default
		VectorIterator() : _ptr() { }
		// 2) Initialization
		VectorIterator(const iterator_type& ptr) : _ptr(ptr) { }
		// 3) Copy
		VectorIterator ( const VectorIterator& x ) { _ptr = x.base(); }
	// ASSIGN OPERATOR
		VectorIterator& operator=( const VectorIterator& x ) {
			if (*this != x)
				_ptr = x.base();
			return	*this;
		}
	// DESTRUCTOR
		~VectorIterator() { }
	// MEMBER FUNCTIONS
		// Base - returns base iterator
		pointer	base() const {
			return _ptr;
		}
		// Pre-increment iterator position
		VectorIterator&	operator++() {
			++_ptr;
			return *this;
		}
		// Post-increment iterator position
		VectorIterator	operator++(int) {
			VectorIterator temp = *this;
			++_ptr;
			return temp;
		}
		// Dereference iterator
		reference	operator*() const {
			return *_ptr;
		}
		// Dereference iterator
		pointer operator->() const {
			return _ptr;
		}
		// Pre-decrement iterator position
		VectorIterator&	operator--() {
			--_ptr;
			return *this;
		}
		// Post-decrement iterator position
		VectorIterator	operator--(int) {
			VectorIterator temp = *this;
			--_ptr;
			return temp;
		}
		// Addition operator
		VectorIterator	operator+ (difference_type n) const {
			return VectorIterator(_ptr + n);
		}
		// Advance iterator
		VectorIterator&	operator+= (difference_type n) {
			_ptr += n;
			return *this;
		}
		// Subtraction operator
		VectorIterator	operator- (difference_type n) const {
			return VectorIterator(_ptr - n);
		}
		// Retrocede iterator
		VectorIterator&	operator-= (difference_type n) {
			_ptr -= n;
			return *this;
		}
		// Dereference iterator with offset
		reference	operator[] (difference_type n) const {
			return *(_ptr + n);
		}
		// Constant cast overload
		operator VectorIterator<const T>() const {
			return (_ptr);
		}
	protected:
		pointer		_ptr;
	};

	//RELATIONAL OPERATORS 
	template <class T>
	bool operator==(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T, class T1>
	bool operator==(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T>
	bool operator!=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T, class T1>
	bool operator!=(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T>
	bool operator>(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T, class T1>
	bool operator>(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T>
	bool operator<(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T, class T1>
	bool operator<(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T>
	bool operator<=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class T, class T1>
	bool operator<=(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class T>
	bool operator>=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class T, class T1>
	bool operator>=(const VectorIterator<T>& lhs, const VectorIterator<T1>& rhs) {
		return lhs.base() >= rhs.base();
	}
	// COMPUTES THE DISTANCE BETWEEN TWO ITERATOR ADAPTORS
	template<class T>
	typename VectorIterator<T>::difference_type
		operator-(	const VectorIterator<T>& lhs, const VectorIterator<T>& rhs ) {
			return lhs.base() - rhs.base();
	}
	template<class T1, class T2>
	typename VectorIterator<T1>::difference_type
		operator-(	const VectorIterator<T1>& lhs, const VectorIterator<T2>& rhs ) {
			return lhs.base() - rhs.base();
	}
	// ADVANCES THE ITERATOR
	template<class T>
	VectorIterator<T>operator+( typename VectorIterator<T>::difference_type n,
										const VectorIterator<T>& it ) {
			return VectorIterator<T>(it.base() + n);
	}
}
