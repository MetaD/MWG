#include "Commander.h"
#include "Soldier.h"	// for Commander's steward
#include "Model.h"
#include "Geometry.h"

#include <iostream>
using std::cout; using std::endl;
using std::shared_ptr;

static const int Commander_initial_strenth_c = 1;
static const double Commander_initial_attack_range_c = 2.5;
static const int steward_initial_health_c = 1;

const double steward_dismiss_distance_c = 8.0;
    // when the distance between the steward and its boss exceeds this number,
    // it will leave

Commander::Commander(const std::string& name_, Point location_) :
		Warrior(name_, location_, Commander_initial_strenth_c,
				Commander_initial_attack_range_c) {}

void Commander::update() {
	Warrior::update();

    shared_ptr<Soldier> steward_ptr = steward.lock();

	if (steward_ptr &&
        cartesian_distance(steward_ptr->get_location(), get_location())
                            > steward_dismiss_distance_c) {
		// steward dismissed silently when out of the range
        disband_steward();
    }
}

void Commander::take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) {
	Warrior::take_hit(attack_strength, attacker_ptr);

    if (!is_alive()){
        disband_steward();
        return;
    }

	if (!attacker_ptr->is_alive())  return;

	if (!is_attacking()) // counter-attack
		start_attacking_noexcept(attacker_ptr);

    shared_ptr<Soldier> steward_ptr = steward.lock();

	if (steward_ptr)	// steward already summoned - cannot do anything
		return;

	// the Commander does not have a steward yet
	// Summon a soldier steward with health = 1 at the attacker's location
	cout << get_name() << ": We will fight as one!" << endl;
	steward_ptr =  shared_ptr<Soldier>(new Soldier(get_name() + "_steward",
				attacker_ptr->get_location(), steward_initial_health_c));
	Model::get_model().add_component(steward_ptr);
	// command it to attack the attacker
	steward_ptr->start_attacking(attacker_ptr);
    steward = steward_ptr;
}

void Commander::describe() const {
	cout << "Commander ";
	Warrior::describe();
}

void Commander::disband_steward() {
    shared_ptr<Soldier> steward_ptr = steward.lock();
    if(steward_ptr){
        cout << steward_ptr->get_name() << ": Good-bye, my lord" << endl;
        Model::get_model().notify_gone(steward_ptr->get_name());
        Model::get_model().remove_component(steward_ptr);
        steward.reset();
    }
}

void Commander::make_sound() const noexcept {
	cout << get_name() << ": Neighhh!" << endl;
}
    

