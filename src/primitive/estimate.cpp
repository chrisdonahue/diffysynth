#include "estimate.hpp"

using namespace diffysynth;

primitive::estimate::estimate() :
	base("estimate")
{};

type::diff primitive::estimate::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return value::diff_zero;
};