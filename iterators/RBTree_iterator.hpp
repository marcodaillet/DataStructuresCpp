/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:02:20 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/22 13:11:16 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "../utils/remove_const.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/node.hpp"

template <typename T>
class RBTree_Iter
{
	public: // Defining what we need to move inside a BST
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type value_type;
		typedef typename ft::iterator_traits<T*>::reference reference;
		typedef typename ft::iterator_traits<T*>::pointer pointer;
		typedef typename ft::iterator_traits<T*>::difference_type difference_type;
		typedef node<typename ft::remove_const<value_type>::type> *node_pointer;
	private:
		node_pointer _node;
		node_pointer tree_max(node_pointer n) const // Right is the biggest branch
		{
			while (!n->right->is_nil)
				n = n->right;
			return (n);
		}
		node_pointer tree_min(node_pointer n) const // Left is the lowest branch
		{
			while (n->left != NULL && !n->left->is_nil)
				n = n->left;
			return (n);
		}
	public:
		// ##### CONSTRUCTOR
		RBTree_Iter() {}
		RBTree_Iter(void *node): _node(static_cast<node_pointer>(node)) {}
		RBTree_Iter(const RBTree_Iter<typename ft::remove_const<value_type>::type > &other)
		{
			*this = other;
		}
		RBTree_Iter &operator=(const RBTree_Iter <typename ft::remove_const<value_type>::type > &other)
		{
			this->_node = other.node();
			return (*this);
		}

		// ##### MEMBER FUNCTIONS
		reference operator*() const // Access content pointer
		{
			return *(_node->content);
		}
		pointer operator->() const // Access content
		{
			return (_node->content);
		}
		RBTree_Iter &operator++() // We iterate through a red_black_tree in InOrderTraversal (LEFT-ROOT-RIGHT)
		{
			if (_node->right && !_node->right->is_nil)
				_node = tree_min(_node->right);
			else
			{
				node_pointer y = _node->father;
				while (y != NULL && _node == y->right)
				{
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return (*this);
		}
		RBTree_Iter operator++(int) // We iterate through a red_black_tree in InOrderTraversal (LEFT-ROOT-RIGHT)
		{
			RBTree_Iter<value_type> tmp = *this;
			if (_node->right && !_node->right->is_nil)
				_node = tree_min(_node->right);
			else
			{
				node_pointer y = _node->father;
				while (y != NULL && _node == y->right)
				{
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return (tmp);
		}
		RBTree_Iter &operator--() // We iterate through a red_black_tree in InOrderTraversal (LEFT-ROOT-RIGHT)
		{
			if (_node->left && !_node->left->is_nil)
				_node = tree_max(_node->left);
			else
			{
				node_pointer y = _node->father;
				while (y != NULL && _node == y->left)
				{
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return (*this);
		}
		RBTree_Iter operator--(int) // We iterate through a red_black_tree in InOrderTraversal (LEFT-ROOT-RIGHT)
		{
			RBTree_Iter<value_type> tmp = *this;
			if (_node->left && !_node->left->is_nil)
				_node = tree_max(_node->left);
			else
			{
				node_pointer y = _node->father;
				while (y != NULL && _node == y->left)
				{
					_node = y;
					y = y->father;
				}
				_node = y;
			}
			return (tmp);
		}
		node_pointer node() const
		{
			return (_node);
		}
};

template <typename A, typename B>
bool operator==(const RBTree_Iter<A> &lhs, const RBTree_Iter<B> &rhs)
{
	return (lhs.node() == rhs.node());
}

template <typename A, typename B>
bool operator!=(const RBTree_Iter<A> &lhs, const RBTree_Iter<B> &rhs)
{
	return (lhs.node() != rhs.node());
}

#endif
