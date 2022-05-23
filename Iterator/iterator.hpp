// https://www.cplusplus.com/reference/iterator/
// https://www.cplusplus.com/reference/iterator/iterator_traits/

#pragma once

#include <iostream>
#include "iterator.hpp"
#include <iterator>

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
		typedef Distance difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

//	The iterator category.
//	It can be one of these: iterator_category
	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag: input_iterator_tag {};
	struct bidirectional_iterator_tag: forward_iterator_tag {};
	struct random_access_iterator_tag: bidirectional_iterator_tag {};

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
		typedef T*              						pointer;
		typedef T&	            						reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t			     				difference_type;
		typedef T							           	value_type;
		typedef const T*              					pointer;
		typedef const T&	            				reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};
//
////	iterator tag validation
//	template <bool status, typename T>
//	struct iterator_validation {
//		const static bool valid = status;
//		typedef T   type;
//	};
//
//	// iterator tag validation result
//	template<typename T>
//	struct is_iterator_tagged:
//			public iterator_validation<false, T> {};
//
//	template<>
//	struct is_iterator_tagged<ft::output_iterator_tag>:
//			public iterator_validation<true, ft::output_iterator_tag> {};
//
//	 template<>
//	 struct is_iterator_tagged<ft::input_iterator_tag>:
//	     public iterator_validation<true, ft::input_iterator_tag> {};
//
//	 template<>
//	 struct is_iterator_tagged<ft::forward_iterator_tag>:
//	     public iterator_validation<true, ft::forward_iterator_tag> {};
//
//	template<>
//	struct is_iterator_tagged<ft::bidirectional_iterator_tag>:
//			public iterator_validation<true, ft::bidirectional_iterator_tag> {};
//
//	template<>
//	struct is_iterator_tagged<ft::random_access_iterator_tag>:
//			public iterator_validation<true, ft::random_access_iterator_tag> {};

}
