#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include "Utility.h" //todo ??
#include "Geometry.h"
#include <memory>
#include <string>

class Agent;
class Structure;
class Composite;

class Component: public Sim_object {
public:
	// return true if this Component is a Composite
    virtual bool is_composite() { return false; }

    // fat interface for adding component to this
    virtual void add_component(std::shared_ptr<Component> elem)
		{ throw Error(get_name() + ": I cannot add!"); }	//??todo use assert

    // remove the component with the given name from its parent
    virtual void remove_component(const std::string& name);

    // fat interface for operations				//todo ?? virtual is unecessary todo use assert?
    virtual bool is_moving() const
    	{ throw Error(get_name() + " is not an object!"); }
    virtual bool is_alive() const
    	{ throw Error(get_name() + " is not an object!"); }
    Point get_location() const override
    	{ throw Error(get_name() + " does not have a location!"); }
    virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr)
    	{ throw Error(get_name() + " cannot take hit!"); }	//?? todo use assert
    virtual void move_to(Point destination_) = 0;
    virtual void stop() = 0;
    virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) = 0;
    virtual void start_attacking(std::shared_ptr<Agent> target_) = 0;

    // set the parent to the given pointer
    void set_parent(std::shared_ptr<Composite> parent_) { parent = parent_; }

protected:
    // private constructor
    Component(const std::string & name) : Sim_object(name) {}

    // return true if the probe is this component's ancestor, false otherwise
    bool is_ancestor(std::shared_ptr<Component> probe);

private:
    std::weak_ptr<Composite> parent;
};

#endif
