#include "diffysynth.hpp"

using namespace diffysynth;

int main(int argc, char* argv[]) {
	// create primitives
	primitive::parameter t;
	primitive::estimate y;
	primitive::square_root sqrt_y;
	primitive::multiply t_times_sqrt_y(2);

	// connect primitives
	sqrt_y.child_set(primitive::square_root::argument, &y);
	t_times_sqrt_y.child_set(0, &t);
	t_times_sqrt_y.child_set(1, &sqrt_y);

	// create differential equation
	diff_eq y_t(static_cast<type::diff>(0.0), &t_times_sqrt_y);

	// create diff_eq_system
	diff_eq_system rosetta_system(1, 0);

	// copy system
	diff_eq_system rosetta_system_copy(const_cast<diff_eq_system&>(rosetta_system));

	// create stepper
	stepper::runge_kutta_4 rosetta_stepper;
	rosetta_stepper.system_set(&rosetta_system);

	// set initial state

	// integrate
	rosetta_stepper.prepare();
	for (int t = 0; t <= 10; t++) {
		rosetta_stepper.integrate();
	}
	rosetta_stepper.release();

	return 0;
};