#include "ChooseRoleScene.h"
#include "ui/CocosGUI.h"
#include "BattleScene.h"
#include "Archer.h"
#include "Knight.h"
#include "Mage.h"

using std::string;
using std::to_string;
Scene* ChooseRoleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseRoleScene::create();
	scene->addChild(layer);
	return scene;
}

bool ChooseRoleScene::init()
{
	Layer::init();
	currentLayer = this;

	rtt[0] = Vec3(-90, -60, 0);
	rtt[1] = Vec3(-90, -70, 0);
	rtt[2] = Vec3(-90, -60, 0);

	pos[0] = Vec3(VisibleSize.width*0.14, VisibleSize.height*0.35, -180);
	pos[1] = Vec3(VisibleSize.width*0.34, VisibleSize.height*0.25, -4);
	pos[2] = Vec3(VisibleSize.width*0.5, VisibleSize.height*0.35, -180);

	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::AUTO);
	initTouchDispatcher();
	AUDIO_ID.CHOOSEROLECHAPTERBGM = experimental::AudioEngine::play2d(BGM_RES.CHOOSEROLESCENEBGM, true, 1);

	//create bk
	addBackground();
	//create heros
	addHeros();
	//create arrow
	addButton();
	//create bag
	addBag();

	return true;
}


Sprite* ChooseRoleScene::addBag()
{
	auto bag = Sprite::createWithSpriteFrameName("cr_bag.png");
	bag->setTag(10);
	_bag = bag;
	switchTextWhenRotate();

	auto bagSize = bag->getContentSize();
	weaponItemPosition = Vec2(bagSize.width*0.36, bagSize.height*0.4);
	armourItemPosition = Vec2(bagSize.width*0.54, bagSize.height*0.4);
	helmetItemPosition = Vec2(bagSize.width*0.72, bagSize.height*0.4);

	_weaponItem = Sprite::createWithSpriteFrameName("knight_w_1.png");
	_weaponItem->setTag(11);
	_weaponItem->setScale(1);
	_weaponItem->setPosition(weaponItemPosition);
	bag->addChild(_weaponItem, 2);

	_armourItem = Sprite::createWithSpriteFrameName("knight_a_1.png");
	_armourItem->setTag(12);
	_armourItem->setScale(1);
	_armourItem->setPosition(armourItemPosition);
	bag->addChild(_armourItem, 2);

	_helmetItem = Sprite::createWithSpriteFrameName("knight_h_1.png");
	_helmetItem->setTag(13);
	_helmetItem->setScale(1);
	_helmetItem->setPosition(helmetItemPosition);
	bag->addChild(_helmetItem, 2);

	bag->setPosition(Vec2(VisibleSize.width* 0.75, VisibleSize.height *0.5));
	bag->setScale(resolutionRate / 2);

	addChild(bag);

	return bag;
}

void ChooseRoleScene::addButton()
{
	//button
	auto touch_next = false;

	auto  touchEvent_next = [this, &touch_next](Ref*sender, ui::Widget::TouchEventType eventType)
	{
		if (touch_next == false)
			touch_next = true;
		if (eventType == ui::Widget::TouchEventType::BEGAN)
		{
			ReSkin.knight.weapon = ((Actor*)getChildByTag(2))->getWeaponID();
			ReSkin.knight.armour = ((Actor*)getChildByTag(2))->getArmourID();
			ReSkin.knight.helmet = ((Actor*)getChildByTag(2))->getHelmetID();
			ReSkin.archer.weapon = ((Actor*)getChildByTag(1))->getWeaponID();
			ReSkin.archer.armour = ((Actor*)getChildByTag(1))->getArmourID();
			ReSkin.archer.helmet = ((Actor*)getChildByTag(1))->getHelmetID();
			ReSkin.mage.weapon = ((Actor*)getChildByTag(3))->getWeaponID();
			ReSkin.mage.armour = ((Actor*)getChildByTag(3))->getArmourID();
			ReSkin.mage.helmet = ((Actor*)getChildByTag(3))->getHelmetID();

			auto playid = experimental::AudioEngine::play2d(BGM_RES.MAINMENUSTART, false, 1);
			//stop schedule
			Director::getInstance()->getScheduler()->unschedule("hero_rotate", this);
			//replace scene
			//package.loaded["BattleScene"] = nil;
			//package.loaded["Manager"] = nil;
			//package.loaded["Helper"] = nil;
			//package.loaded["MessageDispatchCenter"] = nil;
			//package.loaded["BattleFieldUI"] = nil;
			//auto scene = require("BattleScene");
			Director::getInstance()->replaceScene(BattleScene::createScene());
		}

	};


	auto next_Button = ui::Button::create("button1.png", "button2.png", "", ui::TextureResType::PLIST);
	next_Button->setTouchEnabled(true);
	next_Button->setPosition(Vec2(VisibleSize.width*0.34, VisibleSize.height*0.13));
	next_Button->setScale(resolutionRate / 2);
	next_Button->addTouchEventListener(touchEvent_next);
	addChild(next_Button);
}

