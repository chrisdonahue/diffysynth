#ifndef DIFFYSYNTH_VALUE
#define DIFFYSYNTH_VALUE

#include <limits>

#include "define.hpp"
#include "type.hpp"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace diffysynth { namespace value {
	// pi
	const type::cont_64 pi_64					= 3.1415926535897932384626433832795028841971693993751;
	const type::cont_32 pi_32					= 3.14159265358979f;
	const type::cont_64 two_pi_64				= 6.2831853071795864769252867665590057683943387987502;
	const type::cont_32 two_pi_32				= 6.283185307179586f;

	// zero
	const type::cont_32 zero_32				= 0.0f;
	const type::cont_64 zero_64				= 0.0;

	// one
	const type::cont_32 one_32					= 1.0f;
	const type::cont_64 one_64					= 1.0;

	// infinity
	const type::cont_32 infinity_n_32			= -1.0f * std::numeric_limits<type::cont_32>::infinity();
	const type::cont_32 infinity_32			= std::numeric_limits<type::cont_32>::infinity();
	const type::cont_64 infinity_n_64			= -1.0f * std::numeric_limits<type::cont_64>::infinity();
	const type::cont_64 infinity_64			= std::numeric_limits<type::cont_64>::infinity();

	// nan
#ifdef DIFFYSYNTH_DEBUG_DSP
	const type::cont_32 nan_32					= std::numeric_limits<type::cont_32>::signaling_NaN();
	const type::cont_64 nan_64					= std::numeric_limits<type::cont_64>::signaling_NaN();
#else
	const type::cont_32 nan_32					= std::numeric_limits<type::cont_32>::quiet_NaN();
	const type::cont_64 nan_64					= std::numeric_limits<type::cont_64>::quiet_NaN();
#endif

	const type::time time_zero					= static_cast<type::time>(0.0);

#ifdef DIFFYSYNTH_RESOLUTION_64
	const type::diff diff_zero					= static_cast<type::diff>(0.0);
#elif DIFFYSYNTH_SAMPLE_32
#endif

	const type::fitness fitness_unassigned = static_cast<type::fitness>(-1.0);
	const type::fitness fitness_infinity = static_cast<type::fitness>(value::infinity_64);
	const type::fitness fitness_infinity_n = static_cast<type::fitness>(value::infinity_n_64);

}}

#endif