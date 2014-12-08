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
    assert(0);
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

void Component::take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr)
{
    { throw Error(get_name() + " cannot take hit!"); }
}



bool Component::is_ancestor(shared_ptr<Component> probe) {
    shared_ptr<Component> ancestor = parent.lock();
    while (ancestor) {
        if (ancestor == probe)
        	return true;
        ancestor = (ancestor->parent).lock();
    }
    return false;
}
