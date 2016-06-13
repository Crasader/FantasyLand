#include "BattleFieldUI.h"
#include "GlobalVariables.h"
#include <AudioEngine.h>
#include "Actor.h"

bool BattleFieldUI::init()
{
	Layer::init();

	avatarInit();
	bloodbarInit();
	angrybarInit();
	touchButtonInit();
	timeInit();

	experimental::AudioEngine::stopAll();
	//AUDIO_ID.BATTLEFIELDBGM = experimental::AudioEngine::play2d(BGM_RES.BATTLEFIELDBGM, true, 0.6);
	return true;
}

void BattleFieldUI::avatarInit()
{
	auto offset = 8;
	auto scale = 0.7;
	MagePng = Sprite::createWithSpriteFrameName("UI-1136-640_18.png");
	MagePng->setPosition3D(Vec3(1070 / 1136 * G.winSize.width, 70 / 640 * G.winSize.height, 2));
	MagePng->setScale(scale);
	addChild(MagePng, 2);
	MagePngFrame = Sprite::createWithSpriteFrameName("UI-2.png");
	MagePngFrame->setScale(scale);
	MagePngFrame->setPosition3D(Vec3(MagePng->getPositionX() + 1, MagePng->getPositionY() - offset, 1));
	addChild(MagePngFrame, 1);

	KnightPng = Sprite::createWithSpriteFrameName("UI-1136-640_03.png");
	KnightPng->setPosition3D(Vec3(-MagePng->getContentSize().width * 2 + MagePng->getPositionX() + 40, 70 / 640 * G.winSize.height, 2));
	KnightPng->setScale(scale);
	addChild(KnightPng, 2);
	KnightPngFrame = Sprite::createWithSpriteFrameName("UI-2.png");
	KnightPngFrame->setScale(scale);
	KnightPngFrame->setPosition3D(Vec3(KnightPng->getPositionX() + 1, KnightPng->getPositionY() - offset, 1));
	addChild(KnightPngFrame, 1);

	ArcherPng = Sprite::createWithSpriteFrameName("UI-1136-640_11.png");
	ArcherPng->setPosition3D(Vec3(-MagePng->getContentSize().width + MagePng->getPositionX() + 20, 70 / 640 * G.winSize.height, 2));
	ArcherPng->setScale(scale);
	addChild(ArcherPng, 2);
	ArcherPngFrame = Sprite::createWithSpriteFrameName("UI-2.png");
	ArcherPngFrame->setScale(scale);
	ArcherPngFrame->setPosition3D(Vec3(ArcherPng->getPositionX() + 1, ArcherPng->getPositionY() - offset, 1));
	addChild(ArcherPngFrame, 1);
}

