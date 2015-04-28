#include "elementary.hpp"

using namespace diffysynth;

primitive::multiply::multiply() :
	base("*")
{
	child_register("multiplicand_1");
	child_register("multiplicand_2");
};

type::diff primitive::multiply::evaluate(estimator::base::state& es) {
	base::evaluate(es);

	type::diff multiplicand_1_result = child_get("multiplicand_1")->evaluate(es);
	type::diff multiplicand_2_result = child_get("multiplicand_2")->evaluate(es);

	return multiplicand_1_result * multiplicand_2_result;
};