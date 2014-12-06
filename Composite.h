
#ifndef COMPOSITE_H
#define COMPOSITE_H


#include "Component.h"

#include <map>

class Composite: public Component, public std::enable_shared_from_this<Composite>
{
public:
    
    Composite(const std::string & name)
    :Component(name){}
    
    bool is_composite() override
    { return true; }
    
    void add_component(std::shared_ptr<Component> elem) override;
    void remove_component(const std::string& name) override;
    
    // tell this Agent to start moving to location destination_
    virtual void move_to(Point destination_) override;
    
    // tell this Agent to stop its activity
    virtual void stop() override;
    
    /* Fat Interface for derived classes */
    // Throws exception that an Agent cannot work.
    virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) override;
    
    // Throws exception that an Agent cannot attack.
    virtual void start_attacking(std::shared_ptr<Agent> target_) override;
    
    

    
private:
    std::map<std::string, std::shared_ptr<Component>> children;
};

#endif 
