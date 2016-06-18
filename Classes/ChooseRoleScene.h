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
	Sprite* _bag;
	Sprite* _weaponItem;
	Sprite* _armourItem;
	Sprite* _helmetItem;
	Sprite *_background;

	bool _isMoving = false;
	bool _isSceneReplaced;
	bool _isRotateAvaliable;
	bool _isWeaponItemAvaliable;
	bool _isArmourItemAvaliable;
	bool _isHelmetItemAvaliable;
	int _sortOrder[3] = { 1,2,3 }; //hero's tag

	Vec2 _touchBeginPoint;
	Vec3 _rotateType[3] = { Vec3(-90, -60, 0),Vec3(-90, -70, 0),Vec3(-90, -60, 0) };
	Vec3 _heroesPosition[3] = { Vec3(VisibleSize.width*0.14, VisibleSize.height*0.35, -180), 
		Vec3(VisibleSize.width*0.34, VisibleSize.height*0.25, -4), 
		Vec3(VisibleSize.width*0.5, VisibleSize.height*0.35, -180) };
	Vec2 _weaponItemPosition = { 832 - 300, 280 };
	Vec2 _armourItemPosition = { 916 - 300, 280 };
	Vec2 _helmetItemPosition = { 1000 - 300, 280 };
	Rect _heroesSize = Rect(155, 120, 465, 420);


	void addBag();
	void addButtons();
	void addHeroes();
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
