#ifndef CDSP_TYPE
#define CDSP_TYPE

#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>

#include "define.hpp"

namespace diffysynth { namespace type {
	typedef uint32_t disc_32_u;
	typedef uint64_t disc_64_u;
	typedef int32_t disc_32;
	typedef int64_t disc_64;
	typedef float cont_32;
	typedef double cont_64;
	typedef bool boolean;
#ifdef DIFFYSYNTH_RESOLUTION_64
	typedef cont_64 diff;
#else
	typedef cont_32 diff;
#endif
	typedef cont_64 time;
	typedef std::string string;
	typedef disc_64_u specifier;
}}

#endif
