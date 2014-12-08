#ifndef SIM_OBJECT_H
#define SIM_OBJECT_H

#include <string>
class Point;

/* The Sim_object class provides the interface for all of simulation objects. 
It also stores the object's name, and has pure virtual accessor functions for 
the object's position and other information. */

class Sim_object {
public:
	// virtual destructor
	virtual ~Sim_object() {}

	const std::string& get_name() const
		{ return name; }

	// ask model to notify views of current state
    virtual void broadcast_current_state() {}
    
    // update status for this object
	virtual void update(){}
    
    // Pure virtual functions
	virtual Point get_location() const = 0;
	virtual void describe() const = 0;

protected:
	Sim_object(const std::string& name_);

private:
	std::string name;
};

#endif
