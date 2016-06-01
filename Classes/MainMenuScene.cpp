#include "MainMenuScene.h"

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
	size = Director::getInstance()->getVisibleSize();
	_isBloodLabelShowing = false;
	//todo ccexp.AudioEngine:stopAll()
	return true;
}

void MainMenuScene::createLayer()
{
	auto mainLayer = Layer::create();
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::AUTO);
	//add bg
	addBg(mainLayer);

	//add cloud
	addCloud(mainLayer);

	//add logo
	addLogo(mainLayer);

	//add pointlight
	addPointLight(mainLayer);

	//add button
	addButton(mainLayer);

	//when replease scene unschedule schedule

}

void MainMenuScene::addLogo(Layer* layer)
{
	//add logo
	auto logo = Sprite::create("mainmenuscene/logo.png");
	_logoSize = logo->getContentSize();
	logo->setPosition(size.width*0.53, size.height*0.55);
	logo->setScale(0.1);
	_logo = logo;
	layer->addChild(logo, 4);

	auto action = EaseElasticOut::create(ScaleTo::create(2, 1.1));

	//logo shake
	auto time = 0;
	//logo animition
	auto logoShake = [&time, logo]()
	{
		//rand_n = range * math.sin(math.rad(time*speed+offset))
		auto rand_x = 0.1*sin(DEGREES_TO_RADIANS(time*0.5 + 4356));
		auto rand_y = 0.1*sin(DEGREES_TO_RADIANS(time*0.37 + 5436));
		auto rand_z = 0.1*sin(DEGREES_TO_RADIANS(time*0.2 + 54325));
		logo->setRotation3D(Vec3(rand_x, rand_y, rand_z));//todo
		++time;
	};
	//auto logoSchedule = Director::getInstance()->getScheduler()->scheduleScriptFunc(, 0, false);
}

void MainMenuScene::getLightSprite()
{
	_lightSprite = Sprite::createWithSpriteFrameName("light.png");
	//_lightSprite->setBlendFunc(gl); todo
	_lightSprite->setScale(1.2);

	_lightSprite->setPosition3D(Vec3(size.width*0.5, size.height*0.5, 0));
	auto light_size = _lightSprite->getContentSize();
	auto rotate_top = RotateBy::create(0.05, 50);
	auto rotate_bottom = RotateBy::create(0.05, -50);
	auto origin_degree = 20;
	auto sprite_scale = 0;
	auto opacity = 100;
	auto scale_action = ScaleTo::create(0.07, 0.7);

	auto swing_l1 = Sprite::createWithSpriteFrameName("swing_l1.png");
	swing_l1->setScale(sprite_scale);;
	swing_l1->setAnchorPoint(ccp(1, 0));
	swing_l1->setPosition(light_size.width / 2, light_size.height / 2);
	swing_l1->setRotation(-origin_degree);
	swing_l1->setOpacity(opacity);
	//swing_l1->setBlendFunc(gl.ONE, gl.ONE); todo
	_lightSprite->addChild(swing_l1, 5);

	auto swing_l2 = Sprite::createWithSpriteFrameName("swing_l2.png");
	swing_l2->setAnchorPoint(ccp(1, 1));
	swing_l2->setScale(sprite_scale);
	swing_l2->setPosition(light_size.width / 2, light_size.height / 2);
	swing_l2->setRotation(origin_degree);
	swing_l2->setOpacity(opacity);
	_lightSprite->addChild(swing_l2, 5);

	auto swing_r1 = Sprite::createWithSpriteFrameName("swing_r1.png");
	swing_r1->setAnchorPoint(ccp(0, 0));
	swing_r1->setScale(sprite_scale);
	swing_r1->setPosition(light_size.width / 2, light_size.height / 2);
	swing_r1->setRotation(origin_degree);
	swing_r1->setOpacity(opacity);
	//swing_r1->setBlendFunc(gl.ONE, gl.ONE); todo
	_lightSprite->addChild(swing_r1, 5);

	auto swing_r2 = Sprite::createWithSpriteFrameName("swing_r2.png");
	swing_r2->setAnchorPoint(ccp(0, 1));
	swing_r2->setScale(sprite_scale);
	swing_r2->setPosition(light_size.width / 2, light_size.height / 2);
	swing_r2->setRotation(-origin_degree);
	swing_r2->setOpacity(opacity);
	_lightSprite->addChild(swing_r2, 5);

	//runaction
	auto sequence_l1 = Sequence::create(rotate_top, rotate_top->reverse());
	auto sequence_r1 = Sequence::create(rotate_top->reverse()->clone(), rotate_top->clone());
	auto sequence_l2 = Sequence::create(rotate_bottom, rotate_bottom->reverse());
	auto sequence_r2 = Sequence::create(rotate_bottom->reverse()->clone(), rotate_bottom->clone());
	swing_l1->runAction(RepeatForever::create(Spawn::create(sequence_l1, scale_action)));
	swing_r1->runAction(RepeatForever::create(Spawn::create(sequence_r1, scale_action)));
	swing_l2->runAction(RepeatForever::create(Spawn::create(sequence_l2, scale_action)));
	swing_r2->runAction(RepeatForever::create(Spawn::create(sequence_r2, scale_action)));
}

