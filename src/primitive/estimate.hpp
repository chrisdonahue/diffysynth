#ifndef DIFFYSYNTH_PRIMITIVE_ESTIMATE
#define DIFFYSYNTH_PRIMITIVE_ESTIMATE

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class estimate : public base {
	public:
		estimate(type::id _identifier);

		type::diff evaluate(evaluate_signature) override;
	private:
		type::id identifier;
	};
}}

#endif