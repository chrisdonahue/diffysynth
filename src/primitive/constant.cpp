#include "constant.hpp"

using namespace diffysynth;

primitive::constant::constant(type::diff _value) :
	base("constant"),
	value(_value)
{};

type::diff primitive::constant::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return value;
};

