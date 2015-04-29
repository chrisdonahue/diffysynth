#include "system.hpp"

using namespace diffysynth;

system::system() :
{};

void system::diff_eq_set(type::string specifier, diff_eq* instance) {
	diff_eqs.insert(std::make_pair(specifier, instance));
};

diff_eq* system::diff_eq_get(type::string specifier) {
	auto it = diff_eqs.find(specifier);
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(it != diff_eqs.end());
#endif

	return it->second;
};

type::diff system::evaluate(type::string specifier, system_state* state) {
	auto it = diff_eqs.find(specifier);
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(it != diff_eqs.end());
#endif

	return it->second->evaluate(es);
};