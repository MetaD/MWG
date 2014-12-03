#include "Death_Knight.h"
#include "Model.h"
#include "Geometry.h"
#include <iostream>
using std::cout; using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

const int death_knight_initial_strenth_c = 2;
const double death_knight_initial_attack_range_c = 2.0;
const int servant_initial_health_c = 1;
const int servant_leaving_distance_c = 5;
// when the distance between the servant and its master exceeds this number, it will leave

Death_Knight::Death_Knight(const std::string& name_, Point location_) :
		Warrior(name_, location_, death_knight_initial_strenth_c,
				death_knight_initial_attack_range_c) {}

void Death_Knight::update() {
	Warrior::update();

	if (servant &&
		cartesian_distance(servant->get_location(), get_location()) > servant_leaving_distance_c) {
		// servant leaves the world silently when out of the range
		Model::get_model().notify_gone(servant->get_name());
		Model::get_model().remove_agent(servant);
	}
}

void Death_Knight::take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) {
	Warrior::take_hit(attack_strength, attacker_ptr);

	if (!attacker_ptr->is_alive())
		return;

	if (!is_alive()) {
		// servant will be harmed psychologically
		servant->lose_health(attack_strength);
		return;
	}

	if (!is_attacking())
		start_attacking_noexcept(attacker_ptr);	// counter-attack

	if (!servant) {
		// Summon a soldier servant with health = 1 at the attacker's location,
		// and command it to move and attack the attacker
		cout << get_name() << ": We will fight as one!" << endl;
		servant = std::make_shared<Soldier>(get_name() + "_servant", attacker_ptr->get_location(),
											servant_initial_health_c);
		Model::get_model().add_agent(servant);
		servant->start_attacking_noexcept(attacker_ptr);
		return;
	}

	// servant already summoned
	if (!servant->target_out_of_range(attacker_ptr))
		// command the servant to attack if in range
		servant->start_attacking_noexcept(attacker_ptr);
	else
		// command it to move to the attacker's location if out of range
		servant->move_to(attacker_ptr->get_location());
}

void Death_Knight::describe() const {
	cout << "Death Knight ";
	Warrior::describe();
}

void Death_Knight::make_sound() const noexcept {
	cout << get_name() << ": Neighhh!" << endl;
}
