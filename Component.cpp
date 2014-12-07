#include "Component.h"
#include "Composite.h"
#include "Utility.h"
using std::shared_ptr;
using std::string;


void Component::remove_component(const string& name) {
    shared_ptr<Composite> parent_ptr = parent.lock();
    if (name == get_name() && parent_ptr) {
    	// remove this component from its parent
    	parent_ptr->remove_component(name);
        parent.reset();
    }
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
