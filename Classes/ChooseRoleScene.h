#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ChooseRoleScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

protected:

};
