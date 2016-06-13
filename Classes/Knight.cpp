#include "Knight.h"
#include "BattleFieldUI.h"
#include "HPCounter.h"
#include "MessageDispatchCenter.h"

Knight::Knight()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0);

	auto specialAttack = [&]() {
		if (_specialAttackChance == 1)
			return;
		_specialAttackChance = 1;
	};
	//MDC->registerMessage(MessageDispatchCenter::MessageType::SPECIAL_KNIGHT, specialAttack);
}

bool Knight::init()
{
	Actor::init();
	_useWeaponId = ReSkin.knight.weapon;
	_useArmourId = ReSkin.knight.armour;
	_useHelmetId = ReSkin.knight.helmet;
	//copyTable(ActorCommonValues, this);
	//copyTable(KnightValues, this);
	copyData_Knight();
	if (uiLayer != NULL) {
		_bloodBar = uiLayer->KnightBlood;
		_bloodBarClone = uiLayer->KnightBloodClone;
		_avatar = uiLayer->KnightPng;
	}

	init3D();
	initActions();
	return true;
}

void Knight::copyData_Knight()
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
	_angryMax = 500;
	_racetype = HERO;
	_name = "Knight";
	_radius = 50;
	_mass = 1000;
	_shadowSize = 70;
	_hp = 1850;
	_angry = 0;
	_maxhp = 1850;
	_defense = 180;
	_attackFrequency = 2.2;
	_recoverTime = 0.4;
	_AIFrequency = 1.1;
	_attackRange = 140;
	_specialAttackChance = 0;
	_specialSlowTime = 1;
	_normalAttack = KnightValues._normalAttack;
	_specialAttack = KnightValues._specialAttack;
}

void Knight::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Knight::KnightNormalAttackCallback(int audioID, std::string filepath)
{
	experimental::AudioEngine::play2d(WarriorProperty.normalAttack2, false, 1);
}

void Knight::KnightSpecialAttackCallback(int audioID, std::string filepath)
{
	experimental::AudioEngine::play2d(WarriorProperty.specialAttack2, false, 1);
}

void Knight::playDyingEffects()
{
	experimental::AudioEngine::play2d(WarriorProperty.dead, false, 0.7);
}

void Knight::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(WarriorProperty.wounded, false,0.6);
}

void Knight::normalAttack()
{
	experimental::AudioEngine::play2d(WarriorProperty.normalAttackShout, false, 1);
	KnightNormalAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack, this);
	//self._sprite:runAction(self._action.attackEffect:clone()) 
	AUDIO_ID.KNIGHTNORMALATTACK = experimental::AudioEngine::play2d(WarriorProperty.normalAttack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.KNIGHTNORMALATTACK, KnightNormalAttackCallback);
}

void Knight::specialAttack()
{
	_specialAttackChance = KnightValues._specialAttackChance;
	_angry = ActorCommonValues._angry;
	struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry, _angryMax };
	MDC->dispatchMessage(MessageType::ANGRY_CHANGE, angryChange);

	//knight will create 2 attacks one by one  
	experimental::AudioEngine::play2d(WarriorProperty.specialAttackShout, false, 0.7);
	auto attack = _specialAttack;
	attack.knock = 0;
	KnightNormalAttack::CreateWithPos(getPosTable(this), _curFacing, attack, this);

	auto pos = getPosTable(this);
	pos.x += 50;
	pos = ccpRotateByAngle(pos, _myPos, _curFacing);

	AUDIO_ID.KNIGHTSPECIALATTACK = experimental::AudioEngine::play2d(WarriorProperty.specialAttack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.KNIGHTSPECIALATTACK, KnightSpecialAttackCallback);
	
	auto punch = [&]() {
		KnightNormalAttack::CreateWithPos(pos, _curFacing, _specialAttack, this);
	};
	//delayExecute(this, punch, 0.2); todo
}

void Knight::initAttackEffect()
{
	auto speed = 0.15;
	auto startRotate = 145;
	auto rotate = -60;
	auto scale = 0.01;
	auto sprite = Sprite::createWithSpriteFrameName("specialAttack.jpg");
	sprite->setVisible(false);
	//sprite->setBlendFunc(gl.ONE, gl.ONE); todo
	sprite->setScaleX(scale);
	sprite->setRotation(startRotate);
	sprite->setOpacity(0);
	sprite->setAnchorPoint(Vec2(0.5, -0.5));
	sprite->setPosition3D(Vec3(10, 0, 50));
	addChild(sprite);

	auto scaleAction = ScaleTo::create(speed, 2.5, 2.5);
	auto rotateAction = RotateBy::create(speed, rotate);
	auto fadeAction = FadeIn::create(0);
	auto attack = Sequence::create(scaleAction, rotateAction, fadeAction, NULL);
    
	auto fadeAction2 = FadeOut::create(0.5);
	auto scaleAction2 = ScaleTo::create(0, scale, 2.5);
	auto rotateAction2 = RotateBy::create(0, startRotate);
	auto restore = Sequence::create(fadeAction2, rotateAction2, scaleAction2, NULL);

	_sprite = sprite;
	_action.insert("attackEffect", Sequence::create(Show::create(), attack, restore, NULL));
	_action.at("attackEffect")->retain();
}

