#include "LoadingScene.h"

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
	_num = ;//need table
	_totalResource = _num;
	size = Director::getInstance()->getVisibleSize();
	_pm = ParticleManager::getInstance();

	auto layer = Layer::create();

	//add bg
	auto bg = Sprite::create("loadingscene/bg.jpg");
	bg->setPosition(size / 2);
	addChild(bg);

	//add loadingbar
	auto loadingbar = ui::LoadingBar::create("loadingscene/sliderProgress.png");
	loadingbar->setDirection(ui::LoadingBarTypeLeft);
	loadingbar->setPosition(size / 2);
	loadingbar->setScale(3, 2);
	loadingbar->setColor(Color3B(0, 0, 0));
	loadingbar->setOpacity(70);
	loadingbar->setPercent(0);
	auto loadingbarSize = loadingbar->getContentSize().width * 3;
	layer->addChild(loadingbar);

	//add label
	addLoadingText(layer);

	//add slime
	slimeAction(layer);

	//update
	auto update = [this, loadingbar](float dt) {
		_num = _num - 1;
		loadingbar->setPercent((_totalResource - _num) / _totalResource * 100);
		//loading text action
		auto loadingAction = JumpBy::create(dt, ccp(0, 0), 50, 1);
		auto loadingIndex = (_totalResource - _num) % (/*table.getn(self._loading)+1*/999);
		//self._loading[loadingIndex>1 and loadingIndex or 1]:runAction(loadingAction)

		//slime action
		//self._slime:runAction(cc.MoveTo:create(dt, cc.p(self._slimeOriginX + loadingbarSize*loadingbar:getPercent() / 100, self._slimeOriginY)))

		//load resource
		if (_totalResource - _num > 999/*table.getn(particleRes)*/)
			cachedTextureRes();
		else
			cachedParticleRes();

		//replace scene
		if (_num == -1)
		{
			unschedule("LoadingScene");
			Director::getInstance()->replaceScene(MainMenuScene::createScene(););
		}
	};
	schedule(update, 0.1, "LoadingScene");

	return true;
}

void LoadingScene::addLoadingText(Layer* layer)
{
	char loadingStr[] = "loading";
	Label loading[2];
	for (int i = 0, v = 0; i < 6; ++i, ++v)
	{
		Label::createWithTTF("", "chooseRole/actor_param.ttf", 55);

	}
}

void LoadingScene::slimeAction(Layer* layer)
{
	auto slime = Slime::create();
	slime->setAIEnabled(false);
	slime->setPosition(size.width*0.2, size.height*0.3);
	slime->setRotation3D(Vec3(-90, -90, 0));
	addChild(slime);

	float dur = 0.6;
	float bsc = 27;

	slime->runAction(RepeatForever::create(
		Spawn::create(
			Sequence::create(
				DelayTime::create(dur / 8),
				JumpBy::create(dur * 7 / 8, Vec2(0, 0), 30, 1)
				),
			Sequence::create(
				EaseSineOut::create(ScaleTo::create(dur / 8, bsc*1.4, bsc*1.4, bsc*0.75)),
				EaseSineOut::create(ScaleTo::create(dur / 8, bsc*0.85, bsc*0.85, bsc*1.3)),
				EaseSineOut::create(ScaleTo::create(dur / 8, bsc*1.2, bsc*1.2, bsc*0.9)),
				EaseSineOut::create(ScaleTo::create(dur / 8, bsc*0.95, bsc*0.95, bsc*1.1)),
				EaseSineOut::create(ScaleTo::create(dur * 4 / 8, bsc, bsc, bsc))
				)
			)
		));
}

void LoadingScene::cachedParticleRes()
{
	//_pm= AddPlistData(particleRes[self._totalResource - self._num][1], particleRes[self._totalResource - self._num][2])
}

void LoadingScene::cachedTextureRes()
{
	if(_num<0)
		return;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteFrameRes[_totalResource - _num/*-table.getn(particleRes)*/]);
}
