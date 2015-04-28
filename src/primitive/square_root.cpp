#include "square_root.hpp"

using namespace diffysynth;

primitive::square_root::square_root() :
	base("sqrt")
{
	child_register("argument");
};

type::diff primitive::square_root::evaluate(estimator::base::state& es) {
	base::evaluate(es);

	return sqrt(child_get("argument")->evaluate(es));
};