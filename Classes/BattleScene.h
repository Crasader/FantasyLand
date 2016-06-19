#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Actor;
enum MessageType;
class BattleScene :public Layer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BattleScene);
	virtual bool init();
	void update(float dt) override;

private:
	Vec3 _cameraOffset{ 150, -480, 220 };
	Vec2 _lastTouchPosition;
	Vec2 _cameraAngularVelocity;
	Vec3 _cameraVelocity;

	void setCamera();
	void controlCamera();
	void moveCamera(float dt);
	void createBackground();
	void initUILayer();
	void enableTouch();
	void updateParticlePos();
	void gameController(float dt);
	void bloodMinus(Actor *heroActor);
	void angryChange(Actor *heroActor);
	MessageType UIcontainsPoint(Vec2 position);
	Vec2 getPositionOf3DWorld(Vec2 touchPosition);
};
