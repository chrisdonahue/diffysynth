#include "primitive_base.hpp"

using namespace diffysynth;

primitive::base::base(type::string _symbol) :
	symbol(_symbol),
	children(0)
{};

type::disc_32_u primitive::base::children_num_get() {
	return children.size();
};

primitive::base* primitive::base::child_get(type::id child_specifier) {
	auto it = children.find(child_specifier);
#ifdef DIFFYSYNTH_DEBUG_API
	diffysynth::ensure(it != children.end());
#endif

	return it->second;
};

void primitive::base::child_set(type::id child_specifier, base* child) {
#ifdef DIFFYSYNTH_DEBUG_API
	auto it = children.find(child_specifier);
	diffysynth::ensure(it != children.end());
#endif

	children[child_specifier] = child;
};

type::boolean primitive::base::ready() {
	auto it = children.begin();
	while (it != children.end()) {
		if (it->second == nullptr) {
			return false;
		}
		it++;
	}

	return true;
};

type::diff primitive::base::evaluate(evaluate_signature) {
#ifdef DIFFYSYNTH_DEBUG_API
	auto it = children.begin();
	while (it != children.end()) {
		ensure(it->second != nullptr);
		it++;
	}
#endif

	return value::diff_zero;
};

void primitive::base::child_register(type::id child_specifier) {
	children[child_specifier] = nullptr;
};

void primitive::base::as_string(std::stringstream& ss) {
	ss << "(" << symbol;
	auto it = children.begin();
	while (it != children.end()) {
		ss << " " << it->first << ": ";
		if (it->second == nullptr) {
			ss << "(null)";
		}
		else {
			it->second->as_string(ss);
		}
		it++;
	}
	ss << ")";
};