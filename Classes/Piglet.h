#pragma once
#include "Actor.h"

class Piglet : public Actor
{
public:
	Piglet();
	CREATE_FUNC(Piglet);
	virtual bool init();
	void reset();
	void copyData_Piglet();
	virtual void update(float dt);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttackSoundEffects();
	void init3D();
	void initActions();

private:
	std::string file = "model/piglet/piglet.c3b";
};