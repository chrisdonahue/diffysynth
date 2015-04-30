#ifndef DIFFYSYNTH_PRIMITIVE_BASE
#define DIFFYSYNTH_PRIMITIVE_BASE

#include <set>
#include <sstream>
#include <unordered_map>

#include "../define.hpp"
#include "../exception.hpp"
#include "../type.hpp"
#include "../value.hpp"

#define evaluate_signature type::diff* parameters, type::diff* solutions, type::diff* derivatives, type::diff t
#define evaluate_arguments parameters, solutions, derivatives, t

namespace diffysynth { namespace primitive {
	class base {
	public:
		type::disc_32_u children_num_get();
		base* child_get(type::id child_specifier);
		void child_set(type::id child_specifier, base* child);
		type::boolean ready();

		virtual type::diff evaluate(evaluate_signature) = 0;

		void as_string(std::stringstream& ss);

	protected:
		base(type::string _symbol);

		void child_register(type::id identifier);

	private:
		type::string symbol;
		std::unordered_map<type::id, base*> children;
	};
}}

#endif