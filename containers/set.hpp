/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:42:20 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 13:48:13 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "../utils/RB_tree.hpp"
#include <iostream>

// A set is a map withou doubles and where all variables are accessed through their value. There is no pair of key and value such as in map.
// Plus, all variables in the set are constant, we can only insert and erase, but never modify

namespace ft
{
	// compare(a, b) will return true if a is before b in the set --> equivalent as (a < b)
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		// Defining the variables we need for set (almost the same as map, but simplified)
		public:
			typedef T							key_type;
			typedef key_type 						value_type;
			typedef Compare 						key_compare;
			typedef key_compare 						value_compare;
			typedef Alloc 							allocator_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference	 	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 			const_pointer;
			typedef	typename allocator_type::difference_type 		difference_type;
			typedef	typename allocator_type::size_type 			size_type;	
			typedef RB_tree<value_type, key_compare, allocator_type>	tree_type;
			typedef RBTree_Iter<const value_type, node<value_type> >	iterator; // Need a const val even for iterator
			typedef RBTree_Iter<const value_type, node<value_type> >	const_iterator; // Same ite but const
			typedef ft::reverse_iterator<iterator> 				reverse_iterator; // Reverse doesnt change
			typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
		private:
			tree_type 							_tree;
		public:
			// ##### CONSTRUCTORS AND DESTRUCTOR
			explicit set (const key_compare& comp = key_compare(), // (1) Construct an empty set on a empty RB_tree
				const allocator_type& alloc = allocator_type()): _tree(tree_type(comp, alloc)) {}

			template <class InputIterator> // (2) construct our RB_tree with a range of iterators 
			set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const
				Alloc& alloc = Alloc()) : _tree(first, last, comp, alloc) {}
			
			set(const set& old): _tree(old._tree) {} // (3) Copy constructor

			// ##### OPERATOR OVERLOAD
			set &operator=(const set& old)
			{
				if (this == &old)
					return (*this);
				this->_tree = old._tree;
				return (*this);
			}

			// ##### GETTERS
			
			allocator_type get_allocator() const
			{
				return (_tree.get_allocator());
			}
			size_type size() const
			{
				return (_tree.size());
			}
			size_type max_size() const
			{
				return (_tree.max_size());
			}
			bool empty() const
			{
				return (_tree.empty());
			}
			value_compare value_comp() const
			{
				return (_tree.value_comp());
			}
			key_compare key_comp() const
			{
				return (value_compare());
			}

			// ##### ITERATORS
			
			iterator begin() 
			{
				return (_tree.begin());
			}
			iterator end()
			{
				return (_tree.end());
			}
			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}
			reverse_iterator rend()
			{
				return (_tree.rend());
			}
			const_iterator begin() const
			{
				return (_tree.begin());
			}
			const_iterator end() const
			{
				return (_tree.end());
			}
			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}
			const_reverse_iterator crend() const
			{
				return (_tree.rend());
			}

			// MEMBER FUNCTIONS

			void clear()
			{
				_tree.clear();
			}
			void swap(set &other)
			{
				_tree.swap(other._tree);
			}
			iterator find(const T &key)
			{
				return (_tree.find(key));
			}
			const_iterator find(const T &key) const
			{
				return (_tree.find(key));
			}
			size_type count(const T &key) const
			{
				return (_tree.count(key));
			}

			// BOUNDS

			iterator lower_bound(const key_type &key)
			{
				return (_tree.lower_bound(key));
			}
			iterator upper_bound(const key_type &key)
			{
				return (_tree.upper_bound(key));
			}
			const_iterator lower_bound(const key_type &key) const
			{
				return (_tree.lower_bound(key));
			}
			const_iterator upper_bound(const key_type &key) const
			{
				return (_tree.upper_bound(key));
			}
			pair<iterator, iterator> equal_range(const key_type &key)
			{
				return (pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			pair<const_iterator, const_iterator> equal_range(const key_type &key) const
			{
				return (pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

			// MODIFIERS

			// single element (1)
			pair<iterator,bool> insert (const value_type& val)
			{
				if (_tree.insert(val).second == false)
					return (ft::make_pair(find(val), false));
				return (ft::make_pair(find(val), true));
			}
			//with hint (2)
			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return (_tree.insert(val).first);
			}
			//range (3)
			template <class InputIterator>
			void insert (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last)
			{
				_tree.insert(first, last);
			}
			// erase pos (1)	
			void erase (iterator position)
			{
				_tree.erase(*position);
			}
			// Value(2)	
			size_type erase (const value_type& key)
			{
				return (_tree.erase(key));
			}
			// range (3)	
 			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					first = find(*first);
					erase(first++);
				}
			}
		// Declare these as friend so we have access to them even outise the scope of the class
		template<class K, class Comp, class Allocator>
		friend bool operator ==(const set<K, Comp, Allocator> &lhs, const set<K, Comp, Allocator> &rhs);
		template<class K, class Comp, class Allocator>
		friend bool operator <(const set<K, Comp, Allocator> &lhs, const set<K, Comp, Allocator> &rhs);
	};
	template<class T, class Comp, class Allocator>
	bool operator ==(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (lhs._tree == rhs._tree);
	}
	template<class T, class Comp, class Allocator>
	bool operator !=(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (!(lhs == rhs));
	}
	template<class T, class Comp, class Allocator>
	bool operator <(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (lhs._tree < rhs._tree);
	}
	template<class T, class Comp, class Allocator>
	bool operator >(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (rhs < lhs);
	}
	template<class T, class Comp, class Allocator>
	bool operator <=(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (!(lhs > rhs));
	}
	template<class T, class Comp, class Allocator>
	bool operator >=(const set<T, Comp, Allocator> &lhs, const set<T, Comp, Allocator> &rhs)
	{
		return (!(lhs < rhs));
	}
}

namespace std
{
	template <class T, class Comp, class Allocator>
	void swap(const ft::set<T, Comp, Allocator> &lhs, const ft::set<T, Comp, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
