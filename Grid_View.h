#ifndef GRID_VIEW_H
#define GRID_VIEW_H

// The Grid_View provides a 2D representation of the current world

#include "View.h"
#include <vector>
#include <string>
#include <map>

class Grid_View: public View {
public:
	// prints out the current view
    void draw() override;

	// Discard the saved information
    void clear() override { memory.clear(); }

	// Save the supplied name and location for future use in a draw() call
	// If the name is already present,the new location replaces the previous one.
    void update_location(const std::string& name, Point location) override;

	// Remove the name and its data; no error if the name is not present.
    void update_remove(const std::string& name) override;

	// modify the display parameters
	// if the size is out of bounds will throw Error("New map size is too big!")
	// or Error("New map size is too small!")
    virtual void set_size(int size_);

	// If scale is not postive, will throw Error("New map scale must be positive!");
    virtual void set_scale(double scale_);

	// any values are legal for the origin
    virtual void set_origin(Point origin_);

	// does nothing in the base class
    virtual void set_defaults() {}


protected:
	// constructor
	Grid_View(int size_, double scale_, Point origin_) :
		size(size_), scale(scale_), origin(origin_) {}
    
    
    void update_bound(double & max_x, double & max_y, double & min_x, double & min_y);

    
    void print_info() override;

    // output the outside objects
    virtual void print_outsiders(std::vector<std::string> outsiders) = 0;
    

private:
    int size;
    double scale;
    Point origin;
    std::map<std::string, Point> memory;	// the name and location of saved objects
    
    bool get_subscripts(int &ix, int &iy, Point location);
};




#endif
