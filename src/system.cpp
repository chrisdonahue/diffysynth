#include "system.hpp"

using namespace diffysynth;

system::system(type::id _diff_eqs_num, type::id _parameters_num) :
	parameters_num(_parameters_num),
	diff_eqs_num(diff_eqs_num),
	diff_eqs(diff_eqs_num)
{
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		diff_eqs[identifier] = nullptr;
	}
};

type::id system::parameters_num_get() const {
	return parameters_num;
};

type::id system::diff_eqs_num_get() const {
	return diff_eqs_num;
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

void system::evaluate(evaluate_signature) const {
#ifdef DIFFYSYNTH_DEBUG_API
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		ensure(diff_eqs[identifier] != nullptr);
	}
#endif

	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		type::diff diff_eq_result = diff_eqs[identifier]->evaluate(evaluate_arguments);
	}
};