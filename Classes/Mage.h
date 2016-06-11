#pragma once
#include "Actor.h"

class Mage : public Actor
{
public:
	Mage();
	CREATE_FUNC(Mage);
	virtual bool init();
	virtual void update(float dt);
	void copyData_Mage();
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
	float hurt(BasicCollider* collider, bool dirKnockMode = false);

private:
	struct attack_d _specialAttack;
	std::string file = "model/mage/mage.c3b";
};