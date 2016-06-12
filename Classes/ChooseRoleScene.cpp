#include "ChooseRoleScene.h"
#include "ui/CocosGUI.h"
#include "BattleScene.h"
#include "Archer.h"
#include "Knight.h"
#include "Mage.h"

Scene* ChooseRoleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ChooseRoleScene::create();
	scene->addChild(layer);
	return scene;
}

bool ChooseRoleScene::init()
{
	layer->init();
	currentLayer = this;
	return true;
}

Sprite *ChooseRoleScene::addBag()
{
	auto bag = Sprite::createWithSpriteFrameName("cr_bag.png");
	bag->setTag(10);
	_bag = bag;
	switchTextWhenRotate();

	auto bagSize = bag->getContentSize();
	weapon_item_pos = Vec2(bagSize.width*0.36, bagSize.height*0.4);
	armour_item_pos = Vec2(bagSize.width*0.54, bagSize.height*0.4);
	helmet_item_pos = Vec2(bagSize.width*0.72, bagSize.height*0.4);

	_weaponItem = Sprite::createWithSpriteFrameName("knight_w_1.png");
	_weaponItem->setTag(11);
	_weaponItem->setScale(1);
	_weaponItem->setPosition(weapon_item_pos);
	bag->addChild(_weaponItem, 2);

	_armourItem = Sprite::createWithSpriteFrameName("knight_a_1.png");
	_armourItem->setTag(12);
	_armourItem->setScale(1);
	_armourItem->setPosition(armour_item_pos);
	bag->addChild(_armourItem, 2);

	_helmetItem = Sprite::createWithSpriteFrameName("knight_h_1.png");
	_helmetItem->setTag(13);
	_helmetItem->setScale(1);
	_helmetItem->setPosition(helmet_item_pos);
	bag->addChild(_helmetItem, 2);

	bag->setNormalizedPosition(Vec2(0.75, 0.5));
	//bag->setScale(resolutionRate)

	layer->addChild(bag);

	return bag;
}

void ChooseRoleScene::addButton()
{
	//button
	bool touch_next = false;

	auto touchEvent_next = [&touch_next, this](ui::TouchEventType eventType/*sender, eventType*/)
	{
		if (!touch_next)
			touch_next = true;
		if (eventType == ui::TOUCH_EVENT_BEGAN)
		{
			//ReSkin.knight = { weapon = layer->getChildByTag(2) : getWeaponID(),
			//	armour = layer : getChildByTag(2) : getArmourID(),
			//	helmet = layer : getChildByTag(2) : getHelmetID() };
			//ReSkin.arhcer = { weapon = layer->getChildByTag(1) : getWeaponID(),
			//armour = layer : getChildByTag(1) : getArmourID(),
			//helmet = layer : getChildByTag(1) : getHelmetID() };
			//ReSkin.mage = { weapon = layer->getChildByTag(3) : getWeaponID(),
			//armour = layer : getChildByTag(3) : getArmourID(),
			//helmet = layer : getChildByTag(3) : getHelmetID() };

			//auto playid = experimental::AudioEngine::play2d(BGM_RES.MAINMENUSTART, false, 1);
			//stop schedule
			Director::getInstance()->getScheduler()->unscheduleScriptEntry(_schedule_rotate);
			//replace scene
			//package.loaded["BattleScene"] = nil
			//package.loaded["Manager"] = nil
			//package.loaded["Helper"] = nil
			//package.loaded["MessageDispatchCenter"] = nil
			//package.loaded["BattleFieldUI"] = nil
			Director::getInstance()->runWithScene(BattleScene::createScene());
		}
	};

	auto next_Button = ui::Button::create("button1.png", "button2.png", "", ui::TextureResType::PLIST);
	next_Button->setTouchEnabled(true);
	next_Button->setNormalizedPosition(Vec2(0.34, 0.13));
	//next_Button->setScale(resolutionRate);
	//next_Button->addTouchEventListener(touchEvent_next);
	layer->addChild(next_Button);
}

