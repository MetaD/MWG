#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include "Geometry.h"
#include <memory>

class Agent;
class Structure;
class Composite;

class Component: public Sim_object {
public:
	// return true if this Component is a Composite
    virtual bool is_composite() { return false; }

    // fat interface for adding component to this
    virtual void add_component(std::shared_ptr<Component> elem);

    // remove the component with the given name from its parent
    virtual void remove_component(const std::string& name);

    // return a pointer to its child. If this component is not a composite, an error will be throwed
    // if the child is not in this component, an nullptr will be throwed.
    virtual std::shared_ptr<Component> get_child(std::string name);

    // fat interface for operations, these functions throw Errors or assert
    virtual bool is_moving() const;
    virtual bool is_alive() const;
    Point get_location() const override;
    virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr);

    // Commands
    virtual void move_to(Point destination_) = 0;
    virtual void stop() = 0;
    virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) = 0;
    virtual void start_attacking(std::shared_ptr<Component> target_ptr) = 0;

    // return true iff this component has a parent
    bool has_parent() const noexcept { return !parent.expired(); }

    // declare Composite as a friend so that it can set the parent of a Component
    friend class Composite;

protected:
    // private constructor
    Component(const std::string & name) : Sim_object(name) {}

    // return true if the probe is this component's ancestor, false otherwise
    bool is_ancestor(std::shared_ptr<Component> probe) const noexcept;

private:
    std::weak_ptr<Composite> parent;
};

#endif
