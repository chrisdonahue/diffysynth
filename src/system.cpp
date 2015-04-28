#include "system.hpp"

using namespace diffysynth;

system::system() :
	diff_eqs(0)
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

type::diff system::evaluate(type::string specifier, estimator::base::state& es) {
	auto it = diff_eqs.find(specifier);
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(it != diff_eqs.end());
#endif

	return it->second->evaluate(es);
};