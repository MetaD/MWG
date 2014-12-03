#include "Soldier.h"
#include <iostream>
using std::cout; using std::endl;
using std::string;
using std::shared_ptr;

static const int soldier_initial_strenth_c = 2;
static const double soldier_initial_attack_range_c = 2.0;


Soldier::Soldier(const string& name_, Point location_) :
		Warrior(name_, location_, soldier_initial_strenth_c,
				soldier_initial_attack_range_c) {}

Soldier::Soldier(const std::string& name_, Point location_, int health_) :
		Warrior(name_, location_, health_, soldier_initial_strenth_c,
				soldier_initial_attack_range_c) {}

void Soldier::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
	Warrior::take_hit(attack_strength, attacker_ptr);
	if (!is_attacking() && is_alive() && attacker_ptr->is_alive())	// counter-attack
		start_attacking_noexcept(attacker_ptr);
}

void Soldier::describe() const {
	cout << "Soldier ";
	Warrior::describe();
}

void Soldier::make_sound() const noexcept {
	cout << get_name() << ": Clang!" << endl;
}
