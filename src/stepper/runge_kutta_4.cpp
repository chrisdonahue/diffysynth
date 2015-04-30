#include "runge_kutta_4.hpp"

using namespace diffysynth;

stepper::runge_kutta_4::runge_kutta_4() :
	base(),
	buffer(nullptr)
{};

void stepper::runge_kutta_4::prepare() {
	base::prepare();

	if (diff_eqs_num > 0) {
		buffer = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * 5 * diff_eqs_num));
	}
};

void stepper::runge_kutta_4::release() {
	base::release();

	if (buffer != nullptr) {
		free(buffer);
		buffer = nullptr;
	}
};

void stepper::runge_kutta_4::step(step_signature) {
	base::step(t, dt);

	// temporary pointers
	type::diff* solutions_temp = buffer;
	type::diff* derivatives_0 = buffer + diff_eqs_num;
	type::diff* derivatives_1 = derivatives_0 + diff_eqs_num;
	type::diff* derivatives_2 = derivatives_1 + diff_eqs_num;
	type::diff* derivatives_3 = derivatives_2 + diff_eqs_num;
	
	// calculate dy_1
	system->evaluate(const_cast<type::diff*>(solutions), parameters, t, derivatives_0);
	for (type::id i = 0; i < diff_eqs_num; i++) {
		solutions_temp[i] = solutions[i] + 0.5 * dt * derivatives_0[i];
	}

	// calculate dy_2
	system->evaluate(const_cast<type::diff*>(solutions_temp), parameters, t + 0.5 * dt, derivatives_1);
	for (type::id i = 0; i < diff_eqs_num; i++) {
		solutions_temp[i] = solutions[i] + 0.5 * dt * derivatives_1[i];
	}
	
	// calculate dy_3
	system->evaluate(const_cast<type::diff*>(solutions_temp), parameters, t + 0.5 * dt, derivatives_2);
	for (type::id i = 0; i < diff_eqs_num; i++) {
		solutions_temp[i] = solutions[i] + dt * derivatives_2[i];
	}

	// calculate dy_4
	system->evaluate(const_cast<type::diff*>(solutions_temp), parameters, t + dt, derivatives_3);

	// calculate solutions
	for (type::id i = 0; i < diff_eqs_num; i++) {
		solutions[i] +=
		(1.0 / 6.0) * dt * (
			derivatives_0[i] +
			derivatives_1[i] * 2.0 +
			derivatives_2[i] * 2.0 +
			derivatives_3[i]
		);
	}
};