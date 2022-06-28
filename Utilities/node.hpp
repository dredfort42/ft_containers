#pragma once

namespace ft
{
	template <typename T>
	struct rbt_node
	{
		typedef T   	value_type;

		value_type 		value;
		rbt_node		*parent;
		rbt_node		*left;
		rbt_node		*right;
		bool			is_red;

		rbt_node()
		{
			parent = nullptr;
			left = nullptr;
			right = nullptr;
			is_red = true;
		}

		rbt_node(rbt_node *parent = nullptr,
				 rbt_node *left = nullptr,
				 rbt_node *right = nullptr,
				 bool is_red = true)
		{
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->is_red = is_red;
		}

		rbt_node(const value_type &value,
				 rbt_node *parent = nullptr,
				 rbt_node *left = nullptr,
				 rbt_node *right = nullptr,
				 bool is_red = true)
		{
			this->value = value;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->is_red = is_red;
		}

		rbt_node(const rbt_node &node)
		{
			value = node.value,
			parent = node.parent,
			left = node.left,
			right = node.right;
			is_red = node.is_red;
		}

		virtual ~rbt_node() {}

		rbt_node &operator=(const rbt_node &node)
		{
			if (node != *this)
			{
				value = node.value;
				parent = node.parent;
				left = node.left;
				right = node.right;
				is_red = node.is_red;
			}
			return (*this);
		}

		bool operator==(const rbt_node &node)
		{ return value == node.value; }

		bool operator!=(const rbt_node &node)
		{ return !(value == node.value); }
	};
}
