#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Actor;
class BattleFieldUI :public Layer
{
public:
	CREATE_FUNC(BattleFieldUI);
	virtual bool init();

	void bloodDrop(Actor *heroActor);
	void heroDead(Actor *heroActor);
	void angryChange(Actor *heroActor);
	void showVictoryUI();
	void showGameOverUI();

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
	Sprite *PlayerLabel;

	Label *_tmlabel;
	unsigned int _tmSchedule;
	Sprite* KnightAngryFullSignal;
	Sprite* ArcherAngryFullSignal;
	ProgressTimer* MageAngryClone;
	Sprite* MageAngryFullSignal;

	unsigned time;

	Vec3 pngVelocity;
	Vec2 lastTouchPosition;
private:
	void timeInit();
	void avatarInit();
	void bloodbarInit();
	void angrybarInit();
	void touchButtonInit();
	void setGreyShader(Sprite *avatar);
	Repeat* shakeAvatar();
};
