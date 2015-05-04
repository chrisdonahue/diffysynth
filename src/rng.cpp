#include "rng.hpp"

using namespace diffysynth;

rng::rng(type::disc_32 seed) :
	engine(seed)
{};

template <typename T>
T rng::uniform<T>(T min_inclusive, T max_inclusive) {
	throw exception::runtime("unknown type");
};

template <>
type::disc_32 rng::uniform(type::disc_32 min_inclusive, type::disc_32 max_inclusive) {
	std::uniform_int_distribution<type::disc_32> distribution(min_inclusive, max_inclusive);
	return distribution(engine);
};

template <>
type::cont_64 rng::uniform(type::cont_64 min_inclusive, type::cont_64 max_inclusive) {
	std::uniform_real_distribution<type::cont_64> distribution(min_inclusive, max_inclusive);
	return distribution(engine);
};

type::cont_64 rng::uniform_unit() {
	std::uniform_real_distribution<type::cont_64> distribution(value::zero_64, value::one_64);
	return distribution(engine);
};