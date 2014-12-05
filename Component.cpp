#include "Component.h"
#include "Composite.h"
#include "Utility.h"

#include <cassert>

void Component::add_component(std::shared_ptr<Component> elem)
{
    throw Error( get_name() + ": I cannot Add a component!");
}

//remove this component from its parent
void Component::remove_component(const std::string& name)
{
    if (name == get_name() && parent) {
        parent->remove_component(name);
        parent = nullptr;
    }
}


bool Component::is_ancestor(std::shared_ptr<Component> probe)
{
    std::shared_ptr<Component> ancestor = parent;
    while(ancestor){
        if(ancestor == probe) return true;
        ancestor = ancestor->parent;
    }
    return false;
}
