#pragma once

#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Helper.h"
#include "Actor.h"
#include "AttackCommand.h"

std::string file = "model/slime/slime.c3b";

class Slime : public Actor
{
public:
	Slime();
	CREATE_FUNC(Slime);
	virtual bool init();
	void reset();
	virtual void update(float dt);
	void play3DAnim();
	void playAnimation(std::string name, bool loop);
	void init3D();
	void walkMode();
	void attackMode();
	void idleMode();
	void knockMode(BasicCollider* collider, bool dirKnockMode);
	void angryFace(bool trueFalse);
	void initActions();
};