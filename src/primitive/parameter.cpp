#include "parameter.hpp"

using namespace diffysynth;

primitive::parameter::parameter(type::id _identifier) :
	base(),
	identifier(_identifier)
{};

type::diff primitive::parameter::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return parameters[identifier];
};

primitive::base* primitive::parameter::copy_get() {
	return new parameter(identifier);
};

void primitive::parameter::as_symbol(std::stringstream& ss) {
	ss << "parameter " << identifier;
};