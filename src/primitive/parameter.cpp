#include "parameter.hpp"

using namespace diffysynth;

primitive::parameter::parameter() :
base("parameter")
{};

type::diff primitive::parameter::evaluate(estimator::base::state& es) {
	base::evaluate(es);

	return value::diff_zero;
};