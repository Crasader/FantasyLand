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

	_loadedResourceNum = 10;//=num(_particleResource)+num(_spriteFrameResource)
	_totalResourceNum = _loadedResourceNum;

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
	_loadedResourceNum = _loadedResourceNum - 1;
	_loadingBar->setPercent(100 * (_totalResourceNum - _loadedResourceNum) / _totalResourceNum);

	//all loaded,enter mainMenuScene
	if (_loadedResourceNum == -1)
	{
		unschedule(schedule_selector(LoadingScene::update));
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		return;
	}

	//load resource
	if (_totalResourceNum - _loadedResourceNum > 6)
		cachedTextureRes();
	else
		cachedParticleRes();
}

void LoadingScene::addBackground()
{
	auto background = Sprite::create("loadingscene/bg.jpg");
	background->setPosition(VisibleSize / 2);
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
	_loadingBar->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 5));
	_loadingBar->setScale(2);
	addChild(_loadingBar);
}

void LoadingScene::cachedParticleRes()
{
	ParticleManager::getInstance()->AddPlistData(_particleResource[_totalResourceNum - _loadedResourceNum][1]._string, _particleResource[_totalResourceNum - _loadedResourceNum][2]._string);
}

void LoadingScene::cachedTextureRes()
{
	if (_loadedResourceNum == 0)
		return;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_spriteFrameResource[_totalResourceNum - _loadedResourceNum - 6/*num(_particleResource)*/]._string);
}
