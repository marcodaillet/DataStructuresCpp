/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:23:08 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 13:46:16 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <iostream>
#include <vector>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack // LIFO, basically a vector with less funtions :)
	{
		public: // DEFINING WHAT WE NEED
			typedef Container			container_type;
			typedef T 				value_type;
			typedef typename Container::size_type 	size_type;
			typedef value_type 			&reference;
			typedef const value_type 		&const_reference;
		protected:
			container_type 				_container;
		public:
			// ##### CONSTRUCTORS
			explicit stack(const container_type &cont = container_type()): _container(cont) {}
			stack(const stack &other): _container(other._container) {}
			stack &operator=(const stack &old)
			{
				this->_container = old._container;
				return (*this);
			}
			// ##### MEMBER FUNCTIONS
			bool empty() const
			{
				return (this->_container.empty());
			}
			reference top()
			{
				return (this->_container.back());
			}
			const_reference top() const
			{
				return (this->_container.back());
			}
			void push(const T &val)
			{
				this->_container.push_back(val);
			}
			void pop()
			{
				this->_container.pop_back();
			}
			size_type size() const
			{
				return (this->_container.size());
			}

			// ##### RELATIONNAL OPERATORS

			template <class U, class Cont>
			friend bool operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template <class U, class Cont>
			friend bool operator!=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template <class U, class Cont>
			friend bool operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template <class U, class Cont>
			friend bool operator<=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template <class U, class Cont>
			friend bool operator>(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template <class U, class Cont>
			friend bool operator>=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
	};

	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container == rhs._container);
	}
	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container != rhs._container);
	}
	template <class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container < rhs._container);
	}
	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container <= rhs._container);
	}
	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container > rhs._container);
	}
	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs._container >= rhs._container);
	}
}

#endif
