#pragma once

#include EDGE_PCH

namespace edge
{

/// <summary>
/// If character in std::istream is what expected skip this character else set fail flag.
/// </summary>
template <char _character>
inline std::istream& expect(std::istream& in)
{
	if ((in >> std::ws).peek() == _character) {
		in.ignore();
	}
	else {
		in.setstate(std::ios_base::failbit);
	}
	return in;
}

}
