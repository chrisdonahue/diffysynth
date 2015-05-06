#include "population.hpp"

using namespace diffysynth;

gp::population::population(rng& _r, const population_state& _state) :
	r(_r),
	state(_state),
	generations(0)
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

	type::id individual_id = 0;
	for (type::disc_32_u equation_height = state.equation_height_max; equation_height >= state.equation_height_min; equation_height--) {
		if (individual_id == state.size) {
			break;
		}

		for (type::disc_32_u i = 0; i < grow_per_height_value; i++) {
			if (individual_id == state.size) {
				break;
			}
			generations[0]->insert(std::make_pair(individual_id, individual::grow(r, state.primitives_all_get(), state.primitives_nonterminals_get, state.primitives_terminals_get(), state.diff_eqs_num, state.parameters_num, equation_height)));
			individual_id++;
		}

		for (type::disc_32_u i = 0; i < full_per_height_value; i++) {
			if (individual_id == state.size) {
				break;
			}
			generations[0]->insert(std::make_pair(individual_id, individual::full(r, state.primitives_all_get(), state.primitives_nonterminals_get, state.primitives_terminals_get(), state.diff_eqs_num, state.parameters_num, equation_height)));
			individual_id++;
		}
	}

#ifdef DIFFYSYNTH_DEBUG_INTERNAL
	ensure(generations.at(0)->size() == state.size);
#endif
};

void gp::population::generation_next() {
};