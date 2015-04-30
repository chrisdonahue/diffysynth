#include "diffysynth.hpp"

using namespace diffysynth;

int main(int argc, char* argv[]) {
	// create cos primitives
	primitive::constant cos_scalar(-2.0 * static_cast<type::diff>(value::two_pi_64));
	primitive::estimate cos_sin(1);
	primitive::parameter cos_f_1(0);
	primitive::multiply cos_multiplier(3);

	// connect cos primitives
	cos_multiplier.child_set(0, &cos_scalar);
	cos_multiplier.child_set(1, &cos_sin);
	cos_multiplier.child_set(2, &cos_f_1);

	// create cos differential equation
	diff_eq cos_t(&cos_multiplier);

	// create sin primitives
	primitive::constant sin_scalar(2.0 * static_cast<type::diff>(value::two_pi_64));
	primitive::estimate sin_cos(0);
	primitive::parameter sin_f_1(0);
	primitive::multiply sin_multiplier(3);

	// connect sin primitives
	sin_multiplier.child_set(0, &sin_scalar);
	sin_multiplier.child_set(1, &sin_sin);
	sin_multiplier.child_set(2, &sin_f_1);

	// create sin differential equation
	diff_eq sin_t(&sin_multiplier);

	// create diff_eq_system
	diff_eq_system sin_cos_system(2, 1);
	sin_cos_system.diff_eq_set(0, &cos_t);
	sin_cos_system.diff_eq_set(1, &sin_t);

	// create stepper
	stepper::runge_kutta_4 sin_cos_stepper;
	sin_cos_stepper.system_set(&sin_cos_system);
	sin_cos_stepper.prepare();

	// set initial state
	type::diff* solutions = sin_cos_stepper.solutions_get();
	solutions[0] = 1.0;
	solutions[1] = 0.0;

	// set parameters
	type::diff* parameters = sin_cos_stepper.parameters_get();
	parameters[0] = 40.0;

	// integrate
	type::time t = 0.0;
	type::time t_prime = 10.0;
	type::time dt = 0.1;
	type::diff solution = 1.0;
	type::disc_32 steps_num = ceil((t_prime - t) / dt);
	for (type::disc_32 step = 0; step < steps_num; step++) {
		sin_cos_stepper.step(t, dt);
		t += dt;
		solution = solutions[0];
	}

	// release
	sin_cos_stepper.release();

	return 0;
};