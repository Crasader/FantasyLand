#pragma once
#include "cocos2d.h"
#include "Manager.h"
#include "Knight.h"
#include "Mage.h"
#include "Actor.h"
#include "GlobalVariables.h"
#include "Piglet.h"
#include "Slime.h"
#include "Rat.h"
#include "Dragon.h"
#include "Archer.h"

USING_NS_CC;


class GameMaster
{
public:
	CREATE_FUNC(GameMaster);

	virtual bool init();
	virtual void update(float dt);

	void logicUpdate();
	void AddHeros();
	void addMonsters();
	void addDragon();
	void addSlime();
	void addPiglet();
	void addRat();

	void showDragon(bool isFront);
	void showPiglet(bool isFront);
	void showSlime(bool isFront);
	void showRat(bool isFront);
	void randomshowMonster(bool isFront);
	void showBoss();

	void jumpInto( /*obj */ bool isFront);// 不知道obj的类型
	void showWarning();
	void showDialog();
	void showVictoryUI();

private:

	float _totaltime;
	float _logicFrq;
};


extern int gloableZOrder ;
extern int EXIST_MIN_MONSTER;
extern unsigned int scheduleid;
extern int stage;
extern int battleSiteX[3];
extern int frontDistanceWithHeroX;
extern int backwardDistanceWithHeroX;
extern int distanceWithHeroX;
extern int distanceWithHeroY;
extern Size size;
