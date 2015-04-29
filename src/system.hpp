#ifndef DIFFYSYNTH_SYSTEM
#define DIFFYSYNTH_SYSTEM

#include <array>
#include <boost/array.hpp>

#include <map>

#include "define.hpp"
#include "type.hpp"
#include "value.hpp"

#include "diff_eq.hpp"

namespace diffysynth {
	template <type::id diff_eqs_num>
	class system {
	private:
		typedef boost::array<double, diff_eqs_num> odeint_state_type;

	public:
		system() {
			for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
				diff_eqs[identifier] = nullptr;
			}
			parameters = nullptr;
			solutions = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
			derivatives = reinterpret_cast<type::diff*>(malloc(sizeof(type::diff) * diff_eqs_num));
		};
		~system() {
			//free(parameters);
			free(solutions);
			free(derivatives);
		};

		void diff_eq_set(type::id identifier, diff_eq* instance) {
		#ifdef DIFFYSYNTH_DEBUG_API
			ensure(identifier < diff_eqs_num);
		#endif

			diff_eqs[identifier] = instance;
		};

		diff_eq* diff_eq_get(type::id identifier) {
		#ifdef DIFFYSYNTH_DEBUG_API
			ensure(identifier < diff_eqs_num);
		#endif

			return diff_eqs[identifier];
		};

		void evaluate(const odeint_state_type& x, odeint_state_type& dxdt, double t) {
		#ifdef DIFFYSYNTH_DEBUG_API
			for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
				ensure(diff_eqs[identifier] != nullptr);
			}
		#endif

			for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
				solutions[identifier] = x[identifier];
			}

			for (type::id identifier = 0; identifier < diff_eqs_num; identifier++) {
				type::diff diff_eq_result = diff_eqs[identifier]->evaluate(parameters, solutions, derivatives, t);
				dxdt[identifier] = diff_eq_result;
			}
		};

	private:
		type::diff* parameters;
		type::diff* solutions;
		type::diff* derivatives;
		std::array<diff_eq*, diff_eqs_num> diff_eqs;
	};
}

#endif