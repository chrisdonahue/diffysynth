#ifndef DIFFYSYNTH_SYSTEM
#define DIFFYSYNTH_SYSTEM

#include <array>

#include <map>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "diff_eq.hpp"

namespace diffysynth {
	class system {
	public:
		system(type::id _diff_eqs_num, type::id _parameters_num);
		~system();

		void system::diff_eq_set(type::id identifier, diff_eq* instance);
		diff_eq* diff_eq_get(type::id identifier);

		void prepare();
		void release();
		void evaluate();

	private:
		type::boolean prepared;
		type::id parameters_num;
		type::diff* parameters;
		type::id diff_eqs_num;
		std::vector<diff_eq*> diff_eqs;
		type::diff* solutions;
		type::diff* derivatives;
	};
}

#endif