#ifndef DIFFYSYNTH_PRIMITIVE_TIME
#define DIFFYSYNTH_PRIMITIVE_TIME

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class time : public base {
	public:
		time();

		type::diff evaluate(evaluate_signature) override;
	};
}}

#endif