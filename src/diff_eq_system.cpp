#include "diff_eq_system.hpp"

using namespace diffysynth;

diff_eq_system::diff_eq_system(type::id _diff_eqs_num, type::id _parameters_num) :
	diff_eqs_num(_diff_eqs_num),
	diff_eqs(diff_eqs_num),
	parameters_num(_parameters_num)
{
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		diff_eqs[identifier] = nullptr;
	}
};

type::id diff_eq_system::diff_eqs_num_get() const {
	return diff_eqs_num;
};

type::id diff_eq_system::parameters_num_get() const {
	return parameters_num;
};

void diff_eq_system::diff_eq_set(type::id identifier, diff_eq* instance) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(identifier < diff_eqs_num);
#endif

	diff_eqs[identifier] = instance;
};

diff_eq* diff_eq_system::diff_eq_get(type::id identifier) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(identifier < diff_eqs_num);
#endif

	return diff_eqs[identifier];
};

void diff_eq_system::evaluate(evaluate_signature) const {
#ifdef DIFFYSYNTH_DEBUG_API
	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		ensure(diff_eqs[identifier] != nullptr);
	}
#endif

	for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
		type::diff diff_eq_result = diff_eqs[identifier]->evaluate(evaluate_arguments);
	}
};