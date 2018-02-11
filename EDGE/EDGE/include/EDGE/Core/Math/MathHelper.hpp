#pragma once

#include EDGE_PCH

namespace edge
{

namespace Math
{	
	
namespace Constants
{
// Definition of Pi
template <typename Type>
constexpr Type Pi								= static_cast<Type>(3.14159265358979323846L);
// Make Pi available to const char* specialization:
template <>
constexpr const char* Pi<const char*>			= "Pi";
// Make Pi available to const wchar_t* specialization:
template <>
constexpr const wchar_t* Pi<const wchar_t*>		= L"Pi";

// Make Pi available to const char16_t* specialization:
template <>
constexpr const char16_t* Pi<const char16_t*>	= u"Pi";

// Make Pi available to const char32_t* specialization:
template <>
constexpr const char32_t* Pi<const char32_t*>	= U"Pi";


template <typename Type, typename = std::enable_if_t< std::is_floating_point_v<Type> > >
constexpr Type LowTolerance			= static_cast<Type>(0.000'001);

template <typename Type, typename = std::enable_if_t< std::is_floating_point_v<Type> > >
constexpr Type MediumTolerance		= static_cast<Type>(0.000'01);

template <typename Type, typename = std::enable_if_t< std::is_floating_point_v<Type> > >
constexpr Type HighTolerance		= static_cast<Type>(0.000'1);

template <typename Type, typename = std::enable_if_t< std::is_floating_point_v<Type> > >
constexpr Type VeryHighTolerance	= static_cast<Type>(0.001);

} // namespace Constants

/// <summary>
/// Makes sure that `lower_` is <= `higher_`.
/// </summary>
/// <param name="lower_">The value that will be lower one of the two specified.</param>
/// <param name="higher_">The value that will be higher one of the two specified..</param>
template <typename Type>
inline void minMax(Type & lower_, Type & higher_)
{
	if (lower_ > higher_)
		std::swap(lower_, higher_);
}

/// <summary>
/// Checks whether `a_` is nearly equal `b_`, using given equality tolerance.
/// </summary>
/// <param name="a_">The first component.</param>
/// <param name="b_">The second component.</param>
/// <param name="equalityTolerance_">The equality tolerance.</param>
/// <return>
///		<c>true</c> is `a_` is nearly equal `b_`; otherwise, <c>false</c>.
/// </return>
template <typename Type>
inline bool nearlyEquals(Type const a_, Type const b_, Type const equalityTolerance_ = Constants::MediumTolerance<Type>)
{
	return std::abs(a_ - b_) <= equalityTolerance_;
}

/// <summary>
/// Clamps `current_` value between `lowerBoundary_` and `upperBoundary_`.
/// </summary>
/// <param name="current_">The current.</param>
/// <param name="lowerBoundary_">The lower boundary.</param>
/// <param name="upperBoundary_">The upper boundary.</param>
/// <returns>Clamped value.</returns>
template <typename Type>
inline Type clamp(Type const current_, Type const lowerBoundary_, Type const upperBoundary_)
{
	// # Assertion note:
	// This function does not perform any additional check if lowerBoundary_ is <= than upperBoundary_.
	// You must implement it yourself or use `clampChecked` function.
	assert(lowerBoundary_ <= upperBoundary_);
	return std::max<Type>(std::min<Type>(current_, upperBoundary_), lowerBoundary_);
}

/// <summary>
/// Clamps `current_` value between `lowerBoundary_` and `upperBoundary_`. Makes sure that `lowerBoundary_` is <= `upperBoundary_`.
/// </summary>
/// <param name="current_">The current.</param>
/// <param name="lowerBoundary_">The lower boundary.</param>
/// <param name="upperBoundary_">The upper boundary.</param>
/// <returns>Clamped value.</returns>
template <typename Type>
inline Type clampChecked(Type const current_, Type lowerBoundary_, Type upperBoundary_)
{
	minMax(lowerBoundary_, upperBoundary_);
	return std::max<Type>(std::min<Type>(current_, upperBoundary_), lowerBoundary_);
}

} // namespace Math

} // namespace edge