void BattleFieldUI::bloodbarInit()
{
	auto offset = 45;
	auto scale = 0.7;
	KnightBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightBlood->setColor(Color3B(149, 254, 26));
	KnightBlood->setType(ProgressTimerType::BAR);
	KnightBlood->setBarChangeRate(Vec2(1, 0));
	KnightBlood->setMidpoint(Vec2(0, 0));
	KnightBlood->setPercentage(100);
	KnightBlood->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 4));
	KnightBlood->setScale(scale);
	addChild(KnightBlood, 4);

	KnightBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightBloodClone->setColor(Color3B(255, 83, 23));
	KnightBloodClone->setType(ProgressTimerType::BAR);
	KnightBloodClone->setBarChangeRate(Vec2(1, 0));
	KnightBloodClone->setMidpoint(Vec2(0, 0));
	KnightBloodClone->setPercentage(100);
	KnightBloodClone->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 3));
	KnightBloodClone->setScale(scale);
	addChild(KnightBloodClone, 3);

	ArcherBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherBlood->setColor(Color3B(149, 254, 26));
	ArcherBlood->setType(ProgressTimerType::BAR);
	ArcherBlood->setMidpoint(Vec2(0, 0));
	ArcherBlood->setBarChangeRate(Vec2(1, 0));
	ArcherBlood->setPercentage(100);
	ArcherBlood->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 4));
	ArcherBlood->setScale(scale);
	addChild(ArcherBlood, 4);

	ArcherBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherBloodClone->setColor(Color3B(255, 83, 23));
	ArcherBloodClone->setType(ProgressTimerType::BAR);
	ArcherBloodClone->setBarChangeRate(Vec2(1, 0));
	ArcherBloodClone->setMidpoint(Vec2(0, 0));
	ArcherBloodClone->setPercentage(100);
	ArcherBloodClone->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 3));
	ArcherBloodClone->setScale(scale);
	addChild(ArcherBloodClone, 3);

	//杜：此处修改多处，因为我需要返回各种Blood和Clone
	MageBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	MageBlood->setColor(Color3B(149, 254, 26));
	MageBlood->setType(ProgressTimerType::BAR);
	MageBlood->setMidpoint(Vec2(0, 0));
	MageBlood->setBarChangeRate(Vec2(1, 0));
	MageBlood->setPercentage(100);
	MageBlood->setPosition3D(Vec3(MagePng->getPositionX() - 1, MagePng->getPositionY() - offset, 4));
	MageBlood->setScale(scale);
	addChild(MageBlood, 4);

	MageBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	MageBloodClone->setColor(Color3B(255, 83, 23));
	MageBloodClone->setType(ProgressTimerType::BAR);
	MageBloodClone->setBarChangeRate(Vec2(1, 0));
	MageBloodClone->setMidpoint(Vec2(0, 0));
	MageBloodClone->setPercentage(100);
	MageBloodClone->setPosition3D(Vec3(MagePng->getPositionX() - 1, MagePng->getPositionY() - offset, 3));
	MageBloodClone->setScale(scale);
	addChild(MageBloodClone, 3);
}

