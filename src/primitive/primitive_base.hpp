#ifndef DIFFYSYNTH_PRIMITIVE_BASE
#define DIFFYSYNTH_PRIMITIVE_BASE

#include <set>
#include <sstream>
#include <unordered_map>

#include "../define.hpp"
#include "../exception.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../estimator/estimator_base.hpp"

namespace diffysynth { namespace primitive {
	class base {
	public:
		type::disc_32_u children_num_get();
		base* child_get(type::string child_specifier);
		void child_set(type::string child_specifier, base* child);
		type::boolean ready();

		virtual type::diff evaluate(estimator::base::state& es) = 0;

		void as_string(std::stringstream& ss);

	protected:
		base(type::string _symbol);
		void child_register(type::string child_specifier);

	private:
		type::string symbol;
		std::unordered_map<type::string, base*> children;
	};
}}

#endif