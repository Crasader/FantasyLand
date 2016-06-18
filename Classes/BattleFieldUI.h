#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Actor;
class BattleFieldUI :public Layer
{
public:
	CREATE_FUNC(BattleFieldUI);
	virtual bool init();

	void avatarInit();
	void bloodbarInit();
	void angrybarInit();
	void touchButtonInit();
	Repeat* shakeAvatar();
	void bloodDrop(Actor *heroActor);
	void heroDead(Actor *heroActor);
	void angryChange(Actor *heroActor);
	void timeInit();
	void showVictoryUI();
	void showGameOverUI();
	void setGreyShader(Sprite * s);
//杜：此处修改过，因为我要访问这些东西
	ProgressTimer* MageBlood;
	ProgressTimer* MageAngry;
	ProgressTimer* MageBloodClone;
	ProgressTimer* ArcherBlood;
	ProgressTimer* ArcherAngry;
	ProgressTimer* ArcherAngryClone;
	ProgressTimer* ArcherBloodClone;
	ProgressTimer* KnightBlood;
	ProgressTimer* KnightAngry;
	ProgressTimer* KnightAngryClone;
	ProgressTimer* KnightBloodClone;
	Sprite *MagePng;
	Sprite *MagePngFrame;
	Sprite *KnightPng;
	Sprite *KnightPngFrame;
	Sprite *ArcherPng;
	Sprite *ArcherPngFrame;


	Label *_tmlabel;
	unsigned int _tmSchedule;
	Sprite* KnightAngryFullSignal;
	Sprite* ArcherAngryFullSignal;
	ProgressTimer* MageAngryClone;
	Sprite* MageAngryFullSignal;

	unsigned time;

	void controlPng();
	Vec3 pngVelocity;
	Vec2 lastTouchPosition;
};
