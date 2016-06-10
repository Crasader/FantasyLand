#include "BattleScene.h"
#include "Manager.h"
#include "MessageDispatchCenter.h"

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}

bool BattleScene::init()
{
	Layer::init();

	return true;
}

void BattleScene::moveCamera(float dt)
{

}

void BattleScene::updateParticlePos()
{
}

void BattleScene::createBackground()
{
}

void BattleScene::setCamera()
{
}

void BattleScene::gameController(float dt)
{
}

void BattleScene::initUILayer()
{
}

void BattleScene::bloodMinus(Actor* heroActor)
{
}

void BattleScene::angryChange(Actor* heroActor)
{
}

void BattleScene::specialPerspective(Actor* heroActor)
{
}

void BattleScene::enableTouch()
{
}

void BattleScene::UIcontainsPoint(Vec2 position)
{
}
