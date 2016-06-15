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
	Layer::init();
	currentLayer = this;

	addBackground();
	addHeros();
	addBattleButton();

	return true;
}

void ChooseRoleScene::addBackground()
{
	auto background = Sprite::create("chooseRoleScene/cr_bk.jpg");
	background->setPosition(VisibleSize / 2);
	addChild(background);
}

void ChooseRoleScene::addHeros()
{
	auto archer = Archer::create();
	auto mage = Mage::create();
	auto knight = Knight::create();

	archer->setPosition(VisibleSize.width / 4 * 1, VisibleSize.height / 2);
	mage->setPosition(VisibleSize.width / 4 * 2, VisibleSize.height / 2);
	knight->setPosition(VisibleSize.width / 4 * 3, VisibleSize.height / 2);

	archer->setRotation3D(Vec3(-90, 0, 0));
	mage->setRotation3D(Vec3(-90, 0, 0));
	knight->setRotation3D(Vec3(-90, 0, 0));

	addChild(archer);
	addChild(mage);
	addChild(knight);
}

void ChooseRoleScene::addBattleButton()
{
	auto battleButton = ui::Button::create("chooseRoleScene/battleNormal.png", "chooseRoleScene/battleSelected.png");
	battleButton->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 5));

	isTouchedStart = false;
	battleButton->addClickEventListener([this](Ref*)
	{
		if (isTouchedStart)
			return;
		isTouchedStart = true;
		Director::getInstance()->replaceScene(BattleScene::createScene());
	});

	addChild(battleButton);
}
