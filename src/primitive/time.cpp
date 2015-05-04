#include "time.hpp"

using namespace diffysynth;

primitive::time::time() :
	base()
{};

type::diff primitive::time::evaluate(evaluate_signature) {
	base::evaluate(evaluate_arguments);

	return static_cast<type::diff>(t);
};

primitive::base* primitive::time::copy_get() {
	return new time();
};

void primitive::time::as_symbol(std::stringstream& ss) {
	ss << "t";
};