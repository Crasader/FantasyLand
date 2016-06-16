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

	void moveCamera(float dt);
	void updateParticlePos();
	void createBackground();
	void setCamera();
	void gameController(float dt);
	void initUILayer();
	void bloodMinus(Actor *heroActor);
	void angryChange(Actor *heroActor/*angry @lua*/);
	void specialPerspective(Actor *heroActor/*param @lua*/);
	void enableTouch();
	MessageType UIcontainsPoint(Vec2 position/*position @lua*/);

	void controlCamera();
private:
	Camera *specialCamera;
	Scheduler * scheduler;
	Vec3 cameraOffset;
	Vec2 cameraOffsetMin;
	Vec2 cameraOffsetMax;

	bool isDebug;
	Vec2 lastTouchPosition;
	Vec2 cameraAngularVelocity;
	Vec3 cameraVelocity;
};
