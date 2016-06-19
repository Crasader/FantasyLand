#include "MainMenuScene.h"
#include "GlobalVariables.h"
#include "audio/win32/AudioEngine-win32.h"
#include "BattleScene.h"
#include <ui/CocosGUI.h>
#include "ChooseRoleScene.h"

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	Layer::init();
	currentLayer = this;

	addBackground();
	addButton();

	return true;
}

void MainMenuScene::addBackground()
{
	auto bachground = Sprite::create("mainMenuScene/bg.jpg");
	bachground->setPosition(VisibleSize / 2);
	addChild(bachground);

	auto logo = Sprite::create("mainMenuScene/logo.png");
	logo->setPosition(VisibleSize.width / 2, VisibleSize.height * 2 / 3);
	logo->setScale(0.75);
	addChild(logo);
}

void MainMenuScene::addButton()
{
	auto startButton = ui::Button::create("mainMenuScene/start_normal.png", "mainMenuScene/start.png");
	auto starButton = ui::Button::create("mainMenuScene/starNormal.png", "mainMenuScene/starSelected.png");
	auto settingButton = ui::Button::create("mainMenuScene/settingNormal.png", "mainMenuScene/settingSelected.png");
	auto exitButton = ui::Button::create("mainMenuScene/exitNormal.png", "mainMenuScene/exitSelected.png");

	startButton->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 5));
	starButton->setPosition(Vec2(VisibleSize.width - 150, VisibleSize.height - 50));
	settingButton->setPosition(Vec2(VisibleSize.width - 100, VisibleSize.height - 50));
	exitButton->setPosition(Vec2(VisibleSize.width - 50, VisibleSize.height - 50));

	_isSceneReplaced = false;
	startButton->addTouchEventListener([startButton,this](Ref*, ui::Widget::TouchEventType)
	{
		if (_isSceneReplaced)
			return;
		_isSceneReplaced = true;
		Director::getInstance()->replaceScene(ChooseRoleScene::createScene());
	});
	starButton->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType)
	{
		addAboutLayer();
	});
	settingButton->addTouchEventListener([](Ref*, ui::Widget::TouchEventType)
	{

	});
	exitButton->addTouchEventListener([](Ref*, ui::Widget::TouchEventType)
	{
		Director::getInstance()->end();
	});

	addChild(startButton);
	//addChild(starButton);
	//addChild(settingButton);
	addChild(exitButton);
}

void MainMenuScene::addAboutLayer()
{
	setColor(Color3B::GRAY);
	_aboutLayer = Layer::create();
	_aboutLayer->setColor(Color3B::GRAY);
	addChild(_aboutLayer);
}

void MainMenuScene::removeAboutLayer()
{
	setColor(Color3B::WHITE);

	removeChild(_aboutLayer);
}
