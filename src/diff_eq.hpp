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
		
		primitive::base* root_get();

		void reset();
		void condition_initial_set(type::diff _condition_initial);

		type::diff evaluate(evaluate_signature);

		void trace();
		type::disc_32_u height_get();
		primitive::base* subtree_random_get(rng& r);

		std::string to_string(type::disc_32_u precision);
		void to_string_stream(std::stringstream& ss);

	private:
		void trace_recursive(primitive::base* parent, primitive::base* current, type::disc_32_u depth_current);

		//type::diff condition_initial;
		primitive::base* root;

		type::boolean height_valid;
		type::disc_32_u height;
		type::boolean subtrees_valid;
		std::vector<primitive::base*> subtrees;
	};
}

#endif