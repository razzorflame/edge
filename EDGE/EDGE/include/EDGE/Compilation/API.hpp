#pragma once

#ifdef EDGE_STATIC
	// Make sure SFML and GLEW are also statically linked.
	#ifndef SFML_STATIC
		#define SFML_STATIC
	#endif
	#ifndef GLEW_STATIC
		#define GLEW_STATIC
	#endif
	#define EDGE_API
#else
	// Make sure SFML and GLEW are also dynamically linked
	#ifdef SFML_STATIC
		#undef SFML_STATIC
	#endif
	#ifdef GLEW_STATIC
		#undef GLEW_STATIC
	#endif

	#ifdef _MSC_VER
		#ifdef EDGE_ACTIVE_PROJECT
			#define EDGE_API __declspec(dllexport)
		#else
			#define EDGE_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__)
		#ifdef EDGE_ACTIVE_PROJECT
			#define EDGE_API __attribute__((visibility("default")))
		#else
			#define EDGE_API
		#endif	
	#else
		#pragma message "Warning: Your compiler does not support exporting / importing symbols from shared library."
	#endif
#endif
