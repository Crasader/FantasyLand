#include "GameMaster.h"
#include "Actor.h"
#include "Archer.h"
#include "Piglet.h"
#include "Slime.h"
#include "Rat.h"
#include "Dragon.h"
#include "Manager.h"
#include "Knight.h"
#include "Mage.h"
#include "BattleFieldUI.h"
#include "JumpBy3D.h"


int stage = 0;
const int EXIST_MIN_MONSTER = 4;
const int battleSiteX[3] = { -2800,-1800,-800 };
const int frontDistanceWithHeroX = 600;
const int backwardDistanceWithHeroX = 800;
const int distanceWithHeroX = 150;
const int distanceWithHeroY = 150;

struct monsterCount_d monsterCount;

GameMaster * GameMaster::_instance = nullptr;
Actor *GameMaster::_player = nullptr;
std::string GameMaster::_playerName;


bool GameMaster::init()
{
	_totaltime = 0;
	_logicFrq = 1.0;
	AddHeros();
	addMonsters();
	stage = 0;

	srand(time(NULL));
	for (int i = 1; i <= 4; i++)
		randomshowMonster(true);

	stage = 1;
	return true;
}

GameMaster* GameMaster::create()
{
	if (_instance == nullptr)
	{
		_instance = new GameMaster();
	}
	return _instance;
}

GameMaster* GameMaster::getInstance()
{
	return _instance;
}

GameMaster::GameMaster()
{
	init();
}

void GameMaster::update(float dt)
{
	_totaltime += dt;
	if (_totaltime > _logicFrq)
	{
		_totaltime = _totaltime - +_logicFrq;
		logicUpdate();
	}
}

void GameMaster::reset()
{
	delete _instance;
	_instance = nullptr;
}

void GameMaster::logicUpdate()
{
	if (stage == 1)
	{
		if (MonsterManager.size() < EXIST_MIN_MONSTER)
		{
			srand(time(NULL));
			for (int i = 1; i <= 4; i++)
			{
				randomshowMonster(true);
			}
			stage = 2;
		}
	}
	else if (stage == 2)
	{
		if (MonsterManager.size() < EXIST_MIN_MONSTER)
		{
			srand(time(NULL));
			for (int i = 1; i <= 4; i++)
			{
				randomshowMonster(true);
			}
			stage = 3;
		}
	}
	else if (stage == 3)
	{
		if (MonsterManager.size() == 0)
		{
			for (int i = 0; i < HeroManager.size(); i++)
			{
				auto hero = HeroManager[i];
				if (hero != NULL)
				{
					hero->setGoRight(true);
				}
			}
			stage = 4;
		}
	}
	else if (stage == 4)
	{
		if (getFocusPointOfHeros().x > battleSiteX[2])
		{
			srand(time(NULL));
			for (int i = 1; i <= 3; i++)
			{
				randomshowMonster(true);
			}
			for (int i = 1; i <= 4; i++)
			{
				randomshowMonster(false);
			}
			stage = 5;
		}
	}
	else if (stage == 5)
	{
		if (MonsterManager.size() < EXIST_MIN_MONSTER)
		{
			srand(time(NULL));
			for (int i = 1; i <= 4; i++)
			{
				randomshowMonster(true);
			}
			stage = 6;
		}
	}
	else if (stage == 6)
	{
		if (MonsterManager.size() < EXIST_MIN_MONSTER)
		{
			srand(time(NULL));
			for (int i = 1; i <= 4; i++)
			{
				randomshowMonster(false);
			}
			stage = 7;
		}
	}
	else if (stage == 7)
	{
		if (MonsterManager.size() == 0)
		{
			for (int i = 0; i < HeroManager.size(); i++)
			{
				auto hero = HeroManager[i];
				if (hero != NULL)
				{
					hero->setGoRight(true);
				}
			}
			for (int i = 0; i < PigletPool.size(); i++)
			{
				auto monster = PigletPool[i];
				if (monster != NULL)
				{
					monster->removeFromParent();
				}
			}
			for (int i = 0; i < SlimePool.size(); i++)
			{
				auto monster = SlimePool[i];
				if (monster != NULL)
				{
					monster->removeFromParent();
				}
			}
			for (int i = 0; i < DragonPool.size(); i++)
			{
				auto monster = DragonPool[i];
				if (monster != NULL)
				{
					monster->removeFromParent();
				}
			}
			for (int i = 0; i < RatPool.size(); i++)
			{
				auto monster = RatPool[i];
				if (monster != NULL)
				{
					monster->removeFromParent();
				}
			}
			stage = 8;
		}
	}
	else if (stage == 8)
	{
		if (getFocusPointOfHeros().x > battleSiteX[3])
		{
			showWarning();
			stage = 9;
		}
	}
}

