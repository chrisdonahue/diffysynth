#ifndef DIFFYSYNTH_DIFF_EQ
#define DIFFYSYNTH_DIFF_EQ

#include <sstream>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "primitive/primitive_base.hpp"

namespace diffysynth {
	class diff_eq {
	public:
		diff_eq();
		diff_eq(primitive::base* root);
		diff_eq(type::string root_string);

		void reset();
		void condition_initial_set(type::diff _condition_initial);

		type::diff evaluate(evaluate_signature);

		std::string to_string(type::disc_32_u precision);
		void to_string_stream(std::stringstream& ss);

	private:
		//type::diff condition_initial;
		primitive::base* root;
	};
}

#endif