#include "Mage.h"
#include "BattleFieldUI.h"
#include "HPCounter.h"
#include "MessageDispatchCenter.h"

Mage::Mage()
{
	
}

bool Mage::init()
{
	Actor::init();
	_useWeaponId = ReSkin.mage.weapon;
	_useArmourId = ReSkin.mage.armour;
	_useHelmetId = ReSkin.mage.helmet;

	//init data
	copyData_Mage();

	//init bloodbar and avatar
	if (uiLayer != NULL) {
		_bloodBar = uiLayer->MageBlood;
		_bloodBarClone = uiLayer->MageBloodClone;
		_avatar = uiLayer->MagePng;
	}

	//init image
	init3D();
	initActions();
	
	_AIEnabled = true;
	scheduleUpdateWithPriority(0);
	auto specialAttack = [&]() {
		if (_specialAttackChance == 1)
			return;
		_specialAttackChance = 1;
	};

	MessageDispatchCenter::getInstance()->registerMessage(MessageType::SPECIAL_MAGE, [](Actor* data)
	{
		if (data->getSpecialAttackChance() == 1)
			return;
		data->setSpecialAttackChance(1);
	});

	return true;
}

void Mage::copyData_Mage()
{
	//Actor Common Values
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

	//Mage Default Values
	_racetype = EnumRaceType::HERO;
	_name = "Mage";
	_radius = 50;
	_mass = 800;
	_shadowSize = 70;
	_hp = 1100;
	_maxhp = 1100;
	_defense = 120;
	_attackFrequency = 2.67;
	_recoverTime = 0.8;
	_AIFrequency = 1.33;
	_attackRange = 400;
	_specialAttackChance = 0;
	_specialSlowTime = 0.67;
	_normalAttack = MageValues._normalAttack;
	_specialAttack = MageValues._specialAttack;

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
	MageNormalAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack, _target, this);
	
}

void Mage::specialAttack()
{
	_specialAttackChance = MageValues._specialAttackChance;
	_angry = ActorCommonValues._angry;
	struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry, _angryMax };
	MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, this);
	
	experimental::AudioEngine::play2d(MageProperty.specialAttackShout, false, 0.5);
	experimental::AudioEngine::play2d(MageProperty.ice_special, false, 1);

	//mage will create 3 ice spikes on the ground
	auto pos1 = getPosTable(this);
	auto pos2 = pos1;
	auto pos3 = pos2;
	pos1.x += 130;
	pos2.x += 330;
	pos3.x += 530;
	pos1 = ccpRotateByAngle(pos1, _myPos, _curFacing);
	pos2 = ccpRotateByAngle(pos2, _myPos, _curFacing);
	pos3 = ccpRotateByAngle(pos3, _myPos, _curFacing);
	MageIceSpikes::CreateWithPos(pos1, _curFacing, _specialAttack, this);
	auto spike2 = [&]() {
		experimental::AudioEngine::play2d(MageProperty.specialAttackShout, false, 0.5);
		MageIceSpikes::CreateWithPos(pos2, _curFacing, _specialAttack, this);
	};
	auto spike3 = [&]() {
		experimental::AudioEngine::play2d(MageProperty.specialAttackShout, false, 0.5);
		MageIceSpikes::CreateWithPos(pos3, _curFacing, _specialAttack, this);
	};
	auto wait2 = DelayTime::create(0.25);
	this->runAction(Sequence::create(wait2, CallFunc::create(spike2), wait2->clone(), CallFunc::create(spike3), NULL));
	//this->runAction(Sequence::create(wait3, CallFunc::create(spike3), NULL));
}

void Mage::init3D()
{
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(1.9);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
	initShadow();
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

float Mage::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (_isalive == true) {
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

		auto blood = _hpCounter->showBloodLossNum(damage, this, critical);
		blood->setCameraMask(2);
		if (_name == "Rat")
			blood->setPositionZ(Director::getInstance()->getVisibleSize().height * 0.25);
		addEffect(blood);
		//Transfer data to UILayer
		struct MESSAGE_BLOOD_MINUS  bloodMinus = { _name, _maxhp, _hp, _bloodBar, _bloodBarClone, _avatar };
		MessageDispatchCenter::getInstance()->dispatchMessage(BLOOD_MINUS, this);
		struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry,_angryMax };
		MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, this);

		_angry += damage;
		return damage;
	}
	return 0;
}
