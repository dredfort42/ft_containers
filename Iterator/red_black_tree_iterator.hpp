#pragma once

#include "../Iterator/iterator.hpp"
#include "../RedBlackTree/node.hpp"
#include "../Utilities/swich_const.hpp"

namespace ft
{
	template<typename T>
	class rbt_iterator
	{
	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	rbt_it;
		typedef typename rbt_it::iterator_category 							iterator_category;
		typedef typename rbt_it::value_type 								value_type;
		typedef typename rbt_it::difference_type 							difference_type;
		typedef T 															*pointer;
		typedef T 															&reference;
		typedef pointer														iterator_type;
		typedef ft::node<typename ft::switch_const<T>::type> 		        *p_node;

		rbt_iterator()
		{}

		explicit rbt_iterator(const p_node &root, const p_node &node)
			: _root(root), _joint(node)
		{}

		rbt_iterator(const rbt_iterator &src)
		{ *this = src; }

		~rbt_iterator()
		{}

		rbt_iterator &operator=(const rbt_iterator &src)
		{
			if (this == &src)
				return *this;
			_root = src._root;
			_joint = src._joint;
			return *this;
		}

		reference &operator*()
		{ return _joint->value; }

		pointer operator->() const
		{ return &(_joint->value); }

		rbt_iterator &operator++()
		{
			if (!_joint)
				return *this;
			else if (_joint->right)
				_joint = min_node(_joint->right);
			else if (_joint == max_node(_root->parent))
				_joint = 0;
			else
			{
				while (_joint->parent->right == _joint)
					_joint = _joint->parent;
				_joint = _joint->parent;
			}
			return *this;
		}

		rbt_iterator operator++(int)
		{
			rbt_iterator temp = *this;
			++(*this);
			return temp;
		}

		rbt_iterator &operator--()
		{
			if (!_joint)
				_joint = max_node(_root->parent);
			else if (_joint->left)
				_joint = max_node(_joint->left);
			else
			{
				while (_joint->parent->left == _joint)
					_joint = _joint->parent;
				_joint = _joint->parent;
			}
			return *this;
		}

		rbt_iterator operator--(int)
		{
			rbt_iterator temp = *this;
			--(*this);
			return temp;
		}

		bool operator==(const rbt_iterator &it) const
		{ return (it._joint == _joint); }

		bool operator!=(const rbt_iterator &it) const
		{ return (it._joint != _joint); }

		operator rbt_iterator<const T>() const
		{ return rbt_iterator<const T>(_root, _joint); }

	private:
		p_node _root;
		p_node _joint;

		p_node min_node(p_node joint) const
		{
			if (joint)
				while (joint->left)
					joint = joint->left;
			return joint;
		}

		p_node max_node(p_node joint) const
		{
			if (joint)
				while (joint->right)
					joint = joint->right;
			return joint;
		}
	};
}
