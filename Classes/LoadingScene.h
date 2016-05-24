#pragma once
#include "cocos2d.h"
#include "ParticleManager.h"
#include "Slime.h"

USING_NS_CC;

class LoadingScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LoadingScene);
	virtual bool init();

	void addLoadingText(Layer *layer);
	void slimeAction(Layer *layer);
	void cachedParticleRes();
	void cachedTextureRes();

private:
	int _num;
	int _totalResource;
	Size size;
	
	String particleRes[6][2] = {
		{ "FX/iceTrail.plist","iceTrail" },
		{ "FX/magic.plist","magic" },
		{ "FX/pixi.plist","pixi" },
		{ "FX/puffRing.plist","puffRing" },
		{ "FX/puffRing2.plist","puffRing2" },
		{ "FX/walkingPuff.plist","walkpuff" },
	};

	String spriteFrameRes[4] = {
		"FX/FX.plist",
		"chooseRole/chooserole.plist",
		"battlefieldUI/battleFieldUI.plist",
		"mainmenuscene/mainmenuscene.plist",
	};
};