void ChooseRoleScene::addHeros()
{
	auto knight = Knight::create();
	knight->setTag(2);
	knight->setRotation3D(rtt[1]);
	knight->setPosition3D(pos[1]);
	knight->setAIEnabled(false);
	knight->setScale(1.3);
	addChild(knight);

	auto archer = Archer::create();
	archer->setTag(1);
	archer->setRotation3D(rtt[0]);
	archer->setPosition3D(pos[0]);
	archer->setAIEnabled(false);
	archer->setScale(1.3);
	addChild(archer);

	auto mage = Mage::create();
	mage->setTag(3);
	mage->setRotation3D(rtt[2]);
	mage->setPosition3D(pos[2]);
	mage->setAIEnabled(false);
	mage->setScale(1.3);
	addChild(mage);

	//hero rotate
	auto rotate = 0.5;
	auto  hero_rotate = [this, rotate](float dt)
	{
		auto rotation = getChildByTag(sortOrder[1])->getRotation3D();
		getChildByTag(sortOrder[1])->setRotation3D(Vec3(rotation.x, rotation.y + rotate, 0));
	};
	Director::getInstance()->getScheduler()->schedule(hero_rotate, this, 0, -1, "hero_rotate");
}

void ChooseRoleScene::addBackground()
{
	bk = Sprite::create("chooseRole/cr_bk.jpg");
	bk->setAnchorPoint(Vec2(0.5, 0.5));
	bk->setPosition(origin.x + VisibleSize.width / 2, origin.y + VisibleSize.height / 2);
	addChild(bk);
}

