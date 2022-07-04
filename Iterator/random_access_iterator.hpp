#pragma once

#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator
			: ft::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator<std::random_access_iterator_tag, T>	r_a_it;
		typedef typename r_a_it::iterator_category 							iterator_category;
		typedef typename r_a_it::value_type 								value_type;
		typedef typename r_a_it::difference_type 							difference_type;
		typedef T 															*pointer;
		typedef T 															&reference;
		typedef pointer														iterator_type;

		random_access_iterator()
		{}

		random_access_iterator(pointer element) : _element(element)
		{}

		random_access_iterator(const random_access_iterator &src)
		{ *this = src; }

		~random_access_iterator()
		{}

		pointer base() const
		{ return _element; }

		random_access_iterator &operator=(const random_access_iterator &src)
		{
			if (this == &src)
				return *this;
			_element = src._element;
			return *this;
		}

		reference &operator*()
		{ return *_element; }

		pointer operator->() const
		{ return _element; }

		random_access_iterator operator+(difference_type n) const
		{ return _element + n; }

		random_access_iterator &operator++()
		{
			_element++;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator temp = *this;
			++(*this);
			return temp;
		}

		random_access_iterator &operator+=(difference_type n)
		{
			_element += n;
			return *this;
		}

		random_access_iterator operator-(difference_type n) const
		{ return _element - n; }

		random_access_iterator &operator--()
		{
			_element--;
			return (*this);
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator temp = *this;
			--(*this);
			return temp;
		}

		random_access_iterator &operator-=(difference_type n)
		{
			_element -= n;
			return *this;
		}

		reference operator[](difference_type n) const
		{ return *(operator+(n)); }

		operator  random_access_iterator<const T>() const
		{ return (random_access_iterator<T>(_element)); }

	private:
		pointer _element;
	};

	template<class Iterator>
	bool operator==(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() == rhs.base(); }

	template<class Iterator>
	bool operator!=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() != rhs.base(); }

	template<class Iterator>
	bool operator<(const random_access_iterator<Iterator> &lhs,
				   const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() < rhs.base(); }

	template<class Iterator>
	bool operator<=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() <= rhs.base(); }

	template<class Iterator>
	bool operator>(const random_access_iterator<Iterator> &lhs,
				   const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() > rhs.base(); }

	template<class Iterator>
	bool operator>=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() >= rhs.base(); }

	template<class Iterator>
	random_access_iterator<Iterator> operator+(
			typename random_access_iterator<Iterator>::difference_type n,
			const random_access_iterator<Iterator> &_it)
	{ return _it + n; }

	template<class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-(
			const random_access_iterator<Iterator> &lhs,
			const random_access_iterator<Iterator> &rhs)
	{ return lhs.base() - rhs.base(); }
}
