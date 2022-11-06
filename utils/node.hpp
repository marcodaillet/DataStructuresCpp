/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:18:59 by mdaillet          #+#    #+#             */
/*   Updated: 2022/04/20 10:45:33 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

// Define the structure needed for the nodes in the Red_Black_tree

template <class Content>
struct node
{
	public:
		bool is_black; // color
		bool is_nil; // NULL
		Content *content; // value
		node *father; // up
		node *right; // down right
		node *left; // down left

		explicit node(Content *val = 0): is_black(false), is_nil(false), content(val),
			father(0), right(0), left(0) {} // Empty constructor

		node(node const &src): is_black(src.is_black), is_nil(src.is_nil), content(src.content),
			father(src.father), right(src.right), left(src.left) {} // Copy constructor

		node &operator=(const node &other) // Operator =
		{
			this->is_black = other.is_black;
			this->is_nil = other.is_nil;
			this->content = other.content;
			this->father = other.father;
			this->right = other.right;
			this->left = other.left;
			return (*this);
		}

		virtual ~node() {} // Destructor
};

#endif
