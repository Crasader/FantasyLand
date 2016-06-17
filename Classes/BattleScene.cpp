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

	isDebug = false;
	if (isDebug)
	{
		//add camera
		camera = Camera::createPerspective(60, VisibleSize.width / VisibleSize.height, 10, 4000);
		camera->setGlobalZOrder(10);
		camera->setPosition3D(Vec3(-500, 80, 0));
		camera->setCameraFlag(CameraFlag::USER1);
		addChild(camera);
		controlCamera();

		gameMaster = new GameMaster();
		//add background
		auto battlefield = Sprite3D::create("battleScene/changjing.c3b");
		battlefield->setCameraMask(2);
		battlefield->setPosition3D(Vec3(-2300, -1000, 0));
		battlefield->setRotation3D(Vec3(90, 0, 0));
		addChild(battlefield);

		scheduleUpdate();
		setCameraMask(2, true);
		return true;
	}

	//specialCamera
	scheduler = Director::getInstance()->getScheduler();
	cameraOffset = { 150, 0, 0 };
	cameraOffsetMin = { -300,  -400 };
	cameraOffsetMax = { 300,  400 };

	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);

	enableTouch();
	createBackground();
	initUILayer();
	gameMaster = new GameMaster();
	setCamera();
	//scheduler->schedule(gameController, this, 0, false, "gameController");

	MessageDispatchCenter::getInstance()->registerMessage(MessageType::BLOOD_MINUS, [](Actor * heroActor)
	{
		uiLayer->bloodDrop(heroActor);
	});
	MessageDispatchCenter::getInstance()->registerMessage(MessageType::ANGRY_CHANGE, [](Actor * heroActor)
	{
		uiLayer->angryChange(heroActor);
	});
	MessageDispatchCenter::getInstance()->registerMessage(MessageType::SPECIAL_PERSPECTIVE, [](Actor *heroActor)
	{
		
	});

	controlCamera();
	setCameraMask(2);
	scheduleUpdate();
	//gameController(0.1);
	return true;
}

void BattleScene::update(float dt)
{
	camera->setPosition3D(camera->getPosition3D() + cameraVelocity * 5);
	auto i = camera->getPosition3D();
	//camera->setPosition(camera->getPosition() + cameraVelocity);
	gameController(dt);
}

