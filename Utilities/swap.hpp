#pragma once

namespace ft
{
	template<class T>
	void swap(T &lhs, T &rhs) {
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}