void ChooseRoleScene::addHeros()
{
	auto knight = Knight::create();
	knight->setTag(2);
	knight->setRotation3D(rtt[2]);
	knight->setPosition3D(pos/*[2]*/);
	knight->setAIEnabled(false);
	knight->setScale(1.3);
	layer->addChild(knight);

	auto archer = Archer::create();
	archer->setTag(1);
	archer->setRotation3D(rtt[1]);
	archer->setPosition3D(pos/*[1]*/);
	archer->setAIEnabled(false);
	archer->setScale(1.3);
	layer->addChild(archer);

	auto mage = Mage::create();
	mage->setTag(3);
	mage->setRotation3D(rtt[3]);
	mage->setPosition3D(pos/*[3]*/);
	mage->setAIEnabled(false);
	mage->setScale(1.3);
	layer->addChild(mage);

	//hero rotate
	auto rotate = 0.5;
	auto hero_rotate = [this, rotate]()
	{
		auto rotation = layer->getChildByTag(sortorder[2])->getRotation3D();
		layer->getChildByTag(sortorder[2])->setRotation3D(Vec3(rotation.x, rotation.y + rotate, 0));
	};
	//_schedule_rotate = Director::getInstance()->getScheduler()->scheduleScriptFunc(hero_rotate, 0, false);
}

void ChooseRoleScene::addBk()
{
	auto bk = Sprite::create("chooseRole/cr_bk.jpg");
	bk->setAnchorPoint(Vec2(0.5, 0.5));
	bk->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	layer->addChild(bk);
}

Layer *ChooseRoleScene::createLayer()
{

	//create layer
	layer = layer->create();

	//create bk
	addBk();

	//create heros
	addHeros();

	//create arrow
	addButton();

	//create bag
	addBag();

	return layer;
}

//touch relative
void ChooseRoleScene::initTouchDispatcher()
{
	bool isRotateavaliable = false;
	bool isWeaponItemavaliable = false;
	bool isArmourItemavaliable = false;
	bool isHelmetItemavaliable = false;
	bool touchbeginPt;
	auto listenner = EventListenerTouchOneByOne::create();
	listenner->setSwallowTouches(true);
	//listenner:registerScriptHandler(function(touch, event)
	//	touchbeginPt = touch:getLocation()
	//	if rectContainsPoint(heroSize, touchbeginPt) then --rotate
	//		isRotateavaliable = true
	//		return true
	//		end
	//		touchbeginPt = _bag : convertToNodeSpace(touchbeginPt)
	//		if rectContainsPoint(_weaponItem:getBoundingBox(), touchbeginPt) then --weapon
	//			isWeaponItemavaliable = true
	//			_weaponItem : setScale(1.7)
	//			_weaponItem : setOpacity(150)
	//			elseif rectContainsPoint(_armourItem:getBoundingBox(), touchbeginPt) then --armour
	//			isArmourItemavaliable = true
	//			_armourItem : setScale(1.7)
	//			_armourItem : setOpacity(150)
	//			elseif rectContainsPoint(_helmetItem:getBoundingBox(), touchbeginPt) then --helmet
	//			isHelmetItemavaliable = true
	//			_helmetItem : setScale(1.7)
	//			_helmetItem : setOpacity(150)
	//			end
	//
	//			return true
	//			end, Handler.EVENT_TOUCH_BEGAN)
	//listenner:registerScriptHandler(function(touch, event)
	//	if isRotateavaliable == true and isMoving == false then --rotate
	//		auto dist = touch:getLocation().x - touchbeginPt.x
	//		if dist>50 then
	//			--right
	//			self : rotate3Heroes(true)
	//			isRotateavaliable = false
	//			elseif dist<-50 then
	//			--left
	//			self : rotate3Heroes(false)
	//			isRotateavaliable = false
	//		else
	//
	//			end
	//			elseif isWeaponItemavaliable then --weapon
	//			_weaponItem:setPosition(_bag:convertToNodeSpace(touch : getLocation()))
	//			elseif isArmourItemavaliable then --armour
	//			_armourItem : setPosition(_bag:convertToNodeSpace(touch : getLocation()))
	//			elseif isHelmetItemavaliable then --helmet
	//			_helmetItem : setPosition(_bag:convertToNodeSpace(touch : getLocation()))
	//			end
	//			end, Handler.EVENT_TOUCH_MOVED)
	//	listenner:registerScriptHandler(function(touch, event)
	//		if isRotateavaliable then --rotate
	//			isRotateavaliable = false
	//			elseif isWeaponItemavaliable then
	//			isWeaponItemavaliable = false
	//			_weaponItem:setPosition(weapon_item_pos)
	//			_weaponItem : setScale(1)
	//			_weaponItem : setOpacity(255)
	//			layer : getChildByTag(sortorder[2]) : switchWeapon()
	//			_weaponItem : setSpriteFrame(self : getWeaponTextureName())
	//			elseif isArmourItemavaliable then
	//			isArmourItemavaliable = false
	//			_armourItem : setPosition(armour_item_pos)
	//			_armourItem : setScale(1)
	//			_armourItem : setOpacity(255)
	//			layer : getChildByTag(sortorder[2]) : switchArmour()
	//			_armourItem : setSpriteFrame(self : getArmourTextureName())
	//			elseif isHelmetItemavaliable then
	//			isHelmetItemavaliable = false
	//			_helmetItem : setPosition(helmet_item_pos)
	//			_helmetItem : setScale(1)
	//			_helmetItem : setOpacity(255)
	//			layer : getChildByTag(sortorder[2]) : switchHelmet()
	//			_helmetItem : setSpriteFrame(self : getHelmetTextureName())
	//			end
	//			end, Handler.EVENT_TOUCH_ENDED)
	auto eventDispatcher = layer->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listenner, layer);
}

