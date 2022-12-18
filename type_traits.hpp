/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:27:48 by moabid            #+#    #+#             */
/*   Updated: 2022/12/08 23:50:58 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	/* ------------------------------------------------------------- */
    /**
    *   Enable_if is a type trait that can be used to enable
	* 	or disable a function template based on certain conditions.
    */
    /* ------------------------------------------------------------- */
	
	template<bool B, class T = void>
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	
	/* ------------------------------------------------------------- */
    /**
    *   Std::is_integral type trait is used to determine
	* 	whether a given type is an integral type
    */
    /* ------------------------------------------------------------- */
	
	template <class T, T val>
	struct integral_constant {
		typedef integral_constant<T, val>	type;
		typedef T							value_type;

		static const T						value = val;
		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T>
	struct is_integral : public false_type { };

	template <>
	struct is_integral<bool> : public true_type { };
	template <>
	struct is_integral<const bool> : public true_type { };
	template <>
	struct is_integral<volatile bool> : public true_type { };
	template <>
	struct is_integral<const volatile bool> : public true_type { };

	template <>
	struct is_integral<char> : public true_type { };
	template <>
	struct is_integral<const char> : public true_type { };
	template <>
	struct is_integral<volatile char> : public true_type { };
	template <>
	struct is_integral<const volatile char> : public true_type { };

	template <>
	struct is_integral<wchar_t> : public true_type { };
	template <>
	struct is_integral<const wchar_t> : public true_type { };
	template <>
	struct is_integral<volatile wchar_t> : public true_type { };
	template <>
	struct is_integral<const volatile wchar_t> : public true_type { };

	template <>
	struct is_integral<signed char> : public true_type { };
	template <>
	struct is_integral<const signed char> : public true_type { };
	template <>
	struct is_integral<volatile signed char> : public true_type { };
	template <>
	struct is_integral<const volatile signed char> : public true_type { };

	template <>
	struct is_integral<short int> : public true_type { };
	template <>
	struct is_integral<const short int> : public true_type { };
	template <>
	struct is_integral<volatile short int> : public true_type { };
	template <>
	struct is_integral<const volatile short int> : public true_type { };

	template <>
	struct is_integral<int> : public true_type { };
	template <>
	struct is_integral<const int> : public true_type { };
	template <>
	struct is_integral<volatile int> : public true_type { };
	template <>
	struct is_integral<const volatile int> : public true_type { };

	template <>
	struct is_integral<long int> : public true_type { };
	template <>
	struct is_integral<const long int> : public true_type { };
	template <>
	struct is_integral<volatile long int> : public true_type { };
	template <>
	struct is_integral<const volatile long int> : public true_type { };

	template <>
	struct is_integral<long long int> : public true_type { };
	template <>
	struct is_integral<const long long int> : public true_type { };
	template <>
	struct is_integral<volatile long long int> : public true_type { };
	template <>
	struct is_integral<const volatile long long int> : public true_type { };

	template <>
	struct is_integral<unsigned char> : public true_type { };
	template <>
	struct is_integral<const unsigned char> : public true_type { };
	template <>
	struct is_integral<volatile unsigned char> : public true_type { };
	template <>
	struct is_integral<const volatile unsigned char> : public true_type { };

	template <>
	struct is_integral<unsigned short int> : public true_type { };
	template <>
	struct is_integral<const unsigned short int> : public true_type { };
	template <>
	struct is_integral<volatile unsigned short int> : public true_type { };
	template <>
	struct is_integral<const volatile unsigned short int> : public true_type { };

	template <>
	struct is_integral<unsigned int> : public true_type { };
	template <>
	struct is_integral<const unsigned int> : public true_type { };
	template <>
	struct is_integral<volatile unsigned int> : public true_type { };
	template <>
	struct is_integral<const volatile unsigned int> : public true_type { };

	template <>
	struct is_integral<unsigned long int> : public true_type { };
	template <>
	struct is_integral<const unsigned long int> : public true_type { };
	template <>
	struct is_integral<unsigned volatile long int> : public true_type { };
	template <>
	struct is_integral<const volatile unsigned long int> : public true_type { };

	template <>
	struct is_integral<unsigned long long int> : public true_type { };
	template <>
	struct is_integral<const unsigned long long int> : public true_type { };
	template <>
	struct is_integral<unsigned volatile long long int> : public true_type { };
	template <>
	struct is_integral<const volatile unsigned long long int> : public true_type { };
}
