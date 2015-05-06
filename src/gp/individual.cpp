#include "individual.hpp"

using namespace diffysynth;

gp::individual::individual(diff_eq_system* _system) :
	system(_system)
{};

gp::individual::~individual() {
	for (type::id equation_id = 0; equation_id < system->diff_eqs_num_get(); equation_id++) {
		diff_eq* equation = system->diff_eq_get(equation_id);
		subtree_delete(equation->root_get());
		delete equation;
	}
	delete system;
};

diff_eq_system* gp::individual::system_get() {
	return system;
};

void gp::individual::subtree_delete(primitive::base* current) {
	for (type::id child_id = 0; child_id < current->children_num_get(); child_id++) {
		subtree_delete(current->child_get(child_id));
		delete current;
	}
};

void gp::individual::subtree_swap(primitive::base* subtree_0, primitive::base* subtree_1) {
	primitive::base* subtree_0_parent = subtree_0->parent_get();
	primitive::base* subtree_1_parent = subtree_1->parent_get();

	if (subtree_0_parent != nullptr) {
		type::id subtree_0_child_id = subtree_0_parent->child_id_get(subtree_0);
		subtree_0_parent->child_set(subtree_0_child_id, subtree_1);
	}
	if (subtree_1_parent != nullptr) {
		type::id subtree_1_child_id = subtree_1_parent->child_id_get(subtree_1);
		subtree_1_parent->child_set(subtree_1_child_id, subtree_0);
	}

	subtree_0->parent_set(subtree_1_parent);
	subtree_1->parent_set(subtree_0_parent);
};

primitive::base* gp::individual::full_recursive(rng& r, primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current) {
	if (depth_current == depth_max) {
		return terminal[r.uniform<type::disc_32_u>(0, terminal.size() - 1)]->copy_get();
	}
	else {
		primitive::base* parent = nonterminal[r.uniform<type::disc_32_u>(0, nonterminal.size() - 1)]->copy_get();
		for (type::id child = 0; child < parent->children_num_get(); child++) {
			parent->child_set(child, full_recursive(r, primitives_arguments, depth_max, depth_current + 1));
		}
		return parent;
	}
};

gp::individual* gp::individual::full(rng& r, primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height) {
	diff_eq_system* system = new diff_eq_system(diff_eqs_num, parameters_num);
	for (type::id equation = 0; equation < diff_eqs_num; equation++) {
		system->diff_eq_set(equation, new diff_eq(full_recursive(r, primitives_arguments, height, 0)));
	}
	return new gp::individual(system);
};

primitive::base* gp::individual::grow_recursive(rng& r, primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current) {
	if (depth_current == depth_max) {
		return terminal[r.uniform<type::disc_32_u>(0, terminal.size() - 1)]->copy_get();
	}
	else {
		primitive::base* parent = all[r.uniform<type::disc_32_u>(0, all.size() - 1)]->copy_get();
		for (type::id child = 0; child < parent->children_num_get(); child++) {
			parent->child_set(child, grow_recursive(r, primitives_arguments, depth_max, depth_current + 1));
		}
		return parent;
	}
};

gp::individual* gp::individual::grow(rng& r, primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height_max) {
	diff_eq_system* system = new diff_eq_system(diff_eqs_num, parameters_num);
	for (type::id equation = 0; equation < diff_eqs_num; equation++) {
		system->diff_eq_set(equation, new diff_eq(grow_recursive(r, primitives_arguments, height_max, 0)));
	}
	return new gp::individual(system);
};

void gp::individual::crossover(individual** child_0, individual** child_1, rng& r, individual* parent_0, individual* parent_1) {
	diff_eq_system* parent_0_system = parent_0->system_get();
	diff_eq_system* parent_1_system = parent_1->system_get();

	type::disc_32_u parent_0_diff_eqs_num = parent_0_system->diff_eqs_num_get();
	type::disc_32_u parent_1_diff_eqs_num = parent_1_system->diff_eqs_num_get();
	type::disc_32_u diff_eqs_num_min = parent_0_diff_eqs_num < parent_1_diff_eqs_num ? parent_0_diff_eqs_num : parent_1_diff_eqs_num;

	for (type::id diff_eq_id = 0; diff_eq_id < diff_eqs_num_min; diff_eq_id++) {
		diff_eq* parent_0_diff_eq = parent_0_system->diff_eq_get(diff_eq_id);
		diff_eq* parent_1_diff_eq = parent_1_system->diff_eq_get(diff_eq_id);

		primitive::base* parent_0_subtree_random = parent_0_diff_eq->subtree_random_get(r);
		primitive::base* parent_1_subtree_random = parent_1_diff_eq->subtree_random_get(r);

		subtree_swap(parent_0_subtree_random, parent_1_subtree_random);
	}

	*child_0 = new individual(parent_0_system);
	*child_1 = new individual(parent_1_system);
};

void gp::individual::mutate(rng& r, primitives_signature, individual* parent, type::disc_32_u height_max) {
	diff_eq_system* parent_system = parent->system_get();

	for (type::id diff_eq_id = 0; diff_eq_id < parent_system->diff_eqs_num_get(); diff_eq_id++) {
		diff_eq* parent_diff_eq = parent_system->diff_eq_get(diff_eq_id);

		primitive::base* parent_subtree_random = parent_diff_eq->subtree_random_get(r);
		type::disc_32_u parent_subtree_random_depth = parent_subtree_random->depth_get();

		primitive::base* subtree_new = grow_recursive(r, primitives_arguments, parent_subtree_random_depth - height_max, 0);

		subtree_swap(parent_subtree_random, subtree_new);
	}
};

void gp::individual::mutate_constants(rng& r, individual* parent) {
	diff_eq_system* parent_system = parent->system_get();

	for (type::id diff_eq_id = 0; diff_eq_id < parent_system->diff_eqs_num_get(); diff_eq_id++) {
		diff_eq* parent_diff_eq = parent_system->diff_eq_get(diff_eq_id);

		parent_diff_eq->root_get()->randomize(r);
	}
};