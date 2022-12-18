/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:27:55 by moabid            #+#    #+#             */
/*   Updated: 2022/12/14 15:43:52 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdexcept>
# include "iterators/VectorIterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft
{
	/**
    * ------------------------------------------------------------- *
    * ------------------------ FT::VECTOR ------------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct vector
    * (destructor):         Destruct vector
    * operator=:            Assign vector
    *
    * - Iterators:
    * begin:                Return iterator to beginning
    * end:                  Return iterator to end
    * rbegin:               Return reverse iterator to reverse beginning
    * rend:                 Return reverse iterator to reverse end
    *
    * - Capacity:
    * size:                 Return size
    * max_size:             Return maximum size
    * resize:               Change size
    * capacity:             Return size of allocated storage capacity
    * empty:                Test whether vector is empty
    * reserve:              Request a change in capacity
    *
    * - Element access:
    * operator[]:           Access element
    * at:                   Access element
    * front:                Access first element
    * back:                 Access last element
    *
    * - Modifiers:
    * assign:               Assign vector content
    * push_back:            Add element at the end
    * pop_back:             Delete last element
    * insert:               Insert elements
    * erase:                Erase elements
    * swap:                 Swap content
    * clear:                Clear content
    *
    * - Non-member function overloads:
    * relational operators: Relational operators for vector
    * swap:                 Exchange contents of two vectors
    * ------------------------------------------------------------- *
    */
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			/* ------------------------------------------------------------- */
    	    /* -------------------------- ALIASES -------------------------- */
			typedef	T											value_type;
			typedef	Allocator									allocator_type;
			typedef	typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef	ft::VectorIterator<value_type>				iterator;
			typedef	ft::VectorIterator<const value_type>		const_iterator;
			typedef	ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		protected:
    	    /* ------------------------------------------------------------- */
    	    /* ------------------------- ATTRIBUTES ------------------------ */
			size_type		_size;
			size_type		_cap;
			pointer			_begin;
			allocator_type	_alloc;
		public:
    	    /* ------------------------------------------------------------- */
    	    /* ---------------------------- BODY --------------------------- */

 			/* ------------------------------------------------------------- */
            /**
            *   Default constructor, creates a vector with a size of 0.
            *
            *   @param alloc    The template param used for the allocation.
            */
            /* ------------------------------------------------------------- */
			
			explicit vector ( const allocator_type& alloc = allocator_type() )
							: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) { }

            /* ------------------------------------------------------------- */
            /**
            *   Fill constructor, creates a vector with a size of n and initializes the 
            *   values.
            *
            *   @param n        The number of elements that will be created.
            *   @param val      The value used for initialization (value initialized by default).
            *   @param alloc    The template param used for the allocation.
            */
            /* ------------------------------------------------------------- */

			explicit vector ( size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type() )
								: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) {
				assign(n, val);
			}
			
            /* ------------------------------------------------------------- */
            /**
            *   Range constructor, creates a vector with a size equal to the range between two
            *   iterators and copy the values of this range to the new elements created.
            *
            *   @param first    An iterator representing first element of the range.
            *   @param last     An iterator indicating end of the range (will be excluded and not copied).
            *   @param alloc    The template param used for the allocation.
            */
            /* ------------------------------------------------------------- */

			template <class InputIterator>
			vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() )
					: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) {
				assign(first, last);
			}

            /* ------------------------------------------------------------- */
            /**
            *   Copy constructor, creates a vector with the same size and copy/construct
            *   all x values to the new area allocated.
            *   
            *   @param x        The vector that will be copied.
            */
            /* ------------------------------------------------------------- */
			
			vector ( const vector& x ) : _size(0), _cap(0), _begin(nullptr), _alloc(x.get_allocator()) { 
				_vallocate(x.capacity());
				try {
					for ( ; _size < x._size; _size++)
						_alloc.construct(_begin + _size, x[_size]);
				}
				catch(...) {
					_vdeallocate();
				}
			}
	
            /* ------------------------------------------------------------- */
            /**
            *   Destructor, destroys all the elements and free the allocated memory.
            */
            /* ------------------------------------------------------------- */
			
			~vector() { _vdeallocate(); }
	
            /* ------------------------------------------------------------- */
            /**
            *   Assigns a vector to this vecto using the assign method.
            *   
            *   @param x        The vector that will be assigned.
            */
            /* ------------------------------------------------------------- */
			
			vector& operator=( const vector& x ) {
				if (*this == x)
					return (*this);
				assign(x.begin(), x.end());
				return *this;
			}
	
            /* ------------------------------------------------------------- */
            /**
            *   Fill assign, assigns a new size to the vector and fills it with the given value.
            *   
            *   @param count    The new size of the vector.
            *   @param val      The value used for initialization.
            */
            /* ------------------------------------------------------------- */

			void	assign(size_type count, const value_type& val) {
				if (count == 0)
					return;
				clear();
				if (count > _cap) {
					if (_cap > 0)
						_alloc.deallocate(_begin, _cap);
					_vallocate(count);
				}
				try {
					for ( ; _size < count; _size++)
						_alloc.construct(_begin + _size, val);
				}
				catch(...) {
					_vdeallocate();
				}
			}
			
            /* ------------------------------------------------------------- */
            /**
            *   Range assign, assigns a new size to the vector and fills it with the values
            *   of the range between two iterators.
            *   
            *   @param first    An iterator representing first element of the range.
            *   @param last     An iterator indicating end of the range (will be excluded and not copied).
            */
            /* ------------------------------------------------------------- */

			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL) {
				_assignrange(first, last, typename iterator_traits<InputIterator>::iterator_category());
			}
			
            /* ------------------------------------------------------------- */
            /**
            *   Allocator getter, returns the allocator used by the vector.
            */
            /* ------------------------------------------------------------- */

			allocator_type	get_allocator() const { return _alloc; }
	
            /* ------------------------------------------------------------- */
            /**
            *   Element access, returns a reference to the element at the given position.
            *   @param pos     The position of the element.
            */
            /* ------------------------------------------------------------- */

			reference	at(size_type pos) {
				if (pos >= size())			
					throw std::out_of_range("ft::vector");
				return *(_begin + pos);
			}

            /* ------------------------------------------------------------- */

			const_reference	at(size_type pos) const {
				if (pos >= size())			
					throw std::out_of_range("ft::vector");
				return *(_begin + pos);
			}
			
			/* ------------------------------------------------------------- */
			// "[]" - The same behavior as 'at' operator function, but no bounds checking is performed
            /* ------------------------------------------------------------- */			
			
			reference		operator[](size_type pos)		{ return *(_begin + pos); }

	        /* ------------------------------------------------------------- */
			
			const_reference	operator[](size_type pos) const	{ return *(_begin + pos); }
			
			/* ------------------------------------------------------------- */

			reference 		front()							{ return *_begin; }

            /* ------------------------------------------------------------- */
			
			const_reference front() const					{ return *_begin; }

            /* ------------------------------------------------------------- */

			reference		back() 							{ return *(_begin + _size - 1); }

            /* ------------------------------------------------------------- */

			const_reference	back() const					{ return *(_begin + _size - 1); }
            
			/* ------------------------------------------------------------- */
			
			value_type*			data() 						{ return _begin; }

            /* ------------------------------------------------------------- */

			const value_type*	data() const				{ return _begin; }
	
            /* ------------------------------------------------------------- */
            /**
            *   Iterators, returns an iterator to an element of the vector.
            */
            /* ------------------------------------------------------------- */

			iterator				begin()			{ return iterator(_begin); }

            /* ------------------------------------------------------------- */

			const_iterator 			begin() const	{ return const_iterator(_begin); }

            /* ------------------------------------------------------------- */

			iterator				end()			{ return iterator(_begin + _size); }

            /* ------------------------------------------------------------- */

			const_iterator			end() const 	{ return const_iterator(_begin + _size); }

            /* ------------------------------------------------------------- */

			reverse_iterator		rbegin()		{ return reverse_iterator(_begin + _size); }
			
            /* ------------------------------------------------------------- */
			
			const_reverse_iterator	rbegin() const	{ return reverse_iterator(_begin + _size); }
            
			/* ------------------------------------------------------------- */

			reverse_iterator		rend()			{ return reverse_iterator(_begin); }

            /* ------------------------------------------------------------- */

			const_reverse_iterator	rend() const	{ return const_reverse_iterator(_begin); }
	
            /* ------------------------------------------------------------- */
            /**
            *   Capacity, returns the size of the vector.
            */
            /* ------------------------------------------------------------- */
			
			bool	empty() const {
				if (_size == 0)
					return true;
				return false;
			}

            /* ------------------------------------------------------------- */
			
			size_type	size() const {
				return _size;
			}
			
			/* ------------------------------------------------------------- */
			
			size_type max_size() const {
				size_type _amax = _alloc.max_size();
				size_type _nmax = std::numeric_limits<size_type>::max() / 2;
				if (_amax < _nmax)
					return _amax;
				return _nmax;
			}
            
			/* ------------------------------------------------------------- */
			
			void	reserve( size_type new_cap ) {
				if (new_cap > max_size())
					throw std::length_error("ft::vector");
				else if (new_cap > _cap) {
					pointer	tmp = _pallocate(new_cap);
					size_type i = 0;
					try {
						for ( ; i < _size; i++)
							_alloc.construct(tmp + i, _begin[i]);
					}
					catch(...) {
						for (size_type j = 0; j < i; j++)	
							_alloc.destroy(tmp + i);
						_alloc.deallocate(tmp, new_cap);
					}
					_vdeallocate();
					_begin = tmp; _size = i; _cap = new_cap;
				}
			}
			
            /* ------------------------------------------------------------- */

			size_type	capacity() const {
				return _cap;
			}
	
            /* ------------------------------------------------------------- */
            /**
            *     Modifiers, adds or removes elements from the vector.
            */
            /* ------------------------------------------------------------- */

			void	clear() {
				for (; _size != 0; --_size) {
					_alloc.destroy(_begin + _size - 1);
				}
			}
            
			/* ------------------------------------------------------------- */
			
			iterator	insert( iterator position, const value_type& val ) {
				pointer		tmp;
				size_type	cap = _vcapcheck();
				size_type	dist = static_cast<size_type>(ft::distance(begin(), position));
				size_type	i = 0;
				size_type	k = 0;
	
				if (position == end()) {
					push_back(val);
					return &back();
				}
				tmp = _pallocate(cap);
				try {
					for ( ; i < _size; i++) {
						if (i == dist) {
							_alloc.construct(tmp + i, val);
							k = 1;
						}
						_alloc.construct(tmp + i + k, _begin[i]);
					}
				}
				catch(...) {
					for (size_type j = 0; j < i + k; j++)
						_alloc.destroy(tmp + i + k);
					_alloc.deallocate(tmp, cap);
				}
				_vdeallocate();
				_begin = tmp; _size = i + 1; _cap = cap;
				return iterator(_begin + dist);
			}
			
			/* ------------------------------------------------------------- */

			void	insert (iterator position, size_type n, const value_type& val) {
				pointer		new_vec;
				size_type	new_cap = _vcapcheck();
				size_type	new_size = n + _size;
				size_type	pos = static_cast<size_type>(ft::distance(begin(), position));
				size_type	i = 0;
				size_type	k = 0;
	
				if (new_size > new_cap)
					new_cap = new_size;
				new_vec = _pallocate(new_cap);
				try {
					for (; i < new_size; i++) {
						if (i == pos) {
							for ( ; k < n; k++)
								_alloc.construct(new_vec + i + k, val);
						}
						if (i < _size)
							_alloc.construct(new_vec + i + k, *(_begin + i));
					}
				}
				catch(...) {
					for (size_type j = 0; j < i + k; j++)
						_alloc.destroy(new_vec + i + k);
					_alloc.deallocate(new_vec, new_cap);
				}
				_vdeallocate();
				_begin = new_vec; _size = new_size; _cap = new_cap;
			}
			
			/* ------------------------------------------------------------- */
			
			template <class Iterator>
			void insert (iterator position, Iterator first, Iterator last,
						typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type * = NULL) {
				_insertrange(position, first, last,
							typename iterator_traits<Iterator>::iterator_category());
			}
			
			/* ------------------------------------------------------------- */
			
			iterator	erase(iterator position) {
				iterator	last(_begin + _size - 1);
				try	{
					_vdestroy(&(*position));
					for (iterator	tmp = position; tmp != last; tmp++) {
						_alloc.construct(&(*tmp), *(tmp + 1));
						_alloc.destroy(&(*(tmp + 1)));
					}
				}
				catch(...) {
					_vdeallocate();
				}
				return position;
			}
			/* ------------------------------------------------------------- */

			iterator	erase(iterator first, iterator last) {
				iterator	end(_begin + _size);
	
				if (first != last) {
					try	{
						for (iterator tmp = first; tmp != last; tmp++)
							_vdestroy(&(*tmp));
						for (iterator tmp = first; last != end; last++, tmp++) {
							_alloc.construct(&(*tmp), *last);
							_alloc.destroy(&(*last));
						}
					}
					catch(...) {
						_vdeallocate();
					}
				}
				return first;
			}
			
			/* ------------------------------------------------------------- */
			
			void push_back (const value_type& val) {
				reserve(_vcapcheck());
				try {
					_alloc.construct(_begin + _size, val);
				}
				catch(...) {
					_vdeallocate();
				}
				_size++;
			}
			
			/* ------------------------------------------------------------- */

			void	pop_back() {
				if (_size != 0) {
					_vdestroy(_begin + _size - 1);
				}
			}

			/* ------------------------------------------------------------- */

			void	resize(size_type n, value_type val = value_type()) {
				if (n < _size) {
					while (_size != n)
						_vdestroy(_begin + _size - 1);
				}
				else if (n > _size) {
					reserve(n);
					for ( ; _size != n; _size++)
						_alloc.construct(_begin + _size, val);
				}
			}
			
			/* ------------------------------------------------------------- */
			
			void	swap( vector& x ) {
				if (*this != x) {
					ft::swap(_begin, x._begin);
					ft::swap(_cap, x._cap);
					ft::swap(_size, x._size);
				}
			}
	
            /* ------------------------------------------------------------- */
            /**
            *      PRIVATE Utils functions
            */
            /* ------------------------------------------------------------- */
		private:
			void	_vallocate(size_type n) {
				if (n > max_size())
					throw std::length_error("ft::vector");
				_begin = _alloc.allocate(n);
				_cap = n;
			}
			
			/* ------------------------------------------------------------- */
			
			void	_vdeallocate() {
				if (_begin != nullptr) {
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = nullptr;
					_cap = 0;
				}
			}
			
			/* ------------------------------------------------------------- */

			size_type	_vcapcheck() {
				size_type	cap = _cap;
	
				if (_cap == 0)
					cap = 1;
				else if (_cap == _size)
					cap = _cap * 2;
				return (cap);
			}

			/* ------------------------------------------------------------- */
			
			pointer	_pallocate(size_type n) {
				if (n > max_size())
					throw std::length_error("ft::vector");
				return _alloc.allocate(n);
			}
			
			/* ------------------------------------------------------------- */

			void	_vdestroy(pointer element) {
				_alloc.destroy(element);
				_size--;
			}

			/* ------------------------------------------------------------- */

			template <class InputIterator>
			void	_assignrange(InputIterator first, InputIterator last, random_access_iterator_tag) {
				size_type	count = ft::distance(first, last);
	
				clear();
				if (count > _cap) {
					if (_cap > 0)
						_alloc.deallocate(_begin, _cap);
					_vallocate(count);
				}
				try {
					for ( ; first != last; first++, _size++)
						_alloc.construct(_begin + _size, *first);
				}
				catch(...) {
					_vdeallocate();
				}
			}
			
			/* ------------------------------------------------------------- */

			template <class InputIterator>
			void	_assignrange(InputIterator first, InputIterator last, input_iterator_tag) {
				clear();
				for ( ; first != last; first++)
					push_back(*first);
			}

			/* ------------------------------------------------------------- */

			template <class Iterator>
			void _insertrange (iterator position, Iterator first, Iterator last, random_access_iterator_tag) {
				pointer		new_vec;
				size_type	new_cap = _vcapcheck();
				size_type	pos = static_cast<size_type>(ft::distance(begin(), position));
				size_type	dist = static_cast<size_type>(ft::distance(first, last));
				size_type	new_size = dist + _size;
				size_type	i = 0;
	
				if (new_size > new_cap)
					new_cap = new_size;
				new_vec = _pallocate(new_cap);
				try {
					for (size_type j = 0; i < new_size; i++, j++) {
						if (i == pos) {
							for (; first != last; first++, i++)
								_alloc.construct(new_vec + i, *first);
						}
						if (j < _size)
							_alloc.construct(new_vec + i, *(_begin + j));
					}
				}
				catch (...) {
					for (; i != 0; i--)
						_alloc.destroy(new_vec + i - 1);
					_alloc.deallocate(new_vec, new_cap);
				}
				_vdeallocate();
				_begin = new_vec; _size = new_size; _cap = new_cap;
			}
			
			/* ------------------------------------------------------------- */
			
			template <class Iterator>
			void _insertrange (iterator position, Iterator first, Iterator last, input_iterator_tag) {
				for (; first != last; ++first, position++)
					position = insert(position, *first);
			}
	};
	
	template <class T, class Alloc> 
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

    /* ------------------------------------------------------------- */
    /**
    *   Relational operators
    */
    /* ------------------------------------------------------------- */
	
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return lhs.size() == rhs.size() &&ft::equal(lhs.begin(), lhs.end(), rhs.begin());		
	}
	
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
		return rhs < lhs;
	}
	
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}
	
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}
}