void ChooseRoleScene::initTouchDispatcher()
{
	isRotateAvaliable = false;
	isWeaponItemAvaliable = false;
	isArmourItemAvaliable = false;
	isHelmetItemAvaliable = false;
	auto listenner = EventListenerTouchOneByOne::create();
	listenner->setSwallowTouches(true);
	listenner->onTouchBegan = [this](Touch*touch, Event*)
	{
		touchBeginPoint = touch->getLocation();
		if (heroSize.containsPoint(touchBeginPoint)) //rotate
		{
			isRotateAvaliable = true;
			return true;
		}
		touchBeginPoint = _bag->convertToNodeSpace(touchBeginPoint);
		if (_weaponItem->getBoundingBox().containsPoint(touchBeginPoint))  //weapon
		{
			isWeaponItemAvaliable = true;
			_weaponItem->setScale(1.7);
			_weaponItem->setOpacity(150);
		}

		else if (_armourItem->getBoundingBox().containsPoint(touchBeginPoint))  //armour
		{
			isArmourItemAvaliable = true;
			_armourItem->setScale(1.7);
			_armourItem->setOpacity(150);
		}

		else if (_helmetItem->getBoundingBox().containsPoint(touchBeginPoint))  //helmet
		{
			isHelmetItemAvaliable = true;
			_helmetItem->setScale(1.7);
			_helmetItem->setOpacity(150);
		}

		return true;
	};
	listenner->onTouchMoved = [this](Touch*touch, Event*)
	{
		if (isRotateAvaliable == true && isMoving == false)  //rotate
		{
			auto dist = touch->getLocation().x - touchBeginPoint.x;
			if (dist > 50)
			{
				//right
				rotate3Heroes(true);
				isRotateAvaliable = false;
			}

			else if (dist < -50)
			{
				//left
				rotate3Heroes(false);
				isRotateAvaliable = false;
			}
		}
		else if (isWeaponItemAvaliable)  //weapon
			_weaponItem->setPosition(_bag->convertToNodeSpace(touch->getLocation()));
		else if (isArmourItemAvaliable)  //armour
			_armourItem->setPosition(_bag->convertToNodeSpace(touch->getLocation()));
		else if (isHelmetItemAvaliable)  //helmet
			_helmetItem->setPosition(_bag->convertToNodeSpace(touch->getLocation()));
	};
	listenner->onTouchEnded = [this](Touch*touch, Event*)
	{
		auto hero = (Actor*)getChildByTag(sortOrder[1]);
		auto heroName = hero->getname();
		if (isRotateAvaliable) //rotate
			isRotateAvaliable = false;
		else if (isWeaponItemAvaliable)
		{
			isWeaponItemAvaliable = false;
			_weaponItem->setPosition(weaponItemPosition);
			_weaponItem->setScale(1);
			_weaponItem->setOpacity(255);
			if (heroName == "Archer")
				static_cast<Archer*>(hero)->switchWeapon();
			else if (heroName == "Mage")
				static_cast<Mage*>(hero)->switchWeapon();
			else if (heroName == "Knight")
				static_cast<Knight*>(hero)->switchWeapon();
			_weaponItem->setSpriteFrame(getWeaponTextureName());
		}

		else if (isArmourItemAvaliable)
		{
			isArmourItemAvaliable = false;
			_armourItem->setPosition(armourItemPosition);
			_armourItem->setScale(1);
			_armourItem->setOpacity(255);
			if (heroName == "Archer")
				static_cast<Archer*>(hero)->switchArmour();
			else if (heroName == "Mage")
				static_cast<Mage*>(hero)->switchArmour();
			else if (heroName == "Knight")
				static_cast<Knight*>(hero)->switchArmour();
			_armourItem->setSpriteFrame(getArmourTextureName());
		}

		else if (isHelmetItemAvaliable)
		{
			isHelmetItemAvaliable = false;
			_helmetItem->setPosition(helmetItemPosition);
			_helmetItem->setScale(1);
			_helmetItem->setOpacity(255);
			if (heroName == "Archer")
				static_cast<Archer*>(hero)->switchHelmet();
			else if (heroName == "Mage")
				static_cast<Mage*>(hero)->switchHelmet();
			else if (heroName == "Knight")
				static_cast<Knight*>(hero)->switchHelmet();
			_helmetItem->setSpriteFrame(getHelmetTextureName());
		}
	};
	auto eventDispatcher = getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenner, this);
}

void ChooseRoleScene::rotate3Heroes(bool isRight)
{
	//stop hero rotate
	if (isRight)
		getChildByTag(sortOrder[1])->runAction(RotateTo::create(0.1, rtt[2]));
	else
		getChildByTag(sortOrder[1])->runAction(RotateTo::create(0.1, rtt[0]));

	auto rotatetime = 0.6;
	if (isRight)
	{
		auto middle = getChildByTag(sortOrder[1]);
		middle->runAction(Sequence::create(
			CallFunc::create([this]()
		{
			isMoving = true;
		}),
			Spawn::create(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[2])), NULL),
			CallFunc::create([this]()
		{
			isMoving = false;
			playAudioWhenRotate();

		}),
			NULL));
		auto left = getChildByTag(sortOrder[0]);
		left->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[1])));
		auto right = getChildByTag(sortOrder[2]);
		right->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[0])));
		auto t = sortOrder[2];
		sortOrder[2] = sortOrder[1];
		sortOrder[1] = sortOrder[0];
		sortOrder[0] = t;
	}

	else
	{
		auto middle = getChildByTag(sortOrder[1]);
		middle->runAction(Sequence::create(
			CallFunc::create([this]()
		{
			isMoving = true;
		}
				),
			Spawn::create(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[0])), NULL),
			CallFunc::create([this]()
		{
			isMoving = false;
			playAudioWhenRotate();
		}),
			NULL));
		auto left = getChildByTag(sortOrder[0]);
		left->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[2])));
		auto right = getChildByTag(sortOrder[2]);
		right->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos[1])));
		auto t = sortOrder[0];
		sortOrder[0] = sortOrder[1];
		sortOrder[1] = sortOrder[2];
		sortOrder[2] = t;
	}

	switchItemtextureWhenRotate();
	switchTextWhenRotate();
}

