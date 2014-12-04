#include "Model.h"
#include "Agent_factory.h"
#include "Structure_factory.h"
#include "Geometry.h"
#include "Structure.h"
#include "Agent.h"
#include "View.h"
#include "Utility.h"
#include <algorithm>
#include <functional>
#include <cassert>
#include <iterator>
#include <limits>
using std::numeric_limits;
using std::next;
using std::map;
using std::string;
using std::shared_ptr;
using std::pair;


// A helper function to find the nearest element in the given range
template <typename Map_iterator_t>
static Map_iterator_t find_nearest(Map_iterator_t begin, Map_iterator_t end,
							const std::string& name, Point location);

Model::Model() : time(0) {
	// initial structures and agents
	shared_ptr<Structure> initial_stc[] {
		create_structure("Rivendale", "Farm", Point(10., 10.)),
		create_structure("Sunnybrook", "Farm", Point(0., 30.)),
		create_structure("Shire", "Town_Hall", Point(20., 20.)),
		create_structure("Paduca", "Town_Hall", Point(30., 30.)),
	};
	shared_ptr<Agent> initial_agt[] {
		create_agent("Pippin", "Peasant", Point(5., 10.)),
		create_agent("Merry", "Peasant", Point(0., 25.)),
		create_agent("Zug", "Soldier", Point(20., 30.)),
		create_agent("Bug", "Soldier", Point(15., 20.)),
		create_agent("Iriel", "Archer", Point(20., 38.))
	};

    for (auto& stc : initial_stc) {        // insert to structures and sim_objects
        structures.insert({stc->get_name(), stc});
        sim_objects.insert({stc->get_name(), stc});
    }
    for (auto& agt : initial_agt) {        // insert to agents and sim_objects
        agents.insert({agt->get_name(), agt});
        sim_objects.insert({agt->get_name(), agt});
    }
}

bool Model::is_name_in_use(const string& name) const {
	if (sim_objects.count(name) > 0)
		return true;
	return false;
}

bool Model::is_structure_present(const string& name) const {
	return structures.find(name) != structures.end();
}

void Model::add_structure(shared_ptr<Structure> new_stc) {
	structures.insert({new_stc->get_name(), new_stc});
	sim_objects.insert({new_stc->get_name(), new_stc});
	new_stc->broadcast_current_state();
}

shared_ptr<Structure> Model::get_structure_ptr(const string& name) const {
	auto stc_it = structures.find(name);
	if (stc_it == structures.end())
		throw Error("Structure not found!");
	return stc_it->second;
}

bool Model::is_agent_present(const string& name) const {
	return agents.find(name) != agents.end();
}

void Model::add_agent(shared_ptr<Agent> new_agt) {
	agents.insert({new_agt->get_name(), new_agt});
	sim_objects.insert({new_agt->get_name(), new_agt});
	new_agt->broadcast_current_state();
}

void Model::remove_agent(shared_ptr<Agent> agent) {
	string name = agent->get_name();
	sim_objects.erase(name);
	agents.erase(name);
}

shared_ptr<Agent> Model::get_agent_ptr(const string& name) const {
	auto agt_it = agents.find(name);
	if (agt_it == agents.end())
		throw Error("Agent not found!");
	return agt_it->second;
}

void Model::describe() const {
	for (auto& sim : sim_objects)
		sim.second->describe();
}

void Model::update() {
	++time;
	for (auto& sim : sim_objects)
		sim.second->update();
}

void Model::attach(shared_ptr<View> new_view) {
	views.push_back(new_view);
	for (auto& sim : sim_objects)
		sim.second->broadcast_current_state();
}

void Model::detach(std::shared_ptr<View> to_detach) {
	auto to_detach_it = find(views.begin(), views.end(), to_detach);
	assert(to_detach_it != views.end());
	views.erase(to_detach_it);
}

void Model::notify_location(const std::string& name, Point location) {
	for (auto& v : views)
		v->update_location(name, location);
}

void Model::notify_health(const std::string& name, double health) {
	for (auto& v : views)
		v->update_health(name, health);
}

void Model::notify_amount(const std::string& name, double amount) {
	for (auto& v : views)
		v->update_amount(name, amount);
}

void Model::notify_gone(const std::string& name) {
	for (auto& v : views)
		v->update_remove(name);
}

shared_ptr<Agent> Model::nearest_agent(const std::string& name, Point location) {
	auto nearest_it = find_nearest(agents.begin(), agents.end(), name, location);
	if (nearest_it == agents.end())
		return nullptr;		// return nullptr if no more agent exist

	return nearest_it->second;
}

shared_ptr<Structure> Model::nearest_structure(const std::string& name, Point location) {
	auto nearest_it = find_nearest(structures.begin(), structures.end(), name, location);
	if (nearest_it == structures.end())
		return nullptr;		// return nullptr if no more structure exist

	return nearest_it->second;
}

template <typename Map_iterator_t>
Map_iterator_t find_nearest(Map_iterator_t begin, Map_iterator_t end,
							const std::string& name, Point location) {
	if (begin == end || (next(begin) == end && begin->first == name))	// no more object
		return end;

	Map_iterator_t nearest;
	double min_distance = numeric_limits<double>::max();	// largest distance possible
	for (; begin != end; ++begin) {
		if (name == begin->first)
			continue;
		double current_distance = cartesian_distance(begin->second->get_location(), location);
		if (current_distance < min_distance) {
			nearest = begin;
			if (current_distance < numeric_limits<double>::epsilon())	// they are at the same location
				return nearest;
			min_distance = current_distance;
		}
	}
	return nearest;
}

Model& Model::get_model() {
	static Model model;
	return model;
}
