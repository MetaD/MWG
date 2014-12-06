#include "Agent.h"
#include "Model.h"
#include "Utility.h"
#include <iostream>
using std::cout; using std::endl;
using std::string;
using std::shared_ptr;

static const int initial_health_c = 5;
static const double initial_speed_c = 5.0;

Agent::Agent(const string& name_, Point location_) : Component(name_),
		alive(true), health(initial_health_c), movement(location_, initial_speed_c) {}

Agent::Agent(const std::string& name_, Point location_, int health_) :
		Agent(name_, location_) {
	health = health_;
}

Point Agent::get_location() const {
	return movement.get_current_location();
}

bool Agent::is_moving() const {
	return movement.is_currently_moving();
}

void Agent::move_to(Point destination_) {
	movement.start_moving(destination_);
	if (movement.is_currently_moving())
		cout << get_name() << ": I'm on the way" << endl;
	else
		cout << get_name() << ": I'm already there" << endl;
}

void Agent::stop(){
	if (movement.is_currently_moving()) {
		movement.stop_moving();
		cout << get_name() << ": I'm stopped" << endl;
	}
}

void Agent::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr) {
	lose_health(attack_strength);
}

void Agent::update() {
	if (!alive || !movement.is_currently_moving())
		return;
	if (movement.update_location())
		cout << get_name() << ": I'm there!"<< endl;
	else
		cout << get_name() << ": step..." << endl;
	Model::get_model().notify_location(get_name(), movement.get_current_location());
}

void Agent::describe() const {
	cout << get_name() << " at " << get_location() << endl;
	cout << "   Health is " << health << endl;
	if (movement.is_currently_moving())
		cout << "   Moving at speed " << movement.get_current_speed()
			 << " to " << movement.get_current_destination() << endl;
	else
		cout << "   Stopped" << endl;
}

void Agent::broadcast_current_state() {
	Model::get_model().notify_location(get_name(), movement.get_current_location());
	Model::get_model().notify_health(get_name(), health);
}

void Agent::start_working(shared_ptr<Structure>, shared_ptr<Structure>) {
	throw Error(get_name() + ": Sorry, I can't work!");
}

void Agent::start_attacking(shared_ptr<Agent>) {
	throw Error(get_name() + ": Sorry, I can't attack!");
}

void Agent::lose_health(int attack_strength) {
	health -= health < attack_strength ? health : attack_strength;	// the less one
	Model::get_model().notify_health(get_name(), health);
	if (health == 0) {
		alive = false;
		cout << get_name() << ": Arrggh!" << endl;
		Model::get_model().notify_gone(get_name());
		Model::get_model().remove_agent_component(shared_from_this());
	}
	else
		cout << get_name() << ": Ouch!" << endl;
}
