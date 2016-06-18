#pragma once
#include "Actor.h"

class Archer : public Actor
{
public:
	Archer();
	CREATE_FUNC(Archer);
	virtual bool init();
	virtual void update(float dt);
	
	void copyData_Archer();
    static Sprite3D* createArrow();

	//hurt and attack
    static void ArcherlAttackCallback(int audioID, std::string filePath);
	float hurt(BasicCollider* collider, bool dirKnockMode = false);
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void specialAttack();

	void init3D();
	void initActions();

	//equipment event
	void setDefaultEqt();
	void updateWeapon();
	void updateHelmet();
	void updateArmour();
	void switchWeapon();
	void switchHelmet();
	void switchArmour();
    int getWeaponID();
	int getArmourID();
	int getHelmetID();

	//show or hide arrow
	//isShow true:Show,  false:Hide
	//type 0:show/hide all, 1:show /hide 1,  2:show/hide 2
	void showOrHideArrow(bool isShow, int arrowType);

private:
	std::string file = "model/archer/archer.c3b";	
};
