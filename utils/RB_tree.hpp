/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:06:31 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/24 13:48:58 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "enable_if.hpp"
#include "equal.hpp"
#include "integral.hpp"
#include "iterator_traits.hpp"
#include "lexico_comp.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/RBTree_iterator.hpp"

template <class Content, class Comp = std::less<Content>, class Allocator = std::allocator<Content> >
class RB_tree
{
	public: // Defining the variables type we need to creat a RB_tree
		typedef Allocator allocator_type;
		typedef Content value_type;
		typedef Comp value_compare;
		typedef typename allocator_type::pointer content_pointer;	
		typedef typename allocator_type::const_pointer const_content_pointer;
		typedef typename Allocator::template rebind<node<Content> >::other node_allocator;
		typedef typename node_allocator::pointer node_pointer;
		typedef RBTree_Iter<Content> iterator;
		typedef RBTree_Iter<const Content> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
	private: // Defining the variables we need to create a RB_tree
		node_pointer _root; // The top node
		node_pointer _nil; // Null nodes
		node_pointer _header;
		value_compare _cmp;
		size_type _size; // Size of the tree
		node_allocator _node_alloc; // allocator tool to allocate and deallocate memory for the node
		allocator_type _con_alloc; // allocator tool to allocate and deallocate memory for the content

		// ##### INSIDE TREE FUNCTIONS

