#pragma once
#include "GlobalVariables.h"

USING_NS_CC;
class Actor;

class GameMaster
{
public:
	static GameMaster* getInstance();
	static void setPlayer(std::string playerName);
	static Actor *getPlayer();
	static std::string getPlayerName();

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

	void playerControl(Vec2 positionOf3DWorld, float angleOf3DWorld);

private:

	static GameMaster* _instance;
	float _totaltime;
	float _logicFrq;

	static Actor *_palyer;
	static std::string _playerName;
	Actor *getTouchedMonster(Vec2 positionOf3DWorld, float angleOf3DWorld);
};

extern int stage;
extern const int EXIST_MIN_MONSTER;
extern const int battleSiteX[3];
extern const int frontDistanceWithHeroX;
extern const int backwardDistanceWithHeroX;
extern const int distanceWithHeroX;
extern const int distanceWithHeroY;
extern struct monsterCount_d monsterCount;

struct monsterCount_d
{
	int dragon = 1;
	int slime = 7;
	int piglet = 2;
	int rat = 0;//rat count must be 0 for rat is boss
};