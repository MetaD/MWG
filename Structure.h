#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Geometry.h"	// Point
#include "Sim_object.h"

/* A Structure is a Sim_object with a location and interface to derived types */

class Structure : public Sim_object {
public:
	Point get_location() const { return location; }

	void update() override {}	// Does nothing

	// output information about the current state
	void describe() const override;

	// ask model to notify views of current state
    void broadcast_current_state() override;

	// fat interface for derived types
	// by default, withdraw returns the specified amount and deducts that amount
    // from the amount on hand
	virtual double withdraw(double amount_to_give);

	// by default, deposit adds in the supplied amount
	virtual void deposit(double amount_to_give);

protected:
	Structure(const std::string& name_, const Point& location_,
			const double initial_food_ = 0.0);
	const double& get_food_amount() const noexcept { return food_amount; }

private:
	double food_amount;
	Point location;
};

#endif
