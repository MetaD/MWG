#include "Farm.h"
#include <iostream>
using std::cout; using std::endl;

static const double initial_food_amount_c = 50.0;
static const double initial_production_rate_c = 2.0;

Farm::Farm (const std::string& name_, Point location_) :
		Structure(name_, location_, initial_food_amount_c),
		production_rate(initial_production_rate_c) {}

double Farm::withdraw(double amount_to_get) {
	double amount_to_give = get_food_amount() < amount_to_get ?
							get_food_amount() : amount_to_get;
	return Structure::withdraw(amount_to_give);
}

void Farm::update() {
	Structure::deposit(production_rate);
	cout << "Farm " << get_name() << " now has " << get_food_amount() << endl;
}

void Farm::describe() const {
	cout << "Farm ";
	Structure::describe();
	cout << "   Food available: " << get_food_amount() << endl;
}
