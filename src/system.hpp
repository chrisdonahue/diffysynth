#ifndef DIFFYSYNTH_SYSTEM
#define DIFFYSYNTH_SYSTEM

#include <map>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "diff_eq.hpp"

namespace diffysynth {
	class system {
	public:
		class system_state {
			system_state();

			type::diff* derivatives_get() {
				return derivatives;
			};

			type::diff* solutions_get() {
				return solutions;
			};

			type::diff* parameters_get() {
				return parameters;
			};
		protected:
		private:
			type::diff* solutions;
			type::diff* derivatives;
			type::diff* parameters;
		};

		system();

		void diff_eq_set(type::string specifier, diff_eq* instance);
		diff_eq* diff_eq_get(type::string specifier);

		system_state* system_state_allocate();
		type::diff evaluate(type::string specifier, system_state* state);

	private:
		std::map<type::string, diff_eq*> diff_eqs;
	};
}

#endif