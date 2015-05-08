#ifndef DIFFYSYNTH_GP_EVALUATOR
#define DIFFYSYNTH_GP_EVALUATOR

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "individual.hpp"

namespace diffysynth { namespace gp {
	class evaluator {
	public:
		evaluator();

		virtual type::fitness evaluate(individual& individual) const = 0;
	private:
	};
}}

#endif