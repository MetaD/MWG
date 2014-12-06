#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"

#include "Utility.h" //todo ??

#include "Geometry.h" // todo ??

#include <memory>

class Agent;
class Structure;


class Composite;

class Component: public Sim_object {
    
public:
    
    virtual bool is_composite()	// ?? todo in agent or here?
    {return false;}

    virtual void add_component(std::shared_ptr<Component> elem);
    virtual void remove_component(const std::string& name);

    // todo ?? virtual is unecessary todo use assert?
    virtual bool is_moving() const {throw Error(get_name() + "I do not know!");}
    virtual bool is_alive() const {throw Error(get_name() + "I do not know!");}
    virtual Point get_location() const override
    { throw Error(get_name() + "I do not have a location!"); }

    //todo ?? do nothing
    virtual void describe() const override = 0;
    virtual void update() override {}
    void broadcast_current_state() override{}
    
    
    //
    virtual void move_to(Point destination_) = 0;
    virtual void stop() = 0;
    virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) = 0;
    virtual void start_attacking(std::shared_ptr<Agent> target_) = 0;
    
    virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr)
    { throw Error(get_name() + "I cannot take hit!");}
    
    
    
    //??
    void set_parent(std::shared_ptr<Composite> parent_)
    { parent = parent_; }
    
    
    //return true iff probe is this component's ancestor
    bool is_ancestor(std::shared_ptr<Component> probe);
    
    
protected:
    Component(const std::string & name)
    :Sim_object(name){}
    
    
    
    
    
private:
    std::weak_ptr<Composite> parent;
};


#endif
