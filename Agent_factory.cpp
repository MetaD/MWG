#include "Agent_factory.h"
#include "Peasant.h"
#include "Soldier.h"
#include "Archer.h"
#include "Commander.h"

#include "Utility.h"

using std::string;

// Create and return the pointer to the specified Agent type. If the type
// is unrecognized, throws Error("Trying to create agent of unknown type!")
// The Agent is allocated with new, so some other component is resposible for deleting it.
std::shared_ptr<Agent> create_agent(const string& name, const string& type, Point location) {
	if (type == "Peasant")
		return std::shared_ptr<Agent>(new Peasant(name, location));
	else if (type == "Soldier")
		return std::shared_ptr<Agent>(new Soldier(name, location));
	else if (type == "Archer")
		return std::shared_ptr<Agent>(new Archer(name, location));
	else if (type == "Commander")
		return std::shared_ptr<Agent>(new Commander(name, location));
	else
		throw Error("Trying to create agent of unknown type!");
}
