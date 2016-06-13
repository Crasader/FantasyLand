#include "Dragon.h"

Dragon::Dragon()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(1);
}

bool Dragon::init()
{
	Actor::init();
	//copyTable(ActorCommonValues, this);
	//copyTable(DragonValues, this);
	copyData_Dragon();
	init3D();
	initActions();
	return true;
}

void Dragon::copyData_Dragon()
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

	_racetype = EnumRaceType::MONSTER;
	_name = "Dragon";
	_radius = 50;
	_mass = 100;
	_shadowSize = 70;
	_hp = 600;
	_maxhp = 600;
	_defense = 130;
	_attackFrequency = 5.2;
	_recoverTime = 0.8;
	_AIFrequency = 1.337;
	_attackRange = 350;
	_speed = 300;
	_turnSpeed = DEGREES_TO_RADIANS(180);
	_acceleration = 250;
	_decceleration = 750 * 1.7;
	_normalAttack = DragonValues._normalAttack;
}

void Dragon::reset()
{
	copyData_Dragon();
	walkMode();
	setPositionZ(0);
}

void Dragon::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Dragon::dyingMode(Vec2 knockSource, int knockAmount)
{
	setStateType(EnumStateType::DYING);
	playAnimation("dead");
	playDyingEffects();//todo
	//Twice play in order to inhance the sounds,
	//todo:zijian.
	//ccexp.AudioEngine : play2d(MonsterDragonValues.dead, false, 1)

	if (knockAmount){
		auto p = getPosTable(this);
		auto angle = ccpToAngle(ccpSub(p, knockSource));
		auto newPos = ccpRotateByAngle(ccpAdd(Vec2(knockAmount, 0), p), p, angle);
		//runAction(EaseCubicActionInOut::create(MoveTo::create(_action.at("knocked")->getDuration() * 3, newPos)));
	}
	_AIEnabled = false;

	remove(MonsterManager.begin(), MonsterManager.end(), this);

	auto recycle = [&]() {
		setVisible(false);
		getPoolByName(_name).push_back(this);
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
	log("yeah");
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
	//initShadow();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(10);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	initShadow();
	
	
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
