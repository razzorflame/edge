#pragma once

#ifdef EDGE_STATIC
	// Make sure SFML is also statically linked.
	#ifndef SFML_STATIC
		#define SFML_STATIC
	#endif
	#define EDGE_API
#else
	// Make sure SFML is also dynamically linked
	#ifdef SFML_STATIC
		#undef SFML_STATIC
	#endif

	#ifdef EDGE_ACTIVE_PROJECT
		#define EDGE_API __declspec(dllexport)
	#else
		#define EDGE_API __declspec(dllimport)
	#endif
#endif
