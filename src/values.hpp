#ifndef DIFFYSYNTH_VALUE
#define DIFFYSYNTH_VALUE

#include <limits>

#include "define.hpp"
#include "types.hpp"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace diffysynth { namespace values {
	// pi
	const types::cont_64 pi_64					= 3.1415926535897932384626433832795028841971693993751;
	const types::cont_32 pi_32					= 3.14159265358979f;
	const types::cont_64 two_pi_64				= 6.2831853071795864769252867665590057683943387987502;
	const types::cont_32 two_pi_32				= 6.283185307179586f;

	// zero
	const types::cont_32 zero_32				= 0.0f;
	const types::cont_64 zero_64				= 0.0;

	// one
	const types::cont_32 one_32					= 1.0f;
	const types::cont_64 one_64					= 1.0;

	// infinity
	const types::cont_32 infinity_n_32			= -1.0f * std::numeric_limits<types::cont_32>::infinity();
	const types::cont_32 infinity_32			= std::numeric_limits<types::cont_32>::infinity();
	const types::cont_64 infinity_n_64			= -1.0f * std::numeric_limits<types::cont_64>::infinity();
	const types::cont_64 infinity_64			= std::numeric_limits<types::cont_64>::infinity();

	// nan
#ifdef DIFFYSYNTH_DEBUG_DSP
	const types::cont_32 nan_32					= std::numeric_limits<types::cont_32>::signaling_NaN();
	const types::cont_64 nan_64					= std::numeric_limits<types::cont_64>::signaling_NaN();
#else
	const types::cont_32 nan_32					= std::numeric_limits<types::cont_32>::quiet_NaN();
	const types::cont_64 nan_64					= std::numeric_limits<types::cont_64>::quiet_NaN();
#endif

	// channels
	const types::channel channel_zero			= static_cast<types::channel>(0);
	const types::channel channel_max	 		= std::numeric_limits<types::channel>::max();

	// index
	const types::index index_zero				= static_cast<types::index>(0);

	// boolean
	const types::boolean boolean_true			= static_cast<types::boolean>(true);
	const types::boolean boolean_false			= static_cast<types::boolean>(false);

	const types::time time_zero					= static_cast<types::time>(0.0);

#ifdef DIFFYSYNTH_RESOLUTION_64
	const types::diff differential_zero			= static_cast<types::differential>(0.0);
#elif DIFFYSYNTH_SAMPLE_32
#endif
}}

#endif