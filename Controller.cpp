#include "Controller.h"

#include "Model.h"
#include "Utility.h"

#include "Agent.h"
#include "Structure.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include "Component.h"
#include "Composite.h"

#include "Map_View.h"
#include "Local_View.h"
#include "Health_View.h"
#include "Amount_View.h"
#include "Global_View.h"

#include <iostream>
#include <cctype>	// isalnum
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::map;
using std::string;
using std::pair;
using std::shared_ptr;
using std::make_shared;
using std::find_if;

const size_t minimum_agent_name_length_c = 2;
const size_t minimum_group_name_length_c = 1;

// A helper function for build and train to read input name and type
static pair<string, string> read_object_name_type();

// A helper function that throws an error if the given name is invalid.
// A valid name has a length of at least min_length, contains only letters
// and numbers, and is not in use.
static void check_name_validity(const string& name, size_t min_length);

// A helper function that read two doubles and return a Point
static Point read_point();

// A helper function that read a structure name and check its existence
static shared_ptr<Structure> read_Structure();

// A helper function that read an agent name and check its existence
static shared_ptr<Component> read_Component();

// A helper function that returns the group pointer
// and throws an Error if it is a single agent
static shared_ptr<Component> get_group(const string& name);

void Controller::run() {

	// the command maps
	map<string, void (Controller::*)()> view_cmd_func {
		{"open", &Controller::view_open},
		{"close", &Controller::view_close},
		{"show", &Controller::view_show}
	};
	map<string, void (Controller::*)()> map_view_cmd_func {
		{"default", &Controller::map_view_default},
		{"size", &Controller::map_view_size},
		{"zoom", &Controller::map_view_zoom},
		{"pan", &Controller::map_view_pan}
	};
	map<string, void (Controller::*)()> whole_prog_cmd_func {
		{"status", &Controller::status},
		{"go", &Controller::go},
		{"build", &Controller::build},
		{"train", &Controller::train},
		{"group", &Controller::create_group},
		{"ungroup", &Controller::dismiss_group}
	};
	map<string, void (Controller::*)(const string& name)> agent_cmd_func {
		{"move", &Controller::agent_move},
		{"work", &Controller::agent_work},
		{"attack", &Controller::agent_attack},
		{"stop", &Controller::agent_stop},
		// Group commands:
		{"add", &Controller::group_add},
		{"remove", &Controller::group_remove}
	};

	// start action
	while (true) {
		try {
			cout << "\nTime " << Model::get_model().get_time() << ": Enter command: ";
			string first_word;
			cin >> first_word;

			map<string, void (Controller::*)()>::iterator func_it;	// will be used later

			// QUIT
			if (first_word == "quit") {
				cout << "Done" << endl;
				return;
			}
			// agent command
			else if (Model::get_model().is_component_present(first_word)) {
				string agent_cmd;
				cin >> agent_cmd;
				auto func_it = agent_cmd_func.find(agent_cmd);
				if (func_it != agent_cmd_func.end())
					(this->*(func_it->second))(first_word);	// call the agent command function
				else
					throw Error("Unrecognized command!");
			}
			// view command
			else if ((func_it = view_cmd_func.find(first_word)) != view_cmd_func.end())
				(this->*(func_it->second))();
			// map view command
			else if ((func_it = map_view_cmd_func.find(first_word)) != map_view_cmd_func.end()) {
				if (!map_view)
					throw Error("No map view is open!");
				(this->*(func_it->second))();
			}
			// whole-program command
			else if ((func_it = whole_prog_cmd_func.find(first_word)) != whole_prog_cmd_func.end())
				(this->*(func_it->second))();
			else
				throw Error("Unrecognized command!");
		}
		catch (Error& err) {	// project-specific errors
		    cout << err.what() << endl;
		    cin.clear();
		    while (cin.get() != '\n');	// skip the line
		}
		catch (std::bad_alloc&) {
			cout << "Memory allocation failure!" << endl;
			return;
		}
		catch (...) {
			cout << "Unknown exception caught!" << endl;
			return;
		}
	}
}


void Controller::view_open() {
	string view_name;
	cin >> view_name;
	if (find_view(view_name) != views.end())
		throw Error("View of that name already open!");

	shared_ptr<View> new_view;	// the view to be added

	if (view_name == "map")
		new_view = map_view = make_shared<Map_View>();
	else if(view_name == "global")
		new_view = make_shared<Global_View>();
	else if (view_name == "health")
		new_view = make_shared<Health_View>();
	else if (view_name == "amounts")
		new_view = make_shared<Amount_View>();
	else {	// local view
		shared_ptr<Sim_object> object;	// the object to be viewed
		if (Model::get_model().is_component_present(view_name))
			object = Model::get_model().get_component_ptr(view_name);
		else if (Model::get_model().is_structure_present(view_name))	// structure
			object = Model::get_model().get_structure_ptr(view_name);
		else
			throw Error("No object of that name!");

		new_view = make_shared<Local_View>(object->get_name(), object->get_location());
	}
	// add the new view
	views.push_back({view_name, new_view});
	Model::get_model().attach(new_view);
}

