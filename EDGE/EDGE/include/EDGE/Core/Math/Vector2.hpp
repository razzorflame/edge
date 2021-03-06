// File description:
// Implements base class for 2D vector manipulation.
// TODO: implement vectors.

#pragma once

// Precompiled header:
#include EDGE_PCH

// Custom includes:
#include <EDGE/Core/TypeTraits.hpp>
#include <EDGE/Core/Math/MathHelper.hpp>
#include <EDGE/Core/Math/VectorStringBuilder.hpp>

namespace edge
{

template <typename VectorType>
class BaseVector2;

////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds two vectors together.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Sum of two vectors.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_);

/// <summary>
/// Subtracts rhs vector from lhs one.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Difference of two vectors.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator - (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_);

/// <summary>
/// Multiplies two vectors.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Product of two vectors.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_);

/// <summary>
/// Divides lhs vector by rhs vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Quotient of two vectors.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator / (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (BaseVector2<VectorType> const & lhs_, VectorType const rhs_);

/// <summary>
/// Substracts scalar from a vector.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector minus a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator - (BaseVector2<VectorType> const & lhs_, VectorType const rhs_);

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector times a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (BaseVector2<VectorType> const & lhs_, VectorType const rhs_);

/// <summary>
/// Divides vector by a scalar.
/// </summary>
/// <param name="lhs_">The lhs vector.</param>
/// <param name="rhs_">The scalar.</param>
/// <returns>Vector divided by a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator / (BaseVector2<VectorType> const & lhs_, VectorType const rhs_);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Adds scalar to a vector.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector plus a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (VectorType const lhs_, BaseVector2<VectorType> const & rhs_);

/// <summary>
/// Multiplies vector by a scalar.
/// </summary>
/// <param name="lhs_">The scalar.</param>
/// <param name="rhs_">The rhs vector.</param>
/// <returns>Vector times a scalar.</returns>
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (VectorType const lhs_, BaseVector2<VectorType> const & rhs_);




/// <summary>
/// Implements templated two dimensional vector arithmetic class.
/// </summary>
template <typename VectorType>
class BaseVector2
{
	// Performs a type check:
	// Is only set to true when T is not cv-qualified and is non-boolean arithmetic type.
	template <typename _type>
	constexpr static bool is_mathscalar_v =
		is_cvref_v<_type>				&&
		std::is_arithmetic_v<_type>		&&
		!std::is_same_v<_type, bool>;

public:
	using ValueType = VectorType;

	// Allow every non-cv qualified arithmetic type but bool.
	static_assert(
		is_mathscalar_v<ValueType>,
		"ValueType of a vector must be a non-cv qualified math scalar type."
	);

	ValueType x, y;

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	constexpr BaseVector2()
		: x{ 0 }, y{ 0 }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	constexpr BaseVector2(ValueType const x_, ValueType const y_)
		: x{ x_ }, y{ y_ }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="BaseVector2"/> class.
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	constexpr BaseVector2(BaseVector2<ValueType> const &rhs_)
		: x{ rhs_.x }, y{ rhs_.y }
	{
	}

	/// <summary>
	/// Returns number of components contained by this vector.
	/// </summary>
	/// <returns>Number of components contained by this vector</returns>
	constexpr std::size_t size() const {
		return 2;
	}
			
	/// <summary>
	/// Sets values of the vector.
	/// </summary>
	/// <param name="x_">The x value.</param>
	/// <param name="y_">The y value.</param>
	constexpr void set(ValueType const x_, ValueType const y_)
	{
		x = static_cast<ValueType>(x_);
		y = static_cast<ValueType>(y_);
	}
			
	/// <summary>
	/// Returns length of the vector.
	/// </summary>
	/// <returns>Length of the vector.</returns>
	template <typename LengthType = ValueType,
		typename = std::enable_if_t< is_mathscalar_v<LengthType> > >
	LengthType length() const
	{
		if constexpr(std::is_same_v<LengthType, ValueType>)
			return std::sqrt(x * x + y * y);
		else
		{
			auto conv = this->template convert<LengthType>();
			return std::sqrt(conv.x * conv.x + conv.y * conv.y);
		}
	}

