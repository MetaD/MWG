#include "Local_View.h"

#include <iostream>
#include <cassert>
using std::string;

const int local_view_size_c = 9;
const double local_view_scale_c = 2.0;

// A local helper function to calculate and return the location of origin
// given the location of the map center
Point calculate_origin(const Point& center);


Local_View::Local_View(const string& name_, Point location_) :
		Grid_View(local_view_size_c, local_view_scale_c, calculate_origin(location_)),
		obj_name(name_) {}

void Local_View::update_location(const std::string& name, Point location) {
    Grid_View::update_location(name, location);

    if (name == obj_name)
    	Grid_View::set_origin(calculate_origin(location));
}

Point calculate_origin(const Point& center) {
    // difference between the coordinates of the center and the origin
	double distance = (local_view_size_c / 2.) * local_view_scale_c;
	return Point(center.x - distance, center.y - distance);
}

void Local_View::print_info() {
    std::cout << "Local view for: " << obj_name << std::endl;
}


void Local_View::set_size(int size_) {
    assert(0);
}

void Local_View::set_scale(double scale_) {
    assert(0);
}

void Local_View::set_origin(Point origin_) {
    assert(0);
}

void Local_View::set_defaults() {
    assert(0);
}
