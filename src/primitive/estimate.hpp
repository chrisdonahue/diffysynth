#ifndef DIFFYSYNTH_PRIMITIVE_ESTIMATE
#define DIFFYSYNTH_PRIMITIVE_ESTIMATE

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class estimate : public base {
	public:
		estimate(type::id _identifier);

		base* copy_get() override;
		type::diff evaluate(evaluate_signature) override;

	protected:
		void as_symbol(std::stringstream& ss) override;

	private:
		type::id identifier;
	};
}}

#endif