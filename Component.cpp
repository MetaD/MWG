#include "Component.h"
#include "Composite.h"
#include "Utility.h"
#include <cassert>
using std::shared_ptr;
using std::string;


void Component::add_component(std::shared_ptr<Component> elem) {
    assert(0);
}

void Component::remove_component(const string& name) {
    shared_ptr<Composite> parent_ptr = parent.lock();
    if (name == get_name() && parent_ptr) {
    	// remove this component from its parent
    	parent_ptr->remove_component(name);
        parent.reset();
    }
}

shared_ptr<Component> Component::get_child(std::string name) {
    throw Error(get_name() + "I do not have a child!");
}

bool Component::is_moving() const {
    throw Error(get_name() + " is not an object!");
}

bool Component::is_alive() const {
    throw Error(get_name() + " is not an object!");
}

Point Component::get_location() const {
    throw Error(get_name() + " does not have a location!");
}

void Component::take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) {
	throw Error(get_name() + " cannot take hit!");
}

void Component::start_attacking(shared_ptr<Component> target_ptr) {
    assert(target_ptr);
	if (target_ptr->is_composite())
		throw Error(target_ptr->get_name() + "is not an agent!");
}

bool Component::is_ancestor(shared_ptr<Component> probe) const noexcept {
    shared_ptr<Component> ancestor = parent.lock();
    while (ancestor) {
        if (ancestor == probe)
        	return true;
        ancestor = (ancestor->parent).lock();
    }
    return false;
}
