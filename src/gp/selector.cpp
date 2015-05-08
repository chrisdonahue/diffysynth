#include "selector.hpp"

using namespace diffysynth;

gp::selector::base::base(const id_to_fitness_map& _fitness_map) :
	fitness_map(_fitness_map)
{};

gp::selector::uniform::uniform(const id_to_fitness_map& _fitness_map, type::boolean _prefer_lower) :
	base(_fitness_map),
	prefer_lower(_prefer_lower),
	distribution(0)
{};

void gp::selector::uniform::fitness_map_updated() {
	// sum total fitness
	type::fitness total = 0.0;
	type::fitness best = prefer_lower ? value::fitness_infinity_n : value::fitness_infinity;
	auto it = fitness_map.begin();
	while (it != fitness_map.end()) {
		type::fitness current = it->second;
		if (prefer_lower)
		{
			if (current < best) {
				best = current;
			}
		}
		else {
			if (current > best) {
				best = current;
			}
		}
		total += it->second;
		it++;
	}

	// clear distribution vector
	distribution.clear();

	// calculate normalized fitnesses
};

type::id gp::selector::uniform::select(rng& r) {

};