void ChooseRoleScene::rotate3Heroes(bool isRight)
{
	//stop hero rotate
	if (isRight)
		layer->getChildByTag(sortorder[2])->runAction(RotateTo::create(0.1, rtt[3]));
	else
		layer->getChildByTag(sortorder[2])->runAction(RotateTo::create(0.1, rtt[1]));

	double rotatetime = 0.6;
	if (isRight)
	{
		auto middle = layer->getChildByTag(sortorder[2]);
		//middle->runAction(Sequence::create(
		//	CallFunc::create(isMoving = true),
		//	Spawn::create(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[3]*/))),
		//	CallFunc::create([this]()
		//{
		//	isMoving = false;
		//	playAudioWhenRotate();
		//}
		//)));
		auto left = layer->getChildByTag(sortorder[1]);
		layer->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[2]*/)));
		auto right = layer->getChildByTag(sortorder[3]);
		right->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[1]*/)));
		auto t = sortorder[3];
		sortorder[3] = sortorder[2];
		sortorder[2] = sortorder[1];
		sortorder[1] = t;
	}
	else
	{
		auto middle = layer->getChildByTag(sortorder[2]);
		middle->runAction(Sequence::create(
			CallFunc::create([this]() {isMoving = true; }),
			Spawn::create(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[1]*/))
				),
			CallFunc::create([this]()
		{
			isMoving = false;
			playAudioWhenRotate();
		}
		)));
		auto left = layer->getChildByTag(sortorder[1]);
		left->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[3]*/)));
		auto right = layer->getChildByTag(sortorder[3]);
		right->runAction(EaseCircleActionInOut::create(MoveTo::create(rotatetime, pos/*[2]*/)));
		auto t = sortorder[1];
		sortorder[1] = sortorder[2];
		sortorder[2] = sortorder[3];
		sortorder[3] = t;
	}

	switchItemtextureWhenRotate();
	switchTextWhenRotate();
}

void ChooseRoleScene::getWeaponTextureName()
{
	//auto hero = layer->getChildByTag(sortorder[2]);
	//	if (hero->_name == "Knight") //warriors
	//		if (hero-> getWeaponID()) == 0 then
	//			return "knight_w_1.png"
	//			elseif hero : getWeaponID() == 1 then
	//			return "knight_w_0.png"
	//			end
	//			elseif hero._name == "Archer" then --archer
	//			if hero : getWeaponID() == 0 then
	//				return "archer_w_1.png"
	//				elseif hero : getWeaponID() == 1 then
	//				return "archer_w_0.png"
	//				end
	//				elseif hero._name == "Mage" then --sorceress
	//				if hero : getWeaponID() == 0 then
	//					return "mage_w_1.png"
	//					elseif hero : getWeaponID() == 1 then
	//					return "mage_w_0.png"
	//					end
	//					end
}

void ChooseRoleScene::getArmourTextureName()
{

}

void ChooseRoleScene::getHelmetTextureName()
{

}

void ChooseRoleScene::switchItemtextureWhenRotate()
{

}

void ChooseRoleScene::switchTextWhenRotate()
{

}

void ChooseRoleScene::playAudioWhenRotate()
{

}
