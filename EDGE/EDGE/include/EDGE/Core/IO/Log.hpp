#pragma once

#include EDGE_PCH

namespace edge
{

/// <summary>
/// Specifies logged message type.
/// </summary>
enum class EDGE_API LogMessage {
	Default = 0,
	Notice,
	Warning,
	Error,
	FatalError
};

/// <summary>
/// Base class for every log.
/// </summary>
template <typename _valueType>
class EDGE_API BasicLogInterface
{
public:

	using ValueType			= _valueType;
	using StringType		= std::basic_string<ValueType>;
	using StringViewType	= std::basic_string_view<ValueType>;
	using StreamType		= std::basic_ostream<ValueType>;

	/// <summary>
	/// Initializes a new instance of the <see cref="Log"/> class.
	/// </summary>
	/// <param name="output_">The output stream.</param>
	BasicLogInterface(StreamType *output_ = nullptr)
		: m_output{ output_ }
	{
	}
	
	/// <summary>
	/// Pushes the specified message to the stream.
	/// </summary>
	/// <param name="message_">The message.</param>
	void push(StringViewType const message_, bool const flush_ = true)
	{
		if (m_output) {
			(*m_output) << message_;
			if (flush_)
				m_output->flush();
		}
	}
	
	/// <summary>
	/// Flushes the buffer.
	/// </summary>
	void flush() {
		if (m_output) {
			m_output->flush();
		}
	}

private:
	StreamType *m_output;
};

/// <summary>
/// Class for logging debug info. In release mode implementation is empty.
/// </summary>
/// <seealso cref="LogInterface" />
template <typename _valueType>
class BasicDebugLogInterface
	: public BasicLogInterface<_valueType>
{
public:
	using super				= BasicLogInterface<_valueType>;

	using ValueType			= _valueType;
	using StringType		= std::basic_string<ValueType>;
	using StringViewType	= std::basic_string_view<ValueType>;
	using StreamType		= std::basic_ostream<ValueType>;


	// Default constructor is the same.
	using super::BasicLogInterface;

	void pushDebug(StringViewType const message_, bool const flush_ = true)
	{
	#ifdef EDGE_DEBUG
		using namespace std::string_view_literals;

		if constexpr (std::is_same_v<ValueType, char>)
			this->push("[ DEBUG ]: ", false);
		else if constexpr (std::is_same_v<ValueType, wchar_t>)
			this->push(L"[ DEBUG ]: ", false);
		else if constexpr (std::is_same_v<ValueType, char16_t>)
			this->push(u"[ DEBUG ]: ", false);
		else if constexpr (std::is_same_v<ValueType, char32_t>)
			this->push(U"[ DEBUG ]: ", false);
		else
			static_assert(false, "This string type is not supported.");

		this->push(message_, flush);
	#endif
	}
};

using LogInterface			= BasicLogInterface<std::string::value_type>;
using LogInterfaceW			= BasicLogInterface<std::wstring::value_type>;
using LogInterfaceU16		= BasicLogInterface<std::u16string::value_type>;
using LogInterfaceU32		= BasicLogInterface<std::u32string::value_type>;

using DebugLogInterface		= BasicDebugLogInterface<std::string::value_type>;
using DebugLogInterfaceW	= BasicDebugLogInterface<std::wstring::value_type>;
using DebugLogInterfaceU16	= BasicDebugLogInterface<std::u16string::value_type>;
using DebugLogInterfaceU32	= BasicDebugLogInterface<std::u32string::value_type>;

}
