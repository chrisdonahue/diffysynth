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
		individual(diff_eq_system* _system);
		~individual();

		diff_eq_system* system_get();
		
		typedef std::vector<primitive::base*>& primitives;

		static void delete_primitive_recursive(primitive::base* current);

		static primitive::base* full_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* full(primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height);
		static primitive::base* grow_recursive(primitives_signature, type::disc_32_u depth_max, type::disc_32_u depth_current);
		static individual* grow(primitives_signature, type::disc_32_u diff_eqs_num, type::disc_32_u parameters_num, type::disc_32_u height_max);

		static individual* crossover(rng& r, individual* parent_zero, individual* parent_one);
		static void mutate(rng& r, individual* parent);
		static void mutate_constants(rng& r, individual* parent);
		static individual* create_new(rng& r);

	private:
		diff_eq_system* system;

		type::cont_64 novelty;
		type::cont_64 fitness;
	};
}}

#endif