	/// <summary>
	/// Returns squared length of the vector.
	/// </summary>
	/// <returns>Squared length of the vector.</returns>
	template <typename LengthType = ValueType,
		typename = std::enable_if_t< is_mathscalar_v<LengthType> > >
	constexpr LengthType lengthSquared() const
	{
		if constexpr(std::is_same_v<LengthType, ValueType>)
			return x * x + y * y;
		else
		{
			auto conv = this->template convert<LengthType>();
			return static_cast<LengthType>(conv.x * conv.x + conv.y * conv.y);
		}
	}

	/// <summary>
	/// Computes distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Distance between two instances.</returns>
	template <typename DistanceType = ValueType,
		typename = std::enable_if_t< is_mathscalar_v<DistanceType> > >
	DistanceType distance(BaseVector2<ValueType> const & other_) const
	{
		return (*this - other_).template length<DistanceType>();
	}

	/// <summary>
	/// Computes squared distance between two instances.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Squared distance between two instances.</returns>
	template <typename DistanceType = ValueType,
		typename = std::enable_if_t< is_mathscalar_v<DistanceType> > >
	constexpr DistanceType distanceSquared(BaseVector2<ValueType> const & other_) const
	{
		return (*this - other_).template lengthSquared<DistanceType>();
	}

	/// <summary>
	/// Computes dot product of two vectors (this and other).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Dot product of two vectors.</returns>
	template <typename _DotTy = ValueType,
		typename = std::enable_if_t< is_mathscalar_v<_DotTy> > >
	constexpr _DotTy dot(BaseVector2<ValueType> const & other_) const
	{
		if constexpr(std::is_same_v<_DotTy, ValueType>)
			return x * other_.x + y * other_.y;
		else
		{
			auto convThis = this->template convert<_DotTy>();
			auto convOther = other_->template convert<_DotTy>();

			return static_cast<_DotTy>(
				convThis.x * convOther.x + convThis.y * convOther.y
			);
		}
	}

	/// <summary>
	/// Computes cross product of two vectors (this and rhs).
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <returns>Cross product of two vectors.</returns>
	template <typename _CrossTy,
		typename = std::enable_if_t< is_mathscalar_v<_CrossTy> > >
	constexpr _CrossTy cross(BaseVector2<ValueType> const & other_) const
	{
		if constexpr(std::is_same_v<_CrossTy, ValueType>)
			return x * other_.y + y * other_.x;
		else
		{
			auto convThis = this->template convert<_CrossTy>();
			auto convOther = other_->template convert<_CrossTy>();

			return static_cast<_CrossTy>(
				convThis.x * convOther.y + convThis.y * convOther.x
			);
		}
	}

	/// <summary>
	/// Computes reflection vector of specified normal.
	/// </summary>
	/// <param name="normal_">The surface normal.</param>
	/// <returns>Reflection vector of specified normal</returns>
	constexpr BaseVector2<ValueType> reflect(BaseVector2<ValueType> const & normal_) const
	{
		auto normal = normal_.normalize();
		return (*this) - (normal * normal.dot(*this) * ValueType{ 2 });
	}
			
	/// <summary>
	/// Computes reflection vector of specified normal and assigns it to self.
	/// </summary>
	/// <param name="normal_">The normal.</param>
	/// <returns>Reference to self after computing reflection of specified normal.</returns>	
	constexpr BaseVector2<ValueType>& reflectSelf(BaseVector2<ValueType> const & normal_)
	{
		auto normal = normal_.normalize();
		*this -= normal * normal.dot(*this) * ValueType{ 2 };
		return *this;
	}
			
