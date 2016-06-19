#include "BattleScene.h"
#include "GlobalVariables.h"
#include "BattleFieldUI.h"
#include "Actor.h"
#include "MessageDispatchCenter.h"

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	layer->setCascadeColorEnabled(true);
	scene->addChild(layer);
	return scene;
}

bool BattleScene::init()
{
	Layer::init();
	currentLayer = this;
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);

	setCamera();
	controlCamera();
	setCameraMask(2);
	createBackground();
	enableTouch();
	initUILayer();
	GameMaster::getInstance();

	MessageDispatchCenter::getInstance()->registerMessage(MessageType::BLOOD_MINUS, [](Actor * heroActor)
	{
		uiLayer->bloodDrop(heroActor);
	});
	MessageDispatchCenter::getInstance()->registerMessage(MessageType::ANGRY_CHANGE, [](Actor * heroActor)
	{
		uiLayer->angryChange(heroActor);
	});

	scheduleUpdate();
	return true;
}

void BattleScene::update(float dt)
{
	camera->setPosition3D(camera->getPosition3D() + _cameraVelocity * 5);
	if (GameMaster::getPlayer()->getStateType() == EnumStateType::WALKING)
		auto i = 1;
	gameController(dt);
}

void BattleScene::moveCamera(float dt)
{
	//log("moveCamera");
	if (camera == nullptr)
		return;
	auto cameraPosition = camera->getPosition();
	Vec2 focusPoint;
	if (GameMaster::getPlayer() != nullptr) {
	    focusPoint = GameMaster::getPlayer()->getPosition();

	if (HeroManager.size() > 0)
	{
		auto temp = ccpLerp(cameraPosition, ccp(focusPoint.x + _cameraOffset.x, focusPoint.y + _cameraOffset.y), 2 * dt);
		auto position = Vec3(temp.x, temp.y, _cameraOffset.z);
		camera->setPosition3D(position);
		camera->lookAt(Vec3(position.x, focusPoint.y, 50.0), Vec3(0.0, 0.0, 1.0));
	}

}

void BattleScene::updateParticlePos()
{
	//log("updateParticlePos");
	for (auto it : HeroManager)
	{
		if (it->getEffectNode() != nullptr)
			it->getEffectNode()->setPosition(getPosTable(it));
	}
}

void BattleScene::createBackground()
{
	auto background3D = Sprite3D::create("model/scene/changing.c3b");
	background3D->setScale(2.65);
	background3D->setPosition3D(Vec3(-2300, -1000, 0));
	background3D->setRotation3D(Vec3(90, 0, 0));
	background3D->setCameraMask(2);
	addChild(background3D);
}

void BattleScene::setCamera()
{
	camera = Camera::createPerspective(60.0, VisibleSize.width / VisibleSize.height, 10.0, 4000.0);
	camera->setGlobalZOrder(10);
	camera->setCameraFlag(CameraFlag::USER1);
	addChild(camera);
}

void BattleScene::gameController(float dt)
{
	GameMaster::getInstance()->update(dt);
	collisionDetect(dt);
	solveAttacks(dt);
	moveCamera(dt);
}

void BattleScene::initUILayer()
{
	uiLayer = BattleFieldUI::create();
	uiLayer->setPositionZ(-Director::getInstance()->getZEye() / 4);
	uiLayer->setScale(0.25);
	uiLayer->ignoreAnchorPointForPosition(false);
	uiLayer->setGlobalZOrder(10);
	camera->addChild(uiLayer);
}

void BattleScene::bloodMinus(Actor* heroActor)
{
	uiLayer->bloodDrop(heroActor);
}

void BattleScene::angryChange(Actor* heroActor)
{
	uiLayer->angryChange(heroActor);
}

void BattleScene::enableTouch()
{//enable the touch
	auto touchEventListener = EventListenerTouchOneByOne::create();

	touchEventListener->onTouchBegan = [this](Touch *touch, Event*)
	{
		//log("onTouchBegin: %0.2f, %0.2f", touch->getLocation());
		return true;
	};
	touchEventListener->onTouchMoved = [this](Touch *touch, Event*)
	{
		if (UIcontainsPoint(touch->getLocation()) == MessageType::NullMessageType)
			auto delta = touch->getDelta();
	};
	touchEventListener->onTouchEnded = [this](Touch *touch, Event*)
	{
		auto getHeroByName = [](std::string name)
		{
			for (auto it : HeroManager)
				if (it->getname() == name)
					return it;
			return static_cast<Actor*>(nullptr);
		};

		auto  message = UIcontainsPoint(touch->getLocation());
		Actor *hero;
		if (message == SPECIAL_KNIGHT)
			hero = getHeroByName("Knight");
		else if (message == SPECIAL_ARCHER)
			hero = getHeroByName("Archer");
		else if (message == SPECIAL_MAGE)
			hero = getHeroByName("Mage");
		if (message != MessageType::NullMessageType)
			MessageDispatchCenter::getInstance()->dispatchMessage(message, hero);
		else
		{
			//get angleOf3DWorld and positionOf3DWorld
			auto touchPosition = touch->getLocation();
			auto angleOfCamera = atan(-_cameraOffset.y / _cameraOffset.z);
			auto angleOfScreen = atan((touchPosition.y - VisibleSize.height / 2) / (sqrt(3) / 2 * VisibleSize.height));
			auto angleOf3DWorld = angleOfCamera + angleOfScreen;
			auto positionYOf3DWorld = _cameraOffset.z*tan(angleOf3DWorld) + camera->getPositionY();
			auto positionOf3DWorld = Vec2(camera->getPositionX() + touchPosition.x - VisibleSize.width / 2,
				positionYOf3DWorld + 100);
			//enter player control
			GameMaster::getInstance()->playerControl(positionOf3DWorld, angleOf3DWorld);
		}
	};

	currentLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, currentLayer);
}

