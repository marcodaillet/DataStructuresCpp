/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:15:02 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 11:24:24 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

// Implementation of the random_access_iterator, which is the base iterator for the vector container

#include "../utils/iterator_traits.hpp"
#include "../utils/remove_const.hpp"

template<typename T>
class random_access_iterator
{
	public:
		typedef	typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef	typename ft::iterator_traits<T*>::pointer		pointer;
		typedef	typename ft::iterator_traits<T*>::reference		reference;
		typedef	typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef pointer							iterator_type;
		typedef	ft::random_access_iterator_tag 				iterator_category;
	private:
		pointer _ptr;
	public:
		// #### CONSTRUCTORS DESTRUCTOR
		random_access_iterator() : _ptr() {}
		random_access_iterator(pointer a) : _ptr(a) {}
		random_access_iterator(const random_access_iterator<typename ft::remove_const<value_type>::type > &src) :
			_ptr(&(*src)) {}
		virtual ~random_access_iterator() {}
		random_access_iterator<value_type> & operator=(random_access_iterator<typename
				ft::remove_const<value_type>::type > const & src)
		{
			_ptr = &(*src);
			return *this;
		}
		// #### MEMBER FUNCTION
		pointer base() const
		{
			return (_ptr);
		}
		operator random_access_iterator<const T>(void) // Empty overloading to be able to operate on const it and not const it
                { // Its actually a casting 
                        return (random_access_iterator<const T>(_ptr));
                }
		random_access_iterator & operator++() // PostIncrement
		{
			++_ptr;
			return *this;
		}
		random_access_iterator operator++(int) // PreIncrement
		{
			random_access_iterator tmp(*this);
			++_ptr;
			return tmp;
		}
		random_access_iterator & operator--() // PostDecrement
		{
			--_ptr;
			return *this;
		}
		random_access_iterator  operator--(int) // PreDecrement
		{
			random_access_iterator tmp = *this;
			--_ptr;
			return tmp;
		}
		random_access_iterator operator+(const difference_type & a) const
		{
			return _ptr + a;
		}
		random_access_iterator operator-(const difference_type & a) const
		{
			return _ptr - a;
		}
		random_access_iterator & operator+=(const difference_type & a)
		{
			_ptr += a;
			return (*this);
		}
		random_access_iterator & operator-=(const difference_type & a)
		{
			_ptr -= a;
			return (*this);
		}
		pointer operator->() const
		{
			return _ptr;
		}
		reference operator*() const
		{
			return *_ptr;
		}
		reference operator[](difference_type n) const
		{
			return *(_ptr + n);
		}
};

// #### RELATIONAL OPERATOR
	template<typename A, typename B>
bool operator==(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) == &(*rhs);
}
	template<typename A, typename B>
bool operator!=(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) != &(*rhs);
}
	template<typename A, typename B>
bool operator>(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) > &(*rhs);
}
	template<typename A, typename B>
bool operator<(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) < &(*rhs);
}
	template<typename A, typename B>
bool operator<=(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) <= &(*rhs);
}
	template<typename A, typename B>
bool operator>=(const random_access_iterator<A> & lhs, const random_access_iterator<B> & rhs)
{
	return &(*lhs) >= &(*rhs);
}

// #### NON-MEMBER FUNCTION
	template<typename A, typename B>
typename random_access_iterator<A>::difference_type operator-(const random_access_iterator<A> & lhs,
		const random_access_iterator<B> & rhs)
{
	return (&(*lhs) - &(*rhs));
}
	template<typename A, typename B>
typename random_access_iterator<A>::difference_type operator+(const random_access_iterator<A> & lhs,
		const random_access_iterator<B> & rhs)
{
	return &(*lhs) + &(*rhs);
}
	template<typename L>
random_access_iterator<L> operator +(const typename random_access_iterator<L>::difference_type & a,
		random_access_iterator<L> & iter)
{
	return	(iter + a);
}
	template<typename L>
random_access_iterator<L> operator -(const typename random_access_iterator<L>::difference_type & a,
		const random_access_iterator<L> & iter)
{
	return	(iter - a);
}

#endif