	/// <summary>
	/// Computes normalized vector.
	/// </summary>
	/// <returns>Normalized vector</returns>
	constexpr BaseVector2<ValueType> normalize() const
	{
		auto len = this->template length<ValueType>();
		if (len != 0)
		{
			return BaseVector2<ValueType>{ x / len, y / len };
		}
		return *this;
	}
			
	/// <summary>
	/// Normalizes self and returns reference.
	/// </summary>
	/// <returns>Reference to normalized self.</returns>
	constexpr BaseVector2<ValueType>& normalizeSelf()
	{
		auto len = this->template length<ValueType>();
		if (len != 0)
		{
			x /= len; y /= len;
		}
		return *this;
	}

	// yet non-constexpr
	/// <summary>
	/// Converts vector to string.
	/// </summary>
	/// <param name="setup_">The string building setup.</param>
	/// <returns>Vector converted to std::string.</returns>
	std::string toString(VectorStringBuilder const & setup_ = VectorStringBuilder{}) const
	{
		std::stringstream stream;
		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round:		{ stream << "( "; break; }
		case VectorStringBuilder::Wrap::Square:	{ stream << "[ "; break; }
		case VectorStringBuilder::Wrap::Curly:		{ stream << "{ "; break; }
		default: break;
		}

		if (setup_.mantissaFixed)
			stream << std::fixed;
		
		stream.precision(setup_.precision);

		switch (setup_.compVisibility)
		{
		case VectorStringBuilder::CompVisibility::WithColon: {
			stream	<< "x: " << x << setup_.separator << ' '
					<< "y: " << y;
			break;
		}
		case VectorStringBuilder::CompVisibility::WithEqual: {
			stream	<< "x = " << x << setup_.separator << ' '
					<< "y = " << y;
			break;
		}
		default: {
			stream << x << setup_.separator << ' ' << y;
			break;
		}
		}

		switch (setup_.wrap)
		{
		case VectorStringBuilder::Wrap::Round:		{ stream << " )"; break; }
		case VectorStringBuilder::Wrap::Square:		{ stream << " ]"; break; }
		case VectorStringBuilder::Wrap::Curly:		{ stream << " }"; break; }
		default: break;
		}
		return stream.str();
	}

	/// <summary>
	/// Checks if two vectors are equal.
	/// </summary>
	/// <param name="other_">The other vector.</param>
	/// <param name="EqualityTolerance">The equality tolerance.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename VectorType2, typename EqualityType = ValueType,
				typename = std::enable_if_t< std::is_floating_point_v<EqualityType> > >
	constexpr bool equals(BaseVector2<VectorType2> const & other_, EqualityType const equalityTolerance_ = Math::Constants::LowTolerance<EqualityType>) const
	{
		return (
			std::abs(static_cast<EqualityType>(x) - static_cast<EqualityType>(other_.x)) <= equalityTolerance_ &&
			std::abs(static_cast<EqualityType>(y) - static_cast<EqualityType>(other_.y)) <= equalityTolerance_
		);
	}

	/// <summary>
	/// Computes lower bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components { x = min(lhs_.x, rhs_.x), y = min(lhs_.y, rhs_.y) }</returns>
	constexpr static BaseVector2<ValueType> lowerBounds(BaseVector2<ValueType> const & lhs_, BaseVector2<ValueType> const & rhs_)
	{
		return BaseVector2<ValueType>{
			std::min(lhs_.x, rhs_.x),
			std::min(lhs_.y, rhs_.y)
		};
	}

	/// <summary>
	/// Computes upper bound vector of the two specified.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Vector with components { x = max(lhs_.x, rhs_.x), y = max(lhs_.y, rhs_.y) }</returns>
	constexpr static BaseVector2<VectorType> upperBounds(BaseVector2<ValueType> const & lhs_, BaseVector2<ValueType> const & rhs_)
	{
		return BaseVector2<ValueType>{
			std::max(lhs_.x, rhs_.x),
			std::max(lhs_.y, rhs_.y)
		};
	}