void GameMaster::AddHeros()
{
	auto knight = Knight::create();
	knight->setCameraMask(2);
	knight->setPosition(battleSiteX[1], 10);
	currentLayer->addChild(knight);
	knight->idleMode();
	HeroManager.push_back(knight);

	auto mage = Mage::create();
	mage->setCameraMask(2);
	mage->setPosition(battleSiteX[1], 100);
	currentLayer->addChild(mage);
	mage->idleMode();
	HeroManager.push_back(mage);

	auto archer = Archer::create();
	archer->setCameraMask(2);
	archer->setPosition(battleSiteX[1], -80);
	currentLayer->addChild(archer);
	archer->idleMode();
	HeroManager.push_back(archer);
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
	for (int var = 1; var <= monsterCount.dragon; var++)
	{
		auto dragon = Dragon::create();
		dragon->setCameraMask(2);
		currentLayer->addChild(dragon);
		dragon->setVisible(false);
		dragon->setAIEnabled(false);
		DragonPool.push_back(dragon);
	}
}

void GameMaster::addSlime()
{
	for (int i = 1; i <= monsterCount.slime; i++)
	{
		auto slime = Slime::create();
		slime->setCameraMask(2);
		currentLayer->addChild(slime);
		slime->setVisible(false);
		slime->setAIEnabled(false);
		SlimePool.push_back(slime);
	}
}

void GameMaster::addPiglet()
{
	for (int i = 1; i <= monsterCount.piglet; i++)
	{
		auto piglet = Piglet::create();
		piglet->setCameraMask(2);
		currentLayer->addChild(piglet);
		piglet->setVisible(false);
		piglet->setAIEnabled(false);
		PigletPool.push_back(piglet);
	}
}

void GameMaster::addRat()
{
	for (int i = 1; i <= monsterCount.rat; i++)
	{
		auto rat = Rat::create();
		rat->setCameraMask(2);
		currentLayer->addChild(rat);
		rat->setVisible(false);
		rat->setAIEnabled(false);
		RatPool.push_back(rat);
	}
}

