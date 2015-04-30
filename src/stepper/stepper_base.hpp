#ifndef DIFFYSYNTH_STEPPER_BASE
#define DIFFYSYNTH_STEPPER_BASE

#include "../exception.hpp"
#include "../type.hpp"

#include "../diff_eq_system.hpp"

#define step_signature type::time t, type::time dt
#define step_arguments t, dt

namespace diffysynth { namespace stepper {
	class base {
	public:
		void system_set(const diff_eq_system* _system);

		virtual void prepare();
		virtual void release();
		virtual void step(step_signature) = 0;

		type::diff* solutions_get(type::id identifier = 0);
		type::diff* parameters_get(type::id identifier = 0);

	protected:
		base();
		base(const diff_eq_system* _system);
		~base();

		type::boolean prepared;
		type::diff* solutions;
		type::diff* parameters;

		const diff_eq_system* system;
		type::id diff_eqs_num;
		type::id parameters_num;
	private:
	};
}}

#endif