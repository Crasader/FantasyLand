#pragma once
#include "cocos2d.h"
#include "Actor.h"


USING_NS_CC;

class GameMaster
{
public:

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

	void jumpInto( Actor *obj , bool isFront);
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

enum monsterCount
{
	dragon = 1,
	slime = 7,
	piglet = 2,
	rat = 0
};