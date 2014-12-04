#ifndef MAP_VIEW_H
#define MAP_VIEW_H

// Map_view is a kind of Grid_View that can be resized, zoomed and moved

#include "Grid_View.h"


class Map_View: public Grid_View {
public:
	Map_View();

	// Print the parameter information and the outside objects
    void print_info() override;

	// set the parameters to the default Map_View values
	void set_defaults() override;
};


#endif 
