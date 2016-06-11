#pragma once
#include "Actor.h"

class Dragon : public Actor
{
public:
	Dragon();
	CREATE_FUNC(Dragon);
	virtual bool init();
	void copyData_Dragon();
	void reset();
	virtual void update(float dt);
	void dyingMode(Vec2 knockSource, int knockAmount);
	void normalAttackSoundEffects();
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void init3D();
	void initActions();

private:
	std::string file = "model/dragon/dragon.c3b";
};