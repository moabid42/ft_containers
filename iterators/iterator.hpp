/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:27:35 by moabid            #+#    #+#             */
/*   Updated: 2022/12/09 00:27:41 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iterator>

namespace ft {
	typedef	std::output_iterator_tag			output_iterator_tag;
	typedef	std::forward_iterator_tag			forward_iterator_tag;
	typedef	std::bidirectional_iterator_tag		bidirectional_iterator_tag;
	typedef	std::input_iterator_tag				input_iterator_tag;
	typedef	std::random_access_iterator_tag		random_access_iterator_tag;

	//ITERATOR
	template<class Category, class T, class Distance = std::ptrdiff_t,
				class Pointer = T*,  class Reference = T&>
	struct iterator {
		typedef Distance								difference_type;
		typedef T										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef Category								iterator_category;
	};

	//ITERATOR TRAITS
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef std::ptrdiff_t							difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;
	};
	
	template <class T>
	struct iterator_traits<const T*> {
		typedef std::ptrdiff_t							difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	//REVERSE ITERATOR
	template <class Iterator>
	class reverse_iterator {
	public:
		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	// CONSTRUCTOR
		// 1) Default
		reverse_iterator() : _iter() { }
		// 2) Initialization
		explicit	reverse_iterator (iterator_type it) : _iter(it) { } 
		// 3) Copy
		template <class iterator_type>
		reverse_iterator (const reverse_iterator<iterator_type>& other) : _iter(other.base()) {}
		~reverse_iterator() {}

	// ASSIGN OPERATOR
		// Assigns another iterator adaptor
		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other ) {
			_iter = other.base();
			return *this;
		}

	// MEMBER FUNCTIONS
		// Base - returns base iterator
		iterator_type	base() const {
			return _iter;
		}
		// Dereference iterator
		reference	operator*() const {
			iterator_type	tmp = _iter;
			return *--tmp;
		}
		// Addition operator
		reverse_iterator	operator+ (difference_type n) const {
			return reverse_iterator(_iter - n);
		}
		// Pre-increment iterator position
		reverse_iterator&	operator++() {
			--_iter;
			return *this;
		}
		// Post-increment iterator position
		reverse_iterator	operator++(int) {
			reverse_iterator temp = *this;
			--_iter;
			return temp;
		}
		// Advance iterator
		reverse_iterator&	operator+= (difference_type n) {
			_iter -= n;
			return *this;
		}
		// Subtraction operator
		reverse_iterator	operator- (difference_type n) const {
			return reverse_iterator(_iter + n);
		}
		// Pre-decrement iterator position
		reverse_iterator&	operator--() {
			++_iter;
			return *this;
		}
		// Post-decrement iterator position
		reverse_iterator	operator--(int) {
			reverse_iterator temp = *this;
			++_iter;
			return temp;
		}
		// Retrocede iterator
		reverse_iterator&	operator-= (difference_type n) {
			_iter += n;
			return *this;
		}
		// Dereference iterator
		pointer operator->() const {
			return &(operator*());
		}
		// Dereference iterator with offset
		reference	operator[] (difference_type n) const {
			return *(*this + n);
		}
		// Constant cast overload
		operator reverse_iterator<const iterator_type>() const {
			return (_iter);
		}
	protected:
		iterator_type		_iter;
	};

	//RELATIONAL OPERATORS 
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	// COMPUTES THE DISTANCE BETWEEN TWO ITERATOR ADAPTORS
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator-(	const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) {
			return rhs.base() - lhs.base();		
	}
	template<class Iterator, class Iterator2>
	typename reverse_iterator<Iterator>::difference_type
		operator-(	const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs ) {
			return rhs.base() - lhs.base();		
	}

	// ADVANCES THE ITERATOR
	template<class Iterator>
	reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n,
											const reverse_iterator<Iterator>& it ) {
			return reverse_iterator<Iterator>(it.base() - n);
	}

	//Distance function
	template<class Iterator>
	typename ft::iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, random_access_iterator_tag) {
		return last - first;
	}

	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		do_distance(Iterator first, Iterator last, input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type result = 0;
		for ( ; first != last; first++)
			++result;
		return result;
	}
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last) {
		return do_distance(first, last,
				typename iterator_traits<Iterator>::iterator_category());
	}
}
