#ifndef DIFFYSYNTH_RNG
#define DIFFYSYNTH_RNG

#include <random>

#include "define.hpp"
#include "exception.hpp"
#include "type.hpp"
#include "value.hpp"

namespace diffysynth {
	class rng {
	public:
		rng(type::disc_32 seed);

		template <typename T> T uniform(T min_inclusive, T max_inclusive);
		type::cont_64 uniform_unit();

	private:
		std::default_random_engine engine;
	};
}

#endif