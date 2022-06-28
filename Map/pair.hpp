#pragma once

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

//		[V] CONSTRUCT PAIR

//		(1) default constructor
//		Constructs a pair object with its elements value-initialized.
		pair(): first(), second()
		{}

//		(2) copy / move constructor (and implicit conversion)
//		The object is initialized with the contents of the pr pair object.
//		The corresponding member of pr is passed to the constructor of each of its members.
		template<class U, class V>
		pair(const pair<U, V> &pr): first(pr.first), second(pr.second)
		{}

//		(3) initialization constructor
//		Member first is constructed with a and member second with b.
		pair(const first_type &a, const second_type &b) : first(a), second(b)
		{}

//		[V] COPY

//		Assign contents
//		Assigns pr as the new content for the pair object.
//		Member first is assigned pr.first, and member second is assigned pr.second.
		pair &operator=(const pair &pr)
		{
			if (*this != pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}
	};

	//	[V] RELATION OPERATORS FOR PAIR
	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(lhs == rhs); }

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first
			   || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(rhs < lhs); }

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return rhs < lhs; }

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(lhs < rhs); }

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 key, T2 value)
	{ return pair<T1, T2>(key, value); }
}
