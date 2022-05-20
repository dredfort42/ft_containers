#pragma once
#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {
	template <typename T>
	class random_access_iterator: ft::iterator<ft::random_access_iterator_tag, T> {
	public:
		// - категория итератора (самый глубокий из тегов категорий, которой соответствует итератор)
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

		// - тип значений, которые могут быть получены путем разыменования итератора
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;

		// - int, который можно использовать для определения расстояния между итераторами
		//   результат вычитания одного итератора из другого
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
		typedef difference_type                                                             distance_type;

		// - определяет указатель на итерируемый тип (value_type)
		typedef T*                                                                          pointer;

		// - определяет ссылку на итерируемый тип (value_type)
		typedef T&                                                                          reference;

		random_access_iterator(): _element(nullptr) {}
		random_access_iterator(pointer element): _element(element) {}
		random_access_iterator(const random_access_iterator& src) {
			*this = src;
		}
		~random_access_iterator() {}

		random_access_iterator& operator=(const random_access_iterator& src) {
			if (this == &src)
				return (*this);
			_element = src._element;
			return (*this);
		}

		// переопределение разыменования итератора
		reference &operator*() {
			return (*_element);
		}

		// переопределение инкремента итератора
		random_access_iterator& operator++() {
			_element++;
			return (*this);
		}

		//test this operator
		random_access_iterator operator++(int)
		{
			random_access_iterator rtn(*this);
			operator++();
			return (rtn);
		}

		pointer getElement() const {
			return (_element);
		}

	private:
		pointer _element;
	};

	// переопределение операторов сравнения

	// отдельное преобразование для не const итератора не имеет смысла,
	// так как оператор не производит операций с аргументами,
	// и может быть приведен сразу к const
	// template<typename T>
	// typename ft::random_access_iterator<T>::difference_type
	// operator==(const ft::random_access_iterator<T> left, const ft::random_access_iterator<T> right) {
	//     return (left.getElement() == right.getElement());
	//             // for (int i = 0; i < 10; i++)
	//             //     std::cout << left._element;
	// }

	template<typename TL, typename TR>
	typename ft::random_access_iterator<TL>::difference_type
	operator==(const ft::random_access_iterator<TL> left, const ft::random_access_iterator<TR> right) {
		return (left.getElement() == right.getElement());
	}

	template<typename TL, typename TR>
	typename ft::random_access_iterator<TL>::difference_type
	operator!=(const ft::random_access_iterator<TL> left, const ft::random_access_iterator<TR> right) {
		return (left.getElement() != right.getElement());
	}

}
