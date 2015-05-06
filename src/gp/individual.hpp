#ifndef DIFFYSYNTH_GP_INDIVIDUAL
#define DIFFYSYNTH_GP_INDIVIDUAL

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../diff_eq_system.hpp"
#include "../rng.hpp"

#define primitives_signature primitives all, primitives terminal, primitives nonterminal
#define primitives_arguments all, terminal, nonterminal

namespace diffysynth { namespace gp {
	class individual {
	public:
		individual(diff_eq_system* _system);
		~individual();

		diff_eq_system* system_get();
		
		typedef const std::vector<primitive::base*>& primitives;

		static void subtree_delete(primitive::base* current);
		static void subtree_swap(primitive::base* subtree_old, primitive::base* subtree_new);

		static primitive::base* full_recursive(rng& r, primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* full(rng& r, primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height);
		static primitive::base* grow_recursive(rng& r, primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* grow(rng& r, primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height_max);

		static void crossover(individual** child_0, individual** child_1, rng& r, individual* parent_0, individual* parent_1);
		static void mutate(rng& r, primitives_signature, individual* parent, type::disc_32_u height_max);
		static void mutate_constants(rng& r, individual* parent);

	private:
		diff_eq_system* system;

		type::boolean novelty_valid;
		type::fitness novelty;
		type::boolean fitness_valid;
		type::fitness fitness;
	};
}}

#endif