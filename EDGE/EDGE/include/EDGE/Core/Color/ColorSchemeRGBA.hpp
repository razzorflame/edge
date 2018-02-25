#pragma once

#include EDGE_PCH

#include <EDGE/Core/TypeTraits.hpp>
#include <EDGE/Core/Color/ColorHelper.hpp>

namespace edge
{

template <typename _valueType, _valueType _mappedMax>
class ColorSchemeRGBA
{
	constexpr static std::array<_valueType, 4> fromUint32(std::uint32_t const color_) {
		return std::array<_valueType, 4>{
			static_cast<_valueType>( (color_ >> (3 * 8)) * _mappedMax)				/ 255,
			static_cast<_valueType>(((color_ << (1 * 8)) >> (3 * 8)) * _mappedMax)	/ 255,
			static_cast<_valueType>(((color_ << (2 * 8)) >> (3 * 8)) * _mappedMax)	/ 255,
			static_cast<_valueType>(((color_ << (3 * 8)) >> (3 * 8)) * _mappedMax)	/ 255
		};
	}

public:
	// Helper typedefs:
	using ValueType		= _valueType;
	using SizeType		= std::size_t;
	
	// Max value constant:
	static constexpr ValueType		MappedMax			= _mappedMax;
	static constexpr std::size_t	NumberOfChannels	= 4;

