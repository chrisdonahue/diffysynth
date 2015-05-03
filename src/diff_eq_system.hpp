#ifndef DIFFYSYNTH_SYSTEM
#define DIFFYSYNTH_SYSTEM

#include <array>
#include <map>
#include <sstream>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "diff_eq.hpp"

namespace diffysynth {
	class diff_eq_system {
	public:
		diff_eq_system(type::id _diff_eqs_num, type::id _parameters_num);
		diff_eq_system(const diff_eq_system& other);

		type::id diff_eqs_num_get() const;
		type::id parameters_num_get() const;

		void diff_eq_system::diff_eq_set(type::id identifier, diff_eq* instance);
		diff_eq* diff_eq_get(type::id identifier);

		void evaluate(evaluate_signature) const;

		static diff_eq_system* full_recursive(type::disc_32_u depth, type::disc_32_u depth_current);
		static diff_eq_system* full(type::disc_32_u depth);
		static diff_eq_system* grow_recursive(type::disc_32_u depth_current, type::disc_32_u m);
		static diff_eq_system* grow(type::disc_32_u m);
		static diff_eq_system* equation_create();

		void as_string(std::stringstream& ss);

	private:
		type::id diff_eqs_num;
		std::vector<diff_eq*> diff_eqs;
		type::id parameters_num;
	};
}

#endif