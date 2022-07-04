#pragma once

#include <iostream>

namespace ft
{
	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef Distance 	difference_type;
		typedef T 			value_type;
		typedef Pointer 	pointer;
		typedef Reference 	reference;
		typedef Category 	iterator_category;
	};

	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type           value_type;
		typedef typename Iterator::pointer              pointer;
		typedef typename Iterator::reference            reference;
		typedef typename Iterator::iterator_category    iterator_category;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t			     				difference_type;
		typedef T							           	value_type;
		typedef T	              						*pointer;
		typedef T	            						&reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type distance = 0;
		for (; first != last; first++)
			distance++;
		return distance;
	}
}
