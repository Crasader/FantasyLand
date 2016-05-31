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
	return true;
}

void Dragon::reset()
{
	copyTable(ActorCommonValues, this);
	copyTable(DragonValues, this);
	walkMode();
	setPositionZ(0);
}

void Dragon::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt)
}

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
	//自己修改的Erase
	std::vector<Actor*>::iterator it = std::find(MonsterManager.begin(), MonsterManager.end(), this);
	HeroManager.erase(it);
	auto recycle = [&]() {
		setVisible(false);
		getPoolByName(_name).push_back(this);
		//List.pushlast(getPoolByName(_name), self);
	};
	runAction(Sequence::create(DelayTime::create(3),
		MoveBy::create(1.0, Vec3(0, 0, -50)),
		CallFunc::create(recycle), NULL));
}

void Dragon::normalAttackSoundEffects()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.attack, false, 1);
}

void Dragon::playDyingEffects()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.dead, false, 1);
}

void Dragon::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.wounded, false, 0.7);
}

void Dragon::normalAttack()
{
	normalAttackSoundEffects();
	DragonAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack);
}

void Dragon::init3D()
{
	initShadow();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(10);
	_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
}

void Dragon::initActions()
{
	_action.insert("idle", createAnimation(file, 0, 24, 0.7));
	_action.insert("knocked", createAnimation(file, 30, 37, 0.7));
	_action.insert("dead", createAnimation(file, 42, 80, 1));
	_action.insert("attack1", createAnimation(file, 85, 100, 0.7));
	_action.insert("attack2", createAnimation(file, 100, 115, 0.7));
	_action.insert("walk", createAnimation(file, 120, 140, 1));
}
