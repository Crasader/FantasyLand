#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainMenuScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MainMenuScene);
	virtual bool init();

private:
	ui::Button *_star;
	ui::Button *_start;
	ui::Button *_setting;

	bool isTouchedStart;
	Layer *_aboutLayer;

	void addBackground();
	void addButton();
	void addAboutLayer();
	void removeAboutLayer();
};
