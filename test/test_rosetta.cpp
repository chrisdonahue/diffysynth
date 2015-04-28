#include "diffysynth.hpp"

int main(int argc, char* argv[]) {
	// create primitives
	diffysynth::primitive::parameter t;
	diffysynth::primitive::estimate y;
	diffysynth::primitive::square_root sqrt_y;
	diffysynth::primitive::multiply t_times_sqrt_y;
	sqrt_y.child_set("argument", &y);
	t_times_sqrt_y.child_set("multiplicand_1", &t);
	t_times_sqrt_y.child_set("multiplicand_2", &sqrt_y);

	// create differential equation
	diffysynth::diff_eq y_t(static_cast<diffysynth::type::diff>(0.0), &t_times_sqrt_y);

	// create system
	diffysynth::system rosetta;
	rosetta.diff_eq_set("y_t", &y_t);

	// create estimator
	diffysynth::estimator::runge_kutta_4 estimator_rk4;

	// estimate

	return 0;
};