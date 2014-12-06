#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"
#include <string>
#include <map>

//?? TODO ADD COMMENTS

class Composite: public Component, public std::enable_shared_from_this<Composite> {
public:
    Composite(const std::string & name) : Component(name) {}
        
    bool is_composite() override { return true; }

    void add_component(std::shared_ptr<Component> elem) override;
    void remove_component(const std::string& name) override;

    void describe() const override;

    // tell all the children to start moving to location destination_
    void move_to(Point destination_) override;
    
    // tell all the children to stop its activity
    void stop() override;

    void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) override;
    void start_attacking(std::shared_ptr<Agent> target_) override;
    
    
private:
    std::map<std::string, std::shared_ptr<Component>> children;
};

#endif
