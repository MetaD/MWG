#ifndef VIEWS_H
#define VIEWS_H

#include "View.h"
#include "Geometry.h"
#include "Utility.h"
#include <map>
#include <vector>
#include <string>

// Grid_View provides a 2D representation of the current world
class Grid_View : public View {
public:
	// Save the supplied name and location for future use in a draw() call
	// If the name is already present,the new location replaces the previous one.
	void update_location(const std::string& name, Point location) override;

	// Remove the name and its data; no error if the name is not present.
	void update_remove(const std::string& name) override;

	// output the parameters (size, scale and origin)
	void describe() override;

	// prints out the current view
	void draw() override;

	// Discard the saved information
	void clear() override;

	// modify the display parameters
	// if the size is out of bounds will throw Error("New map size is too big!")
	// or Error("New map size is too small!")
	virtual void set_size(int size_);

	// If scale is not postive, will throw Error("New map scale must be positive!");
	virtual void set_scale(double scale_);

	// any values are legal for the origin
	virtual void set_origin(Point origin_);

	// does nothing for the base class
	virtual void set_defaults() {}

protected:
	// constructor
	Grid_View(int size_, double scale_, Point origin_) :
		size(size_), scale(scale_), origin(origin_) {}

	// Print the outside objects. Used for describe.
	void print_outsides();

	// Return the location of origin according to the location of the center
	Point calculate_origin(const Point& center) noexcept;

private:
	int size;
	double scale;
	Point origin;
	std::map<std::string, Point> objects;	// the name and location of objects
	std::vector<std::string> outsides;	// the outside objects

	// calculate the subscripts for the cell
	bool get_subscripts(int &ix, int &iy, Point location);
};


// Map_view is a Grid_View that can be resized, zoomed and moved
class Map_View : public Grid_View {
public:
	// default constructor sets the default size, scale, and origin
	Map_View();

	// print size, scale, origin and outside objects
	void describe() override;

	// set the parameters to the default values
	void set_defaults() override;
};


// Local_View is a Grid_View centered on a fixed object
class Local_View : public Grid_View {
public:
	// default constructor sets the default size, scale, and origin
	Local_View(const std::string& name_, const Point& location_);

	// update the origin if the centered object has moved
	void update_location(const std::string& name, Point location) override;

	// print the name of the centered object
	void describe() override;

	// Display parameters cannot be modified for local view. Will assert.
	void set_size(int size_) override;
	void set_scale(double scale_) override;
	void set_origin(Point origin_) override;

private:
	std::string name;	// name of the centered object
};


// Data_View is a list of objects associated with their data (a double)
class Data_View : public View {
public:
	// Remove the name and its location/data
	void update_remove(const std::string& name) override;

	// prints out the current map
	void draw() override;

	// Discard the saved information - drawing will show only a empty pattern
	void clear() override;

protected:
	// used by derived class to set the datum for an object
	void update_data(const std::string& name, double& data);

private:
	std::map<std::string, double> objects;	// the name and numerical data of objects
};


// Health_View is a list of objects and their health
class Health_View : public Data_View {
	// Save the supplied name and health for future use in a draw() call
	// If the name is already present,the new data replaces the previous one.
	void update_health(const std::string& name, double health) override;

	void describe() override;
};


// Amount_View is a list of objects and the food amount they have
class Amount_View : public Data_View {
	// Save the supplied name and amount for future use in a draw() call
	// If the name is already present,the new data replaces the previous one.
	void update_amount(const std::string& name, double amount) override;

	void describe() override;
};

#endif
