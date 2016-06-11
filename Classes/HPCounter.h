#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Actor;

class HPCounter :public Layer
{
public:
	CREATE_FUNC(HPCounter);
	virtual bool init();
	LabelTTF *showBloodLossNum(float dmage, Actor* racetype, bool atack);

private:
	bool _isBlooding;
	int _num;
	LabelTTF *_blood;
	int num;
	float tm;
	float pointZ;
	float targetScale;

	Vec3 getRandomXYZ();
	LabelTTF *getBlood(Actor *racetype);
	Spawn *getAction(float tm, float targetScale, float pointZ);
};
