#pragma once
#include "cocos2d.h"

USING_NS_CC;

class BattleScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BattleScene);
	virtual bool init();

protected:

};