MessageType BattleScene::UIcontainsPoint(Vec2 position)
{//check if the UILayer contains the touchPoint
	MessageType message;

	auto rectKnight = uiLayer->KnightPngFrame->getBoundingBox();
	auto rectArcher = uiLayer->ArcherPngFrame->getBoundingBox();
	auto rectMage = uiLayer->MagePngFrame->getBoundingBox();

	if (rectKnight.containsPoint(position) && uiLayer->KnightAngry->getPercentage() == 100)
		message = MessageType::SPECIAL_KNIGHT;
	else if (rectArcher.containsPoint(position) && uiLayer->ArcherAngry->getPercentage() == 100)
		message = MessageType::SPECIAL_ARCHER;
	else if (rectMage.containsPoint(position) && uiLayer->MageAngry->getPercentage() == 100)
		message = MessageType::SPECIAL_MAGE;
	else
		return MessageType::NullMessageType;
	return message;
}

void BattleScene::controlCamera()
{//control the camera by arrow keys
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event*)
	{
		_lastTouchPosition = touch->getLocation() / 5;
		return true;
	};
	touchListener->onTouchMoved = [this](Touch* touch, Event*)
	{
		auto touchPosition = touch->getLocation() / 5;
		camera->setRotation3D(Vec3(
			camera->getRotation3D().x - touchPosition.y + _lastTouchPosition.y,
			camera->getRotation3D().y + touchPosition.x - _lastTouchPosition.x,
			0));
		_lastTouchPosition = touchPosition;
	};
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event*)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:++_cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:--_cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:--_cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:++_cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_PG_UP:--_cameraVelocity.z; break;
		case EventKeyboard::KeyCode::KEY_PG_DOWN:++_cameraVelocity.z; break;
		case EventKeyboard::KeyCode::KEY_K:MessageDispatchCenter::getInstance()->dispatchMessage(MessageType::SPECIAL_KNIGHT, HeroManager[0]); break;
		case EventKeyboard::KeyCode::KEY_M:MessageDispatchCenter::getInstance()->dispatchMessage(MessageType::SPECIAL_MAGE, HeroManager[1]); break;
		case EventKeyboard::KeyCode::KEY_A:MessageDispatchCenter::getInstance()->dispatchMessage(MessageType::SPECIAL_ARCHER, HeroManager[2]); break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event*)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:--_cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:++_cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:++_cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:--_cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_PG_UP:++_cameraVelocity.z; break;
		case EventKeyboard::KeyCode::KEY_PG_DOWN:--_cameraVelocity.z; break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}
