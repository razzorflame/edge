// File description:
// Implements basic length class and aliases.
#pragma once

// Precompiled header:
#include EDGE_PCH

namespace edge
{
template<class NonRatioType>
constexpr bool is_ratio_v = false;

template<intmax_t RatioNumerator, intmax_t RatioDenumerator>
constexpr bool is_ratio_v<std::ratio<RatioNumerator, RatioDenumerator>> = true;

/// <summary>
/// Provides implementation of base length unit.
/// </summary>
template < typename LengthType, class _Ratio = std::ratio<1, 1> >
class BaseLength
{
public:
	using RatioType		= _Ratio;
	using ValueType		= LengthType;

	static_assert(is_ratio_v<RatioType>, "Second template parameter must be a valid std::ratio type.");
	static_assert(std::is_floating_point_v<ValueType>, "Length can only be represented by floating point values.");

	ValueType value;
			
	/// <summary>
	/// Returns maximal possible value.
	/// </summary>
	/// <returns>Maximal possible value.</returns>
	constexpr static ValueType max()
	{
		return std::numeric_limits<ValueType>::max();
	}

	/// <summary>
	/// Returns minimal possible value.
	/// </summary>
	/// <returns>Minimal possible value.</returns>
	constexpr static ValueType min()
	{
		return std::numeric_limits<ValueType>::min();
	}

	/// <summary>
	/// Returns zero-length.
	/// </summary>
	/// <returns>Zero-length object.</returns>
	constexpr static BaseLength<ValueType, RatioType> zero()
	{
		return {};
	}

	/// <summary>
	/// Default constructor.
	/// </summary>
	constexpr BaseLength(ValueType value_ = ValueType{ 0 })
		: value(value_)
	{
	}

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="rhs_">Other length object.</param>
	template <typename LengthType1, typename RatioType2nd>
	constexpr BaseLength(const BaseLength<LengthType1, RatioType2nd> &rhs_)
		: value(rhs_.value
				* std::ratio_divide<RatioType2nd, RatioType>::num
				/ std::ratio_divide<RatioType2nd, RatioType>::den)
	{
	}

	/// <summary>
	/// Copy assignment operator.
	/// </summary>
	/// <param name="rhs_">Other length object.</param>
	template <typename LengthType1, typename RatioType2nd>
	constexpr BaseLength<ValueType, RatioType>& operator=(const BaseLength<LengthType1, RatioType2nd> &rhs_)
	{
		value = rhs_.value
			* std::ratio_divide<RatioType2nd, RatioType>::num
			/ std::ratio_divide<RatioType2nd, RatioType>::den;
	}

	/// <summary>
	/// Converts value to other length unit.
	/// </summary>
	template <typename LengthType1, typename RatioType2nd>
	constexpr explicit operator BaseLength<LengthType1, RatioType2nd>() const
	{
		using div_ratio = std::ratio_divide<RatioType2nd, RatioType>;
		return { static_cast<LengthType1>(value) * div_ratio::num / div_ratio::den };
	}

	/// <summary>
	/// Determines whether rhs_ length is *exactly* equal.
	/// </summary>
	/// <param name="rhs_">The right hand side length.</param>
	/// <returns>
	///   <c>true</c> if equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename LengthType2nd, typename RatioType2nd>
	constexpr bool equals(BaseLength<LengthType2nd, RatioType2nd> const &rhs_) const
	{
		using div_ratio = std::ratio_divide<RatioType2nd, RatioType>;
		return value == (static_cast<LengthType2nd>(rhs_.value) * div_ratio::num / div_ratio::den);
	}

	/// <summary>
	/// Determines whether rhs_ length is nearly equal.
	/// </summary>
	/// <param name="rhs_">The right hand side length.</param>
	/// <param name="tolerance">The tolerance.</param>
	/// <returns>
	///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename LengthType2nd, typename RatioType2nd>
	constexpr bool nearlyEquals(BaseLength<LengthType2nd, RatioType2nd> const &rhs_, ValueType const tolerance_ = Math::Constants::MediumTolerance<ValueType>) const
	{
		using div_ratio = std::ratio_divide<RatioType2nd, RatioType>;
		return Math::nearlyEquals(value, static_cast<ValueType>(static_cast<LengthType2nd>(rhs_.value) * div_ratio::num / div_ratio::den), tolerance_);
	}
};
		
/// <summary>
/// Adds rhs_ length to lhs_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Sum of two lengths.</returns>
/// <remarks>
/// <para>Resulting type matches lhs_ type.</para>
/// </remarks>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr BaseLength<LengthType1st, RatioType1st> operator+(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<RatioType2nd, RatioType1st>;
	return { lhs_.value + (static_cast<LengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den) };
}

/// <summary>
/// Subtracts rhs_ length from lhs_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Difference of two lengths.</returns>
/// <remarks>
/// <para>Resulting type matches lhs_ type.</para>
/// </remarks>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr BaseLength<LengthType1st, RatioType1st> operator-(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<RatioType2nd, RatioType1st>;
	return { lhs_.value - (static_cast<LengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den) };
}

