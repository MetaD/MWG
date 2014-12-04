#ifndef VIEW_H
#define VIEW_H

#include "Geometry.h"
#include <string>

class View {
public:
	// Virtual destructor
    virtual ~View() {}
    
    // Remove the name and its location; no error if the name is not present.
    virtual void update_remove(const std::string& name) = 0;

	// Save the supplied name and information for future use in a draw() call
	// If the name is already present,the new information replaces the previous one.
	virtual void update_location(const std::string& name, Point location) {}
    virtual void update_health(const std::string& name, int health) {};
    virtual void update_amount(const std::string& name, double amount) {};
    
	// prints out the current map
	virtual void draw() = 0;
	
	// Discard the saved information - drawing will show only a empty pattern
	virtual void clear() = 0;
};

#endif
