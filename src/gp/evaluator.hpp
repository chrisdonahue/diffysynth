#ifndef DIFFYSYNTH_GP_EVALUATOR
#define DIFFYSYNTH_GP_EVALUATOR

#include <vector>
#include <map>

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "individual.hpp"

namespace diffysynth { namespace gp {
	class evaluator {
	public:
		evaluator();

		virtual type::fitness evaluate(individual& individual) = 0;

	private:
	};
}}

#endif