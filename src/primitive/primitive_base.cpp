#include "primitive_base.hpp"

using namespace diffysynth;

primitive::base::base(type::string _symbol) :
	symbol(_symbol),
	children(0)
{};

type::disc_32_u primitive::base::children_num_get() {
	return children.size();
};

primitive::base* primitive::base::child_get(type::string child_specifier) {
	auto it = children.find(child_specifier);
	return it->second;
};

void primitive::base::child_set(type::string child_specifier, base* child) {
	auto it = children.find(child_specifier);
	type::boolean child_specifier_registered = it != children.end();

#ifdef DIFFYSYNTH_DEBUG_API
	diffysynth::ensure(child_specifier_registered);
#endif

	children.insert(std::make_pair(child_specifier, child));
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

type::diff primitive::base::evaluate(estimator::base::state& es) {
#ifdef DIFFYSYNTH_DEBUG_API
	auto it = children.begin();
	while (it != children.end()) {
		ensure(it->second != nullptr);
	}
#endif

	return value::diff_zero;
};

void primitive::base::child_register(type::string child_specifier) {
	children.insert(std::make_pair(child_specifier, nullptr));
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