	/// <summary>
	/// Computes lower and upper bounds for two specified vectors.
	/// </summary>
	/// <param name="lower_">The lower bound vector.</param>
	/// <param name="upper_">The upper bound vecor.</param>
	/// <remarks>
	/// <para>Uses arguments as output, changes its values.</para>
	/// </remarks>
	constexpr static void bounds(BaseVector2<ValueType> & lower_, BaseVector2<ValueType> & upper_)
	{
		BaseVector2<ValueType> tempMin = lower_;
		lower_ = BaseVector2<ValueType>::lowerBounds(lower_, upper_);
		upper_ = BaseVector2<ValueType>::upperBounds(tempMin, upper_);
	}
			
	/// <summary>
	/// Converts vector to other type.
	/// </summary>
	/// <returns>Vector of other value type.</returns>
	template <typename VectorType2>
	constexpr BaseVector2<VectorType2> convert() const {
		return BaseVector2<VectorType2>{
			static_cast<VectorType2>(x),
			static_cast<VectorType2>(y)
		};
	}

			
	//////////////////////////////////////
	// Operators:
	//////////////////////////////////////

	/// <summary>
	/// Returns component with specified index by ref.
	/// </summary>
	/// <param name="index_">The component index (either 0 or 1).</param>
	/// <returns>Component with specified index by ref.</returns>
	constexpr ValueType& operator[](std::size_t const index_) {
		// # Assertion note:
		// You tried to evaluate Vector2[ >= 2], which would cause memory corruption. Fix your code.
		assert(index_ < 2);
		switch (index_) {
		case 0: { return x; break; }
		case 1: { return y; break; }
		default: throw std::out_of_range{ "Vector2 class has 2 components - x (id 0), y (id 1)!" };
		}
	}
	
	/// <summary>
	/// Returns component with specified index by value.
	/// </summary>
	/// <param name="index_">The component index (either 0 or 1).</param>
	/// <returns>Component with specified index by value.</returns>
	constexpr ValueType operator[](std::size_t const index_) const {
		// # Assertion note:
		// You tried to evaluate Vector2[ >= 2], which would cause memory corruption. Fix your code.
		assert(index_ < 2);
		switch (index_) {
		case 0: { return x; break; }
		case 1: { return y; break; }
		default: throw std::out_of_range{ "Vector2 class has 2 components - x (id 0), y (id 1)!" };
		}
	}

	/// <summary>
	/// Assigns vector to self.
	/// </summary>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self.</returns>
	constexpr BaseVector2<ValueType> & operator = (BaseVector2<ValueType> const & rhs_) {
		x = rhs_.x;
		y = rhs_.y;
		return *this;
	}
			
	/// <summary>
	/// Negates vector.
	/// </summary>
	/// <returns>Negated vector.</returns>
	constexpr BaseVector2<ValueType> operator - () const {
		return BaseVector2<ValueType>{-x, -y};
	}

	/// <summary>
	/// Checks if lhs vector is equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename VectorType2>
	constexpr bool operator == (BaseVector2<VectorType2> const & rhs_) const {
		return equals(rhs_);
	}

	/// <summary>
	/// Checks if lhs vector is not equal to rhs vector (with low tolerance).
	/// </summary>
	/// <param name="rhs_">The other vector.</param>
	/// <returns>
	///  <c>true</c> if vectors are not equal; otherwise, <c>false</c>.
	/// </returns>
	template <typename VectorType2>
	constexpr bool operator != (BaseVector2<VectorType2> const & rhs_) const {
		return !equals(rhs_);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector2<ValueType>& operator += (BaseVector2<ValueType> const & rhs_)
	{
		x += rhs_.x;
		y += rhs_.y;
		return *this;
	}

	/// <summary>
	/// Subtracts rhs vector from lhs one.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self after operation.</returns>
	constexpr BaseVector2<ValueType>& operator -= (BaseVector2<ValueType> const & rhs_) {
		x -= rhs_.x;
		y -= rhs_.y;
		return *this;
	}

	/// <summary>
	/// Multiplies two vectors.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector2<ValueType>& operator *= (BaseVector2<ValueType> const & rhs_) {
		x *= rhs_.x;
		y *= rhs_.y;
		return *this;
	}

