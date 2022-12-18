/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:44 by moabid            #+#    #+#             */
/*   Updated: 2022/12/14 15:41:11 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	/* ------------------------------------------------------------- */
	/**
	*   @brief  min Returns the smaller of a and b.
	*/
	/* ------------------------------------------------------------- */

	template <class InputIterator1, class InputIterator2> 
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!pred(*first1, *first2))
				return false;
		}
		return true;
	}

    /* ------------------------------------------------------------- */
    /**
    *   @brief  lexicographical_compare Compares the elements in the range [first1,last1)
	*   with those in the range [first2,last2) in lexicographical order.
    */
    /* ------------------------------------------------------------- */

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2) 
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	
	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class T> 
	void	swap(T& x, T& y) {
		T z = x;

		x = y;
		y = z;
	}
}
