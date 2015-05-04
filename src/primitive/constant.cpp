#include "constant.hpp"

using namespace diffysynth;

primitive::constant::constant(type::diff _value) :
	base(),
	value(_value)
{};

type::diff primitive::constant::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return value;
};

primitive::base* primitive::constant::copy_get() {
	return new constant(value);
};

void primitive::constant::as_symbol(std::stringstream& ss) {
	ss << value;
};