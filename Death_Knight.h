#ifndef DEATH_KNIGHT_H
#define DEATH_KNIGHT_H

#include "Warriors.h"
#include "Soldier.h"	// for Death Knight's servant
#include <string>
#include <memory>

class Death_Knight : public Warrior {
public:
	Death_Knight(const std::string& name_, Point location_);

	// update implements Death_Knight behavior
	void update() override;

	// Overrides Warrior's take_hit to summon a servant when attacked.
	void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// output information about the current state
	void describe() const override;

	// output the "Neighhh" sound of its horse
	void make_sound() const noexcept override;

private:
	std::shared_ptr<Soldier> servant;
};

#endif
