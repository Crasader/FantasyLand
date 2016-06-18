#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ParticleManager;
class Slime;
class LoadingScene :public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(LoadingScene);
	virtual bool init();
	void update(float dt) override;

private:
	int _loadedResourceNum;
	int _totalResourceNum;
	ui::LoadingBar *_loadingBar;

	String _particleResource[6][2] = {
		{ "FX/iceTrail.plist","iceTrail" },
		{ "FX/magic.plist","magic" },
		{ "FX/pixi.plist","pixi" },
		{ "FX/puffRing.plist","puffRing" },
		{ "FX/puffRing2.plist","puffRing2" },
		{ "FX/walkingPuff.plist","walkpuff" },
	};
	String _spriteFrameResource[4] = {
		"FX/FX.plist",
		"chooseRole/chooserole.plist",
		"battlefieldUI/battleFieldUI.plist",
		"mainmenuscene/mainmenuscene.plist",
	};

	void addBackground();
	void addLoadingText();
	void addLoadingIcon();
	void addLoadingBar();

	void cachedParticleRes();
	void cachedTextureRes();
};
