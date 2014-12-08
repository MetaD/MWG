#ifndef ARCHER_H
#define ARCHER_H

#include "Warrior.h"

/*
An Archer is an Warrior that if attacked, it will run away to the nearest Structure
(even if it does not protect him). When not attacking, an Archer will look for an nearest
Agent, and attack it if in range.
*/
class Archer : public Warrior {
public:
	Archer(const std::string& name_, Point location_);

	// update implements Archer behavior
	void update() override;

	// Overrides Warrior's take_hit to hide when attacked.
	void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// output information about the current state
	void describe() const override;

protected:
	// output the "Twang" sound of the bow
	void make_sound() const noexcept override;
};

#endif
