#pragma once
#include "Actor.h"

class Knight : public Actor
{
public:
	Knight();
	CREATE_FUNC(Knight);
	virtual bool init();
	virtual void update(float dt);
	void copyData_Knight();

	//hurt and attack
	static void KnightNormalAttackCallback(int audioID, std::string filepath);
	static void KnightSpecialAttackCallback(int audioID, std::string filepath);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void specialAttack();
	void initAttackEffect();
    float hurt(BasicCollider* collider, bool dirKnockMode = false);

	void init3D();
	void initActions();
	void setDefaultEqt();

	//Equipment event
	void updateWeapon();
	void updateHelmet();
	void updateArmour();
	void switchWeapon();
	void switchHelmet();
	void switchArmour();
	int getWeaponID();
	int getHelmetID();
	int getArmourID();
	
private:
	std::string file = "model/knight/knight.c3b";
};