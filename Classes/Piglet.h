#pragma once

#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Helper.h"
#include "Actor.h"
#include "AttackCommand.h"

std::string file = "model/piglet/piglet.c3b";

class Piglet : public Actor
{
public:
	Piglet();
	CREATE_FUNC(Piglet);
	virtual bool init();
	void reset();
	virtual void update(float dt);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttackSoundEffects();
	void init3D();
	void initActions();
};