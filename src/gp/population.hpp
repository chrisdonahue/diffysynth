#ifndef DIFFYSYNTH_GP_POPULATION
#define DIFFYSYNTH_GP_POPULATION

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../primitive/primitive_base.hpp"
#include "evaluator.hpp"
#include "individual.hpp"

namespace diffysynth { namespace gp {
	class population {
	public:
		class population_state {
		public:
			population_state();

			// methods
			void primitive_add(primitive::base* _primitive);
			const std::vector<primitive::base*>& primitives_all_get() const;
			const std::vector<primitive::base*>& primitives_nonterminals_get() const;
			const std::vector<primitive::base*>& primitives_terminals_get() const;

			// population parameters
			type::disc_32_u size;

			// system parameters
			type::disc_32_u diff_eqs_num;
			type::disc_32_u parameters_num;

			// eq parameters
			type::boolean equation_height_restrict;
			type::disc_32_u equation_height_min;
			type::disc_32_u equation_height_max;
			type::boolean equation_size_restrict;
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
		population(rng& _r, const population_state& _state);
		~population();

		// initialize
		void initialize();

		// manual evolution
		type::id individual_unevaluated_id_get();
		individual* individual_get(type::id individual_id);
		void individual_fitness_report(type::id individual_id, type::fitness individual_fitness);
		void generation_next();

		// automatic evolution
		void evolve(const evaluator& e);

	private:
		type::id generation_current_individual_register(individual* individual_new);

		rng& r;
		const population_state& state;

		type::id individual_next_id;

		typedef std::map<type::id, individual*> generation;
		std::unordered_map<type::disc_32_u, generation* > generations;

		type::id generation_current_id;
		std::unordered_set<type::id> generation_current_unevaluated;
		std::unordered_set<type::id> generation_current_evaluated;
		std::unordered_map<type::id, type::fitness> generation_current_fitness;
		std::unordered_map<type::id, type::fitness> generation_current_novelty;
	};
}}

#endif