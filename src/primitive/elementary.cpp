#include "elementary.hpp"

using namespace diffysynth;

primitive::multiply::multiply() :
	base("*")
{
	child_register("multiplicand_1");
	child_register("multiplicand_2");
};

type::diff primitive::multiply::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	type::diff multiplicand_1_result = child_get("multiplicand_1")->evaluate(evaluate_arguments);
	type::diff multiplicand_2_result = child_get("multiplicand_2")->evaluate(evaluate_arguments);

	return multiplicand_1_result * multiplicand_2_result;
};