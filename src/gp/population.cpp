#include "population.hpp"

using namespace diffysynth;

gp::population::population(rng& _r, const population_state& _state) :
	r(_r),
	state(_state),
	individual_next_id(0),
	generations(0),
	generation_current_id(0),
	generation_current_unevaluated(0),
	generation_current_evaluated(0),
	generation_current_fitness(0),
	generation_current_novelty(0)
{};

gp::population::~population() {
	auto it = generations.begin();
	while (it != generations.end()) {
		generation* gen = it->second;
		for (type::id individual_id = 0; individual_id < gen->size(); individual_id++) {
			delete gen->at(individual_id);
		}
		delete gen;
	}
};

void gp::population::initialize() {
	generations.insert(std::make_pair(0, new generation()));

	type::disc_32_u individuals_per_height_value = state.size / (state.equation_height_max - state.equation_height_min);
	individuals_per_height_value = individuals_per_height_value < 1 ? 1 : individuals_per_height_value;
	type::disc_32_u grow_per_height_value = static_cast<type::disc_32_u>(state.equation_grow_proportion * static_cast<type::cont_64>(individuals_per_height_value));
	type::disc_32_u full_per_height_value = individuals_per_height_value - grow_per_height_value;

	for (type::disc_32_u equation_height = state.equation_height_max; equation_height >= state.equation_height_min; equation_height--) {
		for (type::disc_32_u i = 0; i < grow_per_height_value; i++) {
			individual* individual_new = individual::grow(r, state.primitives_all_get(), state.primitives_nonterminals_get(), state.primitives_terminals_get(), state.diff_eqs_num, state.parameters_num, equation_height);

			if (generation_current_individual_register(individual_new) == state.size - 1) {
				return;
			}
		}

		for (type::disc_32_u i = 0; i < full_per_height_value; i++) {
			individual* individual_new = individual::full(r, state.primitives_all_get(), state.primitives_nonterminals_get(), state.primitives_terminals_get(), state.diff_eqs_num, state.parameters_num, equation_height);

			if (generation_current_individual_register(individual_new) == state.size - 1) {
				return;
			}
		}
	}
};

type::id gp::population::individual_unevaluated_id_get() {
	return *(generation_current_unevaluated.begin());
};

gp::individual* gp::population::individual_get(type::id individual_id) {
	return generations[generation_current_id]->at(individual_id);
};

void gp::population::individual_fitness_report(type::id individual_id, type::fitness individual_fitness) {
	generation_current_unevaluated.erase(individual_id);
	generation_current_evaluated.insert(individual_id);
	generation_current_fitness[individual_id] = individual_fitness;
};

void gp::population::generation_next() {
#ifdef DIFFYSYNTH_DEBUG_API
	ensure(generation_current_unevaluated.size() == 0);
#endif

	// TODO

	generation_current_evaluated.clear();
	generation_current_fitness.clear();
};

type::id gp::population::generation_current_individual_register(individual* individual_new) {
#ifdef DIFFYSYNTH_DEBUG_INTERNAL
	ensure(generations[generation_current_id]->size() < state.size);
#endif

	type::id individual_new_id = individual_next_id;
	generation_current_unevaluated.insert(individual_new_id);
	generations[generation_current_id]->insert(std::make_pair(individual_new_id, individual_new));
	individual_next_id++;
	return individual_new_id;
};