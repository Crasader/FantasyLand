#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Actor;
class ChooseRoleScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

protected:
	void addBackground();
	void addHeros();
	void addBattleButton();
	bool isTouchedStart;

	//void addBag();
	//void addButton();
	//void addBk();
	//void initTouchDispatcher();
	//void rotate3Heroes(bool isRight);
	//void getWeaponTextureName();
	//void getArmourTextureName();
	//void getHelmetTextureName();
	//void switchItemtextureWhenRotate();
	//void switchTextWhenRotate();
	//void playAudioWhenRotate();


	//int sortorder[3] = { 1,2,3 }; //hero's tag
	//Vec3 rtt[3] = { {  -90, -60, 0 },{  -90, -70, 0 },{  -90, -60, 0 } };
	//Vec2 pos = { {  VisibleSize.width*0.14, visibleSize.height*0.35, -180 },{ x = visibleSize.width*0.34,y = visibleSize.height*0.25,z = -40 },{ x = visibleSize.width*0.5,y = visibleSize.height*0.35,z = -180 } };
	//Vec2 weapon_item_pos = { 832, 280 };
	//Vec2 armour_item_pos = { 916, 280 };
	//Vec2 helmet_item_pos = { 1000, 280 };
	//bool isMoving = false;
	//int direction = 0;
	//Rect heroSize = Rect(155, 120, 465, 420);
};
