#pragma once
#include "cocos2d.h"
#include "Actor.h"

USING_NS_CC;

class ChooseRoleScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

	Sprite *addBag();
	void addButton();
	void addHeros();
	void addBk();
	Layer *createLayer();
	void initTouchDispatcher();
	void rotate3Heroes(bool isRight);
	void getWeaponTextureName();
	void getArmourTextureName();
	void getHelmetTextureName();
	void switchItemtextureWhenRotate();
	void switchTextWhenRotate();
	void playAudioWhenRotate();
protected:
	Sprite *_bag;
	Vec2 weapon_item_pos = Vec2(832, 280);
	Vec2 armour_item_pos = Vec2(916, 280);
	Vec2 helmet_item_pos = Vec2(1000, 280);
	Sprite *_weaponItem;
	Sprite *_armourItem;
	Sprite *_helmetItem;
	Layer *layer;
	unsigned int _schedule_rotate;

	int sortorder[3] = { 1,2,3 };
	Vec3 rtt[3] = { Vec3(-90,-60,0),Vec3(-90,-60,0) ,Vec3(-90,-60,0) };
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec3 pos = { visibleSize.width*0.14, visibleSize.height*0.35, -180 };
	bool isMoving = false;
	int direction = 0;
	Rect heroSize = { 155, 120, 465, 420 };
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
};
