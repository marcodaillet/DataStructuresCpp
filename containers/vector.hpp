/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:26:28 by mdaillet          #+#    #+#             */
/*   Updated: 2022/02/24 13:46:51 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>
#include <iterator>
#include <memory>
#include "../iterators/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../utils/integral.hpp"
#include "../utils/lexico_comp.hpp"
#include "../utils/equal.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		// def of the variable types we need
		typedef T value_type; // Alias of the first parameter of the template
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type& const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef random_access_iterator<value_type> iterator;
		typedef random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

	private:
		pointer		_array;			// array of T
		size_type 	_size;			// how much T vector has
		size_type _capacity;		// how much allocated memory vector has
		allocator_type _allocator;	// allocator for allocating and deallocating memory

	public:
		// ##### CONSTRUCTORS
		explicit vector(const allocator_type& alloc = allocator_type()): // (1) Empty container
			_array(0), _size(0), _capacity(0), _allocator(alloc) {}
		explicit vector(size_type n, const T& value = T(), const allocator_type& alloc = allocator_type()): // (2) Fill construc
			_size(n), _capacity(n), _allocator(alloc)
		{
			this->_array = this->_allocator.allocate(n);
			for (size_type i = 0; i < n; i++)
				this->_allocator.construct(this->_array + i, value);
		}
		template<class InputIt> // (3) Range constructor
		vector(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last,
			   const allocator_type& alloc = allocator_type()): _allocator(alloc)
		{
			if (first > last)
				throw std::length_error("vector");
			_size = last - first;
			_capacity = _size;
			_array = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(_array + i, *(first + i));
		}
		vector(const vector& other): _size(0), _capacity(0) // (4) Copy constructor
		{
			*this = other;
		}

		// ##### DESTRUCTOR
		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_array + i);
			if (_capacity)
				_allocator.deallocate(_array, _capacity);
		}

		// ##### OPERATOR OVERLOAD

		vector &operator=(const vector &old)
		{
			if (this == &old)
				return (*this);
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_array + i);
			this->_size = old._size;
			if (this->_capacity < this->_size) // After destroying, if _size is bigger than capacity there is a memory problem
			{
				if (this->_capacity)
					this->_allocator.deallocate(this->_array, this->_capacity);
				this->_capacity = this->_size;
				this->_array = this->_allocator.allocate(this->_capacity);
			}
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(_array + i, old[i]);
			return (*this);
		}
		iterator begin()
		{
			return (iterator(_array));
		}
		const_iterator begin() const
		{
			return (const_iterator(_array));
		}
		iterator end()
		{
			return (iterator(_array + _size));
		}
		const_iterator end() const 
		{
			return (const_iterator(_array + _size));
		}
		reverse_iterator rbegin()
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

		// ##### CAPACITY

		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_allocator.max_size());
		}
		size_type capacity() const
		{
			return (_capacity);
		}
		bool empty() const
		{
			if (_size == 0)
				return (true);
			return (false);
		}
		void reserve(size_type n) // Request that the vector capacity be at least enough to contain n elements
		{
			if (n <= _capacity)
				return ;
			pointer n_array = _allocator.allocate(n);
			try
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(n_array + i, *(_array + i)); // Copy old array in new array
			}
			catch (std::exception &e) // If allocation failed we destroy and throw an exception
			{
				size_type i = 0;
				while (n_array + i != NULL && i < _size)
				{
					_allocator.destroy(n_array + i);
					i++;
				}
				_allocator.deallocate(n_array, n);
				throw;
			}
			for (size_type i = 0; i < _size; i++) // Destroy old
				_allocator.destroy(_array + i);
			if (_capacity)
				_allocator.deallocate(_array, _capacity); // Deallocate old
			_capacity = n; // new capacity
			_array = n_array; // old array with bigger capacity
		}
		void resize(size_type n, value_type value = T()) // Resize the vector. If n is smaller than _size, deletion of a part. If bigger than _size, reserve more space and fill it with value. If value is not specified, the default constructor is called
		{
			if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_allocator.destroy(_array + i);
				_size = n;
			}
			else if (n > _size)
			{
				if (_capacity < n)
					this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
				for (size_type i = _size; i < n; i++)
					_allocator.construct(this->_array + i, value);
				_size = n;
			}
		}
		
		// ##### ELEMENT ACCESS
		reference operator[](size_type n)
		{
			return *(this->_array + n);
		}
		const_reference operator[](size_type n) const
		{
			return *(this->_array + n);
		}
		reference at(size_type i)
		{
			if (i >= _size)
				throw std::out_of_range("vector");
			return *(_array + i);
		}
		const_reference at(size_type i) const
		{
			if (i >= _size)
				throw std::out_of_range("vector");
			return *(_array + i);
		}
		reference front()
		{
			return (*_array);
		}
		const_reference front() const
		{
			return (*_array);
		}
		reference back()
		{
			return (*(_array + _size - 1));
		}
		const_reference back() const
		{
			return (*(_array + _size - 1));
		}
		allocator_type get_allocator() const
		{
			return (_allocator);
		}
		
		// ##### MODIFIERS
		template <class InputIt> // (1) Copy a range of input iterators in the vector
		void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			if (first > last)
				throw std::logic_error("vector");
			size_type n = static_cast<size_type>(last - first);
			clear();
			if (n > capacity()) // If not enough space we deallocate and reallocate with the right size
			{
				_allocator.deallocate(_array, _capacity);
				_array = _allocator.allocate(n);
				_capacity = n;
			}
			size_type i = 0;
			while (first < last) // Just constructing on the range of iterators
			{
				_allocator.construct(_array + i, *first);
				++first;
				++i;
			}
			_size = n;
		}
		void assign(size_type n, const T &val) // (2)Fill a vector with a value val
		{
			clear();
			if (n > capacity())
			{
				_allocator.deallocate(_array, _capacity);
				_array = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				_allocator.construct(_array + i, val);
			_size = n;
		}
		void clear() // Destroy everything and leaves a size of 0
		{
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_array + i);
			_size = 0;
		}
		void push_back(const T &val) // Adds one element at the end
		{
			if (_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2); // If there is not enough space, push_back doubles it, see tests
			_allocator.construct(_array + _size, val);
			_size++;
		}
		void pop_back() // Remove last element
		{
			_allocator.destroy(_array + (_size - 1));
			_size--;
		}
		iterator erase(iterator position) // (1) Erase a precise position
		{
			size_type distance = static_cast<size_type>(std::distance(begin(), position)); // Calculating offset of the position
			for (size_type i = distance; i < _size - 1; ++i)
			{
				_allocator.destroy(_array + i); // Removing the precise position and reconstructing with the next value
				_allocator.construct(_array + i, *(_array + i + 1)); // In the end, only the first destruction will stay
			}
			_size--; // Updating the _size
			_allocator.destroy(_array + _size);
			return (iterator(_array + distance)); // Returns the iterator at the position next to the one deleted
		}
		iterator erase(iterator first, iterator last) // Erase a range in the vector
		{
			difference_type start = std::distance(begin(), first); // Offset of the range
			difference_type len = std::distance(first, last); // Length of the range
			size_type i;
			for (i = start; i < _size - len; i++) // Constructing whats after the range on the range position until the end
			{
				_allocator.destroy(_array + i);
				_allocator.construct(_array + i, *(_array + i + len));
			}
			while (i < _size) // Deleting the offset caused by the over-construction
			{
				_allocator.destroy(_array + i);
				i++;
			}
			_size -= len;
			return (iterator(_array + start)); // Returns the iterator at the position next to the first one deleted
		}
		void swap(vector &lhs)
		{
			std::swap(this->_array, lhs._array);
			std::swap(this->_size, lhs._size);
			std::swap(this->_capacity, lhs._capacity);
			std::swap(this->_allocator, lhs._allocator);
		}
		iterator insert(iterator pos, const T &val) // (1) Insert one val at a precise position
		{
			if (pos < begin() || pos > end())
				throw (std::logic_error("vector"));
			difference_type start = std::distance(begin(), pos); // ####### NOT SURE THATS RIGHT
			if (_size == _capacity) // If vector is full
			{
				_capacity = _capacity * 2 + (_capacity == 0);
				pointer n_arr = _allocator.allocate(_capacity); // Capacity is always 1 more than the real contained
				std::uninitialized_copy(begin(), pos, iterator(n_arr)); // Copy from begin to pos inside n_arr
				_allocator.construct(n_arr + start, val); // Add the new value at the pos
				std::uninitialized_copy(pos, end(), iterator(n_arr + start + 1)); 
				for (std::size_t i = 0; i < _size; i++) // Destroy old
					_allocator.destroy(_array + i);
				if (_size) // Deallocate old
					_allocator.deallocate(_array, _size);
				_size++;
				_array = n_arr;
			}
			else // If vector isnt full
			{
				for (size_type i = _size; i > static_cast<size_type>(start); i--) // We take the vector from the top
				{
					_allocator.destroy(_array + i);						// Destroy one by one
					_allocator.construct(_array + i, *(_array + i - 1)); // Copy to n + 1 the whole segment after start
				}
				_allocator.destroy(&(*pos)); // Destroy what has been copied to n + 1
				_allocator.construct(&(*pos), val); // Insert the value
				_size++;
			}
			return (begin() + start); // Return the positionof the new input
		}
		void insert(iterator pos, size_type n, const T &val) // (2) Fill n element of value val at the position pos
		{
			if (n == 0)
				return ;
			else if (max_size() - _size < n || pos < begin() || pos > end()) 
				throw std::length_error("vector");
			difference_type start = std::distance(begin(), pos); // ####### NOT SURE THATS RIGHT
			if (_size + n > _capacity) // If the range overloads the vector
			{
				size_type n_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n; // See tests
				pointer n_arr = _allocator.allocate(n_capacity); // allocate the right space
				std::uninitialized_copy(begin(), pos, iterator(n_arr)); // Copy old from begin to new range start in new array
				for (size_type i = 0; i < n; i++) // Input the new value for n elements
					_allocator.construct(n_arr + start + i, val);
				std::uninitialized_copy(pos, end(), iterator(n_arr + start + n)); // Copy the rest of old after the range
				for (size_type i = 0; i < _size; i++) // Some cleaning
					_allocator.destroy(_array + i);
				if (_capacity) // More cleaning
					_allocator.deallocate(_array, _capacity);
				_size += n;
				_capacity = n_capacity;
				_array = n_arr;
			}
			else // If there is enough space
			{
				for (size_type i =_size; i > static_cast<size_type>(start); i--) // Takes vector upside down
				{
					_allocator.destroy(_array + i + n - 1);						 // Move everything thats after position
					_allocator.construct(_array + i + n - 1, *(_array + i - 1)); // up to n places in the vector
				}
				for (size_type i = 0; i < n; i++)
				{
					_allocator.destroy(_array + i + start); // Destroy old
					_allocator.construct(_array + i + start, val); // Input new range;
				}
				_size += n;
			}
		}
		template <class InputIt> // (3) Insert a range of iterators from first to last at the position pos
		void insert(iterator pos, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
		{
			if (first > last || pos < begin() || pos > end())
				throw (std::logic_error("vector"));
			size_type n = static_cast<size_type>(last - first);
			size_type start = static_cast<size_type>(pos - begin());
			if (_size + n > _capacity) // If the range overloads the vector
			{
				size_type n_capacity = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n; // See tests
				pointer n_arr = _allocator.allocate(n_capacity); // allocate the right space
				std::uninitialized_copy(begin(), pos, iterator(n_arr)); // Copy old from begin to new range start in new array
				try
				{
					for (size_type i = 0; i < n; i++) // Try to construct on the iterators starting at first
					{
						_allocator.construct(n_arr + start + i, *first);
						first++;
					}
				}
				catch (...) // Error handling by cleaning whats just been created
				{
					for (size_type i = 0; i < n + start; ++i)
						_allocator.destroy(n_arr + i);
					_allocator.deallocate(n_arr, n_capacity);
					throw ;
				}
				std::uninitialized_copy(pos, end(), iterator(n_arr + start + n)); // Copy the rest of old array;
				for (size_type i = 0; i < _size; i++) // Some cleaning
					_allocator.destroy(_array + i);
				if (_capacity) // More cleaning
					_allocator.deallocate(_array, _capacity);
				_size += n;
				_capacity = n_capacity;
				_array = n_arr;
			}
			else // If there is enough space
			{
				for (size_type i =_size; i > start; i--) // Takes vector upside down
				{
					_allocator.destroy(_array + i + n - 1);						 // Move everything thats after position
					_allocator.construct(_array + i + n - 1, *(_array + i - 1)); // up to n places in the vector
				}
				for (size_type i = 0; i < n; i++)
				{
					_allocator.destroy(_array + i + n); // Destroy old
					_allocator.construct(_array + i + start, *first); // Input new range;
					first++;
				}
				_size += n;
			}
		}
	};
	// ##### RELATIONAL OPERATORS
	template< class A, class Alloc>
	bool operator==(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < rhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}
	template< class A, class Alloc>
	bool operator!=(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template< class A, class Alloc>
	bool operator<(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class A, class Alloc>
	bool operator>(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		return rhs < lhs;
	}
	template< class A, class Alloc>
	bool operator<=(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	template< class A, class Alloc>
	bool operator>=(const ft::vector<A, Alloc> &lhs, const ft::vector<A, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}

namespace ft
{
	template<class T, class Alloc>
	inline void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
