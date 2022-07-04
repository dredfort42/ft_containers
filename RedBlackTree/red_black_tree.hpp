#pragma once

#include <memory>
#include "../Utilities/less.hpp"
#include "../RedBlackTree/node.hpp"

namespace ft
{
	template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class red_black_tree
	{
	public:
		typedef T 									value_type;
		typedef Compare								key_compare;
		typedef Alloc								allocator_type;
		typedef typename allocator_type::size_type	size_type;
		typedef typename allocator_type::pointer 	p_node;

		p_node create_node(value_type src)
		{
			p_node new_joint = _allocator.allocate(1);
			_allocator.construct(new_joint, src);
			return new_joint;
		}

		void delete_node(p_node joint)
		{
			if (joint)
			{
				_allocator.destroy(joint);
				_allocator.deallocate(joint, 1);
			}
		}

		void swap_color(p_node joint)
		{
			bool color = joint->isBlack;
			joint->isBlack = joint->right->isBlack;
			joint->right->isBlack = color;
			joint->left->isBlack = color;
		}

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

		p_node find_node(p_node joint, value_type key) const
		{
			if (joint)
			{
				if (_compare(joint->value, key))
					return find_node(joint->right, key);
				else if (_compare(key, joint->value))
					return find_node(joint->left, key);
			}
			return joint;
		}

		p_node lower(p_node root, value_type key) const
		{
			p_node joint = 0;

			while (root)
			{
				if (_compare(root->value, key))
					root = root->right;
				else
				{
					if (root->left)
					{
						joint = lower(root->left, key);
						if (joint)
							root = joint;
						break;
					}
					else
						break;
				}
			}
			return root;
		}

		void clear(p_node *root)
		{
			if (*root == 0)
				return;
			if (*root)
			{
				if ((*root)->left)
					clear(&((*root)->left));
				if ((*root)->right)
					clear(&((*root)->right));
				delete_node((*root));
			}
			*root = 0;
		}

		size_type max_size() const
		{ return _allocator.max_size(); }

		void insert_balance(p_node *root, p_node joint)
		{
			p_node parent;
			p_node grand;
			p_node tmp;

			while (joint)
			{
				parent = joint->parent;
				grand = 0;
				tmp = parent;
				if (parent)
				{
					grand = parent->parent;
					if (joint->isBlack == false)
					{
						if (parent->isBlack == true)
							joint = parent;
						else if (grand)
						{
							if (grand->left && grand->left->isBlack == false &&
								grand->right && grand->right->isBlack == false)
							{
								swap_color(grand);
								joint = grand;
							}
							else if (grand->right == parent)
							{
								if (parent->left == joint)
								{
									rotate_right(parent, root);
									parent = joint;
								}
								if (parent->right == joint)
									rotate_left(grand, root);
								joint = parent->parent;
							}
							else
							{
								if (parent->right == joint)
								{
									rotate_left(parent, root);
									parent = joint;
								}
								if (parent->left == joint)
									rotate_right(grand, root);
								joint = parent->parent;
							}
						}
					}
					else
						joint = parent;
				}
				else
				{
					joint->isBlack = true;
					joint = joint->parent;
				}
			}
		}

		bool insert(p_node *root, p_node new_joint)
		{
			if (*root == 0)
			{
				*root = new_joint;
				new_joint->isBlack = true;
			}
			else
			{
				p_node tmp = *root;
				while (tmp)
				{
					if (!_compare(tmp->value, new_joint->value) &&
						!_compare(new_joint->value, tmp->value))
					{
						if (tmp != new_joint)
							delete_node(new_joint);
						return false;
					}
					else if (_compare(new_joint->value, tmp->value))
					{
						if (tmp->left)
							tmp = tmp->left;
						else
						{
							tmp->left = new_joint;
							new_joint->parent = tmp;
							break;
						}
					}
					else
					{
						if (tmp->right)
							tmp = tmp->right;
						else
						{
							tmp->right = new_joint;
							new_joint->parent = tmp;
							break;
						}
					}
				}
			}
			insert_balance(root, new_joint);
			return true;
		}

		void swap_p(p_node remove, p_node replace)
		{
			if (remove->parent)
			{
				if (remove->parent->left == remove)
					remove->parent->left = replace;
				else
					remove->parent->right = replace;
			}
			replace->parent = remove->parent;
			if (remove->left)
			{
				remove->left->parent = replace;
			}
			replace->left = remove->left;
			if (remove->right)
			{
				remove->right->parent = replace;
			}
			replace->right = remove->right;
			replace->isBlack = remove->isBlack;
		}

		bool erase(p_node *root, value_type key)
		{
			p_node remove = find_node(*root, key);

			if (remove)
			{
				p_node replace = 0;
				if (remove->left)
					replace = erase_left(remove, root);
				else if (remove->right)
					replace = erase_right(remove, root);
				else
					erase_not_child(remove, root);
				if (replace)
					swap_p(remove, replace);
				if (remove == *root)
				{
					if (replace)
						*root = replace;
					else
						*root = 0;
				}
				delete_node(remove);
				return true;
			}
			return false;
		}

		p_node erase_left(p_node some, p_node *root)
		{
			p_node replace = max_node(some->left);

			if (replace)
			{
				if (replace == some->left)
				{
					some->left = replace->left;
					if (replace->left)
						replace->left->parent = some;
				}
				else
				{
					replace->parent->right = replace->left;
					if (replace->left)
						replace->left->parent = replace->parent;
				}
				if (replace->isBlack == true)
				{
					if (replace->left && replace->left->isBlack == false)
						replace->left->isBlack = true;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		p_node erase_right(p_node some, p_node *root)
		{
			p_node replace = min_node(some->right);

			if (replace)
			{
				if (replace == some->right)
				{
					some->right = replace->right;
					if (replace->right)
						replace->right->parent = some;
				}
				else
				{
					replace->parent->left = replace->right;
					if (replace->right)
						replace->right->parent = replace->parent;
				}
				if (replace->isBlack == true)
				{
					if (replace->right && replace->right->isBlack == false)
						replace->right->isBlack = true;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		p_node erase_not_child(p_node some, p_node *root)
		{
			p_node replace = some;

			if (replace && replace->parent)
			{
				if (replace->parent->right == replace)
					replace->parent->right = 0;
				else
					replace->parent->left = 0;
				if (replace->isBlack == true)
				{
					if (replace->right && replace->right->isBlack == false)
						replace->right->isBlack = true;
					erase_balance(root, replace->parent);
				}
			}
			return replace;
		}

		void erase_balance(p_node *root, p_node some)
		{
			p_node right;
			p_node left;
			p_node brother;

			while (some != *root && some->isBlack)
			{
				brother = some->right;
				if (brother)
				{
					right = brother->right;
					left = brother->left;
					if ((right || left) && (!right || right->isBlack == true) &&
						(!left || left->isBlack == true))
					{
						if (brother->isBlack == true)
						{
							brother->isBlack = false;
							some->isBlack = true;
							rotate_left(some, root);
						}
						else
							some = some->parent;
					}
					else if (right && brother->isBlack == true)
					{
						if (left && left->isBlack == false &&
							right->isBlack == true)
						{
							rotate_right(brother, root);
							right = brother;
							brother = left;
						}
						if (right->isBlack == false &&
							(!left || left->isBlack == true || !some->left))
							rotate_left(some, root);
						else
							some = some->parent;
					}
					else if (brother->isBlack == true &&
							   some->isBlack == false)
					{
						some->isBlack = true;
						brother->isBlack = false;
						some = some->parent;
					}
					else
						some = some->parent;
				}
				else
					break;
			}
		}

		void rotate_left(p_node node, p_node *root)
		{
			p_node right = node->right;
			right->parent = node->parent;

			if (right->parent)
			{
				if (right->parent->right == node)
					right->parent->right = right;
				else
					right->parent->left = right;
			}
			node->parent = right;
			node->right = right->left;
			if (node->right)
			{
				if (node->right->parent == right)
					node->right->parent = node;
				else
					node->right->parent = node;
			}
			right->left = node;
			bool color = node->isBlack;
			node->isBlack = right->isBlack;
			right->isBlack = color;
			if (!right->parent)
				*root = right;
		}

		void rotate_right(p_node some, p_node *root)
		{
			p_node left = some->left;
			left->parent = some->parent;

			if (left->parent)
			{
				if (left->parent->left == some)
					left->parent->left = left;
				else
					left->parent->right = left;
			}
			some->parent = left;
			some->left = left->right;
			if (some->left)
			{
				if (some->left->parent == left)
					some->left->parent = some;
				else
					some->left->parent = some;
			}
			left->right = some;
			some->isBlack = false;
			left->isBlack = true;
			if (!left->parent)
				*root = left;
		}

	private:
		allocator_type 		_allocator;
		key_compare 		_compare;
	};
}
