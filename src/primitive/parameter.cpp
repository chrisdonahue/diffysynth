#include "parameter.hpp"

using namespace diffysynth;

primitive::parameter::parameter(type::id _identifier) :
	base("parameter"),
	identifier(_identifier)
{};

type::diff primitive::parameter::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return parameters[identifier];
};