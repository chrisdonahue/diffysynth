#include "stepper_base.hpp"

using namespace diffysynth;

stepper::base::base() :
	prepared(false),
	solutions(nullptr),
	derivatives(nullptr),
	parameters(nullptr),
	system(nullptr)
{};

stepper::base::base(const diff_eq_system* _system) :
	prepared(false),
	solutions(nullptr),
	derivatives(nullptr),
	parameters(nullptr),
	system(_system)
{};

stepper::base::~base() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(!prepared);
#endif
};

void stepper::base::system_set(const diff_eq_system* _system) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(!prepared);
#endif

	system = _system;
};

void stepper::base::prepare() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(!prepared);
#endif

	type::id diff_eqs_num = system->diff_eqs_num_get();
	if (diff_eqs_num > 0) {
		solutions = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
		derivatives = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
	}

	type::id parameters_num = system->parameters_num_get();
	if (parameters_num > 0) {
		parameters = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * parameters_num));;
	}

	prepared = true;
};

void stepper::base::release() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(prepared);
#endif

	free(solutions);
	free(parameters);
	free(derivatives);
	prepared = false;
};

void stepper::base::integrate() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(prepared);
#endif
};

type::diff* stepper::base::solutions_get(type::id identifier) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(prepared);
#endif

	return solutions + identifier;
};

type::diff* stepper::base::parameters_get(type::id identifier) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(prepared);
#endif

	return parameters + identifier;
};