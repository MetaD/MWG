#include "Archer.h"
#include "Model.h"
#include "Structure.h"
#include <iostream>
using std::cout; using std::endl;

using std::shared_ptr;

static const int archer_initial_strenth_c = 1;
static const double archer_initial_attack_range_c = 6.0;

Archer::Archer(const std::string& name_, Point location_) :
		Warrior(name_, location_, archer_initial_strenth_c, archer_initial_attack_range_c) {}

void Archer::update() {
	Warrior::update();
	if (!is_attacking() || Warrior::target_out_of_range()) {
		// find a new target if the old one is dead or out of range
		shared_ptr<Agent> new_target = Model::get_model().nearest_agent(get_name(), get_location());
		if (!new_target)
			return;
		if (!target_out_of_range(new_target))
			Warrior::start_attacking_noexcept(new_target);
	}
}

void Archer::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
	Warrior::take_hit(attack_strength, attacker_ptr);
	if (is_alive() && attacker_ptr->is_alive())	{	// hide
		shared_ptr<Structure> shelter = Model::get_model().nearest_structure(get_name(), get_location());
		cout << get_name() << ": I'm going to run away to " << shelter->get_name() << endl;
		Agent::move_to(shelter->get_location());
	}
}

void Archer::describe() const {
	cout << "Archer ";
	Warrior::describe();
}

void Archer::make_sound() const noexcept {
	cout << get_name() << ": Twang!" << endl;
}
