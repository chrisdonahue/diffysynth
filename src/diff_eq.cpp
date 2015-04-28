#include "diff_eq.hpp"

using namespace diffysynth;

diff_eq::diff_eq() :
	root(nullptr)
{};

diff_eq::diff_eq(type::diff value_initial, primitive::base* root) :
	root(root)
{};

diff_eq::diff_eq(type::string root_string) :
	root(nullptr)
{};

void diff_eq::reset() {
};

void diff_eq::condition_initial_set(type::diff _condition_initial) {
	condition_initial = _condition_initial;
};

type::diff diff_eq::evaluate(estimator::base::state& es) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	return root->evaluate(es);
};