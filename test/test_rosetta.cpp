#include "diffysynth.hpp"

int main(int argc, char* argv[]) {
	// create primitives
	diffysynth::primitive::parameter t;
	diffysynth::primitive::estimate y;
	diffysynth::primitive::square_root sqrt_y;
	diffysynth::primitive::multiply t_times_sqrt_y;
	diffysynth::primitive::base* y_ptr = sqrt_y.child_get("argument");

	// connect primitives
	sqrt_y.child_set("argument", &y);
	t_times_sqrt_y.child_set("multiplicand_1", &t);
	t_times_sqrt_y.child_set("multiplicand_2", &sqrt_y);

	// create differential equation
	diffysynth::diff_eq y_t(static_cast<diffysynth::type::diff>(0.0), &t_times_sqrt_y);

	// create system
	diffysynth::system rosetta_system(1, 0);

	// create stepper
	diffysynth::stepper::runge_kutta_4 rosetta_stepper(rosetta_system);

	// set initial state

	// integrate
	for (int t = 0; t <= 10; t++) {
		rosetta_steper.integrate(static_cast<type::diff>(t), static_cast<type::diff>(t + 1), static_cast<type::diff>(0.1));
	}

	return 0;
};