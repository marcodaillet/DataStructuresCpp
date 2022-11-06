/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:03:00 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 11:32:13 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

// Implementation of the reverse iterator, which takes another iterator as template,
// but modifys the behavior so its all inverted.

#include "../utils/iterator_traits.hpp"

namespace ft
{
	template<typename It>
	class reverse_iterator
	{
		public:
			typedef It							iterator_type;
			typedef typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::pointer		pointer;
			typedef typename ft::iterator_traits<It>::reference		reference;
			typedef typename ft::iterator_traits<It>::difference_type	difference_type;
			typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
		private:
			iterator_type 							_it;
		public:
			// ##### CONSTRUCTORS
			reverse_iterator(): _it() {}
			explicit reverse_iterator(iterator_type x): _it(x) {}
			template <class U>
			reverse_iterator(const reverse_iterator<U>& old): _it(old.base()) {}
			// ##### OPERATOR OVERLOAD
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& old )
			{
				this->_it = old.base();
				return *this;
			}
			// ##### MEMBER FUNCTIONS
			iterator_type base() const { return _it; }
			reference operator*() const
			{
				iterator_type temp = _it;
				return *--temp;
			}
			pointer operator->() const
			{
				iterator_type temp = _it;
				return &(*(--temp));
			}
			reference operator[]( difference_type n ) const
			{
				return _it.base()[ -n - 1];
			}
			reverse_iterator& operator++()
			{
				_it--;
				return *this;
			}
			reverse_iterator& operator--()
			{
				_it++;
				return *this;
			}
			reverse_iterator operator++( int )
			{
				reverse_iterator<iterator_type> temp = *this;
				_it--;
				return temp;
			}
			reverse_iterator operator--( int )
			{
				reverse_iterator<iterator_type> temp = *this;
				_it++;
				return temp;
			}
			reverse_iterator operator+( difference_type n ) const
			{
				return reverse_iterator(_it - n);
			}
			reverse_iterator operator-( difference_type n ) const
			{
				return reverse_iterator(_it + n);
			}
			reverse_iterator& operator+=( difference_type n )
			{
				_it -= n;
				return *this;
			}
			reverse_iterator& operator-=( difference_type n )
			{
				_it += n;
				return *this;
			}
			difference_type operator-(reverse_iterator const &r)
			{
			return (r.base() - this->base());
			}
	};

	// ##### RELATIONNAL OPERATORS
	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() == rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
	return lhs.base() != rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() < rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() > rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() <= rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return lhs.base() >= rhs.base();
	}
	template< class Iter >
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return it + n;
	}
}

#endif