void Knight::init3D()
{
	//initShadow();
	initPuff();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(25);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
	initShadow();
}

void Knight::initActions()
{
	_action.insert("idle", createAnimation(file, 267, 283, 0.7));
	_action.insert("walk", createAnimation(file, 227, 246, 0.7));
	_action.insert("attack1", createAnimation(file, 103, 129, 0.7));
	_action.insert("attack2", createAnimation(file, 130, 154, 0.7));
	_action.insert("specialattack1", createAnimation(file, 160, 190, 0.3));
	_action.insert("specialattack2", createAnimation(file, 191, 220, 0.4));
	_action.insert("defend", createAnimation(file, 92, 96, 0.7));
	_action.insert("knocked", createAnimation(file, 254, 260, 0.7));
	_action.insert("dead", createAnimation(file, 0, 77, 1));
	initAttackEffect();
}

void Knight::setDefaultEqt()
{
	updateArmour();
	updateHelmet();
	updateWeapon();
}

void Knight::updateWeapon()
{
	if (_useWeaponId == 0) {
		auto weapon = _sprite3d->getMeshByName("zhanshi_wuqi01");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("zhanshi_wuqi02");
		weapon->setVisible(false);
	}
	else {
		auto weapon = _sprite3d->getMeshByName("zhanshi_wuqi02");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("zhanshi_wuqi01");
		weapon->setVisible(false);
	}
}

void Knight::updateHelmet()
{
	if (_useHelmetId == 0) {
		auto helmet = _sprite3d->getMeshByName("zhanshi_tou01");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("zhanshi_tou02");
		helmet->setVisible(false);
	}
	else {
		auto helmet = _sprite3d->getMeshByName("zhanshi_tou02");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("zhanshi_tou01");
		helmet->setVisible(false);
	}
}

void Knight::updateArmour()
{
	if (_useArmourId == 0) {
		auto armour = _sprite3d->getMeshByName("zhanshi_shenti01");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("zhanshi_shenti02");
		armour->setVisible(false);
	}
	else {
		auto armour = _sprite3d->getMeshByName("zhanshi_shenti02");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("zhanshi_shenti01");
		armour->setVisible(false);
	}
}

void Knight::switchWeapon()
{
	_useWeaponId++;
	if (_useWeaponId > 1)
		_useWeaponId = 0;
	updateWeapon();
}

void Knight::switchHelmet()
{
	_useHelmetId++;
	if (_useHelmetId > 1)
		_useHelmetId = 0;
	updateHelmet();
}

void Knight::switchArmour()
{
	_useArmourId++;
	if (_useArmourId > 1)
		_useArmourId = 0;
	updateArmour();
}

int Knight::getWeaponID()
{
	return _useWeaponId;
}

int Knight::getHelmetID()
{
	return _useArmourId;
}

int Knight::getArmourID()
{
	return _useHelmetId;
}

float Knight::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (isAlive()) {
		//TODO add sound effect
		auto damage = collider->getDamage();
		//calculate the real damage
		bool critical = false;
		auto knock = collider->getKnock();
		if (CCRANDOM_0_1() < collider->getCriticalChance()) {
			damage *= 1.5;
			critical = true;
			knock *= 2;
		}
		damage = damage + damage * CCRANDOM_MINUS1_1() * 0.15 - _defense;
		damage = floor(damage);
		if (damage <= 0) damage = 1;
		_hp -= damage;
		if (_hp > 0) {
			if (critical == true) {
				knockMode(collider, dirKnockMode);
				hurtSoundEffects();
			}
			else hurtSoundEffects();
		}
		else {
			_hp = 0;
			_isalive = false;
			dyingMode(getPosTable(collider), knock);
		}

		//three param judge if crit

		/* 这里需要修改 */
		auto blood = _hpCounter->showBloodLossNum(damage, this, critical);
		addEffect(blood);

		struct MESSAGE_BLOOD_MINUS bloodMinus = { _name, _maxhp, _hp, _bloodBar, _bloodBarClone, _avatar };
		MDC->dispatchMessage(MessageType::BLOOD_MINUS, bloodMinus);
		struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry,_angryMax };
		MDC->dispatchMessage(MessageType::ANGRY_CHANGE, angryChange);
		_angry += damage;
		return damage;
	}
	return 0;
}
