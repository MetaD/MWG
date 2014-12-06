#include "Component.h"
#include "Composite.h"
#include "Utility.h"

#include <cassert>

using std::shared_ptr;
using std::string;

// remove this component from its parent
void Component::remove_component(const string& name)	//?? TODO put it in Agent!!!
{
    shared_ptr<Composite> parent_lock = parent.lock();
    if (name == get_name() && parent_lock) {
        parent_lock->remove_component(name);
        parent.reset();
    }
}

bool Component::is_ancestor(shared_ptr<Component> probe)
{
    shared_ptr<Component> ancestor = parent.lock();
    while(ancestor){
        if(ancestor == probe) return true;
        ancestor = (ancestor->parent).lock();
    }
    return false;
}