void BattleFieldUI::angrybarInit()
{
	auto offset = 53;
	auto fullAngerStarOffset = 70;
	auto yellow = Color3B(255, 255, 0);
	auto grey = Color3B(113, 103, 76);
	auto action = RepeatForever::create(RotateBy::create(1, Vec3(0, 0, 360)));

	KnightAngry = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightAngry->setColor(yellow);
	KnightAngry->setType(ProgressTimer::Type::BAR);
	KnightAngry->setBarChangeRate(Vec2(1, 0));
	KnightAngry->setMidpoint(Vec2(0, 0));
	KnightAngry->setPercentage(0);
	KnightAngry->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 4));
	KnightAngry->setScale(0.7);
	addChild(KnightAngry, 4);

	KnightAngryClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightAngryClone->setColor(grey);
	KnightAngryClone->setType(ProgressTimer::Type::BAR);
	KnightAngryClone->setBarChangeRate(Vec2(1, 0));
	KnightAngryClone->setMidpoint(Vec2(0, 0));
	KnightAngryClone->setPercentage(100);
	KnightAngryClone->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 3));
	KnightAngryClone->setScaleX(0.7);
	KnightAngryClone->setScaleY(0.75);
	addChild(KnightAngryClone, 3);

	auto KnightAngryFullSignal = Sprite::createWithSpriteFrameName("specialLight.png");
	KnightAngryFullSignal->setPosition3D(Vec3(KnightPng->getPositionX(), KnightPng->getPositionY() + fullAngerStarOffset, 4));
	KnightAngryFullSignal->runAction(action);
	KnightAngryFullSignal->setScale(1);
	addChild(KnightAngryFullSignal, 4);
	KnightAngryFullSignal->setVisible(false);

	ArcherAngry = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherAngry->setColor(yellow);
	ArcherAngry->setType(ProgressTimer::Type::BAR);
	ArcherAngry->setMidpoint(Vec2(0, 0));
	ArcherAngry->setBarChangeRate(Vec2(1, 0));
	ArcherAngry->setPercentage(0);
	ArcherAngry->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 4));
	ArcherAngry->setScale(0.7);
	addChild(ArcherAngry, 4);

	ArcherAngryClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherAngryClone->setColor(grey);
	ArcherAngryClone->setType(ProgressTimer::Type::BAR);
	ArcherAngryClone->setBarChangeRate(Vec2(1, 0));
	ArcherAngryClone->setMidpoint(Vec2(0, 0));
	ArcherAngryClone->setPercentage(100);
	ArcherAngryClone->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 3));
	ArcherAngryClone->setScaleX(0.7);
	ArcherAngryClone->setScaleY(0.75);
	addChild(ArcherAngryClone, 3);

	auto ArcherAngryFullSignal = Sprite::createWithSpriteFrameName("specialLight.png");
	ArcherAngryFullSignal->setPosition3D(Vec3(ArcherPng->getPositionX(), ArcherPng->getPositionY() + fullAngerStarOffset, 4));
	addChild(ArcherAngryFullSignal, 4);
	ArcherAngryFullSignal->runAction(action->clone());
	ArcherAngryFullSignal->setScale(1);
	ArcherAngryFullSignal->setVisible(false);

	MageAngry = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	MageAngry->setColor(yellow);
	MageAngry->setType(ProgressTimer::Type::BAR);
	MageAngry->setMidpoint(Vec2(0, 0));
	MageAngry->setBarChangeRate(Vec2(1, 0));
	MageAngry->setPercentage(0);
	MageAngry->setPosition3D(Vec3(MagePng->getPositionX() - 1, MagePng->getPositionY() - offset, 4));
	MageAngry->setScale(0.7);
	addChild(MageAngry, 4);

	auto MageAngryClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	MageAngryClone->setColor(grey);
	MageAngryClone->setType(ProgressTimer::Type::BAR);
	MageAngryClone->setBarChangeRate(Vec2(1, 0));
	MageAngryClone->setMidpoint(Vec2(0, 0));
	MageAngryClone->setPercentage(100);
	MageAngryClone->setPosition3D(Vec3(MagePng->getPositionX() - 1, MagePng->getPositionY() - offset, 3));
	MageAngryClone->setScaleX(0.7);
	MageAngryClone->setScaleY(0.75);
	addChild(MageAngryClone, 3);

	auto MageAngryFullSignal = Sprite::createWithSpriteFrameName("specialLight.png");
	MageAngryFullSignal->setPosition3D(Vec3(MagePng->getPositionX(), MagePng->getPositionY() + fullAngerStarOffset, 4));
	addChild(MageAngryFullSignal, 4);
	MageAngryFullSignal->runAction(action->clone());
	MageAngryFullSignal->setScale(1);
	MageAngryFullSignal->setVisible(false);
}

void BattleFieldUI::touchButtonInit()
{
	auto _setBtn = Sprite::createWithSpriteFrameName("UI-1136-640_06.png");
	_setBtn->setPosition3D(Vec3(1093 / 1136 * G.winSize.width, 591 / 640 * G.winSize.height, 3));
	_setBtn->setScale(0.8);
	addChild(_setBtn, 3);

	auto _chest = Sprite::createWithSpriteFrameName("chest.png");
	_chest->setPosition3D(Vec3(861 / 1136 * G.winSize.width, 595 / 640 * G.winSize.height, 3));
	_chest->setScale(0.8);
	addChild(_chest, 3);

	auto _coin = Sprite::createWithSpriteFrameName("coins.png");
	_coin->setPosition3D(Vec3(1028.49 / 1136 * G.winSize.width, 593 / 640 * G.winSize.height, 3));
	_coin->setScaleX(0.8);
	_coin->setScaleY(0.8);
	addChild(_coin, 3);

	auto _chestAmount = Sprite::createWithSpriteFrameName("UI-1.png");
	_chestAmount->setPosition3D(Vec3(785 / 1136 * G.winSize.width, 590 / 640 * G.winSize.height, 2));
	_chestAmount->setScaleX(0.8);
	_chestAmount->setScaleY(0.7);
	addChild(_chestAmount, 2);

	auto _coinAmount = Sprite::createWithSpriteFrameName("UI-1.png");
	_coinAmount->setPosition3D(Vec3(957 / 1136 * G.winSize.width, 590 / 640 * G.winSize.height, 2));
	_coinAmount->setScaleX(0.8);
	_coinAmount->setScaleY(0.7);
	addChild(_coinAmount, 2);
}