	// Components:
	ValueType r, g, b, a;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="ColorSchemeRGBA{_valueType, _mappedMax}"/> struct.
	/// </summary>
	constexpr ColorSchemeRGBA()
		: r{ 0 }, g{ 0 }, b{ 0 }, a{ MappedMax }
	{
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="ColorSchemeRGBA{_valueType, _mappedMax}"/> struct.
	/// </summary>
	constexpr ColorSchemeRGBA(std::uint32_t const color_)
	{
		auto channels = fromUint32(color_);
		for (std::size_t i = 0; i < NumberOfChannels; i++)
			this->operator[i] = channels[i];
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="ColorSchemeRGBA{_valueType, _mappedMax}"/> struct.
	/// </summary>
	constexpr ColorSchemeRGBA(ValueType const r_, ValueType const g_, ValueType const b_, ValueType const a_ = MappedMax)
	{
		// Note: not using initializer list here with purpose. `set` is macro-dependent.
		set(r_, g_, b_, a_);
	}
	
	/// <summary>
	/// Sets color from specified parameters.
	/// </summary>
	/// <param name="r_">The red channel value.</param>
	/// <param name="g_">The green channel value.</param>
	/// <param name="b_">The blue channel value.</param>
	/// <param name="a_">The alpha channel value.</param>
	constexpr void set(ValueType const r_, ValueType const g_, ValueType const b_, ValueType const a_ = MappedMax)
	{
		// Protect from setting invalid values (only in Debug mode).
		// Note: see EDGE Documentation -> Debug vs Release to view other occurrences of debug protecting.
	#if defined(EDGE_DEBUG) or defined(EDGE_PROTECT_NONDEBUG)
		r = std::min(r_, MappedMax); g = std::min(g_, MappedMax);
		b = std::min(b_, MappedMax); a = std::min(a_, MappedMax);
	#else
		r = r_; g = g_; b = b_; a = a_;
	#endif
	}
	
	/// <summary>
	/// Returns value of channel with specified index by value.
	/// </summary>
	/// <param name="index_">The index.</param>
	/// <returns>Value of channel with specified index by value.</returns>
	constexpr ValueType operator[](SizeType const index_) const {
		assert(index_ <= 3);
		switch (index_) {
		case 0: { return r; break; }
		case 1: { return g; break; }
		case 2: { return b; break; }
		case 3: { return a; break; }
		}
	}

	/// <summary>
	/// Returns value of channel with specified index by ref.
	/// </summary>
	/// <param name="index_">The index.</param>
	/// <returns>Value of channel with specified index by ref.</returns>
	constexpr ValueType& operator[](SizeType const index_) {
		assert(index_ <= 3);
		switch (index_) {
		case 0: { return r; break; }
		case 1: { return g; break; }
		case 2: { return b; break; }
		case 3: { return a; break; }
		}
	}

	/// <summary>
	/// Converts this color to another scheme.
	/// </summary>
	/// <returns>Color converted to specified scheme.</returns>
	template <typename _targetValueType,
			template<typename, _targetValueType> typename _targetScheme,
			_targetValueType _targetMax = static_cast<_targetValueType>(MappedMax) >		
	constexpr _targetScheme<_targetValueType, _targetMax> convert() const
	{
		constexpr _targetValueType mappedMaxRatio = _targetMax / static_cast<_targetValueType>(MappedMax);
		return _targetScheme<_targetValueType, _targetMax>::fromRGBA(
			static_cast<_targetValueType>(r * mappedMaxRatio),
			static_cast<_targetValueType>(g * mappedMaxRatio),
			static_cast<_targetValueType>(b * mappedMaxRatio),
			static_cast<_targetValueType>(a * mappedMaxRatio) );
	}

	/// <summary>
	/// Computes lazy average color from specified colors.
	/// </summary>
	/// <param name="first_">The first color.</param>
	/// <param name="restColors_">Rest of the colors.</param>
	/// <returns>Lazy average color from specified colors.</returns>
	template <typename... _colors>
	static constexpr ColorSchemeRGBA lazyAverage(ColorSchemeRGBA const & first_, _colors&&... restColors_)
	{
		using MaxType = make_widest_t<ValueType>;
		MaxType avg[NumberOfChannels];

		for (std::size_t i = 0; i < NumberOfChannels; i++) {
			avg[i] += first_[i];
			avg[i] += (... + restColors_[i]); // unfold.

			// Divide by number of elements:
			avg[i] /= (1 + sizeof...(_colors));
		}
		return ColorSchemeRGBA{
			static_cast<ValueType>(sum[0]),
			static_cast<ValueType>(sum[1]),
			static_cast<ValueType>(sum[2]),
			static_cast<ValueType>(sum[3]) };
	}

	/// <summary>
	/// Computes average color from specified colors.
	/// </summary>
	/// <param name="first_">The first color.</param>
	/// <param name="restColors_">Rest of the colors.</param>
	/// <returns>Average color from specified colors.</returns>
	template <typename... _colors>
	static constexpr ColorSchemeRGBA average(ColorSchemeRGBA const & first_, _colors&&... restColors_)
	{
		// Note: this kind of averaging gives better results, because human brain considers brightness logarithmically.
		// This algorithm uses average of squared components and then takes square root to get final result.

		using MaxType = make_widest_t<ValueType>;
		MaxType avg[NumberOfChannels];
		
		for (std::size_t i = 0; i < NumberOfChannels; i++) {
			avg[i] += (first_[i] * first_[i]);
			avg[i] += (... + (restColors_[i] * restColors_[i])); // unfold.

			// Divide by number of elements and take square root.
			avg[i] = std::sqrt(avg[i] / (1 + sizeof...(_colors)));
		}
		return ColorSchemeRGBA{
			static_cast<ValueType>(avg[0]),
			static_cast<ValueType>(avg[1]),
			static_cast<ValueType>(avg[2]),
			static_cast<ValueType>(avg[3]) };
	}

	/// <summary>
	/// Blends current color with lazy average of others specifed.
	/// </summary>
	/// <param name="alpha_">The alpha.</param>
	/// <param name="otherColor_">The other color.</param>
	/// <param name="restColors_">Rest of the colors.</param>
	/// <returns>Current color blended with lazy average of others specifed.</returns>
	template <typename... _colors>
	constexpr ColorSchemeRGBA lazyBlend(double alpha_,
		ColorSchemeRGBA const & otherColor_, _colors&&... restColors_) const
	{
		auto avg = lazyAverage(otherColor_, std::forward<_colors>(restColors_)...);
		alpha_ = std::min(1.0, alpha_);

		ColorSchemeRGBA result;

		for (std::size_t i = 0; i < NumberOfChannels; i++) {
			result[i] = (this->operator[i] * (1.0 - alpha_) + avg[i] * alpha_);
		}
		return result;
	}

	/// <summary>
	/// Blends current color with average of others specifed.
	/// </summary>
	/// <param name="alpha_">The alpha.</param>
	/// <param name="otherColor_">The other color.</param>
	/// <param name="restColors_">Rest of the colors.</param>
	/// <returns>Current color blended with average of others specifed.</returns>
	template <typename... _colors>
	constexpr ColorSchemeRGBA blend(double alpha_,
		ColorSchemeRGBA const & otherColor_, _colors&&... restColors_) const
	{
		auto avg = average(otherColor_, std::forward<_colors>(restColors_)...);
		alpha_ = std::min(1.0, alpha_);

		ColorSchemeRGBA result;

		for (std::size_t i = 0; i < NumberOfChannels; i++) {
			result[i] = (this->operator[i] * (1.0 - alpha_) + avg[i] * alpha_);
		}
		return result;
	}



	// Conversions:

	/// <summary>
	/// Sets color RGBA values.
	/// </summary>
	/// <param name="r_">The red channel value.</param>
	/// <param name="g_">The green channel value.</param>
	/// <param name="b_">The blue channel value.</param>
	/// <param name="a_">The alpha channel value.</param>
	constexpr static ColorSchemeRGBA fromRGBA(ValueType const r_, ValueType const g_, ValueType const b_, ValueType const a_)
	{
		return ColorSchemeRGBA{ r_, g_, b_, a_ };
	}

	/// <summary>
	/// Creates RGBA color from ARGB values.
	/// </summary>
	/// <param name="a_">The alpha channel value.</param>
	/// <param name="r_">The red channel value.</param>
	/// <param name="g_">The green channel value.</param>
	/// <param name="b_">The blue channel value.</param>
	constexpr static ColorSchemeRGBA fromARGB(ValueType const a_, ValueType const r_, ValueType const g_, ValueType const b_)
	{
		return ColorSchemeRGBA{ r_, g_, b_, a_ };
	}

	/// <summary>
	/// Creates RGBA color from RGB values.
	/// </summary>
	/// <param name="r_">The red channel value.</param>
	/// <param name="g_">The green channel value.</param>
	/// <param name="b_">The blue channel value.</param>
	constexpr static ColorSchemeRGBA fromRGB(ValueType const r_, ValueType const g_, ValueType const b_)
	{
		return ColorSchemeRGBA{ r_, g_, b_ };
	}

	/// <summary>
	/// Creates RGBA color from HSV[ - : &lt;360: 1 ] values.
	/// </summary>
	/// <param name="hue_">The hue channel value.</param>
	/// <param name="saturation_">The saturation channel value.</param>
	/// <param name="value_">The value channel value.</param>
	constexpr static ColorSchemeRGBA fromHSV(ValueType const hue_, ValueType const saturation_, ValueType const value_)
	{
		ColorSchemeRGBA color{};
		colors::convertHSVtoRGB(hue_, saturation_, value_, &color.r, &color.g, &color.b);
		
		color.r *= MappedMax;
		color.g *= MappedMax;
		color.b *= MappedMax;
		color.a = MappedMax;
		return color;
	}

};

}
