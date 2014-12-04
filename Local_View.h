#ifndef LOCAL_VIEW_H
#define LOCAL_VIEW_H

// A Local_View is a Grid_View centered on a fixed object

#include "Grid_View.h"

class Local_View : public Grid_View {
public:
	// default constructor sets the default size, scale, and origin
    Local_View(const std::string& name_, Point location_);

	// update the origin if the centered object has moved
    void update_location(const std::string& name, Point location)override;

	// print the name of the centered object
    void print_info() override;
    
private:
    std::string obj_name;

    // Setters should never be called for Local_Views
    void set_size(int size_) override {}
    void set_scale(double scale_) override {}
    void set_origin(Point origin_) override {}
    void set_defaults() override {}
};

#endif
