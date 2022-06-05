// https://www.cplusplus.com/reference/vector/vector/

#pragma once

#include <memory>
#include "../Iterator/random_access_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"
#include "../Utilities/enable_if.hpp"
#include "../Utilities/is_integral.hpp"
#include "../Utilities/equal.hpp"
#include "../Utilities/lexicographical_compare.hpp"

//#include <iterator>

namespace ft
{
	template<class T, class Allocator = std::allocator <T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

//		[V] CONSTRUCT VECTOR

//		default (1) empty container constructor (default constructor)
//		Constructs an empty container, with no elements.
		explicit vector(const allocator_type &allocator = allocator_type())
		{
			_allocator = allocator;
			_data = nullptr;
			_capacity = 0;
			_size = 0;
		}

//		fill (2) fill constructor
//		Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &allocator = allocator_type())
		{
			if (n < 1)
				throw std::bad_alloc();
			else
			{
				_allocator = allocator;
				_data = _allocator.allocate(n);
				_capacity = n;
				_size = n;
				value_type *tmpData = _data;
				while (n--)
				{
					_allocator.construct(tmpData, val);
					tmpData++;
				}
			}
		}

//		range (3) range constructor
//		Constructs a container with as many elements as the range [first,last),
//		with each element constructed from its corresponding element in that range, in the same order.
		template<class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &allocator = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			   InputIterator>::type* = nullptr)
		{
			_allocator = allocator;
			_size = 0;
			for (InputIterator it = first; it != last; it++)
				_size++;
			_capacity = _size;
			_data = _allocator.allocate(_capacity);
			value_type *tmpData = _data;
			for (InputIterator it = first; it != last; it++)
			{
				_allocator.construct(tmpData, *it);
				tmpData++;
			}
		}

//		copy (4) copy constructor
//		Constructs a container with a copy of each of the elements in x.
//		The copy keeps and uses a copy of x's allocator.
		vector(const vector &x)
		{
			_allocator = x._allocator;
			_size = x._size;
			_capacity = x._capacity;
			_data = _allocator.allocate(_capacity);
			value_type *tmpData = _data;
			for (const_iterator it = x.begin(); it != x.end(); it++)
			{
				_allocator.construct(tmpData, *it);
				tmpData++;
			}
		};

//		[V] VECTOR DESTRUCTOR

		~vector()
		{
			value_type *tmpData = _data;
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.destroy(tmpData);
				tmpData++;
			}
			_allocator.deallocate(_data, _capacity);
		}

//		[V] COPY

		vector &operator=(const vector &x)
		{
			_allocator = x._allocator;
			_size = x._size;
			_capacity = x._capacity;
			_data = _allocator.allocate(_capacity);
			value_type *tmpData = _data;
			for (const_iterator it = x.begin(); it != x.end(); it++)
			{
				_allocator.construct(tmpData, *it);
				tmpData++;
			}
			return *this;
		};

//		[V] ITERATORS

//		Returns an iterator pointing to the first element in the vector.
		iterator begin()
		{ return &_data[0]; }

		const_iterator begin() const
		{ return &_data[0]; }

//		Returns an iterator referring to the past-the-end element in the vector.
		iterator end()
		{ return &_data[_size]; }

		const_iterator end() const
		{ return &_data[_size]; }

//		Returns a reverse iterator pointing to the last element in the vector.
		reverse_iterator rbegin()
		{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const
		{ return reverse_iterator(end()); }

//		Returns a reverse iterator pointing to the theoretical element preceding
//		the first element in the vector
		reverse_iterator rend()
		{ return reverse_iterator(begin()); }

		const_reverse_iterator rend() const
		{ return reverse_iterator(begin()); }

//		[V] CAPACITY

//		Return size (number of elements in the vector)
		size_type size() const
		{ return _size; }

//		Return maximum size (maximum number of elements that vector can hold)
		size_type max_size() const
		{ return _allocator.max_size(); }

//		Resizes the container so that it contains n elements
		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				for (; _size > n; _size--)
					_allocator.destroy(&_data[_size]);
			else if (n > _size && n < max_size())
			{
				if (n > _capacity && n <= _capacity * 2)
					reserve(_capacity * 2);
				else if (n > _capacity * 2)
					reserve(n);
				for (; _size < n; _size++)
					_allocator.construct(&_data[_size], val);
			}
		}

//		Return size of allocated storage capacity
		size_type capacity() const
		{ return _capacity; }

