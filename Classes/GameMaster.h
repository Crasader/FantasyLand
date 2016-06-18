#pragma once
#include "GlobalVariables.h"

USING_NS_CC;
class Actor;

class GameMaster
{
public:
	static GameMaster* getInstance();

	GameMaster();
	bool init();
	void update(float dt);
	static void reset();

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
	void showGameOverUI();


private:

	static GameMaster* _instance;
	float _totaltime;
	float _logicFrq;
};


extern int globalZOrder ;
extern int EXIST_MIN_MONSTER;
extern int stage;
extern int battleSiteX[3];
extern int frontDistanceWithHeroX;
extern int backwardDistanceWithHeroX;
extern int distanceWithHeroX;
extern int distanceWithHeroY;
extern struct monsterCount_d monsterCount;

struct monsterCount_d
{
	int dragon = 1;
	int slime = 7;
	int piglet = 2;
	int rat = 0;
};