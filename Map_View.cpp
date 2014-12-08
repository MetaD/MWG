#include "Map_View.h"

#include <iostream>

const int default_map_view_size_c = 25;
const double default_map_view_scale_c = 2.0;
const Point default_map_view_origin_c(-10.0, -10.0);


Map_View::Map_View() : Grid_View(default_map_view_size_c,
								 default_map_view_scale_c,
								 default_map_view_origin_c) {}


void Map_View::print_info() {
	Grid_View::print_info();
}


void Map_View::set_defaults() {
	set_size(default_map_view_size_c);
	set_scale(default_map_view_scale_c);
	set_origin(default_map_view_origin_c);
}


void Map_View::print_outsiders(std::vector<std::string> outsiders) {
    if (outsiders.empty())
        return;
    for(size_t i = 0; i < outsiders.size(); ++i)
        // output a comma before all names except the first
        std::cout << (i == 0 ? "" : ", ") << outsiders[i];
    std::cout << " outside the map" << std::endl;
}