void BattleFieldUI::shakeAvatar()
{
	Repeat::create(Spawn::create(Sequence::create(ScaleTo::create(0.075, 0.75),
		ScaleTo::create(0.075, 0.7)),
		Sequence::create(MoveBy::create(0.05, { 6.5, 0 }),
			MoveBy::create(0.05, { -13, 0 }),
			MoveBy::create(0.05, { 6.5, 0 }))), 2);
	return;
}

void BattleFieldUI::bloodDrop(Actor* heroActor)
{
	//auto progressTo;
	//auto progressToClone;
	//auto tintTo;
	//auto percent = heroActor->get / heroActor._maxhp * 100;
	//heroActor._bloodBar:stopAllActions();
	//heroActor._bloodBarClone->stopAllActions();
	//heroActor._avatar->runAction(BattlefieldUI->shakeAvatar());

	//if heroActor._hp > 0 and percent > 50 then

	//	progressTo = ProgressTo:create(0.3, percent)
	//	progressToClone = ProgressTo->create(1, percent)
	//	heroActor._bloodBar->runAction(progressTo)
	//	heroActor._bloodBarClone->runAction(progressToClone)

	//	elseif heroActor._hp > 0 and percent <= 50 then

	//	progressTo = ProgressTo:create(0.3, percent)
	//	progressToClone = ProgressTo->create(1, percent)
	//	tintTo = TintTo->create(0.5, 254, 225, 26)

	//	heroActor._bloodBar->runAction(Spawn : create(progressTo, tintTo))
	//	heroActor._bloodBarClone->runAction(progressToClone)
	//	elseif heroActor._hp > 0 and percent <= 30 then

	//	progressTo = ProgressTo:create(0.3, percent)
	//	progressToClone = ProgressTo->create(1, percent)

	//	tintTo = TintTo->create(0.5, 254, 26, 69)
	//	heroActor._bloodBar->runAction(Spawn : create(progressTo, tintTo))
	//	heroActor._bloodBarClone->runAction(progressToClone)
	//	elseif heroActor._hp <= 0 then
	//	progressTo = ProgressTo->create(0.3, 0)
	//	progressToClone = ProgressTo->create(1, 2)

	//	heroActor._bloodBar->runAction(progressTo)
	//	heroActor._bloodBarClone->runAction(progressToClone)
	//	end
}

void BattleFieldUI::heroDead(Actor* heroActor)
{

	/*if hero._name == "Knight" then
		GreyShader : setGreyShader(KnightPng)
		GreyShader->setGreyShader(KnightPngFrame)
		KnightAngryFullSignal->setVisible(false)
		KnightAngryClone->setVisible(false)
		elseif hero._name == "Mage" then
		GreyShader->setGreyShader(MagePng)
		GreyShader->setGreyShader(MagePngFrame)
		MageAngryFullSignal->setVisible(false)
		MageAngryClone->setVisible(false)
		elseif hero._name == "Archer" then
		GreyShader->setGreyShader(ArcherPng)
		GreyShader->setGreyShader(ArcherPngFrame)
		ArcherAngryFullSignal->setVisible(false)
		ArcherAngryClone->setVisible(false)
		end*/
}