void BattleScene::moveCamera(float dt)
{
	//log("moveCamera");
	if (camera == nullptr)
		return;

	auto cameraPosition = getPosTable(camera);
	auto focusPoint = getFocusPointOfHeros();
	//if (specialCamera->isBrushValid()/*?*/)
	//{
	//	auto position = ccpLerp(cameraPosition, ccp(specialCamera->getPosition().x, (cameraOffset.y + focusPoint.y - VisibleSize.height * 3 / 4)*0.5), 5 * dt);
	//	camera->setPosition(position);
	//	camera->lookAt(Vec3(position.x, specialCamera->getPosition().y, 50.0), Vec3(0.0, 1.0, 0.0));
	//}
	/*else */if (HeroManager.size() > 0)
	{
		auto temp = ccpLerp(cameraPosition, ccp(focusPoint.x + cameraOffset.x, cameraOffset.y + focusPoint.y - VisibleSize.height * 3 / 4), 2 * dt);
		auto position = Vec3(temp.x, temp.y, VisibleSize.height / 2 - 100);
		camera->setPosition3D(position);
		camera->lookAt(Vec3(position.x, focusPoint.y, 50.0), Vec3(0.0, 0.0, 1.0));
		//log("\ncalf %f %f %f \ncalf %f %f 50.000000", position.x, position.y, position.z, focusPoint.x, focusPoint.y);
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
	auto spriteBg = Sprite3D::create("model/scene/changing.c3b");

	currentLayer->addChild(spriteBg);
	spriteBg->setScale(2.65);
	spriteBg->setPosition3D(Vec3(-2300, -1000, 0));
	spriteBg->setRotation3D(Vec3(90, 0, 0));
	spriteBg->setCameraMask(2);
	//No Water
}

void BattleScene::setCamera()
{
	camera = Camera::createPerspective(60.0, VisibleSize.width / VisibleSize.height, 10.0, 4000.0);
	camera->setGlobalZOrder(10);
	camera->setCameraFlag(CameraFlag::USER1);
	currentLayer->addChild(camera);

	for (auto it : HeroManager)
	{
		if (it->getPuff() != nullptr)
			it->getPuff()->setCameraMask(2);// sprite._puff:setCamera(camera)
	}

	camera->addChild(uiLayer);
}

void BattleScene::gameController(float dt)
{
	gameMaster->update(dt);
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
	uiLayer->setGlobalZOrder(3000);
}

void BattleScene::bloodMinus(Actor* heroActor)
{
	uiLayer->bloodDrop(heroActor);
}

void BattleScene::angryChange(Actor* heroActor)
{
	uiLayer->angryChange(heroActor);
}

void BattleScene::specialPerspective(Actor* heroActor)
{
	if (specialCamera->getName() == "on")
		return;

	specialCamera->setPosition(heroActor->getPosition());
	specialCamera->setName("on");
	currentLayer->setColor(Color3B(125, 125, 125));//deep grey

	auto restoreTimeScale = [this, heroActor]()
	{
		specialCamera->setName("off");
		currentLayer->setColor(Color3B(255, 255, 255));//default white
		Director::getInstance()->getScheduler()->setTimeScale(1.0);
		heroActor->getTarget()->setCascadeColorEnabled(true);//restore to the default state
	};

	//delayExecute(currentLayer, restoreTimeScale, heroActor);todo 
}

void BattleScene::enableTouch()
{
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
		//cameraOffset = pGetClampPoint(ccpSub(cameraOffset, delta), cameraOffsetMin, cameraOffsetMax);
	};
	touchEventListener->onTouchEnded = [this](Touch *touch, Event*)
	{
		auto  message = UIcontainsPoint(touch->getLocation());
		//if (message != MessageType::NullMessageType)
		//	MessageDispatchCenter->dispatchMessage(message, 1);
	};

	currentLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, currentLayer);
}

MessageType BattleScene::UIcontainsPoint(Vec2 position)
{
	MessageType message;

	auto rectKnight = uiLayer->KnightPngFrame->getBoundingBox();
	auto rectArcher = uiLayer->ArcherPngFrame->getBoundingBox();
	auto rectMage = uiLayer->MagePngFrame->getBoundingBox();

	if (rectKnight.containsPoint(position) && uiLayer->KnightAngry->getPercentage() == 100)
		//log("rectKnight")
		message = MessageType::SPECIAL_KNIGHT;
	else if (rectArcher.containsPoint(position) && uiLayer->ArcherAngry->getPercentage() == 100)
		//log("rectArcher")
		message = MessageType::SPECIAL_ARCHER;
	else if (rectMage.containsPoint(position) && uiLayer->MageAngry->getPercentage() == 100)
		//log("rectMage")
		message = MessageType::SPECIAL_MAGE;
	else
		return MessageType::NullMessageType;
	return message;
}

void BattleScene::controlCamera()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch* touch, Event*)
	{
		lastTouchPosition = touch->getLocation() / 5;
		return true;
	};
	touchListener->onTouchMoved = [this](Touch* touch, Event*)
	{
		auto touchPosition = touch->getLocation() / 5;
		camera->setRotation3D(Vec3(
			camera->getRotation3D().x - touchPosition.y + lastTouchPosition.y,
			camera->getRotation3D().y + touchPosition.x - lastTouchPosition.x,
			0));
		lastTouchPosition = touchPosition;
	};
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event*)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:++cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:--cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:--cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:++cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_PG_UP:--cameraVelocity.z; break;
		case EventKeyboard::KeyCode::KEY_PG_DOWN:++cameraVelocity.z; break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event*)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:--cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:++cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:++cameraVelocity.y; break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:--cameraVelocity.x; break;
		case EventKeyboard::KeyCode::KEY_PG_UP:++cameraVelocity.z; break;
		case EventKeyboard::KeyCode::KEY_PG_DOWN:--cameraVelocity.z; break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}