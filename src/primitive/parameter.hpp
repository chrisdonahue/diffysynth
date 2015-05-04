#ifndef DIFFYSYNTH_PRIMITIVE_parameter
#define DIFFYSYNTH_PRIMITIVE_parameter

#include "primitive_base.hpp"

namespace diffysynth { namespace primitive {
	class parameter : public base {
	public:
		parameter(type::id _identifer);

		base* copy_get() override;
		type::diff evaluate(evaluate_signature) override;

	protected:
		void as_symbol(std::stringstream& ss) override;

	private:
		type::id identifier;
	};
}}

#endif