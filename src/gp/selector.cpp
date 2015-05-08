#include "selector.hpp"

using namespace diffysynth;

gp::selector::base::base(const id_to_fitness_map& _fitness_map) :
	fitness_map(_fitness_map)
{};

gp::selector::uniform::uniform(const id_to_fitness_map& _fitness_map, type::boolean _prefer_lower) :
	base(_fitness_map),
	prefer_lower(_prefer_lower)
{};

void gp::selector::uniform::fitness_map_updated() {

};

type::id gp::selector::uniform::select(rng& r) {

};