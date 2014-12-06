
#include "Composite.h"
#include "Geometry.h"
#include "Utility.h"

#include <algorithm>
#include <cassert>

#include <iostream>

#include "Agent.h" // ?? todo


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
    
    cout << elem->get_name() << " is added to group " << get_name() << endl;
}

void Composite::remove_component(const std::string& name)
{
    if (children.find(name) == children.end()){
        cout << name << " is not in group "  << get_name() << "!" << endl;
        return;
    }

    Component::remove_component(name);
    children.erase(name);

    cout << name << " is removed from group " << get_name() << endl;
}

void Composite::describe() const
{
    cout << "Group " << get_name() <<" has " << children.size() << " component(s):" << endl;

    for(auto &p:children)
        cout << "   " << p.second->get_name() << endl;
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
    } //?? todo
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