	/// <summary>
	/// Adds two vectors together.
	/// </summary>
	/// <param name="lhs_">The lhs vector.</param>
	/// <param name="rhs_">The rhs vector.</param>
	/// <returns>Reference to self, after operation.</returns>
	constexpr BaseVector2<ValueType>& operator /= (BaseVector2<ValueType> const & rhs_) {
		x /= rhs_.x;
		y /= rhs_.y;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// Adds scalar to a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector plus a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator += (ValueType const rhs_) {
		x += rhs_;
		y += rhs_;
		return *this;
	}

	/// <summary>
	/// Substracts scalar from a vector.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector minus a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator -= (ValueType const rhs_) {
		x -= rhs_;
		y -= rhs_;
		return *this;
	}

	/// <summary>
	/// Multiplies vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector times a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator *= (ValueType const rhs_) {
		x *= rhs_;
		y *= rhs_;
		return *this;
	}

	/// <summary>
	/// Divides vector by a scalar.
	/// </summary>
	/// <param name="rhs_">The scalar.</param>
	/// <returns>Vector divided by a scalar.</returns>
	constexpr BaseVector2<ValueType>& operator /= (ValueType const rhs_) {
		x /= rhs_;
		y /= rhs_;
		return *this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		lhs_.x + rhs_.x,
		lhs_.y + rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator - (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		lhs_.x - rhs_.x,
		lhs_.y - rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		lhs_.x * rhs_.x,
		lhs_.y * rhs_.y
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator / (BaseVector2<VectorType> const & lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		lhs_.x / rhs_.x,
		lhs_.y / rhs_.y
	};
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs vector <op> rhs scalar).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (BaseVector2<VectorType> const & lhs_, VectorType const rhs_)
{
	return {
		lhs_.x + rhs_,
		lhs_.y + rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator - (BaseVector2<VectorType> const & lhs_, VectorType const rhs_)
{
	return {
		lhs_.x - rhs_,
		lhs_.y - rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (BaseVector2<VectorType> const & lhs_, VectorType const rhs_)
{
	return {
		lhs_.x * rhs_,
		lhs_.y * rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator / (BaseVector2<VectorType> const & lhs_, VectorType const rhs_)
{
	return {
		lhs_.x / rhs_,
		lhs_.y / rhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Operators (lhs scalar <op> rhs vector).
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator + (VectorType const lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		rhs_.x + lhs_,
		rhs_.y + lhs_
	};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename VectorType>
constexpr BaseVector2<VectorType> operator * (VectorType const lhs_, BaseVector2<VectorType> const & rhs_)
{
	return {
		rhs_.x * lhs_,
		rhs_.y * lhs_
	};
}

// 2D Vector class templated with float
using Vector2f		= BaseVector2<float>;
// 2D Vector class templated with float
using Vector2		= BaseVector2<float>;
// 2D Vector class templated with double
using Vector2d		= BaseVector2<double>;
// 2D Vector class templated with std::int16_t
using Vector2i16	= BaseVector2<std::int16_t>;
// 2D Vector class templated with std::int32_t
using Vector2i32	= BaseVector2<std::int32_t>;
// 2D Vector class templated with std::int64_t
using Vector2i64	= BaseVector2<std::int64_t>;
// 2D Vector class templated with std::uint16_t
using Vector2u16	= BaseVector2<std::uint16_t>;
// 2D Vector class templated with std::uint32_t
using Vector2u32	= BaseVector2<std::uint32_t>;
// 2D Vector class templated with std::uint64_t
using Vector2u64	= BaseVector2<std::uint64_t>;

// 2D Vector class templated with std::size_t
using Vector2size	= BaseVector2<std::size_t>;

} // namespace agdk
