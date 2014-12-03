#ifndef PEASANT_H
#define PEASANT_H

#include "Agent.h"
#include <string>
#include <memory>

/* 
A Peasant is an Agent that can move food between Structures. It can be commanded to
start_working, whereupon it moves to the source, picks up food, returns to destination,
deposits the food, returns to source.  If picks up zero food at the source, it waits there
and tries again on the next update. 
If commanded to move_to somewhere, it stops working, and goes there.
*/

class Peasant : public Agent {
public:
	Peasant(const std::string& name_, Point location_);

	// implement Peasant behavior
	void update() override;

	// overridden to suspend working behavior
    void move_to(Point dest) override;

	// stop moving and working
	void stop() override;

	// starts the working process
	// Throws an exception if the source is the same as the destination.
	void start_working(std::shared_ptr<Structure> source_,
					   std::shared_ptr<Structure> destination_) override;

	// output information about the current state
	void describe() const override;

	// broadcast information including amount
	void broadcast_current_state() override;

private:
	// A helper function that changes the state to NOT_WORKING and reset pointers
	void stop_work_noexcept() noexcept;

	enum Work_state_e {NOT_WORKING, INBOUND, COLLECTING, OUTBOUND, DEPOSITING};

	double food_carrying;
	Work_state_e work_state;
	std::weak_ptr<Structure> food_source;
	std::weak_ptr<Structure> food_destination;
};

#endif
