#ifndef DIFFYSYNTH_PRIMITIVE_parameter
#define DIFFYSYNTH_PRIMITIVE_parameter

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class parameter : public base {
	public:
		parameter();

		type::diff evaluate(evaluate_signature) override;
	};
}}

#endif