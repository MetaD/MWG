#include "Town_Hall.h"
#include <iostream>
using std::cout; using std::endl;

Town_Hall::Town_Hall (const std::string& name_, Point location_)
			: Structure(name_, location_) {}

// Return whichever is less, the request or (the amount on hand - 10%) (a "tax"),
// but amounts less than 1.0 are not supplied - the amount returned is zero.
// update the amount on hand by subtracting the amount returned.
double Town_Hall::withdraw(double amount_to_get) {
	double amount_available = get_food_amount() * 0.9;
	if (amount_available < 1.0)	// none available
		return 0.0;
	return Structure::withdraw(amount_available < amount_to_get ?
							   amount_available : amount_to_get);
}

// output information about the current state
void Town_Hall::describe() const {
	cout << "Town_Hall ";
	Structure::describe();
	cout << "   Contains " << get_food_amount() << endl;
}
