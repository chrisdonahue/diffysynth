#include "individual.hpp"

using namespace diffysynth;

gp::individual::individual() :
	system(nullptr)
{};

primitive::base* gp::individual::full_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current) {
	if (depth_current == depth_max) {
		return terminal[r.uniform<type::disc_32_u>(0, terminal.size() - 1)]->copy_get();
	}
	else {
		primitive::base* parent = nonterminal[r.uniform<type::disc_32_u>(0, nonterminal.size() - 1)]->copy_get();
		for (type::disc_32_u child = 0; child < parent->children_num_get(); child++) {
			parent->child_set(child, full_recursive(primitives_arguments, depth_max, depth_current + 1));
		}
		return parent;
	}
};

gp::individual* gp::individual::full(primitives_signature, type::disc_32_u height) {
};

primitive::base* gp::individual::grow_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current) {
	if (depth_current == depth_max) {
		return terminal[r.uniform<type::disc_32_u>(0, terminal.size() - 1)]->copy_get();
	}
	else {
		primitive::base* parent = all[r.uniform<type::disc_32_u>(0, all.size() - 1)]->copy_get();
		for (type::disc_32_u child = 0; child < parent->children_num_get(); child++) {
			parent->child_set(child, grow_recursive(primitives_arguments, depth_max, depth_current + 1));
		}
		return parent;
	}
};

gp::individual* gp::individual::grow(primitives_signature, type::disc_32_u height_max) {
};

gp::individual* gp::individual::crossover(individual* parent_zero, individual* parent_one) {
};

void gp::individual::mutate(individual* parent) {
};

void gp::individual::mutate_constants(individual* parent) {
};

gp::individual* gp::individual::create_new() {
};