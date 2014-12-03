#include "Structure_factory.h"
#include "Farm.h"
#include "Town_Hall.h"
#include "Utility.h"
#include <string>
using std::string;

// Create and return the pointer to the specified Structure type. If the type
// is unrecognized, throws Error("Trying to create structure of unknown type!")
// The Structure is allocated with new, so some other component is resposible for deleting it.
std::shared_ptr<Structure> create_structure(const string& name, const string& type, Point location) {
	if (type == "Farm")
		return std::shared_ptr<Structure>(new Farm(name, location));
	else if (type == "Town_Hall")
		return std::shared_ptr<Structure>(new Town_Hall(name, location));
	else
		throw Error("Trying to create structure of unknown type!");
}
