#pragma once

#include "iterator.hpp"

namespace ft
{
	template<typename Iter>
	class reverse_iterator
	{
	public:
		typedef Iter                                           			iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer         	pointer;
		typedef typename ft::iterator_traits<Iter>::reference       	reference;


//		default (1) default constructor
//		Constructs a reverse iterator that points to no object.
//		The internal base iterator is value-initialized.
		reverse_iterator() {};

//		initialization (2) initalization constructor
//		Constructs a reverse iterator from some original iterator it.
//		The behavior of the constructed object replicates the original,
//		except that it iterates through its pointed elements in the reverse order.
		explicit reverse_iterator (iterator_type it): _t(it) {};

//		copy (3) copy / type-cast constructor
//		Constructs a reverse iterator from some other reverse iterator.
//		The constructed object keeps the same sense of iteration as rev_it.
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it): _t(rev_it.base()) {};

//		Returns a copy of the base iterator.
		iterator_type base() const {return _t};

//		Dereference iterator
//		Returns a reference to the element pointed to by the iterator.
		reference operator*() const
		{
			Iter tmp = _t;
			return *(--tmp);
		}

//		Addition operator
//		Returns a reverse iterator pointing to the element located n positions
//		away from the element the iterator currently points to.
		reverse_iterator operator+ (difference_type n) const
		{
			return reverse_iterator(_t - n);
		}

//		Increment iterator position
//		Advances the reverse_iterator by one position.
//		(1) The pre-increment version
		reverse_iterator& operator++()
		{
			_t--;
			return reverse_iterator(_t);
		}

//		(2) The post-increment version
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}

//		Advance iterator
//		Advances the reverse_iterator by n element positions.
		reverse_iterator& operator+= (difference_type n)
		{
			_t -= n;
			return _t;
		}

	private:
		Iter _t;
	};


}
