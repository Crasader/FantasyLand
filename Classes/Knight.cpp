#include "Knight.h"

std::string file = "model/knight/knight.c3b";

Knight::Knight()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0);

	auto specialAttack = [&]() {
		if (_specialAttackChance == 1)
			return;
		_specialAttackChance = 1;
	};
	MessageDispatchCenter::registerMessage(MessageDispatchCenter::MessageType::SPECIAL_KNIGHT, specialAttack);
}

bool Knight::init()
{
	_useWeaponId = ReSkin.knight.weapon;
	_useArmourId = ReSkin.knight.armour;
	_useHelmetId = ReSkin.knight.helmet;
	copyTable(ActorCommonValues, this);
	copyTable(KnightValues, this);

	if (uiLayer != NULL) {
		_bloodBar = uiLayer->KnightBlood;
		_bloodBarClone = uiLayer->KnightBloodClone;
		_avatar = uiLayer->KnightPng;
	}

	init3D();
	initActions();
	return true;
}

void Knight::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt)
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
	auto angryChange = { _name, _angry, _angryMax };
	MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, angryChange);

	//knight will create 2 attacks one by one  
	experimental::AudioEngine::play2d(WarriorProperty.specialAttackShout, false, 0.7);
	auto attack = _specialAttack;
	attack.knock = 0;
	KnightNormalAttack::CreateWithPos(getPosTable(this), _curFacing, attack, this);

	auto pos = getPosTable(this);
	pos.x += 50;
	pos = ccpRotateByAngle(pos, _myPos, _curFacing);

	AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(WarriorProperty.specialAttack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.KNIGHTSPECIALATTACK, KnightSpecialAttackCallback);
	
	auto punch = [&]() {
		KnightNormalAttack::CreateWithPos(pos, _curFacing, _specialAttack, this);
	};
	delayExecute(this, punch, 0.2);
}

void Knight::initAttackEffect()
{
	auto speed = 0.15;
	auto startRotate = 145;
	auto rotate = -60;
	auto scale = 0.01;
	auto sprite = Sprite::createWithSpriteFrameName("specialAttack.jpg");
	sprite->setVisible(false);
	sprite->setBlendFunc(gl.ONE, gl.ONE);
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
	initShadow();
	initPuff();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(25);
	_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
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
