#pragma once
#include <iostream>
#include "iterator.hpp"

namespace ft {
	template <typename T>
	class random_access_iterator: ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
		typedef T																			*pointer;
		typedef T																			&reference;

		random_access_iterator() {}
		random_access_iterator(pointer element): _element(element) {}
		random_access_iterator(const random_access_iterator &src) {*this = src;}
		~random_access_iterator() {}

		pointer base() const {return _element;}

		random_access_iterator &operator=(const random_access_iterator &src)
		{
			if (this == &src)
				return (*this);
			_element = src.base();
			return *this;
		}

		reference &operator*() {return (*_element);}

		pointer operator->() const {return &(operator*());}

		random_access_iterator operator+(difference_type n) const
		{
			return _element + n;
		}

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
		{
			return _element - n;
		}

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

		reference operator[](difference_type n) const {return *(operator+(n));}

	private:
		pointer _element;
	};

	template<class Iterator>
	bool operator==(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<class Iterator>
	bool operator!=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<class Iterator>
	bool operator<(const random_access_iterator<Iterator> &lhs,
				   const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<class Iterator>
	bool operator<=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template<class Iterator>
	bool operator>(const random_access_iterator<Iterator> &lhs,
				   const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<class Iterator>
	bool operator>=(const random_access_iterator<Iterator> &lhs,
					const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<class Iterator>
	random_access_iterator<Iterator> operator+(
			typename random_access_iterator<Iterator>::difference_type n,
			const random_access_iterator<Iterator> &_it)
	{
		return _it + n;
	}

	template<class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-(
			const random_access_iterator<Iterator> &lhs,
			const random_access_iterator<Iterator> &rhs)
	{
		return lhs.base() - rhs.base();
	}
}
