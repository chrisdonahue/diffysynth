#ifndef DIFFYSYNTH_PRIMITIVE_ESTIMATE
#define DIFFYSYNTH_PRIMITIVE_ESTIMATE

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class estimate : public base {
	public:
		estimate();

		type::diff evaluate(estimator::base::state& es) override;
	};
}}

#endif