void GameMaster::showDragon(bool isFront)
{
	if (DragonPool.size() != 0)
	{
		Dragon * dragon = dynamic_cast<Dragon*>(DragonPool[0]);
		DragonPool.erase(DragonPool.begin());
		dragon->reset();

		auto appearPos = getFocusPointOfHeros();
		auto randomvarX = CCRANDOM_0_1()*0.2 + 1;

		if (stage == 0)
		{
			appearPos.x = appearPos.x + frontDistanceWithHeroX * randomvarX;
			dragon->setFacing(180);
		}
		else
		{
			if (isFront)
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

		auto  randomvarY = 2 * CCRANDOM_0_1() - 1;
		appearPos.y = appearPos.y + randomvarY*distanceWithHeroY;
		dragon->setPosition(appearPos);
		dragon->getMyPos() = appearPos;
		dragon->setVisible(true);
		dragon->setGoRight(false);
		dragon->setAIEnabled(true);
		MonsterManager.push_back(dragon);
	}
}

void GameMaster::showPiglet(bool isFront)
{
	if (PigletPool.size() != 0)
	{
		Piglet * piglet = dynamic_cast<Piglet*> (PigletPool[0]);
		PigletPool.erase(PigletPool.begin());
		piglet->reset();

		auto appearPos = getFocusPointOfHeros();
		auto randomvarX = CCRANDOM_0_1()*0.2 + 1;

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

		auto  randomvarY = 2 * CCRANDOM_0_1() - 1;
		appearPos.y = appearPos.y + randomvarY*distanceWithHeroY;
		piglet->setPosition(appearPos);
		piglet->getMyPos() = appearPos;
		piglet->setVisible(true);
		piglet->setGoRight(false);
		piglet->setAIEnabled(true);
		MonsterManager.push_back(piglet);
	}
}

void GameMaster::showSlime(bool isFront)
{
	if (SlimePool.size() != 0)
	{
		Slime * cslime = dynamic_cast<Slime *> (SlimePool[0]);
		SlimePool.erase(SlimePool.begin());
		cslime->reset();
		cslime->setGoRight(false);
		jumpInto(cslime, isFront);
		MonsterManager.push_back(cslime);
	}
}

void GameMaster::showRat(bool isFront)
{
	if (RatPool.size() != 0)
	{
		Rat * crat = dynamic_cast<Rat *> (RatPool[0]);

		RatPool.erase(RatPool.begin());
		crat->reset();
		crat->setGoRight(false);
		jumpInto(crat, isFront);
		MonsterManager.push_back(crat);
	}
}


void GameMaster::randomshowMonster(bool isFront)
{
	auto random_var = CCRANDOM_0_1();

	if (random_var < 0.15)
	{
		if (DragonPool.size() != 0)
			showDragon(isFront);
		else
			randomshowMonster(isFront);
	}
	else if (random_var < 0.3)
	{
		if (RatPool.size() != 0)
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

	auto apperPos = Vec3(1000, 200, 300);
	boss->setPosition3D(apperPos);
	boss->setMyPos(Vec2(apperPos.x, apperPos.y));
	boss->setFacing(180);
	boss->setGoRight(false);
	boss->setCameraMask(2);

	auto enableAI = [boss]()
	{
		boss->setAIEnabled(true);
	};
	boss->runAction(Sequence::create(EaseBounceOut::create(MoveBy::create(0.5, Vec3(0, 0, -300))), CallFunc::create(enableAI), NULL));
	MonsterManager.push_back(boss);
}

void GameMaster::jumpInto(Actor* obj, bool isFront)
{
	auto appearPos = getFocusPointOfHeros();
	float randomvar = 2 * CCRANDOM_0_1() - 1;

	if (isFront)
	{
		appearPos.x += frontDistanceWithHeroX + randomvar*distanceWithHeroX;
	}
	else
	{
		appearPos.x = appearPos.x - backwardDistanceWithHeroX + randomvar*distanceWithHeroX;
	}

	appearPos.y += 1500;
	obj->setPosition(appearPos);
	obj->setMyPos(appearPos);

	auto enableAI = [obj]()
	{
		obj->setAIEnabled(true);
	};

	auto visibleMonster = [obj]()
	{
		obj->setVisible(true);
	};

	if (stage == 0)
	{
		obj->setAIEnabled(true);
		obj->runAction(JumpBy3D::create(0.5, Vec3(-200 * (CCRANDOM_0_1()*0.6 + 0.7), -400 * (CCRANDOM_0_1()*0.4 + 0.8), 0), 150, 1));
		obj->runAction(DelayTime::create(CCRANDOM_0_1()));
		obj->setVisible(true);
		obj->runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1()), CallFunc::create(visibleMonster), JumpBy3D::create(0.5, Vec3(-200 * (CCRANDOM_0_1()*0.6 + 0.7), -400 * (CCRANDOM_0_1()*0.4 + 0.8), 0), 150, 1), CallFunc::create(enableAI), NULL));
		obj->setFacing(135);
	}
	else
	{
		if (isFront)
		{
			obj->runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1()), CallFunc::create(visibleMonster), JumpBy3D::create(0.5, Vec3(0, -400 * (rand()*0.4 + 0.8), 0), 150, 1), CallFunc::create(enableAI), NULL));
			obj->setFacing(135);
		}
		else
		{
			obj->runAction(Sequence::create(DelayTime::create(CCRANDOM_0_1()), CallFunc::create(visibleMonster), JumpBy3D::create(0.5, Vec3((200 * rand()*0.6 + 0.7), -400 * (rand()*0.4 + 0.8), 0), 150, 1), CallFunc::create(enableAI), NULL));
			obj->setFacing(45);
		}
	}
}

void GameMaster::showWarning()
{
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::AUTO);

	auto warning = Layer::create();
	auto warning_logo = Sprite::createWithSpriteFrameName("caution.png");
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
	warning_logo->setPosition(VisibleSize.width*0.5, VisibleSize.height*0.5);
	warning_logo->setPositionZ(1);

	auto showdialog = [warning, this]()
	{
		warning->removeFromParent();
		this->showDialog();
		experimental::AudioEngine::play2d("audios/effects/boss/boss.mp3", false, 1);
	};

	warning_logo->runAction(Sequence::create(DelayTime::create(0.5), EaseSineOut::create(Blink::create(1, 5)), CallFunc::create(showdialog), NULL));
	warning->addChild(warning_logo);

	warning->setScale(1.5);
	warning->setPositionZ(-Director::getInstance()->getZEye() / 2);
	warning->ignoreAnchorPointForPosition(false);
	warning->setLocalZOrder(999);
	warning->setPosition(VisibleSize.width / 2, VisibleSize.height / 2);

	currentLayer->addChild(warning);
}

