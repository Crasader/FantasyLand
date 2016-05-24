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

	return true;
}

void LoadingScene::addLoadingText(Layer* layer)
{

}

void LoadingScene::slimeAction(Layer* layer)
{

}

void LoadingScene::cachedParticleRes()
{

}

void LoadingScene::cachedTextureRes()
{

}
