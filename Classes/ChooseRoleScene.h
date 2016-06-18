#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Actor;
extern Size VisibleSize;
class ChooseRoleScene :public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(ChooseRoleScene);
	virtual bool init();

protected:
	bool isTouchedStart;
	Sprite* _bag;
	Sprite* _weaponItem;
	Sprite* _armourItem;
	Sprite* _helmetItem;
	bool isRotateAvaliable;
	bool isWeaponItemAvaliable;
	bool isArmourItemAvaliable;
	bool isHelmetItemAvaliable;
	Vec2 touchBeginPoint;
	int sortOrder[3] = { 1,2,3 }; //hero's tag
	Vec3 rtt[3];
	Vec3 pos[3];
	Vec2 weaponItemPosition = { 832-300, 280 };
	Vec2 armourItemPosition = { 916 - 300, 280 };
	Vec2 helmetItemPosition = { 1000 - 300, 280 };
	bool isMoving = false;
	int direction = 0;
	Rect heroSize = Rect(155, 120, 465, 420);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *bk;

	Sprite* addBag();
	void addButton();
	void addHeros();
	void addBackground();
	void initTouchDispatcher();

	void rotate3Heroes(bool isRight);
	void switchItemtextureWhenRotate();
	void switchTextWhenRotate();
	void playAudioWhenRotate();

	std::string getWeaponTextureName();
	std::string getArmourTextureName();
	std::string getHelmetTextureName();

};
