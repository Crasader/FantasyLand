#pragma once
#include "Actor.h"

class Rat : public Actor
{
public:
	Rat();
	CREATE_FUNC(Rat);
	virtual bool init();
	void reset();
	virtual void update(float dt);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttackSoundEffects();
	void init3D();
	void initActions();
	void dyingMode(Vec2 knockSource, int knockAmount);
	int hurt(BasicCollider* collider, bool dirKnockMode);

private:
	std::string file = "model/rat/rat.c3b";
};