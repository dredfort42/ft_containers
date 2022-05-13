#pragma once

#include <memory>
#include <iterator>
namespace ft
{
	template<class T, class Allocator = std::allocator <T> >
	class vector {
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference     	 	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer         	pointer;
		typedef typename allocator_type::const_pointer   	const_pointer;
		typedef typename allocator_type::size_type       	size_type;

		//tmp iterator defs
		typedef typename std::random_access_iterator_tag	ra_it; // tmp name
		typedef std::iterator<ra_it, value_type> 			iterator;
		typedef std::iterator<ra_it , const value_type> 	const_iterator;
		typedef std::reverse_iterator<iterator>          	reverse_iterator;
		typedef std::reverse_iterator<const_iterator>    	const_reverse_iterator;
		typedef typename std::iterator_traits<iterator>		i_t; // tmp name
		typedef typename i_t::difference_type				difference_type;
	};
}
