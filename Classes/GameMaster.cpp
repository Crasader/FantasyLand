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

void GameMaster::AddHeros()
{
	auto knight = Knight::create();
	knight->setPosition(battleSiteX[1], 10);
	currentLayer->addChild(knight);
	knight->idleMode();
	//List.pushlast(HeroManager, knight)
	
	auto mage = Mage::create();
	mage->setPosition(battleSiteX[1], 100);
	currentLayer->addChild(mage);
	mage->idleMode();
	//List.pushlast(HeroManager, mage)

	auto archer = Archer::create();
	archer->setPosition(battleSiteX[1], -80);
	currentLayer->addChild(archer);
	archer->idleMode();
	/*List.pushlast(HeroManager, archer)*/
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

void GameMaster::randomshowMonster(bool isFront)
{
	auto random_var = rand();

	if( random_var < 0.15 )
	{
		if (/*List.getSize(DragonPool) ~= 0*/)
			showDragon(isFront);
		else
			randomshowMonster(isFront);
	}
	else if(random_var < 0.3)
	{
		if (/*List.getSize(RatPool) ~= 0*/)
			showRat(isFront);
		else
			randomshowMonster(isFront);
	}
	else if (random_var < 0.6)
	{
		if (/*List.getSize(PigletPool) ~= 0*/)
			showPiglet(isFront);
		else
			randomshowMonster(isFront);
	}
	else
		showSlime(isFront);
}

void GameMaster::showBoss()
{
	auto boss = Rat::create();
	currentLayer->addChild(boss);
	boss->reset();

	auto apperPos = Vec3(500, 200, 300);
	boss->setPosition3D(apperPos);
	//boss._myPos = { x = appearPos.x,y = appearPos.y }
	boss->setFacing(180);
	//boss->_goRight = false;
	auto enableAI = [boss]()
	{
		boss->setAIEnabled(true);
	};
	boss->runAction(Sequence::create(EaseBounceOut::create(MoveBy::create(0.5, Vec3(0, 0, -300))), CallFunc::create(enableAI)));
	/*List.pushlast(MonsterManager, boss)*/
}

void GameMaster::showWarning()
{
	/*Texture2D::setDefaultAlphaPixelFormat(TEXTURE2_D_PIXEL_FORMAT_AUTO);*/
	auto warning = Layer::create();
	auto warning_logo = Sprite::createWithSpriteFrameName("caution.png");
	/*Texture2D::setDefaultAlphaPixelFormat(TEXTURE2_D_PIXEL_FORMAT_RG_B565)*/
	warning_logo->setPosition(G.winSize.width*0.5, G.winSize.height*0.5);
	warning_logo->setPositionZ(1);

	auto showdialog = [warning,this]()
	{
		warning->removeFromParent();
		this->showDialog();
		experimental::AudioEngine::play2d("audios/effects/boss/boss.mp3", false, 1);
	};

	//warning_logo->runAction(Sequence::create(DelayTime::create(0.5), EaseSineOut::create(Blink::create(1, 5, 3)), CallFunc::create(showdialog)));
	warning->addChild(warning_logo);

	warning->setScale(0.5);
	warning->setPositionZ(-Director::getInstance()->getZEye() / 2);
	warning->ignoreAnchorPointForPosition(false);
	warning->setLocalZOrder(999);
	/*camera->addChild(warning, 2);*/
}

void GameMaster::showVictoryUI()
{
	uiLayer->showVictoryUI();
}

