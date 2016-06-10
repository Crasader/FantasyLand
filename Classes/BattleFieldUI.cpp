#include "BattleFieldUI.h"
#include <AudioEngine.h>
#include "GlobalVariables.h"

BattleFieldUI *uiLayer;

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
	auto KnightBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightBlood->setColor(Color3B(149, 254, 26));
	KnightBlood->setType(ProgressTimerType::BAR);
	KnightBlood->setBarChangeRate(Vec2(1, 0));
	KnightBlood->setMidpoint(Vec2(0, 0));
	KnightBlood->setPercentage(100);
	KnightBlood->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 4));
	KnightBlood->setScale(scale);
	addChild(KnightBlood, 4);

	auto KnightBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	KnightBloodClone->setColor(Color3B(255, 83, 23));
	KnightBloodClone->setType(ProgressTimerType::BAR);
	KnightBloodClone->setBarChangeRate(Vec2(1, 0));
	KnightBloodClone->setMidpoint(Vec2(0, 0));
	KnightBloodClone->setPercentage(100);
	KnightBloodClone->setPosition3D(Vec3(KnightPng->getPositionX() - 1, KnightPng->getPositionY() - offset, 3));
	KnightBloodClone->setScale(scale);
	addChild(KnightBloodClone, 3);

	auto ArcherBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherBlood->setColor(Color3B(149, 254, 26));
	ArcherBlood->setType(ProgressTimerType::BAR);
	ArcherBlood->setMidpoint(Vec2(0, 0));
	ArcherBlood->setBarChangeRate(Vec2(1, 0));
	ArcherBlood->setPercentage(100);
	ArcherBlood->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 4));
	ArcherBlood->setScale(scale);
	addChild(ArcherBlood, 4);

	auto ArcherBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	ArcherBloodClone->setColor(Color3B(255, 83, 23));
	ArcherBloodClone->setType(ProgressTimerType::BAR);
	ArcherBloodClone->setBarChangeRate(Vec2(1, 0));
	ArcherBloodClone->setMidpoint(Vec2(0, 0));
	ArcherBloodClone->setPercentage(100);
	ArcherBloodClone->setPosition3D(Vec3(ArcherPng->getPositionX() - 1, ArcherPng->getPositionY() - offset, 3));
	ArcherBloodClone->setScale(scale);
	addChild(ArcherBloodClone, 3);

	auto MageBlood = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
	MageBlood->setColor(Color3B(149, 254, 26));
	MageBlood->setType(ProgressTimerType::BAR);
	MageBlood->setMidpoint(Vec2(0, 0));
	MageBlood->setBarChangeRate(Vec2(1, 0));
	MageBlood->setPercentage(100);
	MageBlood->setPosition3D(Vec3(MagePng->getPositionX() - 1, MagePng->getPositionY() - offset, 4));
	MageBlood->setScale(scale);
	addChild(MageBlood, 4);

	auto MageBloodClone = ProgressTimer::create(Sprite::createWithSpriteFrameName("UI-1136-640_36_clone.png"));
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
}

void BattleFieldUI::touchButtonInit()
{
}

void BattleFieldUI::shakeAvatar()
{
}

void BattleFieldUI::bloodDrop(Actor* heroActor)
{
}

void BattleFieldUI::heroDead(Actor* heroActor)
{
}

void BattleFieldUI::angryChange(Actor* heroActor)
{
}

void BattleFieldUI::timeInit()
{
}

void BattleFieldUI::showVictoryUI()
{
}
