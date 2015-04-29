#ifndef DIFFYSYNTH_RUNGE_KUTTA_4
#define DIFFYSYNTH_RUNGE_KUTTA_4

#include "estimator_base.hpp"

namespace diffysynth { namespace estimator {
	class runge_kutta_4 : public base {
	public:
		template <int derivatives_num, int param_num>
		class runge_kutta_4_state : public base::state {
		public:
			runge_kutta_4_state();

			std::array<type::diff, derivatives_num>& derivatives_get() {
				return derivatives;
			};

			std::array<type::diff, derivatives_num>& solutions_get() {
				return solutions;
			};

			std::array<type::diff, derivatives_num>& parameters_get() {
				return parameters;
			};
		protected:
		private:
			std::array<type::diff, derivatives_num> solutions;
			std::array<type::diff, derivatives_num> derivatives;
			std::array<type::diff, param_num> parameters;
		};

		runge_kutta_4();
	protected:
	private:
	};
}}

#endif