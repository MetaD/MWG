#include "Grid_View.h"
#include "Utility.h"

#include <iomanip>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>

using std::numeric_limits;
using std::string;
using std::vector;
using std::cout; using std::endl;
using std::for_each;
using std::setw;
using std::max; using std::min;

// map size should fall in [7, 30]
const int max_size_c = 30;
const int min_size_c = 7;

const int label_field_width_c = 4;	// field width for integer axis labels
const int label_interval_c = 3;	// number of spaces between two labels


void Grid_View::update_location(const std::string& name, Point location) {
    memory[name] = location;
}


void Grid_View::update_remove(const std::string &name) {
    memory.erase(name);
}


void Grid_View::draw() {
    // create 2-D string map of size * size and initialize it to the empty pattern
	vector< vector<string> > map(size, vector<string>(size, ". "));

	// calculate subscripts, store outside objects, and setup the map
	for (auto& object : memory) {
		int ix, iy;
		if (!get_subscripts(ix, iy, object.second)){ // object is outside the map
			outsiders.push_back(object.first);
			continue;
		}
		if (map[iy][ix][0] == '.')
			// the first two chars of the name will appear on the corresponding location
			map[iy][ix] = object.first.substr(0, 2);
		else
			// multiple object on the same location
			map[iy][ix] = "* ";
	}

    print_info();	// output a description of the current map

	// save and reset output parameters so that the labels will appear as integers
    auto old_precision = cout.precision();
    cout.precision(0);

    // print the map
	for (int row = size - 1; row >= 0; --row) {
		// labels on y axis
		if (row % label_interval_c == 0)	// output label
			cout << setw(label_field_width_c) << origin.y + row * scale << " ";
		else
			cout << "     ";
		// the location points
		for_each(map[row].begin(), map[row].end(), [](string& point)
                                    { cout << point; });
		cout << endl;
	}
    // print x-axis
    for (int col = 0; col < size; col += label_interval_c) {
        cout << "  " << setw(label_field_width_c) << origin.x + col * scale ;
    }
    cout << endl;
    
    cout.precision(old_precision);	// restore previous precision
	outsiders.clear();	// reset outsiders
}


void Grid_View::print_info() {
	cout << "Display size: " << size << ", scale: " << scale
        << ", origin: " << origin << endl;
}


void Grid_View::print_outsiders() {
	if (outsiders.empty())
		return;
	for(size_t i = 0; i < outsiders.size(); ++i)
		 // output a comma before all names except the first
		cout << (i == 0 ? "" : ", ") << outsiders[i];
	cout << " outside the map" << endl;
}


void Grid_View::set_size(int size_) {
    if (size_ > max_size_c)
        throw Error("New map size is too big!");
    else if (size_ < min_size_c)
        throw Error("New map size is too small!");

    size = size_;
}

void Grid_View::set_scale(double scale_) {
	if (scale_ < numeric_limits<double>::epsilon())	// scale_ <= 0.0
    	throw Error("New map scale must be positive!");
    scale = scale_;
}

void Grid_View::set_origin(Point origin_) {
    origin = origin_;
}


void Grid_View::update_bound(double &max_x, double &max_y, double &min_x, double &min_y)
{
    max_x = max_y = numeric_limits<double>::min();
    min_x = min_y = numeric_limits<double>::max();
    
    for(auto & p : memory){
        Point location = p.second;
        min_x = min(min_x, location.x);
        max_x = max(max_x, location.x);
        min_y = min(min_y, location.y);
        max_y = max(max_y, location.y);
    }
    
}

// Calculate the cell subscripts corresponding to the supplied location parameter,
// using the current size, scale, and origin of the display.
// This function assumes that origin is a  member variable of type Point,
// scale is a double value, and size is an integer for the number of rows/columns
// currently being used for the grid.
// Return true if the location is within the grid, false if not
bool Grid_View::get_subscripts(int &ix, int &iy, Point location)
{
    // adjust with origin and scale
    Cartesian_vector subscripts = (location - origin) / scale;
    // truncate coordinates to integer after taking the floor
    // floor function will return the largest integer smaller than the supplied value
    // even for negative values, so -0.05 => -1., which will be outside the array.
    ix = int(floor(subscripts.delta_x));
    iy = int(floor(subscripts.delta_y));
    // if out of range, return false
    if ((ix < 0) || (ix >= size) || (iy < 0) || (iy >= size)) {
        return false;
    }
    else
        return true;
}

