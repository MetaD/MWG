#ifndef WARRIORS_H
#define WARRIORS_H

#include "Agent.h"

/*
A Warrior is a kind of Agent that has attack and defense behaviors. It can be
commanded to start attacking another Agent and will continue the attack as long as 
it is alive and the target is alive and in range.
*/
class Warrior : public Agent {
public:
	// update implements Warrior behavior
	void update() override;

	// return true is the Warrior is attacking
	bool is_attacking() { return attacking; }

	// Make this Soldier start attacking the target Agent.
	// Throws an exception if the target is the same as this Agent,
	// is out of range, or is not alive.
	void start_attacking(std::shared_ptr<Agent> target_ptr) override;

	// Overrides Agent's take_hit to counter- attack when attacked.
	void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

	// Overrides Agent's stop to print a message
	void stop() override;

	// output information about the current state
	void describe() const override;

protected:
	// protected constructors
	Warrior(const std::string& name_, Point location_, int strength_, double range_);
	// Warrior's health can be optionally specified when constructed
	Warrior(const std::string& name_, Point location_, int health_, int strength_, double range_);

    
    // output the sound of the weapon
    virtual void make_sound() const noexcept = 0;

    
	// Make this Warrior start attacking the target Agent. No exception is thrown.
	void start_attacking_noexcept(std::shared_ptr<Agent> target_ptr) noexcept;

	// return true if the target is out of attack range
	// assert if target is invalid
	bool target_out_of_range() const;
	bool target_out_of_range(std::shared_ptr<Agent> new_target) const;

private:
	bool attacking;		// true if attacking
	int strength;		// attack strength
	double range;		// attack range
	std::weak_ptr<Agent> target;
};

#endif
