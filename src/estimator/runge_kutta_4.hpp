#ifndef DIFFYSYNTH_RUNGE_KUTTA_4
#define DIFFYSYNTH_RUNGE_KUTTA_4

#include <array>

#include "estimator_base.hpp"

namespace diffysynth { namespace estimator {
	class runge_kutta_4 : public base {
	public:
		runge_kutta_4();

		void solve(system& sys, system_state* state);
	protected:
	private:
	};
}}

#endif