void GameMaster::showDialog()
{
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::AUTO);
	auto colorLayer = LayerColor::create(Color4B(10, 10, 10, 150));
	colorLayer->ignoreAnchorPointForPosition(false);
	colorLayer->setPositionZ(-Director::getInstance()->getZEye() / 5);
	colorLayer->setGlobalZOrder(0);

	colorLayer->setScale(1.5);
	colorLayer->setPosition(VisibleSize.width / 2, VisibleSize.height / 2);
	currentLayer->addChild(colorLayer);

	auto dialog = Layer::create();
	dialog->setPositionX(-VisibleSize.width*0.025);

	auto outframe = Sprite::createWithSpriteFrameName("outframe.png");
	outframe->setPosition(VisibleSize.width * 0.55, VisibleSize.height * 0.27);
	outframe->setScale(0.6*ResolutionRate);
	dialog->addChild(outframe);

	auto inframe = Sprite::createWithSpriteFrameName("inframe.png");
	inframe->setPosition(VisibleSize.width * 0.67, VisibleSize.height * 0.27);
	inframe->setScale(0.5*ResolutionRate);
	dialog->addChild(inframe);

	auto bossicon = Sprite::createWithSpriteFrameName("bossicon.png");
	bossicon->setPosition(VisibleSize.width*0.42, VisibleSize.height*0.46);
	bossicon->setScale(0.75*ResolutionRate);
	bossicon->setFlippedX(true);
	dialog->addChild(bossicon);

	auto bosslogo = Sprite::createWithSpriteFrameName("bosslogo.png");
	bosslogo->setPosition(VisibleSize.width*0.417, VisibleSize.height*0.265);
	bosslogo->setScale(0.74*ResolutionRate);
	dialog->addChild(bosslogo);

	auto text = Label::createWithTTF("How dare you???", "fonts/britanic bold.ttf", 24);
	text->setPosition(VisibleSize.width*0.68, VisibleSize.height*0.27);
	dialog->addChild(text);

	dialog->setScale(0.1);
	dialog->ignoreAnchorPointForPosition(false);
	dialog->setPositionZ(Director::getInstance()->getZEye() / 3);
	dialog->setGlobalZOrder(0);

	dialog->setPosition(VisibleSize.width * 0.45, VisibleSize.height / 2);
	currentLayer->addChild(dialog);

	auto pausegame = []()
	{
		for (int i = 0; i < HeroManager.size(); i++)
		{
			HeroManager[i]->idleMode();
			HeroManager[i]->setAIEnabled(false);
		}
	};

	dialog->runAction(Sequence::create(ScaleTo::create(0.5, 0.65), CallFunc::create(pausegame), NULL));
	uiLayer->setVisible(false);

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
	dialog->runAction(Sequence::create(DelayTime::create(3), ScaleTo::create(0.5, 0.1), CallFunc::create(removeDialog), NULL));

	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
}

void GameMaster::showVictoryUI()
{
	uiLayer->showVictoryUI();
}

void GameMaster::showGameOverUI()
{
	uiLayer->showGameOverUI();
}

void GameMaster::playerControl(Vec2 positionOf3DWorld, float angleOf3DWorld)
{
	//getPlayer()->setPosition(positionOf3DWorld);
	auto monster = getTouchedMonster(positionOf3DWorld, angleOf3DWorld);
	if (monster != nullptr)
	{
		auto state = getPlayer()->getStateType();
		getPlayer()->setTarget(monster);
		if (state == EnumStateType::IDLE || state == EnumStateType::KNOCKING)
		    getPlayer()->walkMode();
	}
	else {
		getPlayer()->setTargetPos(positionOf3DWorld);
		getPlayer()->setTarget(nullptr);
		auto state = getPlayer()->getStateType();
		if (state == EnumStateType::IDLE || state == EnumStateType::KNOCKING)
		    getPlayer()->walkMode();
	}
}

Actor* GameMaster::getTouchedMonster(Vec2 positionOf3DWorld, float angleOf3DWorld)
{
	auto monsterManger = MonsterManager;
	auto getPositionY = [](Actor*monster1, Actor*monster2)
	{
		return monster1->getPositionY() < monster2->getPositionY();
	};
	std::sort(monsterManger.begin(), monsterManger.end(), getPositionY);

	auto width = 200;
	auto depth = 200;
	for (auto it : monsterManger)
	{
		if (it->getPositionX() < positionOf3DWorld.x + width / 2 && it->getPositionX() > positionOf3DWorld.x - width / 2
			&& it->getPositionY() < positionOf3DWorld.y + depth / 2 && it->getPositionY() > positionOf3DWorld.y - depth / 2)
			return it;
	}
	return nullptr;
}

void GameMaster::setPlayer(std::string playerName)
{
	if (playerName == "Knight")
	{
		_playerName = "Knight";
		_player = HeroManager.at(0);
		_player->setAIEnabled(true);
		uiLayer->PlayerLabel->setPosition(uiLayer->KnightPng->getPosition());
	}
	if (playerName == "Mage")
	{
		_playerName = "Mage";
		_player = HeroManager.at(1);
		uiLayer->PlayerLabel->setPosition(uiLayer->MagePng->getPosition());
	}
	if (playerName == "Archer")
	{
		_playerName = "Archer";
		_player = HeroManager.at(2);
		uiLayer->PlayerLabel->setPosition(uiLayer->ArcherPng->getPosition());
	}
	if(playerName=="")
	{
		_playerName = "";
		_player = nullptr;
		return;
	}
	getPlayer()->setPlayer();
}


Actor* GameMaster::getPlayer()
{
	return _player;
}

std::string GameMaster::getPlayerName()
{
	return _playerName;
}
