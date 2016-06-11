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
	static void KnightNormalAttackCallback(int audioID, std::string filepath);
	static void KnightSpecialAttackCallback(int audioID, std::string filepath);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void specialAttack();
	void initAttackEffect();
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
	attack_d _specialAttack;
	std::string file = "model/knight/knight.c3b";
};