/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:53:00 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/20 11:56:42 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICO_COMP_HPP
#define LEXICO_COMP_HPP

#include "integral.hpp"
#include "enable_if.hpp"

// Here we compare two vectors by taking 4 iterators, 1 first and 1 last of each
// We are using enable_if and is_integral so the comparison doesnt work with integrals
// Return true if first range is less than second

namespace ft
{
	template<class It1, class It2>
	bool lexicographical_compare(typename ft::enable_if< !ft::is_integral<It1>::value, It1 >::type first1, It1 last1,
		typename ft::enable_if<!ft::is_integral<It2>::value, It2 >::type first2, It2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	template<class It1, class It2, class Comp>
	bool lexicographical_compare(typename ft::enable_if< !ft::is_integral<It1>::value, It1 >::type first1, It1 last1,
		typename ft::enable_if< !ft::is_integral<It2>::value, It2 >::type first2, It2 last2, Comp cmp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (cmp(*first1, *first2))
				return true;
			if (cmp(*first2, *first1))
				return false;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif
