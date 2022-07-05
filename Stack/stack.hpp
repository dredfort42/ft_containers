#pragma once

#include "../Vector/vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack(const container_type &ctnr = container_type())
		{ c = ctnr; }

		bool empty() const
		{ return c.empty(); }

		size_type size() const
		{ return c.size(); }

		value_type &top()
		{ return c.back(); }

		const value_type &top() const
		{ return c.back(); }

		void push(const value_type &val)
		{ c.push_back(val); }

		void pop()
		{ c.pop_back(); }

		template <class fT, class fContainer>
		friend bool operator==(const ft::stack<fT, fContainer> &lhs,
						const ft::stack<fT, fContainer> &rhs);

		template <class fT, class fContainer>
		friend bool operator!=(const ft::stack<fT, fContainer> &lhs,
							   const ft::stack<fT, fContainer> &rhs);

		template <class fT, class fContainer>
		friend bool operator<(const ft::stack<fT, fContainer> &lhs,
							   const ft::stack<fT, fContainer> &rhs);

		template <class fT, class fContainer>
		friend bool operator<=(const ft::stack<fT, fContainer> &lhs,
							   const ft::stack<fT, fContainer> &rhs);

		template <class fT, class fContainer>
		friend bool operator>(const ft::stack<fT, fContainer> &lhs,
							   const ft::stack<fT, fContainer> &rhs);

		template <class fT, class fContainer>
		friend bool operator>=(const ft::stack<fT, fContainer> &lhs,
							   const ft::stack<fT, fContainer> &rhs);

	protected:
		container_type c;
	};

	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{ return lhs.sct == rhs.sct; }

	template< class T, class Container >
	bool operator!=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{ return (lhs.sct != rhs.sct); }

	template< class T, class Container >
	bool operator<(const ft::stack<T, Container> &lhs,
				   const ft::stack<T, Container> &rhs)
	{ return (lhs.sct < rhs.sct); }

	template< class T, class Container >
	bool operator<=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{ return (lhs.sct <= rhs.sct); }

	template< class T, class Container >
	bool operator>(const ft::stack<T, Container> &lhs,
				   const ft::stack<T, Container> &rhs)
	{ return (lhs.sct > rhs.sct); }

	template< class T, class Container >
	bool operator>=(const ft::stack<T, Container> &lhs,
					const ft::stack<T, Container> &rhs)
	{ return (lhs.sct >= rhs.sct); }
}
