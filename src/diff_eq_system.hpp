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

		diff_eq_system* copy_get();

		type::id diff_eqs_num_get() const;
		type::id parameters_num_get() const;

		void diff_eq_system::diff_eq_set(type::id identifier, diff_eq* instance);
		diff_eq* diff_eq_get(type::id identifier);

		void evaluate(evaluate_signature) const;

		std::string to_string(type::disc_32_u precision);
		void to_string_stream(std::stringstream& ss);

	private:
		type::id diff_eqs_num;
		std::vector<diff_eq*> diff_eqs;
		type::id parameters_num;
	};
}

#endif