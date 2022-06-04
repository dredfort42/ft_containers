#pragma once

namespace ft
{
	template<typename Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator 													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type 			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer 			pointer;
		typedef typename ft::iterator_traits<Iterator>::reference 			reference;


//		default (1) default constructor
//		Constructs a reverse iterator that points to no object.
//		The internal base iterator is value-initialized.
		reverse_iterator() {}

//		initialization (2) initialization constructor
//		Constructs a reverse iterator from some original iterator it.
//		The behavior of the constructed object replicates the original,
//		except that it iterates through its pointed elements in the reverse order.
		explicit reverse_iterator(iterator_type it): _element(it) {}

//		copy (3) copy / type-cast constructor
//		Constructs a reverse iterator from some other reverse iterator.
//		The constructed object keeps the same sense of iteration as rev_it.
		reverse_iterator(const reverse_iterator<Iterator> &rev_it): _element(rev_it.base()) {}

		~reverse_iterator() {}

//		Returns a copy of the base iterator.
		iterator_type base() const {return _element;}

//		Dereference iterator
//		Returns a reference to the element pointed to by the iterator.
		reference operator*() const
		{
			iterator_type tmp = _element;
			return *(--tmp);
		}

//		Addition operator
//		Returns a reverse iterator pointing to the element located n positions
//		away from the element the iterator currently points to.
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(_element - n);
		}

//		Increment iterator position
//		Advances the reverse_iterator by one position.
//		(1) The pre-increment version
		reverse_iterator &operator++()
		{
			_element--;
			return *this;
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
		reverse_iterator &operator+=(difference_type n)
		{
			_element -= n;
			return *this;
		}

//		Subtraction operator
//		Returns a reverse iterator pointing to the element located n positions
//		before the element the iterator currently points to.
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(_element + n);
		}

//		Decrease iterator position
//		Decreases the reverse_iterator by one position.
//		(1) The pre-decrement version
		reverse_iterator &operator--()
		{
			_element++;
			return *this;
		}

//		(2) The post-decrement version
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}

//		Retrocede iterator
//		Descreases the reverse_iterator by n element positions.
		reverse_iterator &operator-=(difference_type n)
		{
			_element += n;
			return *this;
		}

//		Dereference iterator
//		Returns a pointer to the element pointed to by the iterator.
		pointer operator->() const {return &(operator*());}

//		Dereference iterator with offset
//		Accesses the element located n positions away from the element
//		currently pointed to by the iterator.
		reference operator[](difference_type n) const
		{
			return *(operator-(n));
		}

	private:
		Iterator _element;
	};

//	Relational operators for reverse_iterator
//	Performs the appropriate comparison operation between the reverse_iterator
//	objects lhs and rhs.
	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

//	Addition operator
//	Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it
	template<class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &rev_it)
	{
		return rev_it + n;
	}

//	Subtraction operator
//	Returns the distance between lhs and rhs.
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator> &lhs,
			const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() - rhs.base();
	}
}
