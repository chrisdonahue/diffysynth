#ifndef DIFFYSYNTH_GP_POPULATION
#define DIFFYSYNTH_GP_POPULATION

#include <vector>
#include <map>

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../primitive/primitive_base.hpp"
#include "evaluator.hpp"

namespace diffysynth { namespace gp {
	class population {
	public:
		class population_state {
		public:
			population_state();

			// methods
			void primitive_add(primitive::base* _primitive);
			primitive::base* primitive_random_get();
			primitive::base* primitive_random_leaf_get();

			// population parameters
			type::disc_32_u size;

			// system parameters
			type::disc_32_u system_size_min;
			type::disc_32_u system_size_max;

			// eq parameters
			type::disc_32_u equation_height_min;
			type::disc_32_u equation_height_max;
			type::disc_32_u equation_size_min;
			type::disc_32_u equation_size_max;
			type::cont_64 equation_full_proportion;
			type::cont_64 equation_grow_proportion;

			// novelty search parameters
			type::boolean novelty_search_enabled;
			evaluator* novelty_search_function;
			type::cont_64 novelty_search_threshold;

			// reproduction parameters
			// numeric mutation
			type::cont_64 nm_proportion;
			type::cont_64 nm_temperature;
			type::disc_32_u nm_selection_type;
			type::cont_64 nm_selection_percentile;
			// mutation
			type::cont_64 mu_proportion;
			type::disc_32_u mu_type;
			type::disc_32_u mu_selection_type;
			type::cont_64 mu_selection_percentile;
			// crossover
			type::cont_64 x_proportion;
			type::disc_32_u x_type;
			type::disc_32_u x_selection_type;
			type::cont_64 x_selection_percentile;
			// reproduction
			type::cont_64 re_proportion;
			type::disc_32_u re_selection_type;
			type::cont_64 re_selection_percentile;
			bool re_reevaluate;
			// random new individual
			type::cont_64 new_proportion;
			type::disc_32_u new_type;

		private:
			std::vector<primitive::base*> primitives;
			std::vector<primitive::base*> primitives_nonterminals;
			std::vector<primitive::base*> primitives_terminals;
		};

	public:
		population(const population_state& _state);

		void initialize();
		void generation_next();

	private:
		const population_state& state;
	};
}}

#endif