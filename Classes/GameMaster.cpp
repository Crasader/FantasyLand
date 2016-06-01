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

void GameMaster::showDragon(bool isFront)
{
	if(DragonPool.size() != 0 )
	{
		auto dragon = DragonPool[0];
		DragonPool.erase(DragonPool.begin());
		//dragon->reset();

		auto appearPos = getFocusPointOfHeros();
		auto randomvarX = random()*0.2 + 1;

		if( stage == 0 )
		{
			appearPos.x = appearPos.x + frontDistanceWithHeroX * randomvarX;
			dragon->setFacing(180);
		}
		else
		{
			if( isFront )
			{
				appearPos.x = appearPos.x + frontDistanceWithHeroX*1.8*randomvarX;
				dragon->setFacing(180);
			}
			else
			{
				appearPos.x = appearPos.x - backwardDistanceWithHeroX*1.8*randomvarX;
				dragon->setFacing(0);
			}
		}

		auto  randomvarY = 2 * random() - 1;
		appearPos.y = appearPos.y + randomvarY*distanceWithHeroY;
		dragon->setPosition(appearPos);
		//dragon->_myPos = appearPos;
		dragon->setVisible(true);
		//dragon._goRight = false;
		dragon->setAIEnabled(true);
		MonsterManager.push_back(dragon);
	}
}

void GameMaster::showPiglet(bool isFront)
{
	if( PigletPool.size() != 0 )
	{
		auto piglet = PigletPool[0];
		PigletPool.erase(PigletPool.begin());
		piglet->reset();

		auto appearPos = getFocusPointOfHeros();
		auto randomvarX = random()*0.2 + 1;

		if (stage == 0)
		{
			appearPos.x = appearPos.x + frontDistanceWithHeroX * randomvarX;
			piglet->setFacing(180);
		}
		else
		{
			if (isFront)
			{
				appearPos.x = appearPos.x + frontDistanceWithHeroX*1.8*randomvarX;
				piglet->setFacing(180);
			}
			else
			{
				appearPos.x = appearPos.x - backwardDistanceWithHeroX*1.8*randomvarX;
				piglet->setFacing(0);
			}
		}

		auto  randomvarY = 2 * random() - 1;
		appearPos.y = appearPos.y + randomvarY*distanceWithHeroY;
		piglet->setPosition(appearPos);
		//piglet->_myPos = appearPos;
		piglet->setVisible(true);
		//piglet._goRight = false;
		piglet->setAIEnabled(true);
		MonsterManager.push_back(piglet);
	}
	}
}

void GameMaster::showSlime(bool isFront)
{
	if( SlimePool.size() != 0 )
	{
		auto slime = SlimePool[0];
		SlimePool.erase(SlimePool.begin());
		//slime->reset();
		//slime._goRight = false
		jumpInto(slime, isFront);
		MonsterManager.push_back(slime);
	}
}



void GameMaster::randomshowMonster(bool isFront)
{
	auto random_var = rand();

	if( random_var < 0.15 )
	{
		if (DragonPool.size() != 0 )
			showDragon(isFront);
		else
			randomshowMonster(isFront);
	}
	else if(random_var < 0.3)
	{
		if (RatPool.size() != 0 )
			showRat(isFront);
		else
			randomshowMonster(isFront);
	}
	else if (random_var < 0.6)
	{
		if (PigletPool.size() != 0)
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
	//boss->_myPos = { x = appearPos.x,y = appearPos.y };
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

void GameMaster::showDialog()
{
	Texture2D::setDefaultAlphaPixelFormat(/*TEXTURE2_D_PIXEL_FORMAT_AUTO*/);
	auto colorLayer = LayerColor::create(Color4B(10, 10, 10, 150));
	colorLayer->ignoreAnchorPointForPosition(false);
	colorLayer->setPositionZ(-Director::getInstance()->getZEye() / 5);
	colorLayer->setGlobalZOrder(0);
	camera->addChild(colorLayer);

	auto dialog = Layer::create();
	dialog->setPositionX(-G.winSize.width*0.025);

	auto outframe = Sprite::createWithSpriteFrameName("outframe.png");
	outframe->setPosition(G.winSize.width * 0.55, G.winSize.height * 0.27);
	outframe->setScale(0.6*resolutionRate);
	dialog->addChild(outframe);

	auto inframe = Sprite::createWithSpriteFrameName("inframe.png");
	inframe->setPosition(G.winSize.width * 0.67, G.winSize.height * 0.27);
	inframe->setScale(0.5*resolutionRate);
	dialog->addChild(inframe);

	auto bossicon = Sprite::createWithSpriteFrameName("bossicon.png");
	bossicon->setPosition(G.winSize.width*0.42, G.winSize.height*0.46);
	bossicon->setScale(0.75*resolutionRate);
	bossicon->setFlippedX(true);
	dialog->addChild(bossicon);

	auto bosslogo = Sprite::createWithSpriteFrameName("bosslogo.png");
	bosslogo->setPosition(G.winSize.width*0.417, G.winSize.height*0.265);
	bosslogo->setScale(0.74*resolutionRate);
	dialog->addChild(bosslogo);

	auto text = Label::createWithTTF(BossTaunt, "fonts/britanic bold.ttf", 24);
	text->setPosition(G.winSize.width*0.68, G.winSize.height*0.27);
	dialog->addChild(text);

	dialog->setScale(0.1);
	dialog->ignoreAnchorPointForPosition(false);
	dialog->setPositionZ(-cc.Director:getInstance() : getZEye() / 3);
	dialog->setGlobalZOrder(0);
	camera->addChild(dialog);

	auto pausegame = []()
	{
		for (int i = 0; i < HeroManager.size(); i++)
		{
			HeroManager[i]->idleMode();
			HeroManager[i]->setAIEnabled(false);
		}
	};

	dialog->runAction(Sequence::create(ScaleTo::create(0.5, 0.5), CallFunc::create(pausegame)));
	uiLayer->setVisible(false);

	auto exitDialog = [dialog, colorLayer, this]()
	{
		auto removeDialog = [dialog, colorLayer, this]()
		{
			dialog->removeFromParent();
			colorLayer->removeFromParent();
			uiLayer->setVisible(true);
			for (int var = 0; var < HeroManager.size(); var++)
			{
				HeroManager[var]->setAIEnabled(true);
			}
			this->showBoss();
		};

		dialog->runAction(Sequence::create(ScaleTo::create(0.5, 0.1), CallFunc::create(removeDialog)));
		Director::getInstance()->getScheduler()->unscheduleScriptEntry(scheduleid);
	};

	scheduleid = Director::getInstance()->getScheduler()->scheduleScriptFunc(exitDialog, 3, false);//todo
	Texture2D::setDefaultAlphaPixelFormat(TEXTURE2_D_PIXEL_FORMAT_RG_B565);
}

void GameMaster::showVictoryUI()
{
	uiLayer->showVictoryUI();
}

