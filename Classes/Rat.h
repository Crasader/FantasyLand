#pragma once
#include "Actor.h"

class Rat : public Actor
{
public:
	Rat();
	CREATE_FUNC(Rat);
	virtual bool init();
	void reset();
	void copyData_Rat();
	virtual void update(float dt);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttackSoundEffects();
	void init3D();
	void initActions();
	void dyingMode(Vec2 knockSource, int knockAmount);
	float hurt(BasicCollider* collider, bool dirKnockMode = false);

private:
	std::string file = "model/rat/rat.c3b";
};