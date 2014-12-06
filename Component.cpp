#include "Component.h"
#include "Composite.h"
#include "Utility.h"

#include <cassert>

using std::shared_ptr;


void Component::add_component(std::shared_ptr<Component> elem)
{
    throw Error( get_name() + ": I cannot Add a component!");
}

//remove this component from its parent
void Component::remove_component(const std::string& name)
{
    shared_ptr<Composite> parent_lock = parent.lock();
    if (name == get_name() && parent_lock ) {
        parent_lock->remove_component(name);
        parent.reset();
    }
}


bool Component::is_ancestor(std::shared_ptr<Component> probe)
{
    std::shared_ptr<Component> ancestor = parent.lock();
    while(ancestor){
        if(ancestor == probe) return true;
        ancestor = (ancestor->parent).lock();
    }
    return false;
}
