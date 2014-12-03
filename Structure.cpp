#include "Structure.h"
#include "Model.h"
#include <iostream>
using std::cout; using std::endl;
using std::string;

Structure::Structure(const string& name_, const Point& location_,
		const double initial_food_) :
			Sim_object(name_), food_amount(initial_food_), location(location_) {}

void Structure::describe() const {
	cout << get_name() << " at " << location << endl;
}

void Structure::broadcast_current_state() {
	Model::get_model().notify_location(get_name(), location);
	Model::get_model().notify_amount(get_name(), food_amount);
}

double Structure::withdraw(double amount_to_give) {
	food_amount -= amount_to_give;
	Model::get_model().notify_amount(get_name(), food_amount);
	return amount_to_give;
}

void Structure::deposit(double amount_to_give) {
	food_amount += amount_to_give;
	Model::get_model().notify_amount(get_name(), food_amount);
}
