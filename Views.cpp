#include "Views.h"
#include "Geometry.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <cassert>
using std::cout; using std::endl;
using std::numeric_limits;
using std::setw;
using std::vector;
using std::string;
using std::for_each;

static const int default_map_view_size_c = 25;
static const double default_map_view_scale_c = 2.0;
static const Point default_map_view_origin_c(-10.0, -10.0);

static const int local_view_size_c = 9;
static const double local_view_scale_c = 2.0;

//----------------------------------------- Grid_View ----------------------------------------//

void Grid_View::update_location(const std::string& name, Point location) {
	// change its location if the object exists, insert it otherwise
	objects[name] = location;
}

void Grid_View::update_remove(const std::string& name) {
	objects.erase(name);
}

void Grid_View::draw() {
	// initialize to the empty pattern
	vector< vector<string> > map(size, vector<string>(size, ". "));

	// calculate subscripts, store outside objects, and change the map
	for (auto& object : objects) {
		int ix, iy;
		if (!get_subscripts(ix, iy, object.second)) {	// object is outside the map
			outsides.push_back(object.first);
			continue;
		}
		if (map[iy][ix][0] == '.')
			// the first two chars of the name will appear on the corresponding location
			map[iy][ix] = object.first.substr(0, 2);
		else
			// multiple object on the same location
			map[iy][ix] = "* ";
	}

	// output a description (Hollywood principle)
	describe();

	// output the map
	auto prev_precision = cout.precision();
	cout.precision(0);	// labels will be output as integers
	for (int row = size - 1; row >= 0; --row) {
		// labels on y axis
		if (row % 3 == 0)	// output label
			cout << setw(4) << origin.y + row * scale << " ";
		else
			cout << "     ";
		// map
		for_each(map[row].begin(), map[row].end(), [](string& point){ cout << point; });
		cout << endl;
	}
	// labels on x axis
	for (int col = 0; col < size; ++col) {
		if (col % 3 == 0)
			cout << "  " << setw(4) << origin.x + col * scale;
	}
	cout << endl;
	cout.precision(prev_precision);	// restore previous precision
	outsides.clear();
}

void Grid_View::describe() {
	cout << "Display size: " << size << ", scale: " << scale << ", origin: " << origin << endl;
}

void Grid_View::print_outsides() {
	if (outsides.empty())
		return;
	for(size_t i = 0; i < outsides.size(); ++i) {
		if (i != 0)
			cout << ", "; // output before all names except the first
		cout << outsides[i];
	}
	cout << " outside the map" << endl;
}

void Grid_View::clear() {
	objects.clear();
}

void Grid_View::set_size(int size_) {
	if (size_ > 30)
		throw Error("New map size is too big!");
	else if (size_ <= 6)
		throw Error("New map size is too small!");
	else
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

Point Grid_View::calculate_origin(const Point& location) noexcept {
	double variation = (local_view_size_c/2.) * local_view_scale_c;
	return Point(location.x - variation, location.y - variation);
}

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

//----------------------------------------- Map_View -----------------------------------------//

Map_View::Map_View() :
		Grid_View(default_map_view_size_c, default_map_view_scale_c, default_map_view_origin_c) {}

void Map_View::describe() {
	Grid_View::describe();
	print_outsides();
}

void Map_View::set_defaults() {
	set_size(default_map_view_size_c);
	set_scale(default_map_view_scale_c);
	set_origin(default_map_view_origin_c);
}

//---------------------------------------- Local_View ----------------------------------------//

Local_View::Local_View(const string& name_, const Point& location_) :
		Grid_View(local_view_size_c, local_view_scale_c, calculate_origin(location_)),  name(name_) {}

void Local_View::update_location(const std::string& name_, Point location) {
	Grid_View::update_location(name_, location);
	if (name_ == name)
		Grid_View::set_origin(calculate_origin(location));
}

void Local_View::describe() {
	cout << "Local view for: " << name << endl;
}

void Local_View::set_size(int size_) { assert(false); }
void Local_View::set_scale(double scale_) { assert(false); }
void Local_View::set_origin(Point origin_) { assert(false); }

//----------------------------------------- Data_View ----------------------------------------//

void Data_View::update_remove(const std::string& name) {
	objects.erase(name);
}

void Data_View::draw() {
	describe();
	cout << "--------------" << endl;
	for(auto& object : objects)
		cout << object.first << ": " << object.second << endl;
	cout << "--------------" << endl;
}

void Data_View::clear() {
	objects.clear();
}

void Data_View::update_data(const std::string& name, double& data) {
	// change its data if the object exists, insert it otherwise
	objects[name] = data;
}

//---------------------------------------- Health_View ---------------------------------------//

void Health_View::update_health(const std::string& name, double health) {
	Data_View::update_data(name, health);
}

void Health_View::describe() {
	cout << "Current Health:" << endl;
}

//---------------------------------------- Amount_View ---------------------------------------//

void Amount_View::update_amount(const std::string& name, double amount) {
	Data_View::update_data(name, amount);
}

void Amount_View::describe() {
	cout << "Current Amounts:" << endl;
}
