#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include <memory>

class Agent;
class Structure;

class Component: public Sim_object {
    
public:
    virtual void add_component(std::shared_ptr<Component> elem);
    virtual void remove_component(const std::string& name);
    
    
    Point get_location() const = 0; //todo ??
    void describe() const override {}
    void update() override {}


    // tell this Agent to start moving to location destination_
    virtual void move_to(Point destination_) = 0;
    
    // tell this Agent to stop its activity
    virtual void stop() = 0;
    
    /* Fat Interface for derived classes */
    // Throws exception that an Agent cannot work.
    virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) = 0;
    
    // Throws exception that an Agent cannot attack.
    virtual void start_attacking(std::shared_ptr<Agent>) = 0;

   
    
    
    
//    // return this Agent's location
//    Point get_location() const override;
//    
//    // return true if this Agent is in motion
//    bool is_moving() const;
//    bool is_alive() const;
//    // Tell this Agent to accept a hit from an attack of a specified strength
//    // The attacking Agent identifies itself with its this pointer.
//    // A derived class can override this function.
//    // The function lose_health is called to handle the effect of the attack.
//    virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr);
//    
//    // update the moving state and Agent state of this object.
//    void update() override;
//    
//    // output information about the current state
//    void describe() const override;
//    
//    // ask Model to broadcast our current state to all Views
//    void broadcast_current_state() override;
    
protected:
    Component(const std::string & name)
    :Sim_object(name){}
};


#endif
