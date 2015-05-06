#ifndef DIFFYSYNTH_PRIMITIVE_BASE
#define DIFFYSYNTH_PRIMITIVE_BASE

#include <set>
#include <sstream>
#include <unordered_map>

#include "../define.hpp"
#include "../exception.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../rng.hpp"

#define evaluate_signature const type::diff* solutions, type::diff* parameters, type::time t, type::diff* derivatives
#define evaluate_arguments solutions, parameters, t, derivatives

namespace diffysynth { namespace primitive {
	class base {
	public:
		base();

		base* parent_get();
		void parent_set(base* _parent);

		type::id children_num_get();
		base* child_get(type::id child_specifier);
		void child_set(type::id child_specifier, base* child);
		type::boolean ready();

		// TODO pure virtual
		virtual base* copy_get();
		virtual void randomize(rng& engine);
		virtual type::diff evaluate(evaluate_signature);

		void to_string_stream(std::stringstream& ss);

	protected:
		void child_register(type::id identifier);

		virtual void as_symbol(std::stringstream& ss) = 0;

	private:
		base* parent;
		std::unordered_map<type::id, base*> children;
	};
}}

#endif