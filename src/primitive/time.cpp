#include "time.hpp"

using namespace diffysynth;

primitive::time::time() :
	base("time")
{};

type::diff primitive::time::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return static_cast<type::diff>(t);
};