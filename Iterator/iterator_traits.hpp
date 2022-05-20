// https://www.cplusplus.com/reference/iterator/iterator_traits/

#pragma once

#include <iostream>
#include "iterator.hpp"

namespace ft
{

//	The iterator category.
//	It can be one of these: iterator_category
	struct output_iterator_tag {};
	struct input_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

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



//	iterator tag validation
	template <bool status, typename T>
	struct iterator_validation {
		const static bool valid = status;
		typedef T   type;
	};

	// iterator tag validation result
	template<typename T>
	struct is_iterator_tagged:
			public iterator_validation<false, T> {};

	template<>
	struct is_iterator_tagged<ft::output_iterator_tag>:
			public iterator_validation<true, ft::output_iterator_tag> {};

	 template<>
	 struct is_iterator_tagged<ft::input_iterator_tag>:
	     public iterator_validation<true, ft::input_iterator_tag> {};

	 template<>
	 struct is_iterator_tagged<ft::forward_iterator_tag>:
	     public iterator_validation<true, ft::forward_iterator_tag> {};

	template<>
	struct is_iterator_tagged<ft::bidirectional_iterator_tag>:
			public iterator_validation<true, ft::bidirectional_iterator_tag> {};

	template<>
	struct is_iterator_tagged<ft::random_access_iterator_tag>:
			public iterator_validation<true, ft::random_access_iterator_tag> {};

//
//
//
//
//	// вспомогательная структура-шаблон, используется для указания всех критических определений типов, которые должен иметь итератор.
//	// получает информацию от класса Iterator в аргументе шаблона
//	template <typename Iterator>
//	struct iterator_traits {
//		// - категория итератора (самый глубокий из тегов категорий, которой соответствует итератор)
//		typedef typename Iterator::iterator_category    iterator_category;
//
//		// - тип значений, которые могут быть получены путем разыменования итератора
//		typedef typename Iterator::value_type           value_type;
//
//		// - int, который можно использовать для определения расстояния между итераторами
//		//   результат вычитания одного итератора из другого
//		typedef typename Iterator::difference_type      difference_type;
//		typedef difference_type                         distance_type;
//
//		// - определяет указатель на итерируемый тип (value_type)
//		typedef typename Iterator::pointer              pointer;
//
//		// - определяет ссылку на итерируемый тип (value_type)
//		typedef typename Iterator::reference            reference;
//	};
//

//	template <typename T>
//	struct iterator_traits<T*> {
//		// - категория итератора (самый глубокий из тегов категорий, которой соответствует итератор)
//		typedef ft::random_access_iterator_tag    iterator_category;
//
//		// - тип значений, которые могут быть получены путем разыменования итератора
//		typedef T                                       value_type;
//
//		// - int, который можно использовать для определения расстояния между итераторами
//		//   результат вычитания одного итератора из другого
//		typedef ptrdiff_t                               difference_type;
//		typedef difference_type                         distance_type;
//
//		// - определяет указатель на итерируемый тип (value_type)
//		typedef T*                                      pointer;
//
//		// - определяет ссылку на итерируемый тип (value_type)
//		typedef T&                                      reference;
//	};
//


}
