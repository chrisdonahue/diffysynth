#ifndef DIFFYSYNTH_STEPPER_RUNGE_KUTTA_4
#define DIFFYSYNTH_STEPPER_RUNGE_KUTTA_4

#include "stepper_base.hpp"

namespace diffysynth { namespace stepper {
	class runge_kutta_4 : public base {
	public:
		runge_kutta_4();

		void prepare() override;
		void release() override;
		void step(step_signature) override;
	protected:
	private:
		type::diff* buffer;
	};
}}

#endif