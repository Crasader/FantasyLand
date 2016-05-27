#include "GameMaster.h"

int gloableZOrder = 1;
enum { dragon = 1, slime = 7, piglet = 2, rat = 0 } monsterCount;
int EXIST_MIN_MONSTER = 4;
unsigned int scheduleid;
int stage = 0;
int battleSiteX[3] = { -2800,-1800,-800 };
int frontDistanceWithHeroX = 600;
int backwardDistanceWithHeroX = 800;
int distanceWithHeroX = 150;
int distanceWithHeroY = 150;
Size size = Director::getInstance()->getWinSize();

bool GameMaster::init()
{
	_totaltime = 0;
	_logicFrq = 1.0;
	AddHeros();
	AddHeros();
	stage = 0;

	srand(time(NULL));//math.randomseed(tostring(os.time()):reverse():sub(1, 6))
	for (int i = 1; i <= 4; i++)
		randomshowMonster(true);

	stage = 1;
}

void GameMaster::update(float dt)
{
	_totaltime += dt;
	if( _totaltime > _logicFrq)
	{
		_totaltime = _totaltime - +_logicFrq;
		logicUpdate();
	}
}

void GameMaster::addMonsters()
{
	addDragon();
	addSlime();
	addPiglet();
	addRat();
}

void GameMaster::addDragon()
{
	for (int var = 1; var <= monsterCount.dragon ; var++)
	{
		auto dragon = Dragon::create();
		currentLayer->addChild(dragon);
		dragon->setVisible(false);
		dragon->setAIEnabled(false);
		//	List.pushlast(DragonPool, dragon)
	}
}

void GameMaster::addSlime()
{
	for (int i = 1; i <= monsterCount.slime ; i++)
	{
		auto slime = Slime::create();
		currentLayer->addChild(slime);
		slime->setVisible(false);
		slime->setAIEnabled(false);
		/*List.pushlast(SlimePool, slime)*/
	}
}

void GameMaster::addPiglet()
{
	for (int i = 1; i <= monsterCount.piglet; i++)
	{
		auto piglet = Piglet::create();
		currentLayer->addChild(piglet);
		piglet->setVisible(false);
		piglet->setAIEnabled(false);
		/*List.pushlast(PigletPool, piglet)*/
	}
}

void GameMaster::addRat()
{
	for (int i = 1; i <= monsterCount.rat; i++)
	{
		auto rat = Rat::create();
		currentLayer->addChild(rat);
		rat->setVisible(false);
		rat->setAIEnabled(false);
		/*List.pushlast(RatPool, rat)*/
	}
}


void GameMaster::showVictoryUI()
{
	uiLayer->showVictoryUI();
}

