#include "Dragon.h"

static std::string file = "model/dragon/dragon.c3b";

Dragon::Dragon()
{
	_AIEnabled = true;
	scheduleUpdate(0.5);
}

bool Dragon::init()
{
	copyTable(ActorCommonValues, this);
	copyTable(DragonValues, this);
	init3D();
	initActions();
}

void Dragon::reset()
{
	copyTable(ActorCommonValues, this);
	copyTable(DragonValues, this);
	walkMode();
	setPositionZ(0);
};

void Dragon::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt)
};

void Dragon::dyingMode(Vec2 knockSource, int knockAmount)
{
	setStateType(EnumStateType::DYING);
	playAnimation("dead");

	//Twice play in order to inhance the sounds,
	//todo:zijian.
	//ccexp.AudioEngine : play2d(MonsterDragonValues.dead, false, 1)

	if (knockAmount){
		auto p = getPosTable(this);
		auto angle = ccpToAngle(ccpSub(p, knockSource));
		auto newPos = ccpRotateByAngle(ccpAdd(Vec2(knockAmount, 0), p), p, angle);
		runAction(EaseCubicActionInOut::create(MoveTo::create(_action.at("knocked")->getDuration() * 3, newPos)));
	}
	_AIEnabled = false;
	





};

void Dragon::normalAttackSoundEffects()
{

};

void Dragon::playDyingEffects()
{

};

void Dragon::hurtSoundEffects()
{

};

void Dragon::normalAttack()
{

};

void Dragon::init3D()
{

};

void Dragon::initActions()
{

};