void MainMenuScene::addPointLight(Layer* layer)
{
	//add pointlight
	_pointLight = PointLight::create(Vec3(0, 0, -100), Color3B(255, 255, 255), 10000);
	_pointLight->setCameraMask(1);
	_pointLight->setEnabled(true);

	//add lightsprite
	getLightSprite();
	_lightSprite->addChild(_pointLight);
	addChild(_pointLight, 10);
	_lightSprite->setPositionZ(100);

	//effectNormalMap
//	auto effectNormalMapped = EffectNormalMapped:create("mainmenuscene/logo_normal.png");
//	effectNormalMapped:setPointLight(_pointLight)
//	effectNormalMapped : setKBump(50)
//	_logo : setEffect(effectNormalMapped)

	//action
	auto getBezierAction = [this]()
	{
		ccBezierConfig bezierConfig1;
		bezierConfig1.controlPoint_1 = ccp(size.width*0.9, size.height*0.4);
		bezierConfig1.controlPoint_2 = ccp(size.width*0.9, size.height*0.8);
		bezierConfig1.endPosition = ccp(size.width*0.5, size.height*0.8);
		ccBezierConfig bezierConfig2;
		bezierConfig2.controlPoint_1 = ccp(size.width*0.1, size.height*0.8);
		bezierConfig2.controlPoint_2 = ccp(size.width*0.1, size.height*0.4);
		bezierConfig2.endPosition = ccp(size.width*0.5, size.height*0.4);

		auto bezier1 = BezierTo::create(5, bezierConfig1);
		auto bezier2 = BezierTo::create(5, bezierConfig2);
		auto bezier = Sequence::create(bezier1, bezier2);//todo 优化b1,b2为栈变量

		return bezier;
	};
	_lightSprite->runAction(Sequence::create(getBezierAction()));

	//touch eventlistener
	auto onTouchBegin = [this](Touch touch, Event *event)
	{
		_lightSprite->stopAllActions();

		auto location = touch.getLocation();
		_prePosition = location;

		auto movePoint = [this](float dt)
		{
			auto lightSpritePos = getPosTable(_lightSprite);
			auto point = ccpLerp(lightSpritePos, _prePosition, dt * 2);
			_lightSprite->setPosition(point);
			auto z = sin(rand_0_1()*M_PI) * 100 + 100;
			//_lightSprite:setPositionZ(z)
		};
		//auto _scheduleMove = Director::getInstance()->getScheduler()->scheduleScriptFunc(movePoint,0,false);

		return true;
	};

	auto onTouchMoved = [this](Touch touch, Event *event)
	{
		//again set prePosition
		auto location = touch.getLocation();
		_prePosition = location;

		auto _angle = ccpToAngle(ccpSub(location, getPosTable(_lightSprite)));
	};
	auto onTouchEnded = [this, getBezierAction](Touch touch, Event *event)
	{
		//unschedule and stop action
		//Director::getInstance()->getScheduler()->unscheduleScriptEntry();
		//_lightSprite:setPositionZ(100)
		_lightSprite->runAction(RepeatForever::create(getBezierAction()));
	};

	//add event listener
	auto touchEventListener = EventListenerTouchOneByOne::create();
	touchEventListener->onTouchBegan = onTouchBegin;
	touchEventListener->onTouchMoved = onTouchMoved;
	touchEventListener->onTouchEnded = onTouchEnded;
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, layer);
}

