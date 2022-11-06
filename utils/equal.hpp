/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:52:40 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/19 13:47:05 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

// Simply compare 2 ranges of it without more complications and return true if
// they are the same

namespace ft
{
	template <class It1, class It2>
	bool equal ( It1 first1, It1 last1, It2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	template <class It1, class It2, class Predicate>
	bool equal (It1 first1, It1 last1, It2 first2, Predicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
}

#endif
