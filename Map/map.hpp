#pragma once

#include <memory>
#include "../Utilities/less.hpp"
#include "../Utilities/pair.hpp"
#include "../Utilities/pair_compare.hpp"
#include "../Utilities/swap.hpp"
#include "../Utilities/equal.hpp"
#include "../Utilities/lexicographical_compare.hpp"
#include "../Iterator/red_black_tree_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"
#include "../RedBlackTree/red_black_tree.hpp"


namespace ft
{
	template<class Key, class T, class Compare = ft::less<Key>, class Alloc =
	        std::allocator <ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key 													key_type;
		typedef T 														mapped_type;
		typedef ft::pair<const Key, T> 									value_type;
		typedef Compare 												key_compare;
		typedef Alloc 													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::rbt_iterator<value_type> 							iterator;
		typedef ft::rbt_iterator<const value_type> 						const_iterator;
		typedef ft::reverse_iterator<iterator> 							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef difference_type 										size_type;

		typedef typename ft::pair_compare<key_type, mapped_type, key_compare>	value_compare;
		typedef typename Alloc::template rebind<node<value_type> >::other		node_allocator_type;
		typedef red_black_tree<value_type, value_compare, node_allocator_type> 	tree_type;
		typedef typename ft::node<value_type> 									*p_node;

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &allocator = allocator_type())
		{
			_allocator = allocator;
			_joint = _tree.create_node(value_type());
			_key_compare = comp;
		}

		template<class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &allocator = allocator_type())
		{
			_allocator = allocator;
			_joint = _tree.create_node(value_type());
			_key_compare = comp;
			insert(first, last);
		}

		~map()
		{
			_tree.clear(&_joint->parent);
			_tree.clear(&_joint);
		}

		map(const map &src)
		{
			_allocator = src._allocator;
			_joint = _tree.create_node(value_type());
			_key_compare = src._key_compare;
			*this = src;
		}

		map &operator=(const map &src)
		{
			clear();
			_allocator = src._allocator;
			_key_compare = src._key_compare;
			_value_compare = src._value_compare;
			insert(src.begin(), src.end());
			return *this;
		}

		iterator begin()
		{ return iterator(_joint, _tree.min_node(_joint->parent)); }

		const_iterator begin() const
		{ return const_iterator(_joint, _tree.min_node(_joint->parent)); }

		iterator end()
		{ return iterator(_joint, 0); }

		const_iterator end() const
		{ return const_iterator(_joint, 0); }

		reverse_iterator rbegin()
		{ return reverse_iterator(end()); }

		const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

		reverse_iterator rend()
		{ return reverse_iterator(begin()); }

		const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }

		bool empty() const
		{ return _size == 0; }

		size_type size() const
		{ return _size; }

		size_type max_size() const
		{ return _tree.max_size(); }

		mapped_type &operator[](const key_type &k)
		{
			bool res = _tree.insert(&_joint->parent,
									_tree.create_node(bind(k)));
			_size += res;
			p_node p = _tree.find_node(_joint->parent, bind(k));
			return p->value.second;
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			bool res = _tree.insert(&_joint->parent, _tree.create_node(val));
			_size += res;
			p_node ptr = _tree.find_node(_joint->parent, val);
			return ft::pair<iterator, bool>(iterator(_joint, ptr), res);
		}

		iterator insert(iterator, const value_type &val)
		{
			_size += _tree.insert(&_joint->parent, _tree.create_node(val));
			p_node p = _tree.find_node(_joint->parent, val);
			return iterator(_joint, p);
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(*first);
		}

		void erase(iterator position)
		{
			bool res = _tree.erase(&_joint->parent, *position);
			if (res)
				--_size;
		}

		size_type erase(const key_type &k)
		{
			bool res = (bool) _tree.erase(&_joint->parent, bind(k));
			if (res)
				--_size;
			return res;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap(map &x)
		{
			ft::swap(x._joint, _joint);
			ft::swap(x._key_compare, _key_compare);
			ft::swap(x._value_compare, _value_compare);
			ft::swap(x._size, _size);
		}

		void clear()
		{
			_tree.clear(&_joint->parent);
			_joint->parent = 0;
			_size = 0;
		}

		key_compare key_comp() const
		{ return _key_compare; }

		value_compare value_comp() const
		{ return _value_compare; }

		iterator find(const key_type &k)
		{
			p_node ptr = _tree.find_node(_joint->parent, bind(k));
			return iterator(_joint, ptr);
		}

		const_iterator find(const key_type &k) const
		{
			p_node ptr = _tree.find_node(_joint->parent, bind(k));
			return const_iterator(_joint, ptr);
		}

		size_type count(const key_type &k) const
		{
			if (_tree.find_node(_joint->parent, bind(k)))
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &k)
		{
			return (iterator(_joint, _tree.lower(_joint->parent, bind(k))));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return (const_iterator(_joint, _tree.lower(_joint->parent, bind(k))));
		}

		iterator upper_bound(const key_type &k)
		{
			p_node temp = _tree.lower(_joint->parent, bind(k));
			iterator res(_joint, temp);

			if (temp && temp->value.first == k)
				++res;
			return iterator(res);
		}

		const_iterator upper_bound(const key_type &k) const
		{
			p_node temp = _tree.lower(_joint->parent, bind(k));
			iterator res(_joint, temp);

			if (temp && temp->value.first == k)
				++res;
			return const_iterator(res);
		}

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{ return ft::make_pair(lower_bound(k), upper_bound(k)); }

		ft::pair<const_iterator, const_iterator>
		equal_range(const key_type &k) const
		{ return ft::make_pair(lower_bound(k), upper_bound(k)); }

		allocator_type get_allocator() const
		{ return _allocator; }

	private:
		tree_type 			_tree;
		allocator_type 		_allocator;
		p_node 				_joint;
		key_compare 		_key_compare;
		value_compare 		_value_compare;
		size_type 			_size;

		value_type bind(const Key &key)
		{ return ft::make_pair(key, mapped_type()); }

		value_type bind(const Key &key) const
		{ return ft::make_pair(key, mapped_type()); }
	};

	template<class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{
		return x.size() == y.size() &&
			   ft::equal(x.begin(), x.end(), y.begin()) &&
			   ft::equal(y.begin(), y.end(), x.begin());
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{ return !(x == y); }

	template<class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &x,
				   const map<Key, T, Compare, Allocator> &y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end())
			&& x != y;
	}

	template<class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{ return x < y || x == y; }

	template<class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &x,
				   const map<Key, T, Compare, Allocator> &y)
	{ return y < x; }

	template<class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{ return x > y || x == y; }

	template<class Key, class T, class Compare, class Allocator>
	void swap(map<Key, T, Compare, Allocator> &x,
			  map<Key, T, Compare, Allocator> &y)
	{ x.swap(y); }
}