/// <summary>
/// Returns lhs_ multiplied by a scalar_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="scalar_">The scalar_.</param>
/// <returns>Product of lhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <typename LengthType, typename RatioType, typename ScalarType,
	typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<ScalarType> > > > >
constexpr BaseLength<LengthType, RatioType> operator*(BaseLength<LengthType, RatioType> const & lhs_, ScalarType const scalar_)
{
	return { lhs_.value * scalar_ };
}

/// <summary>
/// Returns lhs_ divided by a scalar_.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="scalar_">The scalar_.</param>
/// <returns>Quotient of lhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <typename LengthType, typename RatioType, typename ScalarType,
	std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<ScalarType> > > > >
constexpr BaseLength<LengthType, RatioType> operator/(BaseLength<LengthType, RatioType> const & lhs_, ScalarType const scalar_)
{
	return { lhs_.value / scalar_ };
}

/// <summary>
/// Returns rhs_ multiplied by a scalar_.
/// </summary>
/// <param name="scalar_">The scalar_.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Product of rhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <typename ScalarType, typename LengthType, typename RatioType,
	typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<ScalarType> > > > >
constexpr BaseLength<LengthType, RatioType> operator*(ScalarType const scalar_, BaseLength<LengthType, RatioType> const & rhs_)
{
	return { rhs_.value * scalar_ };
}

/// <summary>
/// Returns lhs_ divided by a scalar_.
/// </summary>
/// <param name="scalar_">The scalar_.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>Quotient of rhs_ length and scalar_.</returns>
/// <remarks>
/// <para>Resulting type matches length type.</para>
/// </remarks>
template <typename ScalarType, typename LengthType, typename RatioType,
	typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<ScalarType> > > > >
constexpr BaseLength<LengthType, RatioType> operator/(ScalarType const scalar_, BaseLength<LengthType, RatioType> const & rhs_)
{
	return { rhs_.value / scalar_ };
}

/// <summary>
/// Checks if lhs_ length is *nearly* equal rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator==(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	return lhs_.nearlyEquals(rhs_);
}

/// <summary>
/// Checks if lhs_ length is not *nearly* equal rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>false</c> if nearly equal; otherwise, <c>true</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator!=(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	return !lhs_.nearlyEquals(rhs_);
}

/// <summary>
/// Checks if lhs_ length is greater than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is greater; otherwise, <c>false</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator>(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<RatioType2nd, RatioType1st>;
	return lhs_.value > (static_cast<LengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den);
}

/// <summary>
/// Checks if lhs_ length is greater or equal than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is greater or equal; otherwise, <c>false</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator>=(BaseLength<LengthType1st, RatioType1st> const &lhs_, BaseLength<LengthType2nd, RatioType2nd> const & rhs_)
{
	using div_ratio = std::ratio_divide<RatioType2nd, RatioType1st>;
	return lhs_.value >= (static_cast<LengthType1st>(rhs_.value) * div_ratio::num / div_ratio::den);
}

/// <summary>
/// Checks if lhs_ length is less than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is less; otherwise, <c>false</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator<(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const &rhs_)
{
	return !(lhs_ >= rhs_);
}

/// <summary>
/// Checks if lhs_ length is less or equal than rhs_ length.
/// </summary>
/// <param name="lhs_">The left hand side length.</param>
/// <param name="rhs_">The right hand side length.</param>
/// <returns>
///   <c>true</c> if lhs_ is less or equal; otherwise, <c>false</c>.
/// </returns>
template <typename LengthType1st, typename RatioType1st, typename LengthType2nd, typename RatioType2nd>
constexpr bool operator<=(BaseLength<LengthType1st, RatioType1st> const & lhs_, BaseLength<LengthType2nd, RatioType2nd> const &rhs_)
{
	return !(lhs_ > rhs_);
}


using Nanometers	= BaseLength<double, std::nano>;		// 0.000'000'001m
using Micrometers	= BaseLength<double, std::micro>;		// 0.000'001m
using Millimeters	= BaseLength<double, std::milli>;		// 0.001m
using Centimeters	= BaseLength<double, std::centi>;		// 0.01m
using Decimeters	= BaseLength<double, std::deci>;		// 0.1m
using Meters		= BaseLength<double>;					// 1m
using Decameters	= BaseLength<double, std::deca>;		// 10m
using Hectometers	= BaseLength<double, std::hecto>;		// 100m
using Kilometers	= BaseLength<double, std::kilo>;		// 1'000m
using Megameters	= BaseLength<double, std::mega>;		// 1'000'000m
using Gigameters	= BaseLength<double, std::giga>;		// 1'000'000'000m
using Miles			= BaseLength<double, std::ratio_multiply<std::kilo, std::ratio<1609, 1000>>>; // 1609m
using Yards			= BaseLength<double, std::ratio<9144, 10000>>;		// 0.9144m
using Lightyears	= BaseLength<double, std::ratio<9460730472580800>>;	// 9460730472580800m
}
