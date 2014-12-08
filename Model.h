#ifndef MODEL_H
#define MODEL_H

/*
Model is part of a simplified Model-View-Controller pattern.
Model keeps track of the Sim_objects in the little world. It is the only
thing that knows how many Structures, Agents, and Component there are, but it does not
know about any of their derived classes, nor which Agents are of what kind of Agent. 
It has facilities for looking up objects by name, and removing Agents.  When
created, it creates an initial group of Structures and Agents using the Structure_factory
and Agent_factory.
Finally, it keeps the system's time.
*/

#include <map>
#include <vector>
#include <string>
#include <memory>
class View;
class Sim_object;
class Agent;
class Structure;
class Component;
class Point;

class Model {
public:
	// return the current time
	int get_time() { return time; }

	// is name already in use for either agent or structure?
    // return true if the name matches the name of an existing agent or structure
	bool is_name_in_use(const std::string& name) const;

	// is there a structure with this name?
	bool is_structure_present(const std::string& name) const;
	// add a new structure; assumes none with the same name
	void add_structure(std::shared_ptr<Structure>);
	// will throw Error("Structure not found!") if no structure of that name
	std::shared_ptr<Structure> get_structure_ptr(const std::string& name) const;

	// is there a components with this name?
	bool is_component_present(const std::string& name) const;
    // is there an agent with this name?
    bool is_component_present_non_composite(const std::string& name) const; //?? todo
	// add a new agent; assumes none with the same name
	void add_component(std::shared_ptr<Component>);
	// remove an agent from all containers
	void remove_component(std::shared_ptr<Component>);
	// will throw Error("Agent not found!") if no agent of that name
	std::shared_ptr<Component> get_component_ptr(const std::string& name) const;

	// tell all objects to describe themselves to the console
	void describe() const;
	// increment the time, and tell all objects to update themselves
	void update();	

	/* View services */
	// Attaching a View adds it to the container and causes it to be updated
    // with all current objects'location (or other state information.
	void attach(std::shared_ptr<View>);
	// Detach the View by discarding the supplied pointer from the container of Views
    // - no updates sent to it thereafter.
	void detach(std::shared_ptr<View>);
    // notify the views about an object's location
	void notify_location(const std::string& name, Point location);
    // notify the views about an object's health
	void notify_health(const std::string& name, int health);
    // notify the views about an object's amount
	void notify_amount(const std::string& name, double amount);
	// notify the views that an object is now gone
	void notify_gone(const std::string& name);

	// find the structure/agent (different from the given name) nearest to the given location
	// nullptr is returned when no more object exist
	std::shared_ptr<Agent> nearest_agent(const std::string& name, Point location);
	std::shared_ptr<Structure> nearest_structure(const std::string& name, Point location);

	// get the only instance of model
	static Model& get_model();


private:
	int time;
	std::map<std::string, std::shared_ptr<Sim_object>> sim_objects;
	std::map<std::string, std::shared_ptr<Component>> components;
	std::map<std::string, std::shared_ptr<Structure>> structures;
	std::vector<std::shared_ptr<View>> views;

	// private constructor and destructor
	Model();
	~Model() {};
	// disallow copy/move construction or assignment
	Model(const Model&) = delete;
	Model& operator= (const Model&)  = delete;
	Model(Model&&) = delete;
	Model& operator= (Model&&) = delete;
};

#endif
