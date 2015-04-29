#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

#include "diffysynth.hpp"

typedef boost::array<double, 1> odeint_state_type;

// create primitives
diffysynth::primitive::parameter t;
diffysynth::primitive::estimate y;
diffysynth::primitive::square_root sqrt_y;
diffysynth::primitive::multiply t_times_sqrt_y;
diffysynth::primitive::base* y_ptr = sqrt_y.child_get("argument");

// create differential equation
diffysynth::diff_eq y_t(static_cast<diffysynth::type::diff>(0.0), &t_times_sqrt_y);

// create system
diffysynth::system<1> rosetta;

void evaluate(const odeint_state_type& x, odeint_state_type& dxdt, double t) {
	rosetta.evaluate(x, dxdt, t);
};

int main(int argc, char* argv[]) {
	// connect system
	sqrt_y.child_set("argument", &y);
	t_times_sqrt_y.child_set("multiplicand_1", &t);
	t_times_sqrt_y.child_set("multiplicand_2", &sqrt_y);
	rosetta.diff_eq_set(0, &y_t);

	// estimate
	odeint_state_type state = {1.0};
	boost::numeric::odeint::integrate(evaluate, state, 0.0, 10.0, 0.1);

	return 0;
};