		bool is_nil(node_pointer node) const
		{
			return (node == _nil || node == _header);
		}
		node_pointer tree_min(node_pointer node) const // Goes to the bottom left to find smallest value on the last row
		{
			while (node->left != _nil)
				node = node->left;
			return (node);
		}
		node_pointer tree_max(node_pointer node) const // Goes to the bottom right to find biggest value
		{
			while (!is_nil(node->right))
			{
				node = node->right;
			}
			return (node);
		}
		void free_node(node_pointer node)
		{
			_con_alloc.destroy(node->content); // Empty node content
			_con_alloc.deallocate(node->content, 1); // Deallocate it
			_node_alloc.deallocate(node, 1); // Deallocate the node itself (that is empty because no content already)
		}
		void clear_node(node_pointer node) // Clears a node and all its subtrees
		{
			if (node && !is_nil(node))
			{
				clear_node(node->right);	
				clear_node(node->left);
				free_node(node);
			}
		}
		content_pointer create_content(const value_type &content)
		{
			content_pointer n_content = _con_alloc.allocate(1);
			_con_alloc.construct(n_content, content);
			return (n_content);
		}
		void transplant(node_pointer first, node_pointer second) // Replace first node and its link by the second
		{
			if (first == _root)
				_root = second;
			else if (first == first->father->left)
				first->father->left = second; // Needs to go one row upper to keep links altogether
			else
				first->father->right = second; // Needs to go one row upper to keep links altogether
			second->father = first->father; // Ascending link
		}
		void left_rotate(node_pointer x) // So, the target x become the left child of its right child
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (!(is_nil(y->left)))
				y->left->father = x;
			y->father = x->father;
			if (x->father == NULL)
				_root = y;
			else if (x == x->father->left)
				x->father->left = y;
			else
				x->father->right = y;
			y->left = x;
			x->father = y;
		}
		void right_rotate(node_pointer x) // So, the target x become the right child of its left child
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (!(is_nil(y->right)))
				y->right->father = x;
			y->father = x->father;
			if (x->father == NULL)
				_root = y;
			else if (x == x->father->left)
				x->father->left = y;
			else
				x->father->right = y;
			y->right = x;
			x->father = y;
		}
		node_pointer insert_node2(node_pointer root, node_pointer new_node) // Recursive wau of inserting a node to the right place
		{
			if (_cmp(*new_node->content, *root->content)) // If val in new is less than root we go to the left branch
			{
				if (!is_nil(root->left)) // If left node isnt free, we recursively call the function so it ges to the right place
					return (insert_node2(root->left, new_node));
				root->left = new_node;
			}
			else // Otherwise, we go to the right branch
			{
				if (!is_nil(root->right)) // If left node isnt free, we recursively call the function so it ges to the right place
					return (insert_node2(root->right, new_node));
				root->right = new_node;
			}
			new_node->father = root;
			return (new_node);
		}
		node_pointer insert_node1(node_pointer new_node, node_pointer where) // Just splitting the insert utils
		{
			if (_root == _header)
				_root = new_node;
			else
				insert_node2(where, new_node);
			return (new_node);
		}
		void insert_correct(node_pointer curr) // After inserting a new node, we need to repair the tree properties
		{ // Watch this video if you forgot --> https://www.youtube.com/watch?v=5IBxA-bZZH8
			if (curr != _root && curr->father != _root)
			{
				while (curr != _root && !curr->father->is_black)
				{
					if (curr->father == curr->father->father->left) // If father is a left child
					{
						node_pointer uncle = curr->father->father->right;
						if (!uncle->is_black) // If uncle is red
						{
							curr->father->is_black = true;
							uncle->is_black = true;
							curr->father->father->is_black = false;
							curr = curr->father->father;
						}
						else // If uncle is black
						{
							if (curr == curr->father->right)
							{
								curr = curr->father;
								left_rotate(curr);
							}
							curr->father->is_black = true;
							curr->father->father->is_black = false;
							right_rotate(curr->father->father);
						}
					}
					else // If father is a right child
					{
						node_pointer uncle = curr->father->father->left; 	
                		if (!uncle->is_black) // If uncle is red
                		{
                			curr->father->is_black = true;
                			uncle->is_black = true;
                			curr->father->father->is_black = false;
                			curr = curr->father->father;
                		}
                		else // If uncle is black
                		{
                			if (curr == curr->father->left)
                			{
                				curr = curr->father;
                				right_rotate(curr);
                			}
                			curr->father->is_black = true;
                			curr->father->father->is_black = false;
                			left_rotate(curr->father->father);
                		}
                	}
				}
			}
			_root->is_black = true;
		}
		void erase_correct(node_pointer curr) // Here, we correct the erasing, because we have to keep the properties
		{ // https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
			node_pointer bro;
			while (curr != _root && curr->is_black)
			{
				if (curr == curr->father->left)
				{
					bro = curr->father->right;
					if (!bro->is_black) // Case 1 on the tuto
					{
						bro->is_black = true;
						curr->father->is_black = false;
						left_rotate(curr->father);
						bro = curr->father->right;
					}
					if (bro->left->is_black && bro->right->is_black)// Case 2 on the tuto
					{
						bro->is_black = false;
						curr = curr->father;
					}
					else
					{
						if (bro->right->is_black) // Case 3 on the tuto
						{
							bro->left->is_black = true;
							bro->is_black = false;
							right_rotate(bro);
							bro = curr->father->right;
						}
						// Case 4 on the tuto
						bro->is_black = curr->father->is_black; // I MODIFIED HERE
						curr->father->is_black = true;
						bro->right->is_black = true;
						left_rotate(curr->father);
						curr = _root;
					}
				}
				else // Exactly the same but reversed
				{
					bro = curr->father->left;
					if (!bro->is_black) // Case 1 on the tuto
					{
						bro->is_black = true;
						curr->father->is_black = false;
						right_rotate(curr->father);
						bro = curr->father->left;
					}
					if (bro->right->is_black && bro->left->is_black) // Case 2 on the tuto
					{
						bro->is_black = false;
						curr = curr->father;
					}
					else
					{
						if (bro->left->is_black) // Case 3 on the tuto
						{
							bro->right->is_black = true;
							bro->is_black = false;
							left_rotate(bro);
							bro = curr->father->left;
						} // Case 4 on the tuto
						bro->is_black = curr->father->is_black;
						curr->father->is_black = true;
						bro->left->is_black = true;
						right_rotate(curr->father);
						curr = _root;
					}
				}
			}
			curr->is_black = true;
		}
		node_pointer search(const value_type &value, node_pointer node) const // Searching for a precise value
		{
			if (!node || is_nil(node)) // If no node we done
				return (NULL);
			if (_cmp(value, *node->content)) // If value is less than node content we go on the left branch
				return (search(value, node->left));
			if (_cmp(*node->content, value)) // Else we go on the right branch
				return (search(value, node->right));
			return (node); // If we have a value that not less or more, we have the one we want
		}
		node_pointer copy_node(node_pointer old) // Copying a node
		{
			node_pointer n_node = _node_alloc.allocate(1); // Initialisation
			_node_alloc.construct(n_node, node<Content>()); // We create a node holding the Content type in the structure
			n_node->is_black = old->is_black;
			n_node->is_nil = old->is_nil;
			if (old->content)
			{
				n_node->content = _con_alloc.allocate(1);
				_con_alloc.construct(n_node->content, *old->content);
			}
			return (n_node);
		}
		void copy_subtree(node_pointer dst, node_pointer src)  // Recusively copy a node and all its subtree
		{
			if (src->left->is_nil) // if we at the end we just put _nil
				dst->left = _nil;
			else
			{
				dst->left = copy_node(src->left); // Copy the node
				dst->left->father = dst;
				copy_subtree(dst->left, src->left); // Recursive call on the left branch
			}
			if (src->right->is_nil) // if we at the end we just put _nil
				dst->right = _nil;
			else if (src->right->right == NULL)
			{
				dst->right = _header;
				_header->father = dst;
			}
            else
            {
            	dst->right = copy_node(src->right); // Copy the node
            	dst->right->father = dst;
            	copy_subtree(dst->right, src->right); // Recursive call on the right branch
			}
		}
		void init_nil_header(void) // Initialize nil and header nodes
		{
			_nil = _node_alloc.allocate(1);
			_node_alloc.construct(_nil, node<Content>());
			_nil->is_black = true;
			_nil->is_nil = true;
			_header = _node_alloc.allocate(1);
			_node_alloc.construct(_header, node<Content>());
			_header->content = _con_alloc.allocate(1);
			_con_alloc.construct(_header->content, Content());
			_header->is_black = true;
		}
	public:
		// ##### CONSTRUCTORS DESTRUCTOR
		RB_tree():	_root(0), _con_alloc(allocator_type()), _node_alloc(node_allocator()), _cmp(value_comp() ), _size(0)
		{// (1) Empty tree
			init_nil_header();
			_root = _header;
		}
		RB_tree(const value_compare &comp, const allocator_type &a = allocator_type()):
			_root(0),_cmp(comp), _size(0), _node_alloc(node_allocator()), _con_alloc(a)
		{// (1) Empty tree again
			init_nil_header();
			_root = _header;
		}
		template <class InputIt> // (2) Range constructor
		RB_tree(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
				const value_compare &comp, const allocator_type &alloc = allocator_type()):
				_cmp(comp), _size(0), _node_alloc(node_allocator()),_con_alloc(alloc)
		{
			init_nil_header();
	       	_root = _header;
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}
		RB_tree(const RB_tree &old): _root(0), _cmp(old._cmp) // (3) Copy constructor
		{
			*this = old;
		}
		~RB_tree() // Cleans everything including _nil and _header
		{
			clear_node(_root);
			_con_alloc.destroy(_header->content);
			_con_alloc.deallocate(_header->content, 1);
			_node_alloc.deallocate(_nil, 1);
			_node_alloc.deallocate(_header, 1);
		}
		
		// ##### OPERATOR OVERLOAD
		RB_tree &operator=(const RB_tree &old) // Copy the other RB_tree even if the dst isnt empty
		{
			if (this == &old)
				return (*this);
			this->_node_alloc = old._node_alloc;
			this->_con_alloc = old._con_alloc;
			this->_cmp = old._cmp;
			if (this->_root == NULL)
				init_nil_header();
			else
				clear_node(_root);
			if (old._size == 0)
				this->_root = this->_header;
			else
			{
				this->_root = copy_node(old._root);
				copy_subtree(this->_root, old._root);
			}
			this->_size = old._size;
			return (*this);
		}

		// ##### MODIFIERS FUNCTIONS
		ft::pair<iterator, bool> insert(const value_type &val) // (1) Insert a simple value
		{
			node_pointer find_res = search(val, _root);
			if (find_res)
				return (ft::pair<iterator, bool>(iterator(find_res), false)); // If val already in tree we return it
			node_pointer n_node = _node_alloc.allocate(1);
			_node_alloc.construct(n_node, node<value_type>(create_content(val))); // Create the node with the right specs
			n_node->left = _nil;
			n_node->right = _nil;
			insert_node1(n_node, _root); // Insert the node
			ft::pair<iterator, bool> res(iterator(n_node), true);
			insert_correct(n_node); // Repair the tree properties
			_size++;
			n_node = tree_max(_root);
			n_node->right = _header;
			_header->father = n_node;
			return (res);
		}
		iterator insert(iterator pos, const value_type &val) // (2) pos is a Hint for the position where the elem can be inserted
		{
			node_pointer n_node = search(val, _root);
			if (n_node)
				return (iterator(n_node)); // If val already in tree we return it
			n_node = _node_alloc.allocate(1);
			_node_alloc.construct(n_node, node<value_type>(create_content(val)));
			n_node->left = _nil;
			n_node->right = _nil;
			if (pos == begin())
			{
				if (pos != end() && _cmp(val, *pos))
					insert_node1(n_node, tree_min(_root));
				else
					insert_node1(n_node, _root);
			}
			else if (pos == end())
			{
				if (pos != begin() && _cmp(*(--pos), val))
					insert_node1(n_node, _header->father);
				else
					insert_node1(n_node, _root);
			}
			else
				insert_node1(n_node, _root);
			insert_correct(n_node);
			_size++;
			node_pointer max_of_tree = tree_max(_root);
			max_of_tree->right = _header;
			_header->father = max_of_tree;
			return (iterator(n_node));
		}
		template <class InputIt> // (3) insert a range of iterators
		void insert(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			for (; first != last; ++first)
				insert(*first); // Call (1) with the value insert
		}
		void erase(iterator pos)
		{
			node_pointer y = pos.node(), x, to_free = y;
			bool y_original_is_black = y->is_black;
			if (is_nil(y->left)) // if !y->left, we replace y by y->right
			{
				x = y->right;
				transplant(y, y->right);
			}
			else if (is_nil(y->right)) // if !y->right, we replace y by y->left
			{
				x = y->left;
				transplant(y, y->left);
			}
			else
			{
				node_pointer z = y; // save y in z
				y = tree_min(z->right); // We go to the min of the right branch of y;
				y_original_is_black = y->is_black; // Update on y color;
				x = y->right;
				if (y->father != z)
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->father = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->father = y;
				y->is_black = z->is_black;
			}
			free_node(to_free);
			if (y_original_is_black)
				erase_correct(x);
			_size--;
			_nil->father = NULL;
			if (_size == 0)
				_root = _header;
			else
			{
				if (_size != 1)
					x = tree_max(_root);
				else
					x = _root;
				x->right = _header; // Header is the further right _nil node
				_header->father = x;
			}
		}
		size_type erase(const value_type &key) // (2) Try to erase by finding a key
		{
			node_pointer find_res = search(key, _root);
			if (find_res)
				erase(iterator(find_res));
			return (find_res != NULL);
		}
		void erase(iterator first, iterator last) // (3) Erase a range of iterators
		{
			while (first != last)
				erase(first++);
		}
		void clear()
		{
			clear_node(_root);
			_root = _header;
			_header->father = NULL;
			_size = 0;
		}
		iterator find(const value_type &val)
		{
			node_pointer find_res = search(val, _root);
			return (find_res == NULL ? end() : iterator(find_res));
		}
		const_iterator find(const value_type &val) const
		{
			node_pointer find_res = search(val, _root);
			return (find_res == NULL ? end() : const_iterator(find_res));
		}
		size_type count(const value_type &val) const
		{
			return (find(val) != end());
		}
		void swap(RB_tree &old)
		{
			std::swap(this->_root, old._root);
			std::swap(this->_nil, old._nil);
			std::swap(this->_header, old._header);
			std::swap(this->_size, old._size);
			std::swap(this->_node_alloc, old._node_alloc);
			std::swap(this->_con_alloc, old._con_alloc);
			std::swap(this->_cmp, old._cmp);
		}
		// ##### GETTER FUNCTIONS
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_con_alloc.max_size());
		}
		bool empty() const
		{
			return (_size == 0);
		}
		value_compare value_comp() const
		{
			return (_cmp);
		}
		allocator_type get_allocator() const
		{
			return (_con_alloc);
		}

		// ##### ITERATORS
		iterator begin() // header if size == 0
		{
			return (iterator(_size == 0 ? _header : iterator(tree_min(_root))));
		}
		const_iterator begin() const
		{
			return (const_iterator(_size == 0 ? _header : const_iterator(tree_min(_root))));
		}
		iterator end()
		{
			return (iterator(_header));
		}
		const_iterator end() const
		{
			return (const_iterator(_header));
		}
		reverse_iterator rbegin() // Just opposite of normal begin()
		{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		// ##### BOUNDS
		iterator lower_bound(const value_type &val) // Goes from begin to last and returns an iterator to the first element whose key is not less than k
		{
			iterator last = end();
			iterator first = begin();
			while (first != last)
			{
				if (!_cmp(*first, val))
					return (first);
				++first;
			}
			return (last);
		}
		const_iterator lower_bound(const value_type &val) const // Goes from begin to last and returns an iterator to the first element whose key is not less than k
        {
         	const_iterator last = end();
        	const_iterator first = begin();
         	while (first != last)
			{
         		if (!_cmp(*first, val))
         			return (first);
        		++first;
        	}
        	return (last);
        }
		iterator upper_bound(const value_type &val) // Goes from begin to last and the function returns an iterator to the first element whose key is greater than k
		{
			iterator last = end();
			iterator first = begin();
			while (first != last)
			{
				if (_cmp(val, *first))
					return (first);
				++first;
			}
			return (last);
		}
		const_iterator upper_bound(const value_type &val) const // Goes from begin to last and the function returns an iterator to the first element whose key is greater than k
       	{
         	const_iterator last = end();
			const_iterator first = begin();
         	while (first != last)
        	{
         		if (_cmp(val, *first))
         			return (first);
        		++first;
        	}
        	return (last);
        }
		// A similar member function, lower_bound, has the same behavior as upper_bound, except in the case that the map contains an element with a key equivalent to k: In this case lower_bound returns an iterator pointing to that element, whereas upper_bound returns an iterator pointing to the next element.
		ft::pair<iterator,iterator> equal_range(const value_type &val)
		{
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}
		ft::pair<const_iterator,const_iterator> equal_range(const value_type &val) const
		{
			return ft::make_pair(lower_bound(val), upper_boud(val));
		}
};

template <class Content, class Compare, class Alloc>
bool operator==(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Content, class Compare, class Alloc>
bool operator!=(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (!(lhs == rhs));
}

template <class Content, class Compare, class Alloc>
bool operator<(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin()));
}
	
template <class Content, class Compare, class Alloc>
bool operator>(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (rhs < lhs);
}

template <class Content, class Compare, class Alloc>
bool operator<=(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (!(lhs > rhs));
}

template <class Content, class Compare, class Alloc>
bool operator>=(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
{
	return (!(lhs > rhs));
}

namespace std
{
	template <class Content, class Compare, class Alloc>
	void swap(const RB_tree<Content, Compare, Alloc> &lhs, const RB_tree<Content, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
