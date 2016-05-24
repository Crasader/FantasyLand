#pragma once
#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Actor.h"

USING_NS_CC;

class BattleFieldUI :public Layer
{
public:
	CREATE_FUNC(BattleFieldUI);
	virtual bool init();

	void avatarInit();
	void bloodbarInit();
	void angrybarInit();
	void touchButtonInit();
	void shakeAvatar();
	void bloodDrop(Actor *heroActor);
	void heroDead(Actor *heroActor);
	void angryChange(Actor *heroActor);
	void timeInit();
	void showVictoryUI();

protected:

};
