#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MainMenuScene);
	virtual bool init();

protected:

};
