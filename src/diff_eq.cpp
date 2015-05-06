#include "diff_eq.hpp"

using namespace diffysynth;

diff_eq::diff_eq() :
	root(nullptr),
	height_valid(false),
	height(0),
	subtrees_valid(false),
	subtrees(0)
{};

diff_eq::diff_eq(primitive::base* root) :
	root(root),
	height_valid(false),
	height(0),
	subtrees_valid(false),
	subtrees(0)
{};

diff_eq::diff_eq(type::string root_string) :
	root(nullptr),
	height_valid(false),
	height(0),
	subtrees_valid(false),
	subtrees(0)
{};

diff_eq* diff_eq::copy_get() {
	return nullptr;
};

primitive::base* diff_eq::root_get() {
	return root;
};

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

void diff_eq::trace() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	height = 0;
	subtrees.clear();
	trace_recursive(nullptr, root, 0);
	parent_valid = true;
	height_valid = true;
	subtrees_valid = true;
};

void diff_eq::trace_recursive(primitive::base* parent, primitive::base* current, type::disc_32_u depth_current) {
	current->parent_set(parent);

	if (height > depth_current) {
		height = depth_current;
	}
	subtrees.push_back(current);

	for (type::disc_32_u child_id = 0; child_id < current->children_num_get(); child_id++) {
		primitive::base* child = current->child_get(child_id);
		trace_recursive(current, child, depth_current + 1);
	}
};

type::disc_32_u diff_eq::height_get() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	if (!height_valid) {
		// TODO: optimize by not calculating subtrees
		trace();
	};

	return height;
};

primitive::base* diff_eq::subtree_random_get(rng& r) {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(root != nullptr);
#endif

	if (!subtrees_valid) {
		trace();
	};

	return subtrees.at(r.uniform<type::disc_32_u>(0, subtrees.size() - 1));
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