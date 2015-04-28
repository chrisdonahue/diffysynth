#ifndef DIFFYSYNTH_SYSTEM
#define DIFFYSYNTH_SYSTEM

#include <unordered_map>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "diff_eq.hpp"

namespace diffysynth {
	class system {
	public:
		system();

		void diff_eq_set(type::string specifier, diff_eq* instance);
		diff_eq* diff_eq_get(type::string specifier);

		type::diff evaluate(type::string specifier, estimator::base::state& es);

	private:
		std::unordered_map<type::string, diff_eq*> diff_eqs;
	};
}

#endif