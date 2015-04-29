#include "system.hpp"

using namespace diffysynth;

system::system(type::id _diff_eqs_num, type::id _parameters_num) :
	prepared(false),
	parameters_num(_parameters_num),
	parameters(nullptr),
	diff_eqs_num(diff_eqs_num),
	diff_eqs(diff_eqs_num),
	solutions(nullptr),
	derivatives(nullptr)
{
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		diff_eqs[identifier] = nullptr;
	}
};

void system::diff_eq_set(type::id identifier, diff_eq* instance) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(identifier < diff_eqs_num);
#endif

	diff_eqs[identifier] = instance;
};

diff_eq* system::diff_eq_get(type::id identifier) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(identifier < diff_eqs_num);
#endif

	return diff_eqs[identifier];
};

void system::prepare() {
	parameters = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * parameters_num));;
	solutions = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
	derivatives = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
};

void system::release() {
	free(parameters);
	free(solutions);
	free(derivatives);
};

void system::evaluate() {
#ifdef DIFFYSYNTH_DEBUG_API
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		ensure(diff_eqs[identifier] != nullptr);
	}
#endif

	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		solutions[identifier] = x[identifier];
	}

	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		type::diff diff_eq_result = diff_eqs[identifier]->evaluate(parameters, solutions, derivatives, t);
		dxdt[identifier] = diff_eq_result;
	}
};