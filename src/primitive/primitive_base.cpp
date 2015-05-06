#include "primitive_base.hpp"

using namespace diffysynth;

primitive::base::base() :
	parent(nullptr),
	children(0)
{};

/*
primitive::base::base(const base& other)
{
	auto it = other.children.begin();
	while (it != other.children.end()) {
		base* other_child = it->second;

		if (other_child == nullptr) {
			children[it->first] = nullptr;
		}
		else {
			children[it->first] = new base(const_cast<base&>(*other_child));
		}
		
		it++;
	}
};
*/

primitive::base* primitive::base::parent_get() {
	return parent;
};

void primitive::base::parent_set(primitive::base* _parent) {
	parent = _parent;
};

type::id primitive::base::children_num_get() {
	return children.size();
};

primitive::base* primitive::base::child_get(type::id child_specifier) {
	auto it = children.find(child_specifier);
#ifdef DIFFYSYNTH_DEBUG_API
	diffysynth::ensure(it != children.end());
#endif

	return it->second;
};

type::id primitive::base::child_id_get(base* child) {
	auto it = children.begin();
	while (it != children.end()) {
		if (it->second == child) {
			return it->first;
		}
	}

#ifdef DIFFYSYNTH_DEBUG_API
	throw exception::runtime("child not found in primitive");
#endif

	return 0;
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

void primitive::base::randomize(rng& engine) {};

// TODO
primitive::base* primitive::base::copy_get() {
	return nullptr;
};

void primitive::base::as_symbol(std::stringstream& ss) {};

void primitive::base::to_string_stream(std::stringstream& ss) {
	ss << "(";
	as_symbol(ss);
	auto it = children.begin();
	while (it != children.end()) {
		ss << " " << it->first << ": ";
		if (it->second == nullptr) {
			ss << "(null)";
		}
		else {
			it->second->to_string_stream(ss);
		}
		it++;
	}
	ss << ")";
};