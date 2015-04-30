#ifndef DIFFYSYNTH_PRIMITIVE_ELEMENTARY
#define DIFFYSYNTH_PRIMITIVE_ELEMENTARY

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class multiply : public base {
	public:
		multiply(type::id _children_num);

		type::diff evaluate(evaluate_signature) override;

		type::id children_num;
	private:
	};
}}

#endif