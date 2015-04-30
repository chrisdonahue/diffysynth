#include "diffysynth.hpp"

using namespace diffysynth;

int main(int argc, char* argv[]) {
	// create primitives
	primitive::time _t;
	primitive::estimate y(0);
	primitive::square_root sqrt_y;
	primitive::multiply t_times_sqrt_y(2);

	// connect primitives
	sqrt_y.child_set(primitive::square_root::argument, &y);
	t_times_sqrt_y.child_set(0, &_t);
	t_times_sqrt_y.child_set(1, &sqrt_y);

	// create differential equation
	diff_eq y_t(&t_times_sqrt_y);

	// create diff_eq_system
	diff_eq_system rosetta_system(1, 0);
	rosetta_system.diff_eq_set(0, &y_t);

	// copy system
	//diff_eq_system rosetta_system_copy(const_cast<diff_eq_system&>(rosetta_system));

	// create stepper
	stepper::runge_kutta_4 rosetta_stepper;
	rosetta_stepper.system_set(&rosetta_system);
	rosetta_stepper.prepare();

	// set initial state
	type::diff* solutions = rosetta_stepper.solutions_get();
	solutions[0] = 1.0;

	// integrate
	type::time t = 0.0;
	type::time t_prime = 10.0;
	type::time dt = 0.1;
	type::diff solution = 1.0;
	type::diff solution_exact = 1.0;
	type::diff error_relative = 0.0;
	type::disc_32 steps_num = static_cast<type::disc_32>(ceil((t_prime - t) / dt));
	for (type::disc_32 step = 0; step < steps_num; step++) {
		rosetta_stepper.step(t, dt);
		t += dt;
		solution = solutions[0];
		solution_exact = pow(t * t / 4 + 1, 2);
		error_relative = (solution / solution_exact) - 1.0;
	}

	// release
	rosetta_stepper.release();

	return 0;
};