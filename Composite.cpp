
#include "Composite.h"

//#include "Agent.h"
#include "Geometry.h"
#include "Utility.h"

#include <algorithm>
//#include <functional>

using std::for_each; using std::bind;
using std::shared_ptr;

void Composite::add_component(std::shared_ptr<Component> elem)
{
    if( shared_ptr<Composite> composite = std::dynamic_pointer_cast<Composite>(elem) ){
        //add each individual to this group
        for (auto &p: composite->children)
            children[p.first] = p.second;
    }else{
        children[elem->get_name()] = elem;
    }

}

void Composite::remove_component(const std::string& name)
{
    children.erase(name);
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
//    for_each(children.begin(), children.end(),
//             bind(&Component::start_working, source_, destination_));
    for(auto & p : children)
        p.second->start_working(source_, destination_);

}

void Composite::start_attacking(std::shared_ptr<Agent> target_)
{
//    for_each(children.begin(),children.end(), bind(&Component::start_attacking, target_));
}