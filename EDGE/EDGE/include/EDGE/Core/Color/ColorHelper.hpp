#pragma once

#include EDGE_PCH

namespace edge::color
{

/// <summary>
/// Converts color in HSV[ - : <360 : 1 ] format to RGB[ - : 1 ] format.
/// </summary>
/// <param name="hue_">The HSV hue component (range: 0 to &lt;360).</param>
/// <param name="sat_">The HSV saturation component (range: 0 to 1).</param>
/// <param name="value_">The HSV value component (range: 0 to 1).</param>
/// <param name="red_">[out] The red component (range: 0 to 1).</param>
/// <param name="green_">[out] The green component (range: 0 to 1).</param>
/// <param name="blue_">[out] The blue component (range: 0 to 1).</param>
template <typename _floatType>
void convertHSVtoRGB(_floatType const hue_, _floatType const sat_, _floatType const value_, _floatType& red_, _floatType& green_, _floatType& blue_)
{
	using type = _floatType;

	assert(hue_ >= 0 && hue < 360);

	type chroma	= value_ * sat_;
	type x		= chroma * (type{ 1 } - std::abs(std::fmod(hue_ / type{ 60 }, type{ 2 }) - type{ 1 }));
	type m		= value_ - chroma;

	if (hue_ >= type{ 0 } && hue_ < type{ 60 }) {
		red_ = chroma; green_ = x; blue_ = 0;
	}
	else if (hue_ >= type{ 60 } && hue_ < type{ 120 }) {
		red_ = x; green_ = chroma; blue_ = 0;
	}
	else if (hue_ >= type{ 120 } && hue_ < type{ 180 }) {
		red_ = 0; green_ = chroma; blue_ = x;
	}
	else if (hue_ >= type{ 180 } && hue_ < type{ 240 }) {
		red_ = 0; green_ = x; blue_ = chroma;
	}
	else if (hue_ >= type{ 240 } && hue_ < type{ 300 }) {
		red_ = x; green_ = 0; blue_ = chroma;
	}
	else if (hue_ >= type{ 300 } && hue_ < type{ 360 }) {
		red_ = chroma; green_ = 0; blue_ = x;
	}
	else { red_ = 0; green_ = 0;blue_ = 0; }

	red_ += m; green_ += m; blue_ += m;
}

/// <summary>
/// Converts color in RGB[ - : 255 ] format to HSV[ - : <360 : 1 ] format.
/// </summary>
/// <param name="red_">The red component (range: 0 to 255).</param>
/// <param name="green_">The green component (range: 0 to 255).</param>
/// <param name="blue_">The blue component (range: 0 to 255).</param>
/// <param name="hue_">[out] The HSV hue component (range: 0 to &lt;360).</param>
/// <param name="sat_">[out] The HSV saturation component (range: 0 to 1).</param>
/// <param name="value_">[out] The HSV value component (range: 0 to 1).</param>
template <typename _floatType>
void convertRGBtoHSV(_floatType const red_, _floatType const green_, _floatType const blue_, _floatType& hue_, _floatType& sat_, _floatType& value_)
{
	auto normalizedRed		= red_ / 255;
	auto normalizedGreen	= green_ / 255;
	auto normalizedBlue		= blue_ / 255;
	auto chromaMax = std::max({ normalizedRed, normalizedGreen, normalizedBlue });
	auto chromaMin = std::min({ normalizedRed, normalizedGreen, normalizedBlue });
	auto delta = chromaMax - chromaMin;

	if (delta == 0) {
		hue_ = 0;
	}
	else if (chromaMax == normalizedRed) {
		hue_ = ( std::fmod((normalizedGreen - normalizedBlue) / delta, 6) ) * 60;
	}
	else if (chromaMax == normalizedGreen) {
		hue_ = ( (normalizedBlue - normalizedRed) / delta + 2 ) * 60;
	}
	else if (chromaMax == normalizedBlue) {
		hue_ = ( (normalizedRed - normalizedGreen) / delta + 4 ) * 60;
	}

	if (chromaMax == 0)
		sat_ = 0;
	else
		sat_ = delta / chromaMax;

	value_ = chromaMax;
}

} // namespace edge::color