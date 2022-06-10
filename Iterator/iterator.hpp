// https://www.cplusplus.com/reference/iterator/
// https://www.cplusplus.com/reference/iterator/iterator_traits/

#pragma once

#include <iostream>

namespace ft
{
//	Iterator base class
//	This is a base class template that can be used to derive iterators from it.
//	It isn't an iterator class and does not provide any of the functionality
//	an iterator is expected to have.
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

//	Iterator traits
//	Traits class defining properties of iterators.
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

//	Distance between iterators
//	Calculates the number of elements between first and last.
	template<class InputIter>
	typename ft::iterator_traits<InputIter>::difference_type
	distance(InputIter first, InputIter last)
	{
		typename ft::iterator_traits<InputIter>::difference_type r = 0;
		for (; first != last; first++)
			r++;
		return r;
	}
}
