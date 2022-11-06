/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_const.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:57:00 by mdaillet          #+#    #+#             */
/*   Updated: 2022/01/10 13:00:46 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_CONST_HPP
#define REMOVE_CONST_HPP

namespace ft
{
	template <class T>
	struct remove_const
	{
		typedef T type;
	};

	template <class T>
	struct remove_const <const T>
	{
		typedef T type;
	};
}

#endif
