#ifndef OVERALL_VIEW_H
#define OVERALL_VIEW_H

#include "Grid_View.h"

class Overall_View : public Grid_View {
public:
    Overall_View();

    // print the information of the Overall_Map
    void print_info() override;

    // update the object location, and reset borders, scale and origin as needed
    void update_location(const std::string& name, Point location) override;
    
private:
    double min_x, max_x, min_y, max_y;	// borders of the overall map

    // Setters should never be called for Overall_Views
    void set_size(int size_) override {}	//?? TODO use assert
    void set_scale(double scale_) override {}
    void set_origin(Point origin_) override {}
    void set_defaults() override {}
};

#endif 
