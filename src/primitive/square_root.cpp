#include "square_root.hpp"

using namespace diffysynth;

primitive::square_root::square_root() :
	base("sqrt")
{
	child_register("argument");
};

type::diff primitive::square_root::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	type::diff argument_result = child_get("argument")->evaluate(evaluate_arguments);

	return sqrt(argument_result);
};