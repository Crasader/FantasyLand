#pragma once
#include "cocos2d.h"

USING_NS_CC;

class HPCounter:public Layer
{
public:
	CREATE_FUNC(HPCounter);
	virtual bool init();
	void showBloodLossNum(float dmage,/*EnumRaceType racetype$need gVar*,*/bool atack
		/*dmage, racetype, atack @lua*/);

protected:
};
