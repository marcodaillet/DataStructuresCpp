/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:52:34 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/19 13:46:46 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

// Enabe_if struct contains the type T if the boolean passed is true. If not, its empty.
// Its a way of allowing smthg depending on the condition

namespace ft
{
    template<bool B, class T = void>
	struct enable_if {};

    template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif
