#include "estimate.hpp"

using namespace diffysynth;

primitive::estimate::estimate(type::id _identifier) :
	base(),
	identifier(_identifier)
{};

type::diff primitive::estimate::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return solutions[identifier];
};

primitive::base* primitive::estimate::copy_get() {
	return new estimate(identifier);
};

void primitive::estimate::as_symbol(std::stringstream& ss) {
	ss << "estimate " << identifier;
};