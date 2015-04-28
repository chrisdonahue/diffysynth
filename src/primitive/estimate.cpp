#include "estimate.hpp"

using namespace diffysynth;

primitive::estimate::estimate() :
	base("estimate")
{};

type::diff primitive::estimate::evaluate(estimator::base::state& es) {
	base::evaluate(es);

	return value::diff_zero;
};