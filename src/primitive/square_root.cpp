#include "square_root.hpp"

using namespace diffysynth;

primitive::square_root::square_root() :
	base()
{
	child_register(argument);
};

type::diff primitive::square_root::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	type::diff argument_result = child_get(argument)->evaluate(evaluate_arguments);

	return sqrt(argument_result);
};

// TODO
primitive::base* primitive::square_root::copy_get() {
	return nullptr;
};

void primitive::square_root::as_symbol(std::stringstream& ss) {
	ss << "sqrt";
};