#include "Global_View.h"
#include <iostream>
#include <limits>
#include <cassert>

using std::string;
using std::cout; using std::endl;
using std::min; using std::max;
using std::numeric_limits;

const int Global_View_size_c = 20;
const double initial_Global_View_scale_c = 2.0;
const Point initial_Global_View_origin_c(-10.0, -10.0);
const double min_side_length_c = 5.0;

Global_View::Global_View() :
Grid_View(Global_View_size_c, initial_Global_View_scale_c,
          initial_Global_View_origin_c){}


void Global_View::draw()
{
    double max_x, max_y, min_x, min_y;
    
    Grid_View::update_bound(max_x, max_y, min_x, min_y);

    double side_length = max(max_y - min_y, max_x - min_x);
    side_length = max(side_length, min_side_length_c);
    // side length must be big enough to make sense
    
    Grid_View::set_scale(side_length / (Global_View_size_c - 1));
    // Use (size - 1) to avoid rounding problem
    
    Grid_View::set_origin(Point(min_x, min_y));
    
    Grid_View::draw();
}

void Global_View::print_info() {
    cout << "Global View of the world:" << endl;
}

void Global_View::print_outsiders(std::vector<std::string> outsiders)
{
    // there should be not outsiders in Global View
    assert(outsiders.size() == 0);
}


void Global_View::set_size(int size_) {
    assert(0);
}

void Global_View::set_scale(double scale_) {
    assert(0);
}

void Global_View::set_origin(Point origin_) {
    assert(0);
}

void Global_View::set_defaults() {
    assert(0);
}
