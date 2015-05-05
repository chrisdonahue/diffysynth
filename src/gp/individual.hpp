#ifndef DIFFYSYNTH_GP_INDIVIDUAL
#define DIFFYSYNTH_GP_INDIVIDUAL

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../diff_eq_system.hpp"
#include "../rng.hpp"

#define primitives_signature rng& r, primitives all, primitives terminal, primitives nonterminal
#define primitives_arguments r, all, terminal, nonterminal

namespace diffysynth { namespace gp {
	class individual {
	public:
		individual();
		
		typedef std::vector<primitive::base*>& primitives;

		static primitive::base* full_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* full(primitives_signature, type::disc_32_u height);
		static primitive::base* grow_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* grow(primitives_signature, type::disc_32_u height_max);

		static individual* crossover(individual* parent_zero, individual* parent_one);
		static void mutate(individual* parent);
		static void mutate_constants(individual* parent);
		static individual* create_new();

	private:
		diff_eq_system* system;
	};
}}

#endif