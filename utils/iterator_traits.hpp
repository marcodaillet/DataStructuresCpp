/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:01:00 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 11:37:07 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// Define all iterators properties for it, *it and const it*
#include <cstddef>

namespace ft
{
	// Empty structs to have the different tags
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag : 		public input_iterator_tag {};
	struct	bidirectional_iterator_tag :	public forward_iterator_tag {};
	struct	random_access_iterator_tag : 	public bidirectional_iterator_tag {};
	
	template <class Iterator>
	class iterator_traits // Iterator traits if we pass another iterator
	{
		public:
			typedef typename Iterator::difference_type	difference_type;
			typedef typename Iterator::value_type		value_type;
			typedef typename Iterator::pointer		pointer;
			typedef typename Iterator::reference		reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	template <class T> // Iterator traits
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t				difference_type;
			typedef T					value_type;
			typedef T*					pointer;
			typedef T&					reference;
			typedef random_access_iterator_tag		iterator_category;
	};
	template <class T> // Iterator traits where its const
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t				difference_type;
			typedef const T					value_type;
			typedef const T*				pointer;
			typedef const T&				reference;
			typedef random_access_iterator_tag		iterator_category;
	};
	// Struct Ite to initialize an iterator with only its value_type and its iterator type
	template <class T, class Type, class Dist = std::ptrdiff_t, class Ptr = T*, class Ref = T&>
	struct iterator
	{
		typedef T						value_type;
		typedef Dist						difference_type;
		typedef Ptr						pointer;
		typedef Ref						reference;
		typedef Type						iterator_category;
	};

}

#endif
