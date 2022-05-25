#pragma once

#include "iterator.hpp"

namespace ft
{
	template<typename Iter>
	class reverse_iterator
	{
	private:
		Iter _t;

	public:
		typedef Iter                                           		iterator_type;
		typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iter>::reference       reference;
		typedef typename ft::iterator_traits<Iter>::pointer         pointer;

		reverse_iterator() {};
		explicit reverse_iterator(Iter x): _t(x) {};

		reference operator*() const
		{
			Iter tmp = _t;
			return *--tmp;
		}
	};


}
