#ifndef DIFFYSYNTH_PRIMITIVE_SQRT
#define DIFFYSYNTH_PRIMITIVE_SQRT

#include <math.h>

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class square_root : public base {
	public:
		square_root();

		base* copy_get() override;
		type::diff evaluate(evaluate_signature) override;

		enum children_ids {
			argument = 0,
			children_num
		};

	protected:
		void as_symbol(std::stringstream& ss) override;

	};
}}

#endif