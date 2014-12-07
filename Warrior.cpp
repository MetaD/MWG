#include "Warrior.h"

#include "Geometry.h"	// cartesian_distance
#include "Utility.h"
#include <iostream>
#include <cassert>
using std::cout; using std::endl;
using std::string;
using std::shared_ptr;


Warrior::Warrior(const string& name_, Point location_, int strength_, double range_) :
	Agent(name_, location_), attacking(false), strength(strength_), range(range_) {}

Warrior::Warrior(const string& name_, Point location_, int health_, int strength_, double range_) :
	Agent(name_, location_, health_), attacking(false), strength(strength_), range(range_) {}

void Warrior::update() {
	Agent::update();

	if (!is_alive() || !attacking)
		return;

	// Attacking
	shared_ptr<Agent> to_attack = target.lock();
	if (!to_attack) {
		cout << get_name() << ": Target is dead" << endl;
		attacking = false;
		target.reset();
		return;
	}
	if (to_attack && target_out_of_range()) {
		cout << get_name() << ": Target is now out of range" << endl;
		attacking = false;
		return;
	}
	make_sound();
    to_attack->take_hit(strength, shared_from_this());

	if (!to_attack->is_alive()) {
		cout << get_name() << ": I triumph!" << endl;
		attacking = false;
		target.reset();
	}
}

void Warrior::start_attacking(shared_ptr<Agent> target_ptr) {
	if (target_ptr->get_name() == get_name())
		throw Error(get_name() + ": I cannot attack myself!");
	if (!target_ptr->is_alive())
		throw Error(get_name() + ": Target is not alive!");
	if (cartesian_distance(target_ptr->get_location(), get_location()) > range)
		throw Error(get_name() + ": Target is out of range!");

	start_attacking_noexcept(target_ptr);
}

void Warrior::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
	lose_health(attack_strength);
	if (attacking && !is_alive()) {
		attacking = false;
		target.reset();
	}
}

void Warrior::stop() {
	cout << get_name() << ": Don't bother me" << endl;
}

void Warrior::describe() const {
	Agent::describe();
	if (attacking) {
		shared_ptr<Agent> target_ptr = target.lock();
		if (target_ptr)
			cout << "   Attacking " << target_ptr->get_name() << endl;
		else
			cout << "   Attacking dead target" << endl;
	}
	else
		cout << "   Not attacking" << endl;
}

void Warrior::start_attacking_noexcept(shared_ptr<Agent> target_ptr) noexcept {
	target = target_ptr;
	attacking = true;
	cout << get_name() << ": I'm attacking!" << endl;
}

bool Warrior::target_out_of_range() const {
	return target_out_of_range(target.lock());
}

bool Warrior::target_out_of_range(std::shared_ptr<Agent> new_target) const {
	assert(new_target);
	return cartesian_distance(new_target->get_location(), get_location()) > range;
}
