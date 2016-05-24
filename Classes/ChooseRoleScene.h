#pragma once
#include "cocos2d.h"
#include "Actor.h"
#include "Knight.h"
#include "Archer.h"
#include "Mage.h"

USING_NS_CC;

class ChooseRoleScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

	void addBag();
	void addButton();
	void addHeros();
	void addBk();
	void createLayer();
	void initTouchDispatcher();
	void rotate3Heroes(bool isRight);
	void getWeaponTextureName();
	void getArmourTextureName();
	void getHelmetTextureName();
	void switchItemtextureWhenRotate();
	void switchTextWhenRotate();
	void playAudioWhenRotate();
protected:

};
