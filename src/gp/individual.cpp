#include "individual.hpp"

using namespace diffysynth;

gp::individual::individual(diff_eq_system* _system) :
	system(_system)
{};

gp::individual::~individual() {
	for (type::disc_32_u equation_id = 0; equation_id < system->diff_eqs_num_get(); equation_id++) {
		diff_eq* equation = system->diff_eq_get(equation_id);
		delete_primitive_recursive(equation->root_get());
		delete equation;
	}
	delete system;
};

diff_eq_system* gp::individual::system_get() {
	return system;
};

void gp::individual::delete_primitive_recursive(primitive::base* current) {
	for (type::disc_32_u child_id = 0; child_id < current->children_num_get(); child_id++) {
		delete_primitive_recursive(current->child_get(child_id));
		delete current;
	}
};

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

gp::individual* gp::individual::full(primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height) {
	diff_eq_system* system = new diff_eq_system(diff_eqs_num, parameters_num);
	for (type::disc_32_u equation = 0; equation < diff_eqs_num; equation++) {
		system->diff_eq_set(equation, new diff_eq(full_recursive(primitives_arguments, height, 0)));
	}
	return new gp::individual(system);
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

gp::individual* gp::individual::grow(primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height_max) {
	diff_eq_system* system = new diff_eq_system(diff_eqs_num, parameters_num);
	for (type::disc_32_u equation = 0; equation < diff_eqs_num; equation++) {
		system->diff_eq_set(equation, new diff_eq(grow_recursive(primitives_arguments, height_max, 0)));
	}
	return new gp::individual(system);
};

gp::individual* gp::individual::crossover(rng& r, individual* parent_0, individual* parent_1) {
	diff_eq_system* parent_0_system = parent_0->system_get();
	diff_eq_system* parent_1_system = parent_1->system_get();

	type::disc_32_u parent_0_diff_eqs_num = parent_0_system->diff_eqs_num_get();
	type::disc_32_u parent_1_diff_eqs_num = parent_1_system->diff_eqs_num_get();
	type::disc_32_u diff_eqs_num_min = parent_0_diff_eqs_num < parent_1_diff_eqs_num ? parent_0_diff_eqs_num : parent_1_diff_eqs_num;

	for (type::disc_32_u diff_eq_id = 0; diff_eq_id < diff_eqs_num_min; diff_eq_id++) {
		diff_eq* parent_0_diff_eq = parent_0_system->diff_eq_get(diff_eq_id);
		diff_eq* parent_1_diff_eq = parent_1_system->diff_eq_get(diff_eq_id);

		primitive::base* parent_0_subtree_random = parent_0_diff_eq->subtree_random_get(r);
		primitive::base* parent_1_subtree_random = parent_1_diff_eq->subtree_random_get(r);
	}
};

void gp::individual::mutate(rng& r, individual* parent) {
};

void gp::individual::mutate_constants(rng& r, individual* parent) {
};

gp::individual* gp::individual::create_new(rng& r) {
};