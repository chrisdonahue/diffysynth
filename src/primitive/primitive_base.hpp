#ifndef DIFFYSYNTH_PRIMITIVE_BASE
#define DIFFYSYNTH_PRIMITIVE_BASE

#include "../type.hpp"

#include "../estimator/estimator_base.hpp"

namespace diffysynth { namespace primitive {
	class base {
	public:
		base();

		type::disc_32_u children_num_get();
		base* child_get(type::string child_specifier);
		void child_set(type::string child_specifier, base* child);
		type::boolean ready();

		type::diff evaluate(estimator::base::state& es);
	protected:
		void child_register(type::string child_specifier);
	private:
		std::map<type::string, base*> children;
	};
}}

#endif