//		Test whether vector is empty
//		Returns whether the vector is empty (i.e. whether its size is 0).
		bool empty() const
		{ return _size ? false : true; }

//		Requests that the vector capacity be at least enough to contain n elements.
		void reserve(size_type n)
		{
			if (n > _capacity && n < max_size())
			{
				pointer temp = _allocator.allocate(n);
				try
				{
					std::uninitialized_copy(_data, _data + _size, temp);
				}
				catch (...)
				{
					_allocator.deallocate(temp, n);
					throw;
				}
				_allocator.deallocate(_data, _capacity);
				_data = temp;
				_capacity = n;
			}
		}

//		[V] ELEMENT ACCESS:

//		Returns a reference to the element at position n in the vector container.
		reference operator[](size_type n)
		{ return _data[n]; }

		const_reference operator[](size_type n) const
		{ return _data[n]; }

//		Access element
//		Returns a reference to the element at position n in the vector.
		reference at(size_type n)
		{
			if (n < _size)
				return _data[n];
			throw std::out_of_range("ERROR: position out of range");
		}

		const_reference at(size_type n) const
		{
			if (n < _size)
				return _data[n];
			throw std::out_of_range("ERROR: position out of range");
		}

//		Access first element
//		Returns a reference to the first element in the vector.
		reference front()
		{ return &_data[0]; }

		const_reference front() const
		{ return &_data[0]; }

//		Access last element
//		Returns a reference to the last element in the vector.
		reference back()
		{ return &_data[_size - 1]; }

		const_reference back() const
		{ return &_data[_size - 1]; }

//		[V] MODIFIERS:
//		In the range version, the new contents are elements constructed
//		from each of the elements in the range between first and last,
//		in the same order.
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					InputIterator>::type* = nullptr)
		{
			clear();
			size_type distance = ft::distance(first, last);

			if (_capacity < distance)
			{
				if (_capacity * 2 >= distance)
					reserve(_capacity * 2);
				else
					reserve(distance);
			}
			for (; first < last; _size++, first++)
				_allocator.construct(&(*(begin() + _size)), *first);
		}

//		In the fill version, the new contents are n elements,
//		each initialized to a copy of val.
		void assign(size_type n, const value_type &val)
		{
			clear();
			if (_capacity < n)
			{
				if (_capacity * 2 >= n)
					reserve(_capacity * 2);
				else
					reserve(n);
			}
			for (; _size < n; _size++)
				_allocator.construct(&(*(begin() + _size)), val);
		}

//		Add element at the end
//		Adds a new element at the end of the vector, after its current last element.
//		The content of val is copied (or moved) to the new element.
		void push_back(const value_type &val)
		{
			if (!_size)
				reserve(1);
			else if (_size == _capacity)
				reserve(_capacity * 2);
			_allocator.construct(&(*end()), val);
			_size++;
		}

//		Delete last element
//		Removes the last element in the vector, effectively reducing the container size by one.
		void pop_back()
		{
			if (_size)
			{
				_allocator.destroy(&(*(end() - 1)));
				_size--;
			}
		}

//		Insert elements
//		The vector is extended by inserting new elements before the element at
//		the specified position, effectively increasing the container size by
//		the number of elements inserted.

//		single element (1)
		iterator insert(iterator position, const value_type &val)
		{
			value_type *temp_data;
			if (!_size)
			{
				if (!_capacity)
					reserve(1);
				_allocator.construct(&(*position), val);
				return position;
			} else if (_size == _capacity)
			{
				temp_data = _allocator.allocate(_capacity * 2);
				_capacity *= 2;
			} else
				temp_data = _allocator.allocate(_capacity);

			value_type *p = temp_data;
			for (int i = 0; begin() + i < position; i++)
			{
				_allocator.construct(temp_data, *(begin() + i));
				temp_data++;
				_allocator.destroy(&(*(begin() + i)));
			}
			_allocator.construct(temp_data, val);
			temp_data++;
			for (int i = 0; position + i < end(); i++)
			{
				_allocator.construct(temp_data, *(position + i));
				temp_data++;
				_allocator.destroy(&(*(position + i)));
			}
			_allocator.deallocate(&(*begin()), _size);
			_data = p;
			_size++;
			return position;
		}

