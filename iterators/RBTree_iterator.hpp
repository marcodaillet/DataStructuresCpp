/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:02:20 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/26 11:40:19 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "../utils/remove_const.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/node.hpp"

template <class T, class Node>
class RBTree_Iter : public ft::iterator<T, ft::bidirectional_iterator_tag> // Inhert from the struct iterator with the empty tag bidirect
{
	public: // Defining what we need to move inside a BST
		typedef T value_type;
		typedef typename ft::iterator<value_type, ft::bidirectional_iterator_tag>::difference_type	difference_type;
		typedef typename ft::iterator<value_type, ft::bidirectional_iterator_tag>::pointer		pointer;
		typedef typename ft::iterator<value_type, ft::bidirectional_iterator_tag>::reference		reference;
		typedef typename ft::iterator<value_type, ft::bidirectional_iterator_tag>::iterator_category	iterator_category;
		typedef Node 											node_type;
		typedef Node* 											node_pointer;
	private:
		node_pointer 											_node;
		node_pointer tree_max(node_pointer n) const // Right is the biggest branch
		{
			while (!n->right->is_nil)
				n = n->right;
			return (n);
		}
		node_pointer tree_min(node_pointer n) const // Left is the lowest branch
		{
			if (n->left)
				while (n->left != NULL && !n->left->is_nil)
					n = n->left;
			return (n);
		}
	public:
		// ##### CONSTRUCTOR
		RBTree_Iter() {}
		RBTree_Iter(void *node): _node(static_cast<node_pointer>(node)) {}
		RBTree_Iter(const RBTree_Iter<T, Node> &other)
		{
			*this = other;
		}
		RBTree_Iter &operator=(const RBTree_Iter<T, Node> &other)
		{
			this->_node = other.node();
			return (*this);
		}
		// ##### MEMBER FUNCTIONS
		operator RBTree_Iter<const T, Node>(void) // Need to cast everytime we call an operator so int --> const int. Needs this to be able to operate const it with normal it
		{
			return RBTree_Iter<const T, Node>(_node);
		}
		reference operator*(void) const // Access content
		{
			return *(_node->content);
		}
		pointer operator->(void) const // Access content
		{
			return &(operator*());
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
			RBTree_Iter<T, Node> tmp = *this;
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
			RBTree_Iter<T, Node> tmp = *this;
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

template <class T, class Node>
bool operator==(const RBTree_Iter<T, Node> &lhs, const RBTree_Iter<T, Node> &rhs)
{
	return (lhs.node() == rhs.node());
}

template <class T1, class T2, class Node>
bool operator==(const RBTree_Iter<T1, Node> &lhs, const RBTree_Iter<T2, Node> &rhs)
{
	return (lhs.node() == rhs.node());
}

template <class T, class Node>
bool operator!=(const RBTree_Iter<T, Node> &lhs, const RBTree_Iter<T, Node> &rhs)
{
	return (lhs.node() != rhs.node());
}

template <class T1, class T2, class Node>
bool operator!=(const RBTree_Iter<T1, Node> &lhs, const RBTree_Iter<T2, Node> &rhs)
{
	return (lhs.node() != rhs.node());
}

#endif
