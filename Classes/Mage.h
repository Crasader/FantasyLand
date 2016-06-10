#pragma once

#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Helper.h"
#include "Actor.h"
#include "AttackCommand.h"



class Mage : public Actor
{
public:
	Mage();
	CREATE_FUNC(Mage);
	virtual bool init();
	virtual void update(float dt);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void specialAttack();
	void init3D();
	void initActions();
	void setDefaultEqt();
	void updateWeapon();
	void updateHelmet();
	void updateArmour();
	void switchWeapon();
	void switchHelmet();
	void switchArmour();
	int getWeaponID();
	int getHelmetID();
	int getArmourID();
	int hurt(BasicCollider* collider, bool dirKnockMode);

	std::string file = "model/mage/mage.c3b";
};