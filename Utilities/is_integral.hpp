#pragma once

namespace ft
{
	template<typename T, bool is_integral_type>
	struct integral_type
	{
		typedef T 				value_type;
		static const bool value = is_integral_type;

		operator value_type() const
		{ return value; }
	};

//	https://www.cplusplus.com/reference/type_traits/is_integral/
	template <typename T>
	struct is_integral_type
			: public ft::integral_type<T, false> {};

	template <>
	struct is_integral_type<bool>
			: public ft::integral_type<bool, true> {};

	template <>
	struct is_integral_type<char>
			: public ft::integral_type<char, true> {};

	template <>
	struct is_integral_type<char16_t>
			: public ft::integral_type<char16_t, true> {};

	template <>
	struct is_integral_type<char32_t>
			: public ft::integral_type<char32_t, true> {};

	template <>
	struct is_integral_type<wchar_t>
			: public ft::integral_type<wchar_t, true> {};

	template <>
	struct is_integral_type<signed char>
			: public ft::integral_type<signed char, true> {};

	template <>
	struct is_integral_type<short int>
			: public ft::integral_type<short int, true> {};

	template <>
	struct is_integral_type<int>
			: public ft::integral_type<int, true> {};

	template <>
	struct is_integral_type<long int>
			: public ft::integral_type<long int, true> {};

	template <>
	struct is_integral_type<long long int>
			: public ft::integral_type<long long int, true> {};

	template <>
	struct is_integral_type<unsigned char>
			: public ft::integral_type<unsigned char, true> {};

	template <>
	struct is_integral_type<unsigned short int>
			: public ft::integral_type<unsigned short int, true> {};

	template <>
	struct is_integral_type<unsigned int>
			: public ft::integral_type<unsigned int, true> {};

	template <>
	struct is_integral_type<unsigned long int>
			: public ft::integral_type<unsigned long int, true> {};

	template <>
	struct is_integral_type<unsigned long long int>
			: public ft::integral_type<unsigned long long int, true> {};

	template<typename T>
	struct is_integral
			: public is_integral_type<T> {};
}
