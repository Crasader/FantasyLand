#pragma once

#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Helper.h"
#include "Actor.h"
#include "AttackCommand.h"


std::string file = "model/dragon/dragon.c3b";

class Dragon : public Actor
{
public:
	Dragon();
	CREATE_FUNC(Dragon);
	virtual bool init();
	void reset();
	virtual void update(float dt);
	void dyingMode(Actor* knockSource, int knockAmount);
	void normalAttackSoundEffects();
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void init3D();
	void initActions();
};