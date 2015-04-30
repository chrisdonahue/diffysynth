#ifndef DIFFYSYNTH_STEPPER_BASE
#define DIFFYSYNTH_STEPPER_BASE

#include "../exception.hpp"
#include "../type.hpp"

#include "../diff_eq_system.hpp"

namespace diffysynth { namespace stepper {
	class base {
	public:
		void system_set(const diff_eq_system* _system);

		void prepare();
		void release();
		virtual void integrate() = 0;

		type::diff* solutions_get(type::id identifier = 0);
		type::diff* parameters_get(type::id identifier = 0);

	protected:
		base();
		base(const diff_eq_system* _system);
		~base();

		type::boolean prepared;
		type::diff* solutions;
		type::diff* parameters;
		type::diff* derivatives;

	private:
		const diff_eq_system* system;
	};
}}

#endif