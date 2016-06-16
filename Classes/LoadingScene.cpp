#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "ParticleManager.h"
#include "GlobalVariables.h"

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

	_num = 10;//=num(particleRes)+num(spriteFrameRes)
	_totalResource = _num;
	size = Director::getInstance()->getWinSize();
	_pm = ParticleManager::getInstance();

	//add background
	addBackground();

	//add loadingText;
	addLoadingText();

	//add loadingIcon
	addLoadingIcon();

	//add loadingBar
	addLoadingBar();

	//update
	schedule(schedule_selector(LoadingScene::update), 0.1);

	return true;
}

void LoadingScene::update(float dt)
{
	_num = _num - 1;
	_loadingBar->setPercent(100 * (_totalResource - _num) / _totalResource);

	//all loaded,enter mainMenuScene
	if (_num == -1)
	{
		unschedule(schedule_selector(LoadingScene::update));
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		return;
	}

	//load resource
	if (_totalResource - _num > 6)
		cachedTextureRes();
	else
		cachedParticleRes();
}

void LoadingScene::addBackground()
{
	auto background = Sprite::create("loadingscene/bg.jpg");
	background->setPosition(size / 2);
	addChild(background);
}

void LoadingScene::addLoadingText()
{

}

void LoadingScene::addLoadingIcon()
{

}

void LoadingScene::addLoadingBar()
{
	_loadingBar = ui::LoadingBar::create("loadingscene/sliderProgress.png");
	_loadingBar->setDirection(ui::LoadingBarTypeLeft);
	_loadingBar->setPosition(Vec2(size.width / 2, size.height / 5));
	_loadingBar->setScale(2);
	addChild(_loadingBar);
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
