#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

#include "diffysynth.hpp"

typedef boost::array<double, 1> odeint_state_type;

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
	diffysynth::system<1> rosetta;
	rosetta.diff_eq_set(0, &y_t);

	// estimate
	odeint_state_type state = {0.0};
	auto rosetta_evaluate = [rosetta] (const odeint_state_type& x, odeint_state_type& dxdt, double t) mutable {
		rosetta.evaluate(x, dxdt, t);
	};
	boost::numeric::odeint::integrate(rosetta_evaluate, state, 0.0, 10.0, 0.1);

	return 0;
};