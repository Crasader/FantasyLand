#pragma once
#include "cocos2d.h"
#include "Helper.h"
#include "Actor.h"

USING_NS_CC;

class BattleScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BattleScene);
	virtual bool init();

	void moveCamera(float dt);
	void updateParticlePos();
	void createBackground();
	void setCamera();
	void gameController(float dt);
	void initUILayer();
	void bloodMinus(Actor *heroActor);
	void angryChange(Actor *heroActor/*angry @lua*/);
	void specialPerspective(Actor *heroActor/*param @lua*/);
	void enableTouch();
	void UIcontainsPoint(Vec2 position/*position @lua*/);

private:

};
