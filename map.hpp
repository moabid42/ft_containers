/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 00:27:08 by moabid            #+#    #+#             */
/*   Updated: 2022/12/13 23:25:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdexcept>
# include "iterators/tree.hpp"

namespace ft
{
	/**
    * ------------------------------------------------------------- *
    * ------------------------ FT::MAP ---------------------------- *
    *
    * - Coplien form:
    * (constructor):        Construct map
    * (destructor):         Destruct map
    * operator=:            Assign map
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
    * empty:                Test whether map is empty
    *
    * - Element access:
    * operator[]:           Access element
    * at:                   Access element
    *
    * - Modifiers:
    * assign:               Assign map content
    * insert:               Insert elements
    * erase:                Erase elements
    * swap:                 Swap content
    * clear:                Clear content
    *
    * - Non-member function overloads:
    * relational operators: Relational operators for map
    * swap:                 Exchange contents of two maps
    * ------------------------------------------------------------- *
    */
   
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			/* ------------------------------------------------------------- */
    	    /* -------------------------- ALIASES -------------------------- */
			typedef	Key															key_type;
			typedef	T															mapped_type;
			typedef	Compare														key_compare;
			typedef	typename ft::pair<const Key, T>								value_type;
			typedef	Allocator													allocator_type;
			typedef	typename allocator_type::reference							reference;
			typedef	typename allocator_type::const_reference					const_reference;
			typedef	typename allocator_type::pointer							pointer;
			typedef	typename allocator_type::const_pointer						const_pointer;
			typedef	typename allocator_type::size_type							size_type;
			typedef typename allocator_type::difference_type					difference_type;
		
			class value_compare
			{
				private:
					friend class map;
				protected:
					Compare				comp;
					value_compare	(Compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
			
					bool	operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};
		
			typedef	ft::tree<value_type, value_compare, allocator_type>		tree;
			typedef	typename tree::iterator									iterator;
			typedef	typename tree::const_iterator							const_iterator;
			typedef	typename tree::reverse_iterator							reverse_iterator;
			typedef	typename tree::const_reverse_iterator					const_reverse_iterator;
		
		private:
    	    /* ------------------------------------------------------------- */
    	    /* ------------------------- ATTRIBUTES ------------------------ */
			key_compare				_comp;
			allocator_type			_alloc;
			tree					_tree;
			
		public:
			/* ------------------------------------------------------------- */
    	    /* ---------------------------- BODY --------------------------- */

 			/* ------------------------------------------------------------- */
            /**
            *   Default constructor, creates a map with a size of 0.
            *
            */
            /* ------------------------------------------------------------- */
			
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
						: _comp(comp), _alloc(alloc), _tree(value_compare(comp), alloc) { }
			
			/* ------------------------------------------------------------- */
            /**
            *   Range constructor, creates a map with a size equal to the range between two
            *   iterators and copy the values of this range to the new elements created.
            */
            /* ------------------------------------------------------------- */
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree(value_compare(comp), alloc) {
				insert(first, last);
			}
			
            /* ------------------------------------------------------------- */
            /**
            *   Copy constructor, creates a map with the same size and copy/construct
            *   all x values to the new area allocated.
            *   
            *   @param x        The map that will be copied.
            */
            /* ------------------------------------------------------------- */
			
			map (const map& x) : _comp(x.key_comp()), _alloc(x.get_allocator()), _tree(x._tree) { }

            /* ------------------------------------------------------------- */
            /**
            *   Destructor, destroys all the elements and free the allocated memory.
            */
            /* ------------------------------------------------------------- */

			~map () { }

            /* ------------------------------------------------------------- */
            /**
            *   Assigns a map to this vecto using the assign method.
            *   
            *   @param x        The map that will be assigned.
            */
            /* ------------------------------------------------------------- */

			map& operator= (const map& x) {
				_alloc = x.get_allocator();
				_comp = x.key_comp();
				_tree = x._tree;
				return *this;
			}

            /* ------------------------------------------------------------- */
            /**
            *   Allocator getter, returns the allocator used by the map.
            */
            /* ------------------------------------------------------------- */

			allocator_type get_allocator() const { return _alloc; }
		
            /* ------------------------------------------------------------- */
            /**
            *   Element access, returns a reference to the element at the given position.
            *   @param pos     The position of the element.
            */
            /* ------------------------------------------------------------- */
			
			mapped_type& at (const key_type& k) {
				Node<value_type>* tmp = _tree.find(ft::make_pair(k, mapped_type()));
				if (tmp == nullptr)
					throw std::out_of_range("ft::map::at");
				return (tmp->value.second);
			}

            /* ------------------------------------------------------------- */
			
			const mapped_type& at (const key_type& k) const {
				Node<value_type>* tmp = _tree.find(ft::make_pair(k, mapped_type()));
				if (tmp == nullptr)
					throw std::out_of_range("ft::map::at");
				return (tmp->value.second);
			}

			/* ------------------------------------------------------------- */
			// "[]" - The same behavior as 'at' operator function, but no bounds checking is performed
            /* ------------------------------------------------------------- */		

			mapped_type& operator[] (const key_type& k) {
				return (insert(ft::make_pair(k, mapped_type())).first)->second;
			}

            /* ------------------------------------------------------------- */
            /**
            *   Iterators, returns an iterator to an element of the map.
            */
            /* ------------------------------------------------------------- */

			iterator begin() {
				return _tree.begin();
			}

			/* ------------------------------------------------------------- */

			const_iterator begin() const {
				return _tree.begin();
			}

			/* ------------------------------------------------------------- */

			iterator end() {
				return _tree.end();
			}

			/* ------------------------------------------------------------- */
			
			const_iterator end() const {
				return _tree.end();
			}

			/* ------------------------------------------------------------- */

			reverse_iterator rbegin() {
				return reverse_iterator(_tree.end());
			}

			/* ------------------------------------------------------------- */
			
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(_tree.end());
			}

			/* ------------------------------------------------------------- */
			
			reverse_iterator rend() {
				return reverse_iterator(_tree.begin());
			}

			/* ------------------------------------------------------------- */
			
			const_reverse_iterator rend() const {
				return const_reverse_iterator(_tree.begin());
			}

            /* ------------------------------------------------------------- */
            /**
            *   Capacity, returns the size of the map.
            */
            /* ------------------------------------------------------------- */
			
			bool empty() const { return _tree.empty(); }
			
			/* ------------------------------------------------------------- */
			
			size_type size() const { return _tree.size(); }
			
			/* ------------------------------------------------------------- */
			
			size_type max_size() const { return _tree.max_size(); }

			/* ------------------------------------------------------------- */
			/**
			*   Modifiers, modifies the map.
			*/
			/* ------------------------------------------------------------- */

			void clear() { _tree.clear(); }
			
			/* ------------------------------------------------------------- */

			ft::pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); }
			
			/* ------------------------------------------------------------- */
			
			iterator insert (iterator position, const value_type& val) {
				(void)position;
				return _tree.insert(val).first;
			}
			
			/* ------------------------------------------------------------- */
			
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {
				for (; first != last; first++)
					insert(*first);
			}
			
			/* ------------------------------------------------------------- */

			void erase (iterator position) { _tree.erase(position.base()); }

			/* ------------------------------------------------------------- */
			
			size_type erase (const key_type& k) { return _tree.erase(ft::make_pair(k, mapped_type())); }
			
			/* ------------------------------------------------------------- */
			
			void erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}
			
			/* ------------------------------------------------------------- */
			
			void swap (map& x) {
				_tree.swap(x._tree);
			}
   			
			/* ------------------------------------------------------------- */
   			/**
   			*   Lookup operators
   			*/
   			/* ------------------------------------------------------------- */
			
			size_type count (const key_type& k) const {
				return _tree.count(ft::make_pair(k, mapped_type()));
			}
			
			/* ------------------------------------------------------------- */

			iterator find (const key_type& k) { return iterator(_tree.iter_find(ft::make_pair(k, mapped_type()))); }
			const_iterator find (const key_type& k) const { return const_iterator(_tree.iter_find(ft::make_pair(k, mapped_type()))); }
			
			/* ------------------------------------------------------------- */	

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			
			/* ------------------------------------------------------------- */
			
			pair<iterator,iterator> equal_range (const key_type& k) {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			
			/* ------------------------------------------------------------- */

			iterator lower_bound (const key_type& k) { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
			const_iterator lower_bound (const key_type& k) const { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
			
			/* ------------------------------------------------------------- */
			
			iterator upper_bound (const key_type& k) { return _tree.upper_bound(ft::make_pair(k, mapped_type())); }
			const_iterator upper_bound (const key_type& k) const { return _tree.upper_bound(ft::make_pair(k, mapped_type())); }

			/* ------------------------------------------------------------- */

			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return value_compare(_comp); }
	};

    /* ------------------------------------------------------------- */
    /**
    *   Relational operators
    */
    /* ------------------------------------------------------------- */
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	
	template <class Key, class T, class Compare, class Alloc> 
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare (lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc> 
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return 	!(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc> 
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return 	!(lhs < rhs);
	}
	
	/* ------------------------------------------------------------- */
	/**
	*   Swap
	*/
	/* ------------------------------------------------------------- */
	
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs) { lhs.swap(rhs); }
}