void BattleFieldUI::angryChange(Actor* heroActor)
{
	/*auto tintTo
		auto percent = angry._angry / angry._angryMax * 100
		auto progressTo = ProgressTo:create(0.3, percent)
		auto progressToClone = ProgressTo->create(1, percent + 2)

		auto bar
		if angry._name == KnightValues._name then
			bar = KnightAngry
			if percent >= 100 then
				KnightAngryFullSignal->setVisible(true)
				elseif percent == 0 then
				KnightAngryFullSignal->setVisible(false)
				end
				elseif angry._name == ArcherValues._name then
				bar = ArcherAngry
				if percent >= 100 then
					ArcherAngryFullSignal->setVisible(true)
					elseif percent == 0 then
					ArcherAngryFullSignal->setVisible(false)
					end
					elseif angry._name == MageValues._name then
					bar = MageAngry
					if percent >= 100 then
						MageAngryFullSignal->setVisible(true)
						elseif percent == 0 then
						MageAngryFullSignal->setVisible(false)
						end
						end

						bar->runAction(progressTo)*/
}

void BattleFieldUI::timeInit()
{
	//auto tm = { "00","00" }
	//	tm = table.concat(tm, ":")

	//	auto ttfconfig = { outlineSize = 1,fontSize = 25,fontFilePath = "fonts/britanic bold.ttf" }
	//	auto tm_label = Label:createWithTTF(ttfconfig, tm)
	//	tm_label->setAnchorPoint(0, 0)
	//	tm_label->setPosition3D(Vec3(G.winSize.width*0.02, G.winSize.height*0.915, 2))
	//	tm_label->enableOutline(c4b(0, 0, 0, 255))
	//	_tmlabel = tm_label
	//	addChild(tm_label, 5)
	//	--time update
	//	auto time = 0
	//	auto function tmUpdate()
	//	time = time + 1
	//	if time >= 3600 then
	//time = 0
	//end

	//auto dev = time
	//auto min = math.floor(dev / 60)
	//auto sec = dev % 60
	//if min < 10 then
	//min = "0"..min
	//end
	//if sec < 10 then
	//sec = "0"..sec
	//end
	//_tmlabel->setString(min..":"..sec)
	//end

	//_tmSchedule = Director->getInstance()->getScheduler()->scheduleScriptFunc(tmUpdate, 1, false)

}

void BattleFieldUI::showVictoryUI()
{
	//--diable AI

	//	--color layer
	//	auto layer = LayerColor:create(c4b(10, 10, 10, 150))
	//	layer->ignoreAnchorPointForPosition(false)
	//	layer->setPosition3D(Vec3(G.winSize.width*0.5, G.winSize.height*0.5, 0))
	//	--add victory
	//	auto victory = Sprite::createWithSpriteFrameName("victory.png")
	//	victory->setPosition3D(Vec3(G.winSize.width*0.5, G.winSize.height*0.5, 3))
	//	victory->setScale(0.1)
	//	layer->addChild(victory, 1)

	//	--victory runaction
	//	auto action = EaseElasticOut->create(ScaleTo:create(1.5, 1))
	//	victory->runAction(action)

	//	--touch event
	//	auto function onTouchBegan(touch, event)
	//	return true
	//	end
	//	auto function onTouchEnded(touch, event)
	//	--stop schedule
	//	Director : getInstance()->getScheduler()->unscheduleScriptEntry(_tmSchedule)
	//	Director->getInstance()->getScheduler()->unscheduleScriptEntry(gameControllerScheduleID)
	//	--stop sound
	//	ccexp.AudioEngine->stop(AUDIO_ID.BATTLEFIELDBGM)
	//	--replace scene
	//	Director->getInstance()->replaceScene(require("ChooseRoleScene")->create())
	//	end
	//	auto listener = EventListenerTouchOneByOne->create()
	//	listener->registerScriptHandler(onTouchBegan, Handler.EVENT_TOUCH_BEGAN)
	//	listener->registerScriptHandler(onTouchEnded, Handler.EVENT_TOUCH_ENDED)
	//	auto eventDispatcher = layer->getEventDispatcher()
	//	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, layer)

	//	addChild(layer)
}
