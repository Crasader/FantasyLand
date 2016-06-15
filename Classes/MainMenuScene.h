#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainMenuScene:public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MainMenuScene);
	virtual bool init();

	void createLayer();
	void onExit(Event *event);
	void addLogo(Layer *layer);
	void getLightSprite();
	void addPointLight(Layer *layer);
	void addButton(Layer *layer);
	void addCloud(Layer *layer);
	void addBg(Layer *layer);


	void addBackground();
	void addButton();
	void addAboutLayer();
	void removeAboutLayer();
private:
	bool _isBloodLabelShowing;

	Size _logoSize;
	Sprite *_logo;
	Sprite *_lightSprite;
	PointLight *_pointLight;
	Vec2 _prePosition;

	ui::Button *_star;
	ui::Button *_start;
	ui::Button *_setting; 

	bool isTouchedStart;
	Layer *_aboutLayer;
};
