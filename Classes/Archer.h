#pragma once
#include "Actor.h"

class Archer : public Actor
{
public:
	Archer();
	CREATE_FUNC(Archer);
	virtual bool init();
	virtual void update(float dt);
	static Sprite3D* createArrow();
	static void ArcherlAttackCallback(int audioID, std::string filePath);
	void copyData_Archer();
	void playDyingEffects();
	void hurtSoundEffects();
	void normalAttack();
	void specialAttack();
	void init3D();
	void initActions();

	//set default equipments
	void setDefaultEqt();
	void updateWeapon();
	void updateHelmet();
	void updateArmour();

	//switth weapon
	void switchWeapon();
	//switch helmet
	void switchHelmet();
	//switch armour
	void switchArmour();
	//show/hide arrow
	//isShow: true : Show false : Hide
	//type: 0 : show / hide all 1 : show / hide 1 2 : show / hide 2
	void showOrHideArrow(bool isShow, int arrowType);
	//get weapon id
	int getWeaponID();
	//get armour id
	int getArmourID();
	//get helmet id
	int getHelmetID();
	float hurt(BasicCollider* collider, bool dirKnockMode = false);


private:
	//struct attackCollierInfoForSpecial {
	//	int minRange;
	//	int maxRange;
	//	float angle;
	//	int knock;
	//	int damage;
	//	EnumRaceType mask;
	//	float duration;
	//	int speed;
	//	float criticalChance;
	//	float DOTTimer;
	//	float curDOTTimer;
	//	bool DOTApplied;
	//}_specialAttack;
	struct attack_d _specialAttack;

	std::string file = "model/archer/archer.c3b";
	
};
