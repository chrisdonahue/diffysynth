#ifndef DIFFYSYNTH_PRIMITIVE_CONSTANT
#define DIFFYSYNTH_PRIMITIVE_CONSTANT

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class constant : public base {
	public:
		constant(type::diff _value);

		type::diff evaluate(evaluate_signature) override;
	private:
		type::diff value;
	};
}}

#endif