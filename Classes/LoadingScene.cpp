#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "ParticleManager.h"
#include "GlobalVariables.h"

//local varibles
//local particleRes
//local spriteFrameRes

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	Layer::init();
	currentLayer = this;

	_num = 6 + 4;//num(particleRes)+num(spriteFrameRes)
	_totalResource = _num;
	size = Director::getInstance()->getWinSize();
	_pm = ParticleManager::getInstance();

	//add background
	addBackground();

	//add loadingText;
	addLoadingText();

	//add loadingIcon
	addLoadingIcon();

	//update
	schedule(schedule_selector(LoadingScene::update), 1);

	return true;
}

void LoadingScene::update(float dt)
{
	_num = _num - 1;

	//load resource
	if (_totalResource - _num > 6)
		cachedTextureRes();
	else
		cachedParticleRes();

	//replace scene
	if (_num == -1)
	{
		unschedule(schedule_selector(LoadingScene::update));
		auto i = Director::getInstance()->getScheduler()->isScheduled(schedule_selector(LoadingScene::update), this);
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	}
}

void LoadingScene::addBackground()
{
	auto background = Sprite::create("loadingscene/background.jpg");
	background->setPosition(size / 2);
	addChild(background);
}

void LoadingScene::addLoadingText()
{
	
}

void LoadingScene::addLoadingIcon()
{

}

void LoadingScene::cachedParticleRes()
{
	_pm->AddPlistData(particleRes[_totalResource - _num][1]._string, particleRes[_totalResource - _num][2]._string);
}

void LoadingScene::cachedTextureRes()
{
	if (_num == 0)
		return;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteFrameRes[_totalResource - _num - 6/*num(particleRes)*/]._string);
}
