#ifndef DIFFYSYNTH_PRIMITIVE_SQRT
#define DIFFYSYNTH_PRIMITIVE_SQRT

#include <math.h>

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class square_root : public base {
	public:
		square_root();

		type::diff evaluate(estimator::base::state& es) override;
	};
}}

#endif