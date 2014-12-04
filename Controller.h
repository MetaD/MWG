#ifndef CONTROLLER_H
#define CONTROLLER_H

/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

#include <string>
#include <memory>
#include <vector>
class View;
class Map_View;

class Controller {
public:	
	// create View object, run the program by accepting user commands, then destroy View object
	void run();

private:
	// command functions
	void view_open();
	void view_close();
	void view_show();
	void map_view_default();
	void map_view_size();
	void map_view_zoom();
	void map_view_pan();

	void status();
	void go();
	void build();
	void train();

	void agent_move(std::string& name);
	void agent_work(std::string& name);
	void agent_attack(std::string& name);
	void agent_stop(std::string& name);

	// Views
	using view_list_t = std::vector<std::pair<std::string, std::shared_ptr<View>>>;
	view_list_t views;	// all views stored with pair<name, pointer>
	std::shared_ptr<Map_View> map_view;		// the only map view

	// find a view by name
	view_list_t::iterator find_view(const std::string& name);
};

#endif
