#ifndef DIFFYSYNTH_GP_SELECTOR
#define DIFFYSYNTH_GP_SELECTOR

#include <unordered_map>

#include "../define.hpp"
#include "../type.hpp"
#include "../value.hpp"

#include "../rng.hpp"

namespace diffysynth { namespace gp { namespace selector {
	class base {
	protected:
		typedef std::unordered_map<type::id, type::fitness> id_to_fitness_map;

	public:
		base(const id_to_fitness_map& _fitness_map);

		virtual void fitness_map_updated();
		virtual type::id select(rng& r) = 0;

	protected:
		const id_to_fitness_map& fitness_map;
	};

	class uniform : public base {
	public:
		uniform(const id_to_fitness_map& _fitness_map, type::boolean _prefer_lower);

		void fitness_map_updated() override;
		type::id select(rng& r) override;

	private:
		type::boolean prefer_lower;
	};
}}}

#endif