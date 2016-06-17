#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Actor;
extern Size VisibleSize;
class ChooseRoleScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

protected:
	bool isTouchedStart;
	Sprite* _bag;
	Sprite* _weaponItem;
	Sprite* _armourItem;
	Sprite* _helmetItem;
	bool isRotateavaliable;
	bool isWeaponItemavaliable;
	bool isArmourItemavaliable;
	bool isHelmetItemavaliable;
	Vec2 touchbeginPt;
	Sprite* addBag();
	void addButton();
	void addHeros();
	void addBk();
	void createLayer();
	void initTouchDispatcher();
	void rotate3Heroes(bool isRight);
	std::string getWeaponTextureName();
	std::string getArmourTextureName();
	std::string getHelmetTextureName();
	void switchItemtextureWhenRotate();
	void switchTextWhenRotate();
	void playAudioWhenRotate();


	int sortorder[3] = { 1,2,3 }; //hero's tag
	Vec3 rtt[3];
	Vec3 pos[3];
	Vec2 weapon_item_pos = { 832, 280 };
	Vec2 armour_item_pos = { 916, 280 };
	Vec2 helmet_item_pos = { 1000, 280 };
	bool isMoving = false;
	int direction = 0;
	Rect heroSize = Rect(155, 120, 465, 420);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
};
