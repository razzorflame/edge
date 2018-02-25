#pragma once

namespace edge
{
/// <summary>
/// Interface for every non-copyable class.
/// </summary>
class INonInstantiable {
public:	
	/// <summary>
	/// Prevents instantiation of the <see cref="INonInstantiable"/> class.
	/// </summary>
	INonInstantiable() = delete;
};

} // namespace edge
