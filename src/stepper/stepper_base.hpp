#ifndef DIFFYSYNTH_STEPPER_BASE
#define DIFFYSYNTH_STEPPER_BASE

#include "../exception.hpp"
#include "../type.hpp"

#include "../system.hpp"

namespace diffysynth { namespace stepper {
	class base {
	public:
		void system_set(const system* __system);

		void prepare();
		void release();
		virtual void integrate() = 0;

		type::diff* solutions_get(type::id identifier = 0);

	protected:
		base();
		base(const system* __system);
		~base();

		type::boolean prepared;
		type::diff* parameters;
		type::diff* solutions;
		type::diff* derivatives;

	private:
		const system* _system;
	};
}}

#endif