/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:01:00 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/21 18:08:56 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// Define all iterators properties for it, *it and const it*

namespace ft
{
	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef typename std::random_access_iterator_tag	iterator_category;
	};
	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef const T			value_type;
			typedef const T*		pointer;
			typedef const T&		reference;
			typedef typename std::random_access_iterator_tag	iterator_category;
	};
}

#endif
