#ifndef DIFFYSYNTH_RUNGE_KUTTA_4
#define DIFFYSYNTH_RUNGE_KUTTA_4

#include "estimator_base.hpp"

namespace diffysynth { namespace estimator {
	class runge_kutta_4 : public base {
	public:
		class runge_kutta_4_state : public base::state {
		public:
		protected:
		private:
		};

		runge_kutta_4();
	protected:
	private:
	};
}}

#endif