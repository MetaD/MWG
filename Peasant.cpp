#include "Peasant.h"
#include "Structure.h"
#include "Utility.h"
#include "Model.h"
#include <iostream>
#include <limits>
using std::cout; using std::endl;
using std::numeric_limits;
using std::string;
using std::shared_ptr;

static const double max_carry_amount_c = 35.0;

Peasant::Peasant(const string& name_, Point location_) :
		Agent(name_, location_), food_carrying(0), work_state(NOT_WORKING) {}

void Peasant::update() {
	Agent::update();

	if (!is_alive() || work_state == NOT_WORKING)
		return;

	shared_ptr<Structure> source = food_source.lock();
	shared_ptr<Structure> destination = food_destination.lock();
	switch (work_state) {	// is working
	case INBOUND:
		if (!is_moving() && get_location() == source->get_location())
			work_state = COLLECTING;
		break;
	case COLLECTING:
	{	// the scope of amount_get is limited to this case
		double amount_get = source->withdraw(max_carry_amount_c - food_carrying);
		food_carrying += amount_get;
		Model::get_model().notify_amount(get_name(), food_carrying);	// notify views
		if (amount_get > 0.0) {
			cout << get_name() << ": Collected " << amount_get << endl;
			work_state = OUTBOUND;
			Agent::move_to(destination->get_location());
		}
		else
			cout << get_name() << ": Waiting " << endl;
	}
		break;
	case OUTBOUND:
		if (!is_moving() && get_location() == destination->get_location())
			work_state = DEPOSITING;
		break;
	case DEPOSITING:
		destination->deposit(food_carrying);
		cout << get_name() << ": Deposited " << food_carrying << endl;
		food_carrying = 0.0;
		Model::get_model().notify_amount(get_name(), food_carrying);	// notify views
		work_state = INBOUND;
		Agent::move_to(source->get_location());
		break;
	default:
		break;
	}
}

void Peasant::move_to(Point dest) {
	stop();
	Agent::move_to(dest);
}

void Peasant::stop() {
	Agent::stop();
	if (work_state != NOT_WORKING) {
		stop_work_noexcept();
		cout << get_name() << ": I'm stopping work" << endl;
	}
}

void Peasant::start_working(shared_ptr<Structure> source_, shared_ptr<Structure> destination_) {
	Agent::stop();
	stop_work_noexcept();
	if (source_ == destination_)
		throw Error(get_name() + ": I can't move food to and from the same place!");
	food_source = source_;
	food_destination = destination_;

	// start working
	if (food_carrying < numeric_limits<double>::epsilon()) {	// not carrying
		if (get_location() == source_->get_location())	// at the source
			work_state = COLLECTING;
		else {											// not at the source
			Agent::move_to(source_->get_location());
			work_state = INBOUND;
		}
	}
	else {	// carrying
		if (get_location() == destination_->get_location())	// at the destination
			work_state = DEPOSITING;
		else {												// not at the destination
			Agent::move_to(destination_->get_location());
			work_state = OUTBOUND;
		}
	}
}

void Peasant::stop_work_noexcept() noexcept {
	work_state = NOT_WORKING;
	food_source.reset();
	food_destination.reset();
}

void Peasant::describe() const {
	cout << "Peasant ";
	Agent::describe();
	cout << "   Carrying " << food_carrying << endl;

	shared_ptr<Structure> source = food_source.lock();
	shared_ptr<Structure> destination = food_destination.lock();
	switch (work_state) {
	case OUTBOUND:
		cout << "   Outbound to destination " << destination->get_name() << endl;
		break;
	case INBOUND:
		cout << "   Inbound to source " << source->get_name() << endl;
		break;
	case COLLECTING:
		cout << "   Collecting at source " << source->get_name() << endl;
		break;
	case DEPOSITING:
		cout << "   Depositing at destination " << destination->get_name() << endl;
		break;
	default:
		break;
	}
}

void Peasant::broadcast_current_state() {
	Agent::broadcast_current_state();
	Model::get_model().notify_amount(get_name(), food_carrying);
}
