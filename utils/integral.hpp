/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:52:48 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/19 13:15:07 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGRAL_HPP
#define INTEGRAL_HPP

#include <uchar.h>

// Here we create a structure to know if a type is integral or not (integral --> int, short, long, char and their extensions)
// We go a general template to say that by default the tab passed is not integral
// Then we do what we call a template specialization
// Its when you want to define a behavior for a specific parameter (here all of our integrals
// The template <> has to be put before the specialization


namespace ft
{
	template<class T, bool v>
	struct integral_const
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_const type;
		operator value_type() const { return value; }
	};
	template <class T>
	struct is_integral: public ft::integral_const<T, false> {};
	template <>
	struct is_integral<short> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<unsigned short> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<int> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<unsigned int> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<long> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<unsigned long> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<long long> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<unsigned long long> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<bool> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<char> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<signed char> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<unsigned char> : public ft::integral_const<bool, true> {};
	template <>
	struct is_integral<wchar_t>	: public ft::integral_const<bool, true> {};
	//template <>
	//struct is_integral<char16_t> : public ft::integral_const<bool, true> {};
}

#endif
