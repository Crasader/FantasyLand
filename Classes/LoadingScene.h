#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LoadingScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LoadingScene);
	virtual bool init();

protected:

};
