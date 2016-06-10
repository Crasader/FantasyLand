#include "Mage.h"
#include "GlobalVariables.h"
#include "AttackCommand.h"

Mage::Mage()
{
	_AIEnabled = true;
	scheduleUpdateWithPriority(0);
	auto specialAttack = [&]() {
		if (_specialAttackChance == 1)
			return;
		_specialAttackChance = 1;
	};
	//MessageDispatchCenter::registerMessage(MessageDispatchCenter::MessageType::SPECIAL_MAGE, specialAttack);
}

bool Mage::init()
{
	_useWeaponId = ReSkin.mage.weapon;
	_useArmourId = ReSkin.mage.armour;
	_useHelmetId = ReSkin.mage.helmet;
	//copyTable(ActorCommonValues, this);
	//copyTable(MageValues, this);

	/*if (uiLayer != NULL) {
		_bloodBar = uiLayer->MageBlood;
		_bloodBarClone = uiLayer->MageBloodClone;
		_avatar = uiLayer->MagePng;
	}*/

	init3D();
	initActions();
	return true;
}

void Mage::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

void Mage::playDyingEffects()
{
	experimental::AudioEngine::play2d(MageProperty.dead, false, 0.7);
}

void Mage::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(MageProperty.wounded, false, 1);
}

void Mage::normalAttack()
{
	experimental::AudioEngine::play2d(MageProperty.normalAttackShout, false, 0.4);
	experimental::AudioEngine::play2d(MageProperty.ice_normal, false, 0.8);
	//MageNormalAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack, _target, this);
}

void Mage::specialAttack()
{
	_specialAttackChance = MageValues._specialAttackChance;
	_angry = ActorCommonValues._angry;
	//auto angryChange = { _name, _angry, _angryMax };
	//MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, angryChange);

	//mage will create 3 ice spikes on the ground
	//get 3 positions
	experimental::AudioEngine::play2d(MageProperty.specialAttackShout, false, 0.5);
	experimental::AudioEngine::play2d(MageProperty.ice_special, false, 1);
	
	auto pos1 = getPosTable(this);
	auto pos2 = getPosTable(this);
	auto pos3 = getPosTable(this);
	pos1.x += 130;
	pos2.x += 330;
	pos3.x += 530;
	pos1 = ccpRotateByAngle(pos1, _myPos, _curFacing);
	pos2 = ccpRotateByAngle(pos2, _myPos, _curFacing);
	pos3 = ccpRotateByAngle(pos3, _myPos, _curFacing);
	//MageIceSpikes::CreateWithPos(pos1, _curFacing, _specialAttack, this);
	//auto spike2 = [&]() {
	//	MageIceSpikes::CreateWithPos(pos2, _curFacing, _specialAttack, this);
	//};
	//auto spike3 = [&]() {
	//	MageIceSpikes::CreateWithPos(pos3, _curFacing, _specialAttack, this);
	//};
	
	//delayExecute(this, spike2, 0.25);
	//delayExecute(this, spike3, 0.5);
}

void Mage::init3D()
{
	initShadow();
	initPuff();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(1.9);
	//_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
}

void Mage::initActions()
{
	_action.insert("idle", createAnimation(file, 206, 229, 0.7));
	_action.insert("walk", createAnimation(file, 99, 119, 0.7));
	_action.insert("attack1", createAnimation(file, 12, 30, 0.7));
	_action.insert("attack2", createAnimation(file, 31, 49, 0.7));
	_action.insert("specialattack1", createAnimation(file, 56, 74, 0.2));
	_action.insert("specialattack2", createAnimation(file, 75, 92, 0.2));
	_action.insert("defend", createAnimation(file, 1, 5, 0.7));
	_action.insert("knocked", createAnimation(file, 126, 132, 0.7));
	_action.insert("dead", createAnimation(file, 139, 199, 0.7));
}

void Mage::setDefaultEqt()
{
	updateArmour();
	updateHelmet();
	updateWeapon();
}

void Mage::updateWeapon()
{
	if (_useWeaponId == 0) {
		auto weapon = _sprite3d->getMeshByName("fashi_wuqi01");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("fashi_wuqi2");
		weapon->setVisible(false);
	}
	else {
		auto weapon = _sprite3d->getMeshByName("fashi_wuqi2");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("fashi_wuqi01");
		weapon->setVisible(false);
	}
}

void Mage::updateHelmet()
{
	if (_useHelmetId == 0) {
		auto helmet = _sprite3d->getMeshByName("fashi_tou01");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("fashi_tou2");
		helmet->setVisible(false);
	}
	else {
		auto helmet = _sprite3d->getMeshByName("fashi_tou2");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("fashi_tou01");
		helmet->setVisible(false);
	}
}

void Mage::updateArmour()
{
	if (_useArmourId == 0) {
		auto armour = _sprite3d->getMeshByName("fashi_shenti01");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("fashi_shenti2");
		armour->setVisible(false);
	}
	else {
		auto armour = _sprite3d->getMeshByName("fashi_shenti2");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("fashi_shenti01");
		armour->setVisible(false);
	}
}

void Mage::switchWeapon()
{
	_useWeaponId++;
	if (_useWeaponId > 1)
		_useWeaponId = 0;
	updateWeapon();
}

void Mage::switchHelmet()
{
	_useHelmetId++;
	if (_useHelmetId > 1)
		_useHelmetId = 0;
	updateHelmet();
}

void Mage::switchArmour()
{
	_useArmourId++;
	if (_useArmourId > 1)
		_useArmourId = 0;
	updateArmour();
}

int Mage::getWeaponID()
{
	return _useWeaponId;
}

int Mage::getHelmetID()
{
	return _useArmourId;
}

int Mage::getArmourID()
{
	return _useHelmetId;
}

int Mage::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (_isalive == true) {
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
		/*Sprite* blood = _hpCounter->showBloodLossNum(damage, this, critical);
		if (_name == "Rat")
			setPositionZ(Director::getInstance()->getVisibleSize().height * 0.25);
		addEffect(blood);

		auto bloodMinus = { _name, _maxhp, _hp, _bloodBar, _bloodBarClone, _avatar };
		MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::BLOOD_MINUS, bloodMinus);
		auto anaryChange = { _name, _angry,_angryMax };
		MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANCE, anaryChange);*/
		return damage;
	}
	return 0;
}
