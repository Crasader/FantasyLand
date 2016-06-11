#include "Piglet.h"

Piglet::Piglet()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0.5);
};

bool Piglet::init()
{
	Actor::init();
	_useWeaponId = ReSkin.mage.weapon;
	_useArmourId = ReSkin.mage.armour;
	//copyTable(ActorCommonValues, this);
	//copyTable(PigletValues, this);
	copyData_Piglet();
	init3D();
	initActions();
	return true;
}

void Piglet::copyData_Piglet()
{
	_aliveTime = 0,
	_curSpeed = 0;
	_curAnimation = "";
	_curAnimation3d = NULL;
	_curFacing = 0;
	_isalive = true;
	_AITimer = 0;
	_AIEnabled = false;
	_attackTimer = 0;
	_timeKnocked = 0;
	_cooldown = false;
	_hp = 1000;
	_goRight = true;
	_targetFacing = 0;
	_target = NULL;
	_myPos = ccp(0, 0);
	_angry = 0;
	_angryMax = 500;
	_racetype = MONSTER;
	_name = "Piglet";
	_radius = 50;
	_mass = 69;
	_shadowSize = 60;
	_hp = 400;
	_maxhp = 400;
	_defense = 65;
	_attackFrequency = 4.73;
    _recoverTime = 0.9;
	_AIFrequency = 2.3;
	_attackRange = 120;
	_speed = 350;
	_turnSpeed = DEGREES_TO_RADIANS(270);
	_normalAttack =
	{
		0 , 120 , DEGREES_TO_RADIANS(50) ,
		0 , 150 , MONSTER , 0 , 0 , 0.15f
	};
}

void Piglet::reset()
{
	copyData_Piglet();
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