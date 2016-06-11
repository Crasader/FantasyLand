#include "Slime.h"

Slime::Slime()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0.5);
	play3DAnim();
}

bool Slime::init()
{
	//copyTable(ActorCommonValues, this);
	//copyTable(SlimeValues, this);
	_angryFace = false;
	init3D();
	initActions();
	return true;
}

void Slime::reset()
{
	//copyTable(ActorCommonValues, this);
	//copyTable(SlimeValues, this);
	bool allDead;
	_findEnemy(_racetype, allDead);
	walkMode();
	setPositionZ(0);
}

void Slime::copyData_Slime()
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
	_name = "Slime";
	_radius = 35;
	_mass = 20;
	_shadowSize = 45;
	_hp = 300;
	_maxhp = 300;
	_defense = 65;
	_attackFrequency = 1.5;
	_recoverTime = 0.7;
	_AIFrequency = 3.3;
	_AITimer = 2.0;
	_attackRange = 50;
	_speed = 150;
	_acceleration = 9999;
	_decceleration = 9999;
	//_normalAttack = SlimeValues._normalAttack;
}

void Slime::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Slime::play3DAnim() 
{
	_sprite3d->runAction(RepeatForever::create(createAnimation(file, 0, 22, 0.7)));
}

void Slime::playAnimation(std::string name, bool loop)
{
	if (_curAnimation != name) {	//--using name to check which animation is playing
		_sprite3d->stopAction(_curAnimation3d);
		if (loop)
			_curAnimation3d = RepeatForever::create(_action.at(name)->clone());
		else
			_curAnimation3d = _action.at(name)->clone();
		_sprite3d->setPosition3D(Vec3(0, 0, 0));
		_sprite3d->setRotation3D(Vec3(90, 0, -90));
		_sprite3d->runAction(_curAnimation3d);
		_curAnimation = name;
	}
}

void Slime::init3D()
{
	initShadow();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setTexture("model/slime/baozi.jpg");
	_sprite3d->setScale(17);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
};

void Slime::walkMode()
{
	angryFace(false);
	Actor::walkMode();

};

void Slime::attackMode()
{
	angryFace(true);
	Actor::attackMode();
};

void Slime::idleMode()
{
	angryFace(false);
	Actor::idleMode();
};

void Slime::knockMode(BasicCollider* collider, bool dirKnockMode)
{
	angryFace(false);
	Actor::knockMode(collider, dirKnockMode);
};

void Slime::angryFace(bool trueFalse)
{
	if (_angryFace != trueFalse) {
		_angryFace = trueFalse;
		if (trueFalse)
			_sprite3d->setTexture("model/slime/baozi2.jpg");
		else
			_sprite3d->setTexture("model/slime/baozi.jpg");
	}
}

//init Slime animations
void Slime::initActions()
{
	float dur = 0.6;
	float bsc = 17;
	auto walk = Spawn::create(
		Sequence::create(
			DelayTime::create(dur / 8),
			JumpTiles3D::create(dur * 7 / 8, Size(0,0), 30, 1),
			NULL
			),
		Sequence::create(
			EaseSineOut::create(ScaleTo::create(dur / 8, bsc * 1.4, bsc * 1.4, bsc * 0.75)),
			EaseSineOut::create(ScaleTo::create(dur / 8, bsc * 0.85, bsc * 0.85, bsc * 1.3)),
			EaseSineOut::create(ScaleTo::create(dur / 8, bsc * 1.2, bsc * 1.2, bsc * 0.9)),
			EaseSineOut::create(ScaleTo::create(dur / 8, bsc * 0.95, bsc * 0.95, bsc * 1.1)),
			EaseSineOut::create(ScaleTo::create(dur * 4 / 8, bsc, bsc, bsc)),
			NULL
			),
		NULL
		);
	walk->retain();
	auto idle = Sequence::create(
		ScaleTo::create(dur / 2, bsc * 1.1, bsc * 1.1, bsc * 0.8),
		ScaleTo::create(dur / 2, bsc, bsc, bsc),
		NULL
		);
	idle->retain();
	auto attack1 = Spawn::create(
		MoveBy::create(dur / 2, Vec3(0, 0, 20)),
		RotateBy::create(dur * 3 / 4, Vec3(-70, 0, 0)),
		EaseBounceOut::create(MoveTo::create(dur / 2, Vec2(40, 0))),
		NULL
		);
	auto attack2 = Spawn::create(
		MoveBy::create(dur / 2, Vec3(0, 0, 0)),
		RotateBy::create(dur * 3 / 4, Vec3(-70, 0, 0)),
		EaseBounceOut::create(MoveTo::create(dur, Vec2(0, 0))),
		NULL
		);
	attack1->retain();
	attack2->retain();
	auto die = Spawn::create(
		Sequence::create(
			JumpBy::create(dur / 2, Vec2(0, 0), 30, 1),
			ScaleBy::create(dur, 2, 2, 0.1),
			NULL
			),
		RotateBy::create(dur, Vec3(-90, 0, 0)),
		NULL
		);
	die->retain();
	auto knock = Sequence::create(
		EaseBounceOut::create(RotateBy::create(dur / 3, Vec3(-60, 0, 0))),
		RotateBy::create(dur / 2, Vec3(60, 0, 0)),
		NULL
		);
	knock->retain();

	_action.insert("idle", idle);
	_action.insert("walk", walk);
	_action.insert("attack1", attack1);
	_action.insert("attack2", attack2);
	_action.insert("knocked", knock);
	_action.insert("dead", die);
}