void MainMenuScene::addButton(Layer* layer)
{
	bool isTouchButton = false;
	auto button_callback = [this, &isTouchButton]()
	{
		if (!isTouchButton)
		{
			isTouchButton = true;
			/*if eventType == ccui.TouchEventType.began then
				ccexp.AudioEngine:play2d(BGM_RES.MAINMENUSTART, false, 1)
				ccexp.AudioEngine : stop(AUDIO_ID.MAINMENUBGM)
				Director : getInstance() : replaceScene(require("ChooseRoleScene").create())
				end*/
		}
	};

	auto button = ui::Button::create("start.png", "", "", ui::TextureResType::PLIST);
	button->setPosition(Vec2(size.width*0.5, size.height*0.15));
	button->addTouchEventListener(button_callback);
	layer->addChild(button, 4);

	/*auto effectNormalMapped = EffectNormalMapped:create("mainmenuscene/start_normal.png")
		effectNormalMapped : setPointLight(_pointLight)
		effectNormalMapped : setKBump(100)*/

		//auto effectSprite = EffectSprite:create("mainmenuscene/start.png")
		//	effectSprite : setPosition(size.width*0.5, size.height*0.15)
		//	layer : addChild(effectSprite, 5)
		//	effectSprite : setEffect(effectNormalMapped)
}

void MainMenuScene::addCloud(Layer* layer)
{
	//cloud
	auto cloud0 = Sprite::createWithSpriteFrameName("cloud1.png");
	auto cloud1 = Sprite::createWithSpriteFrameName("cloud1.png");
	auto cloud3 = Sprite::createWithSpriteFrameName("cloud2.png");

	//setScale
	auto scale = 2;
	cloud0->setScale(scale);
	cloud1->setScale(scale);
	cloud3->setScale(scale);

	//setPosition
	cloud0->setPosition(size.width*1.1, size.height*0.9);
	cloud1->setPosition(size.width*0.38, size.height*0.6);
	cloud3->setPosition(size.width*0.95, size.height*0.5);

	//add to layer
	layer->addChild(cloud0, 2);
	layer->addChild(cloud1, 2);
	layer->addChild(cloud3, 2);
	auto clouds = { cloud0,cloud1,cloud3 };

	////move cloud
	//auto cloud_move = []()
	//{
	//	//set cloud move speed
	//	auto offset = { -0.5,-1.0,-1.2 };
	//	for (int i; i < 3;++i)
	//	{
	//		auto point = v:getPositionX() + offset[i];
	//	if (point < -v:getContentSize().width*scale / 2)
	//		point = size.width + v : getContentSize().width*scale / 2;
	//	}
	//v: setPositionX(point);
	//};
	//auto scheduleCloudMove = Director::getInstance()->getScheduler()->scheduleScriptFunc(cloud_move, 1 / 60, false);
}

void MainMenuScene::addBg(Layer* layer)
{
	//background
	auto bg_back = Sprite::create("mainmenuscene/bg.jpg");
	bg_back->setPosition(size / 2);
	layer->addChild(bg_back, 1);
}
