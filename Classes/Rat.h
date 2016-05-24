#pragma once

#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Helper.h"
#include "Actor.h"
#include "AttackCommand.h"

std::string file = "model/rat/rat.c3b";

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
	void dyingMode(Actor* knockSource, int knockAmount);
	void hurt(BasicCollider* collider, bool dirKnockMode);
};