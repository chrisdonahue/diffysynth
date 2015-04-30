#include "estimate.hpp"

using namespace diffysynth;

primitive::estimate::estimate(type::id _identifier) :
	base("estimate"),
	identifier(_identifier)
{};

type::diff primitive::estimate::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return solutions[identifier];
};