string ChooseRoleScene::getWeaponTextureName()
{
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	if (hero->getname() == "Knight")  //warriors
	{
		if (hero->getHelmetID() == 0)
			return "knight_w_1.png";
		else if (hero->getHelmetID() == 1)
			return "knight_w_0.png";
	}

	else if (hero->getname() == "Archer") //archer
	{
		if (hero->getHelmetID() == 0)
			return "archer_w_1.png";
		else if (hero->getHelmetID() == 1)
			return "archer_w_0.png";
	}

	else if (hero->getname() == "Mage")  //sorceress
	{
		if (hero->getHelmetID() == 0)
			return "mage_w_1.png";
		else if (hero->getHelmetID() == 1)
			return "mage_w_0.png";
	}
}

string ChooseRoleScene::getArmourTextureName()
{
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	if (hero->getname() == "Knight")  //warriors
	{
		if (hero->getHelmetID() == 0)
			return "knight_a_1.png";
		else if (hero->getHelmetID() == 1)
			return "knight_a_0.png";
	}

	else if (hero->getname() == "Archer") //archer
	{
		if (hero->getHelmetID() == 0)
			return "archer_a_1.png";
		else if (hero->getHelmetID() == 1)
			return "archer_a_0.png";
	}

	else if (hero->getname() == "Mage")  //sorceress
	{
		if (hero->getHelmetID() == 0)
			return "mage_a_1.png";
		else if (hero->getHelmetID() == 1)
			return "mage_a_0.png";
	}
}

string  ChooseRoleScene::getHelmetTextureName()
{
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	if (hero->getname() == "Knight")  //warriors
	{
		if (hero->getHelmetID() == 0)
			return "knight_h_1.png";
		else if (hero->getHelmetID() == 1)
			return "knight_h_0.png";
	}

	else if (hero->getname() == "Archer") //archer
	{
		if (hero->getHelmetID() == 0)
			return "archer_h_1.png";
		else if (hero->getHelmetID() == 1)
			return "archer_h_0.png";
	}

	else if (hero->getname() == "Mage")  //sorceress
	{
		if (hero->getHelmetID() == 0)
			return "mage_h_1.png";
		else if (hero->getHelmetID() == 1)
			return "mage_h_0.png";
	}
}

void ChooseRoleScene::switchItemtextureWhenRotate()
{
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	auto xxx = sortOrder[1];
	auto type = hero->getRaceType();

	string  weaponTexture;
	string  armourTexture;
	string  helmetTexture;
	if (hero->getname() == "Knight")  //warroir
	{
		if (hero->getWeaponID() == 0)
			weaponTexture = "knight_w_1.png";
		else
			weaponTexture = "knight_w_0.png";
		if (hero->getArmourID() == 0)
			armourTexture = "knight_a_1.png";
		else
			armourTexture = "knight_a_0.png";
		if (hero->getHelmetID() == 0)
			helmetTexture = "knight_h_1.png";
		else
			helmetTexture = "knight_h_0.png";
	}

	if (hero->getname() == "Archer")  //archer
	{
		if (hero->getWeaponID() == 0)
			weaponTexture = "archer_w_1.png";
		else
			weaponTexture = "archer_w_0.png";
		if (hero->getArmourID() == 0)
			armourTexture = "archer_a_1.png";
		else
			armourTexture = "archer_a_0.png";

		if (hero->getHelmetID() == 0)
			helmetTexture = "archer_h_1.png";
		else
			helmetTexture = "archer_h_0.png";
	}

	if (hero->getname() == "Mage")  //sorceress
	{
		if (hero->getWeaponID() == 0)
			weaponTexture = "mage_w_1.png";
		else
			weaponTexture = "mage_w_0.png";
		if (hero->getArmourID() == 0)
			armourTexture = "mage_a_1.png";
		else
			armourTexture = "mage_a_0.png";
		if (hero->getHelmetID() == 0)
			helmetTexture = "mage_h_1.png";
		else
			helmetTexture = "mage_h_0.png";
	}

	_weaponItem->setSpriteFrame(weaponTexture);
	_armourItem->setSpriteFrame(armourTexture);
	_helmetItem->setSpriteFrame(helmetTexture);
}