void Controller::view_close() {
	string view_name;
	cin >> view_name;
	auto to_close = find_view(view_name);
	if (to_close == views.end())
		throw Error("No view of that name is open!");
	Model::get_model().detach(to_close->second);
	views.erase(to_close);

	if (view_name == "map")
		map_view.reset();
}

using view_list_t = std::vector<pair<string, shared_ptr<View>>>;
view_list_t::iterator Controller::find_view(const std::string& name) {
	return find_if(views.begin(), views.end(),
			[&name](view_list_t::value_type& pair){ return pair.first == name; });
}

void Controller::view_show() {
	for(auto& view : views)
		view.second->draw();
}

void Controller::map_view_default() {
	map_view->set_defaults();
}

void Controller::map_view_size() {
	int size_in;
	cin >> size_in;
	if (!cin.good())
		throw Error("Expected an integer!");
	map_view->set_size(size_in);
}

void Controller::map_view_zoom() {
	double scale_in;
	cin >> scale_in;
	if (!cin.good())
		throw Error("Expected a double!");
	map_view->set_scale(scale_in);
}

void Controller::map_view_pan() {
	double x_in, y_in;
	cin >> x_in >> y_in;
	if (!cin.good())
		throw Error("Expected a double!");
	map_view->set_origin(Point(x_in, y_in));
}

void Controller::status() {
	Model::get_model().describe();
}

void Controller::go() {
	Model::get_model().update();
}

void Controller::build() {
	auto name_type_pair = read_object_name_type();
	Point location = read_point();
	shared_ptr<Structure> new_struct = create_structure(name_type_pair.first, name_type_pair.second, location);
	Model::get_model().add_structure(new_struct);
}

void Controller::train() {
	auto name_type_pair = read_object_name_type();
	Point location = read_point();
	check_name_validity(name_type_pair.first, minimum_agent_name_length_c);
	shared_ptr<Component> new_agent = create_agent(name_type_pair.first, name_type_pair.second, location);
	Model::get_model().add_component(new_agent);
}

// A helper function for build and train to read input name and type, and check name
static pair<string, string> read_object_name_type() {
	// read name and type, check name
	string name, type;
	cin >> name >> type;
	if (name.length() < 2 || Model::get_model().is_name_in_use(name))
		throw Error("Invalid name for new object!");
	for (char c : name) {
		if (!isalnum(c))	// not a number or letter
			throw Error("Invalid name for new object!");
	}
	return make_pair(name, type);
}

void Controller::create_group() {
	string group_name;
	cin >> group_name;
	check_name_validity(group_name, minimum_group_name_length_c);
	shared_ptr<Composite> new_compo(new Composite(group_name));
	Model::get_model().add_component(new_compo);
}

void check_name_validity(const string& name, size_t min_length) {
	if (name.length() < min_length || Model::get_model().is_name_in_use(name))
		throw Error("Invalid name for new object!");
	for (char c : name) {
		if (!isalnum(c))	// not a number or letter
			throw Error("Invalid name for new object!");
	}
}

void Controller::agent_move(const string& name) {
	Point destination = read_point();
	(Model::get_model().get_component_ptr(name))->move_to(destination);
}

// A helper function that read two doubles and return a Point
static Point read_point() {
	double x_in, y_in;
	cin >> x_in >> y_in;
	if (!cin.good())
		throw Error("Expected a double!");
	return Point(x_in, y_in);
}

void Controller::agent_work(const string& name) {
	shared_ptr<Structure> source = read_Structure();
	shared_ptr<Structure> destination = read_Structure();
	Model::get_model().get_component_ptr(name)->start_working(source, destination);
}

// A helper function that read a structure name and check its existence
static shared_ptr<Structure> read_Structure() {
	string stc_name;
	cin >> stc_name;
	return Model::get_model().get_structure_ptr(stc_name);
}

void Controller::agent_attack(const string& name) {
	shared_ptr<Component> compo_ptr = read_Component();
	Model::get_model().get_component_ptr(name)->start_attacking(compo_ptr);
}

void Controller::agent_stop(const string& name) {
	Model::get_model().get_component_ptr(name)->stop();
}

void Controller::group_add(const string& name) {
	get_group(name)->add_component(read_Component());
}

void Controller::group_remove(const string& name) {
    shared_ptr<Component> group = get_group(name);
    string to_remove = read_Component()->get_name();
    if(!group->get_child(to_remove))		// the group does not have this child
    	throw Error(to_remove + " is not in " + name);
    group->remove_component(to_remove);
}

void Controller::dismiss_group() {
    string group_name;
    cin >> group_name;
    shared_ptr<Component> group = get_group(group_name);
    Model::get_model().remove_component(group);
}

static shared_ptr<Component> read_Component() {
	string agent_name;
	cin >> agent_name;
	shared_ptr<Component> agent_ptr = Model::get_model().get_component_ptr(agent_name);
	return agent_ptr;
}

static shared_ptr<Component> get_group(const string& name) {
	shared_ptr<Component> group = Model::get_model().get_component_ptr(name);
	if (!group->is_composite())
		throw Error(name + " is not a group!");
	return group;
}
