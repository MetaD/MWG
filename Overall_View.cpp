//#define NDEBUG
#include "Overall_View.h"
#include <iostream>
#include <limits>
#include <cassert>

using std::string;
using std::cout; using std::endl;
using std::min; using std::max;
using std::numeric_limits;

const int overall_view_size_c = 25;
const double initial_overall_view_scale_c = 2.0;
const Point initial_overall_view_origin_c(-10.0, -10.0);
const double min_side_length_c = 5.0;

Overall_View::Overall_View() :
Grid_View(overall_view_size_c, initial_overall_view_scale_c,
          initial_overall_view_origin_c)
{}


void Overall_View::draw()
{
    double max_x, max_y, min_x, min_y;
    
    Grid_View::update_bound(max_x, max_y, min_x, min_y);

    double side_length = max(max_y - min_y, max_x - min_x);
    side_length = max(side_length, min_side_length_c);
    // side length must be big enough to make sense
    
    Grid_View::set_scale(side_length / (overall_view_size_c - 1));
    // Use (size - 1) to avoid rounding problem
    
    Grid_View::set_origin(Point(min_x, min_y));
    
    
    Grid_View::draw();
}

void Overall_View::print_info() {
    cout << "Overall View of the world:" << endl;
}
