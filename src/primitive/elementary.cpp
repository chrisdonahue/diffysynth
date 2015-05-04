#include "elementary.hpp"

using namespace diffysynth;

primitive::multiply::multiply(type::id _children_num) :
	base(),
	children_num(_children_num)
{
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(children_num > 0);
#endif

	for (type::id child = 0; child < children_num; child++) {
		child_register(child);
	}
};

type::diff primitive::multiply::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	type::diff result = child_get(0)->evaluate(evaluate_arguments);
	for (type::id child = 1; child < children_num; child++) {
		result *= child_get(child)->evaluate(evaluate_arguments);
	}

	return result;
};

// TODO
primitive::base* primitive::multiply::copy_get() {
	return nullptr;
};

void primitive::multiply::as_symbol(std::stringstream& ss) {
	ss << "*";
};