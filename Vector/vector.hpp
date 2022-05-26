// https://www.cplusplus.com/reference/vector/vector/

#pragma once

#include <memory>
#include "../Iterator/random_access_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"

//#include <iterator>

namespace ft
{
	template<class T, class Allocator = std::allocator <T> >
	class vector
	{
	public:
		typedef T															value_type;
		typedef Allocator 													allocator_type;
		typedef typename allocator_type::reference 							reference;
		typedef typename allocator_type::const_reference 					const_reference;
		typedef typename allocator_type::pointer 							pointer;
		typedef typename allocator_type::const_pointer 						const_pointer;
		typedef typename allocator_type::size_type 							size_type;
		typedef ft::random_access_iterator<value_type> 						iterator;
		typedef ft::random_access_iterator<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator> 								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

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
			   const allocator_type &allocator = allocator_type())
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

		vector	&operator= (const vector& x)
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

//		ITERATORS

//		Returns an iterator pointing to the first element in the vector.
		iterator begin() {return &_data[0];}
		const_iterator begin() const {return &_data[0];}

//		Returns an iterator referring to the past-the-end element in the vector.
		iterator end() {return &_data[_size];}
		const_iterator end() const {return &_data[_size];}

//		Returns a reverse iterator pointing to the last element in the vector.
		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return reverse_iterator(end());}

//		Returns a reverse iterator pointing to the theoretical element preceding
//		the first element in the vector
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return reverse_iterator(begin());}

//		CAPACITY

//		Return size (number of elements in the vector)
		size_type size() const {return _size;}

//		Return maximum size (maximum number of elements that vector can hold)
		size_type max_size() const {return _allocator.max_size();}

//		Resizes the container so that it contains n elements
//		void resize (size_type n, value_type val = value_type());

//		Return size of allocated storage capacity
		size_type capacity() const {return _capacity;}

//		[V] ELEMENT ACCESS:

//		Returns a reference to the element at position n in the vector container.
		reference operator[] (size_type n) {return _data[n];}
		const_reference operator[] (size_type n) const {return _data[n];}

	private:
		allocator_type _allocator;
		value_type *_data;
		size_type _capacity;
		size_type _size;
	};
}
