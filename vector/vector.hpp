// https://www.cplusplus.com/reference/vector/vector/

#pragma once

#include <memory>
#include <iterator>

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

//			tmp iterator defs
		typedef typename std::random_access_iterator_tag ra_it; // tmp name
		typedef std::iterator <ra_it, value_type> iterator;
		typedef std::iterator<ra_it, const value_type> const_iterator;
		typedef std::reverse_iterator <iterator> reverse_iterator;
		typedef std::reverse_iterator <const_iterator> const_reverse_iterator;
		typedef typename std::iterator_traits<iterator> i_t; // tmp name
		typedef typename i_t::difference_type difference_type;

//		CONSTRUCT VECTOR

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

////			copy (4)
//			vector(const vector &x)
//			{ *this = x };

//		VECTOR DESTRUCTOR

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

//		CAPACITY

//		Return size (number of elements in the vector)
		size_type size() const {return _size;}

//		Return maximum size (maximum number of elements that vector can hold)
		size_type max_size() const {return _allocator.max_size();}

//		Resizes the container so that it contains n elements
//		void resize (size_type n, value_type val = value_type());

//		Return size of allocated storage capacity
		size_type capacity() const {return _capacity;}

	private:
		allocator_type _allocator;
		value_type *_data;
		size_type _capacity;
		size_type _size;
	};
}