void ChooseRoleScene::switchTextWhenRotate()
{
	//get hero type
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	auto type = hero->getRaceType();
	//get bag, bagSize and judge if has child
	auto bag = _bag;
	auto size = bag->getContentSize();
	auto actor = bag->getChildByTag(101);
	if (actor != nullptr)
	{
		bag->removeChildByTag(101);
		bag->removeChildByTag(102);
	}
	//actor point
	Vec2 point;

	//label
	TTFConfig ttfconfig;
	ttfconfig.outlineSize = 0;
	ttfconfig.fontSize = 15;
	ttfconfig.fontFilePath = "chooseRole/actor_param.ttf";
	auto text = "LEVEL""\n""ATT""\n""HP""\n""DEF""\n""AGI""\n""CRT""\n""S.ATT";

	//set actor and label
	string  attr;
	if (hero->getname() == "Knight")  //warriors
	{
		actor = Sprite::createWithSpriteFrameName("knight.png");
		point = ccp(size.width*0.395, size.height*0.9);
		attr = "23""\n"
			+ to_string(int(KnightValues._normalAttack.damage)) + "\n"
			+ to_string(int(KnightValues._hp)) + "\n"
			+ to_string(int(KnightValues._defense)) + "\n"
			+ to_string(int(KnightValues._AIFrequency) * 100) + "\n"
			+ to_string(int(KnightValues._specialAttack.damage)) + "\n"
			+ to_string(int(KnightValues._specialAttack.damage));
	}
	else if (hero->getname() == "Archer")  //archer
	{
		actor = Sprite::createWithSpriteFrameName("archer.png");
		point = Vec2(size.width*0.4, size.height*0.905);
		attr = "23""\n"
			+ to_string(int(ArcherValues._normalAttack.damage)) + "\n"
			+ to_string(int(ArcherValues._hp)) + "\n"
			+ to_string(int(ArcherValues._defense)) + "\n"
			+ to_string(int(ArcherValues._AIFrequency) * 100) + "\n"
			+ to_string(int(ArcherValues._specialAttack.damage)) + "\n"
			+ to_string(int(ArcherValues._specialAttack.damage));
	}
	else if (hero->getname() == "Mage")  //sorceress
	{
		actor = Sprite::createWithSpriteFrameName("mage.png");
		point = Vec2(size.width*0.38, size.height*0.9);
		attr = "23""\n"
			+ to_string(int(MageValues._normalAttack.damage)) + "\n"
			+ to_string(int(MageValues._hp)) + "\n"
			+ to_string(int(MageValues._defense)) + "\n"
			+ to_string(int(MageValues._AIFrequency) * 100) + "\n"
			+ to_string(int(MageValues._specialAttack.damage)) + "\n"
			+ to_string(int(MageValues._specialAttack.damage));
	}

	//add to bag
	actor->setPosition(point);
	auto text_label = Label::createWithTTF(ttfconfig, text, TextHAlignment::CENTER, 400);
	text_label->setPosition(Vec2(size.width*0.45, size.height*0.68));
	text_label->enableShadow(Color4B(92, 50, 31, 255), Size(1, -2), 0);

	auto attr_label = Label::createWithTTF(ttfconfig, attr, TextHAlignment::CENTER, 400);
	attr_label->setPosition(Vec2(size.width*0.65, size.height*0.68));
	attr_label->enableShadow(Color4B(92, 50, 31, 255), Size(1, -2), 0);
	bag->addChild(actor, 1, 101);
	bag->addChild(text_label, 1);
	bag->addChild(attr_label, 1, 102);
}

void ChooseRoleScene::playAudioWhenRotate()
{
	auto hero = static_cast<Actor*>(getChildByTag(sortOrder[1]));
	auto type = hero->getRaceType();
	if (hero->getname() == "Knight")
		experimental::AudioEngine::play2d(WarriorProperty.kickit, false, 1);
	else if (hero->getname() == "Archer")
		experimental::AudioEngine::play2d(Archerproperty.iwillfight, false, 1);
	else if (hero->getname() == "Mage")
		experimental::AudioEngine::play2d(MageProperty.letstrade, false, 1);
}
