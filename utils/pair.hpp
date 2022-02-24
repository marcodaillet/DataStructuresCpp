/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:09:07 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/18 21:58:43 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

// Create associated pairs

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair(): first(first_type()), second(second_type()) {}
			pair(const T1 &rhs, const T2 &lhs): first(rhs), second(lhs) {}
			
			template <class U1, class U2>
			pair(const pair<U1, U2> &p): first(p.first), second(p.second) {}
			pair(const pair &p): first(p.first), second(p.second) {}
			pair &operator=(const pair &other)
			{
				this->first = other->first;
				this->second = other->second;
				return (*this);
			}
	};

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 f, T2 s)
	{
		return pair<T1, T2>(f, s);
	}
	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == lhs.second);
	}
	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}
		template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(lhs.first > lhs.first) && lhs.second < rhs.second));
	}
	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs > rhs));
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs < rhs));
	}
}
	
#endif
