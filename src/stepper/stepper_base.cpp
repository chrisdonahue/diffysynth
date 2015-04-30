#include "stepper_base.hpp"

using namespace diffysynth;

stepper::base::base() :
	prepared(false),
	parameters(nullptr),
	solutions(nullptr),
	derivatives(nullptr),
	system(nullptr)
{};

stepper::base::base(const diff_eq_system* _system) :
	prepared(false),
	parameters(nullptr),
	solutions(nullptr),
	derivatives(nullptr),
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

	parameters = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * system->parameters_num_get()));;
	solutions = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * system->diff_eqs_num_get()));
	derivatives = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * system->diff_eqs_num_get()));
	prepared = true;
};

void stepper::base::release() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(prepared);
#endif

	free(parameters);
	free(solutions);
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