#include "diff_eq.hpp"

using namespace diffysynth;

diff_eq::diff_eq() :
	root(nullptr)
{};

diff_eq::diff_eq(primitive::base* root) :
	root(root)
{};

diff_eq::diff_eq(type::string root_string) :
	root(nullptr)
{};

void diff_eq::reset() {
};

void diff_eq::condition_initial_set(type::diff _condition_initial) {
	//condition_initial = _condition_initial;
};

type::diff diff_eq::evaluate(evaluate_signature) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	return root->evaluate(evaluate_arguments);
};

std::string diff_eq::to_string(type::disc_32_u precision) {
	std::stringstream ss;
	ss.precision(precision);
	to_string_stream(ss);
	return ss.str();
};

void diff_eq::to_string_stream(std::stringstream& ss) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	root->to_string_stream(ss);
};