#include "parameter.hpp"

using namespace diffysynth;

primitive::parameter::parameter() :
base("parameter")
{};

type::diff primitive::parameter::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	// TODO: fix this
	return t;
};