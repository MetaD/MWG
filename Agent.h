#ifndef AGENT_H
#define AGENT_H

#include "Component.h"
#include "Moving_object.h"
#include <memory>
class Structure;

/*
Agents are a kind of Sim_object, and privately inherit from Moving_object.
Agents can be commanded to move to a destination. Agents have a health, which
is decreased when they take a hit. If the Agent's health > 0, it is alive.
If its heath <= 0, it becomes dead and disappears.
*/

class Agent : public Component, public std::enable_shared_from_this<Agent>
{
public:
	// return true if this agent is Alive
	bool is_alive() const override
    { return alive; }

	// return this Agent's location
	Point get_location() const override;

	// return true if this Agent is in motion
	bool is_moving() const override;

	// tell this Agent to start moving to location destination_
    void move_to(Point destination_) override;

	// tell this Agent to stop its activity
    void stop() override;

	// Tell this Agent to accept a hit from an attack of a specified strength
	// The attacking Agent identifies itself with its this pointer.
	// A derived class can override this function.
	// The function lose_health is called to handle the effect of the attack.
    void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// update the moving state and Agent state of this object.
	void update() override;

	// output information about the current state
	void describe() const override;

	// ask Model to broadcast our current state to all Views
	void broadcast_current_state() override;

	/* Fat Interface for derived classes */
	// Throws exception that an Agent cannot work.
    void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>) override;

	// Throws exception that an Agent cannot attack.
    void start_attacking(std::shared_ptr<Agent> target_) override;

protected:
	// Protected constructor to prevent direct creation.
	Agent(const std::string& name_, Point location_);
	// Derived classes are able to specify the health of the agent
	Agent(const std::string& name_, Point location_, int health_);

	// calculate loss of health due to hit.
	// if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
	void lose_health(int attack_strength);

private:
	bool alive;
	int health;
	Moving_object movement;
};

#endif
