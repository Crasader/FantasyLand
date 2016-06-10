#include "Piglet.h"



Piglet::Piglet()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0.5);
};

bool Piglet::init()
{
	_useWeaponId = ReSkin.mage.weapon;
	_useArmourId = ReSkin.mage.armour;
	//copyTable(ActorCommonValues, this);
	//copyTable(PigletValues, this);
	init3D();
	initActions();
	return true;
}

void Piglet::reset()
{
	//copyTable(ActorCommonValues, this);
	//copyTable(PigletValues, this);
	bool allDead;
	_findEnemy(_racetype, allDead);
	walkMode();
	setPositionZ(0);
}

void Piglet::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Piglet::playDyingEffects()
{
	experimental::AudioEngine::play2d(MonsterPigletValues.dead, false, 1);
}

void Piglet::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(MonsterPigletValues.hurt, false, 1);
}

void Piglet::normalAttackSoundEffects()
{
	float randomEffect = CCRANDOM_0_1();
	if (randomEffect <= 0.3 && randomEffect >= 0) {
		experimental::AudioEngine::play2d(MonsterPigletValues.attack1, false, 1);
	}
	else if (randomEffect <= 0.6 && randomEffect > 0.3) {
		experimental::AudioEngine::play2d(MonsterPigletValues.attack2, false, 1);
	}
	else if (randomEffect > 0.6 && randomEffect <= 1) {
		experimental::AudioEngine::play2d(MonsterPigletValues.attack3, false, 1);
	}
}

void Piglet::init3D()
{
	initShadow();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setTexture("model/piglet/zhu0928.jpg");
	_sprite3d->setScale(1.3);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
}

void Piglet::initActions()
{
	_action.insert("idle", createAnimation(file, 0, 40, 0.7));
	_action.insert("walk", createAnimation(file, 135, 147, 1.5));
	_action.insert("attack1", createAnimation(file, 45, 60, 0.7));
	_action.insert("attack2", createAnimation(file, 60, 75, 0.7));
	_action.insert("defend", createAnimation(file, 92, 96, 0.7));
	_action.insert("knocked", createAnimation(file, 81, 87, 0.7));
	_action.insert("dead", createAnimation(file, 95, 127, 1));
}