//		fill (2)
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (_size + n > _capacity)
			{
				if (_size + n >= _capacity * 2)
					_capacity = _size + n;
				else
					_capacity *= 2;
			}
			value_type *temp_data = _allocator.allocate(_capacity);
			value_type *p = temp_data;
			for (int i = 0; begin() + i < position; i++)
			{
				_allocator.construct(temp_data, *(begin() + i));
				temp_data++;
				_allocator.destroy(&(*(begin() + i)));
			}
			for (size_type i = 0; i < n; i++)
			{
				_allocator.construct(temp_data, val);
				temp_data++;
			}
			for (int i = 0; position + i < end(); i++)
			{
				_allocator.construct(temp_data, *(position + i));
				temp_data++;
				_allocator.destroy(&(*(position + i)));
			}
			_allocator.deallocate(&(*begin()), _size);
			_data = p;
			_size += n;
		}

//		range (3)
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value,
					InputIterator>::type* = nullptr)
		{
			size_type distance = ft::distance(first, last);

			if (_size + distance > _capacity)
			{
				if (_size + distance >= _capacity * 2)
					_capacity = _size + distance;
				else
					_capacity *= 2;
			}
			value_type *temp_data = _allocator.allocate(_capacity);
			value_type *p = temp_data;
			for (int i = 0; begin() + i < position; i++)
			{
				_allocator.construct(temp_data, *(begin() + i));
				temp_data++;
				_allocator.destroy(&(*(begin() + i)));
			}
			for (; first != last; first++)
			{
				_allocator.construct(temp_data, *first);
				temp_data++;
			}
			for (int i = 0; position + i < end(); i++)
			{
				_allocator.construct(temp_data, *(position + i));
				temp_data++;
				_allocator.destroy(&(*(position + i)));
			}
			_allocator.deallocate(&(*begin()), _size);
			_data = p;
			_size += distance;
		}

//		Removes from the vector either a single element (position).
		iterator erase(iterator position)
		{
			if (position + 1 == end())
				_allocator.destroy(&(*position));
			else
			{
				for (int i = 0; position + i + 1 < end(); i++)
				{
					_allocator.construct(&(*(position + i)),
										 *(position + i + 1));
					_allocator.destroy(&(*(position + i + 1)));
				}
			}
			_size -= 1;
			return position;
		}

//		Removes from the vector a range of elements ([first,last)).
		iterator erase(iterator first, iterator last)
		{
			iterator temp = first;
			size_type distance = ft::distance(first, last);

			for (; first < end() - distance; first++)
			{
				_allocator.destroy(&(*first));
				_allocator.construct(&(*first), *(first + distance));
				_allocator.destroy(&(*(first + distance)));
			}
			_size -= distance;
			return temp;
		}

//		Swap content
//		Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		void swap(vector &x)
		{
			allocator_type temp_allocator = x._allocator;
			value_type *temp_data = x._data;
			size_type temp_capacity = x._capacity;
			size_type temp_size = x._size;
			x._allocator = _allocator;
			x._data = _data;
			x._capacity = _capacity;
			x._size = _size;
			_allocator = temp_allocator;
			_data = temp_data;
			_capacity = temp_capacity;
			_size = temp_size;
		}

//		Clear content
//		Removes all elements from the vector (which are destroyed),
//		leaving the container with a size of 0.
		void clear()
		{
			for (; _size; _size--)
				_allocator.destroy(&_data[_size]);
		}

//		[V] ALLOCATOR:
//		Returns a copy of the allocator object associated with the vector.
		allocator_type get_allocator() const
		{ return _allocator; }

	private:
		allocator_type _allocator;
		value_type *_data;
		size_type _capacity;
		size_type _size;
	};

//	[V] RELATION OPERATORS FOR VECTOR

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs,
					const ft::vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::const_iterator l_it = lhs.begin();
		typename ft::vector<T>::const_iterator r_it = rhs.begin();
		while (l_it == r_it && (l_it != lhs.end() || r_it != rhs.end()))
		{
			l_it++;
			r_it++;
		}
		if (l_it == lhs.end() && r_it == rhs.end())
			return true;
		else
			return false;
//		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
//			return true;
		return false;
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs,
					const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs,
				   const ft::vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(
				lhs.begin(), lhs.end(),
				rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs,
					const ft::vector<T, Alloc> &rhs)
	{
		if (lhs == rhs)
			return true;
		return (lhs < rhs);
	}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs,
				   const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs,
					const vector<T, Alloc> &rhs)
	{
		if (lhs == rhs)
			return true;
		return !(lhs < rhs);
	}

//	[V] EXCHANGE CONTENTS OF VECTORS
	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}
