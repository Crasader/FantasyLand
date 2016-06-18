#pragma once
#include "Actor.h"

class Slime : public Actor
{
public:
	Slime();
	CREATE_FUNC(Slime);
	virtual bool init();
	void reset();
	void copyData_Slime();
	virtual void update(float dt);

	void play3DAnim();
	void playAnimation(std::string name, bool loop);
	void init3D();

	void walkMode();
	void attackMode();
	void idleMode();
	void knockMode(BasicCollider* collider, bool dirKnockMode = false);

	void angryFace(bool trueFalse);
	void initActions();

private:
	bool _angryFace;
	std::string file = "model/slime/slime.c3b";
};