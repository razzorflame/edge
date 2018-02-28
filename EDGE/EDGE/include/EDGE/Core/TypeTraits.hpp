#pragma once

#include EDGE_PCH

namespace edge
{

// Remove reference and cv-qualifier from type.
template <typename _type>
struct remove_cvref { using type = std::remove_reference_t < std::remove_cv_t<_type> >; };
template <typename _type>
using remove_cvref_t = typename remove_cvref<_type>::type;

// Obtain widest type
// Example:
// - make_widest_t<float>			= long double
// - make_widest_t<char>			= std::intmax_t
// - make_widest_t<std::uint8_t>	= std::uintmax_t

template <typename _type, typename = void>
struct make_widest { using type = _type; };
template <typename _type,
	typename = std::enable_if_t< std::is_integral_v<_type> && !std::is_unsigned_v<_type> > >
struct make_widest { using type = std::intmax_t; };
template <typename _type,
	typename = std::enable_if_t< std::is_integral_v<_type> && std::is_unsigned_v<_type> > >
struct make_widest { using type = std::uintmax_t; };
template <typename _type,
	typename = std::enable_if_t< std::is_floating_point_v<_type> > >
struct make_widest { using type = long double; };

template <typename _type>
using make_widest_t = typename make_widest <_type>::type;

// Check whether type is cv/ref qualified:
// is_cvref_v<int>			= false
// is_cvref_v<int&>			= true
// is_cvref_v<const int>	= true
template <typename _type>
struct is_cvref {
	static constexpr bool value = std::is_same_v<_type, remove_cvref_t<_type> >;
};
template <typename _type>
constexpr bool is_cvref_v = is_cvref<_type>::value;

} // namespace edge
