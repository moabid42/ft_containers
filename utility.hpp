/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:38:51 by moabid            #+#    #+#             */
/*   Updated: 2022/12/08 23:38:54 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	/* ------------------------------------------------------------- */
    /**
    *	@brief  Pair is a data type that can be used to store two values
	*   of different types. The values can be accessed through its public
	*   members first and second.
    */
    /* ------------------------------------------------------------- */
	template <class T1, class T2>
	struct pair {
		public:
			typedef	T1		first_type;
			typedef	T2		second_type;

			/* ------------------------------------------------------------- */
    	    /* --------------------------- MEMBERS ------------------------- */
			first_type		first;
			second_type		second;

			/* ------------------------------------------------------------- */
    	    /* ------------------------ CONSTRUSTORS ----------------------- */

			pair() : first(), second() { }

			template<class U, class V>
			pair( const pair<U,V>& pr ) : first( pr.first ), second( pr.second ) { }

			pair( const first_type& a, const second_type& b ) : first( a ), second( b ) { }
			
			pair& operator=( const pair& pr ) {
				this->first = pr.first;
				this->second = pr.second;
				return(*this);
			}
	};
	
	/* ------------------------------------------------------------- */
    /**
    *	@brief  Creates a pair object with its members first and second
    */
    /* ------------------------------------------------------------- */
	
	template <class T1,class T2>
  	pair<T1,T2> make_pair( T1 x, T2 y )
  	{ return ( pair<T1,T2>(x,y) ); }

	/* ------------------------------------------------------------- */
    /**
    *	@brief  Relational operators for pairs
    */
    /* ------------------------------------------------------------- */
	
	template <class T1, class T2>
	bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }
	
	template <class T1, class T2>
	bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return !(lhs == rhs); }
	
	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
	
	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs < lhs); }
	
	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs < lhs; }
	
	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs < rhs); }
}
