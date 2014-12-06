
#include "Composite.h"
#include "Geometry.h"
#include "Utility.h"

#include <algorithm>
#include <cassert>

#include <iostream>

#include "Agent.h" // ?? todo
#include <iostream> // ?? todo

using std::for_each; using std::bind;
using std::shared_ptr;
using std::cout; using std::endl;


void Composite::add_component(std::shared_ptr<Component> elem)
{
    //check is elem valid? if it's this's parent
    if( is_ancestor(elem) )
        throw Error(get_name() + "I cannot add my ancestor as my child!");
    
    
    children[elem->get_name()] = elem;
    elem->set_parent(shared_from_this());
}

void Composite::remove_component(const std::string& name)
{
    Component::remove_component(name);
    children.erase(name);
}

void Composite::describe() const
{
    cout << "Group " << get_name() <<" has " << children.size() << " components: ";
    
    size_t i = children.size();
    for(auto &p:children){
        i--;
        cout << p.second->get_name();
        cout << (i==0 ? "." : ", ");
    }
    
    cout << endl;
}




void Composite::move_to(Point destination_)
{
    for(auto & p : children)
        p.second->move_to(destination_);
}

void Composite::stop()
{
    for(auto & p : children)
        p.second->stop();
}

void Composite::start_working(std::shared_ptr<Structure> source_,
                              std::shared_ptr<Structure> destination_)
{
    for(auto & p : children){
        try{
            p.second->start_working(source_, destination_);
        }catch (Error& err){
            handle_error(err);
        }
    }
}

void Composite::start_attacking(std::shared_ptr<Agent> target_)
{
    assert(target_);
    
    for(auto & p : children){
        try{
            p.second->start_attacking( target_ );
        }catch (Error& err){
            handle_error(err);
        }
    }
}


bool Composite::is_composite()
{ return true; }
