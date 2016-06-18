#include "Archer.h"
#include "BattleFieldUI.h"
#include "HPCounter.h"
#include "MessageDispatchCenter.h"

struct ArcherValues;

Archer::Archer()
{
};

bool Archer::init()
{
	Actor::init();

	//init equipment
	_useWeaponId = ReSkin.archer.weapon;
	_useArmourId = ReSkin.archer.armour;
	_useHelmetId = ReSkin.archer.helmet;

	//init data
	copyData_Archer();

	//init UI
	if (uiLayer != NULL) {
		_bloodBar = uiLayer->ArcherBlood;
		_bloodBarClone = uiLayer->ArcherBloodClone;
		_avatar = uiLayer->ArcherPng;
	}

	//init image
	init3D();
	initActions();    
	
	//init state machine
	idleMode();
	_AIEnabled = true;
	scheduleUpdateWithPriority(0);

	MessageDispatchCenter::getInstance()->registerMessage(SPECIAL_ARCHER, [](Actor * data)
	{
		if (data->getSpecialAttackChance() == 1)
			return;
		data->setSpecialAttackChance(1);
	});
	return true;
}

void Archer::copyData_Archer()
{
	//actor common values
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
	//archer default values
	_racetype = HERO;
	_name = "Archer";
	_radius = 50;
	_mass = 800;
	_shadowSize = 70;
	_hp = 1200;
	_maxhp = 1200;
	_defense = 130;
	_attackFrequency = 2.5;
	_recoverTime = 0.4;
	_AIFrequency = 1.3;
	_attackRange = 450;
	_specialAttackChance = 0;
	_specialSlowTime = 0.5;
	_turnSpeed = DEGREES_TO_RADIANS(360);
	_normalAttack = ArcherValues._normalAttack;
	_specialAttack = ArcherValues._specialAttack;
}

void Archer::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
}

//call by AttackCommand.cpp
//create arrow when create ArcherNormalAttack or ArcherSpecialAttack
Sprite3D* Archer::createArrow()
{
	auto sprite3d = Sprite3D::create("model/archer/arrow.obj");
	sprite3d->setTexture("model/archer/hunter01_tex_head.jpg");
	sprite3d->setScale(2);
	sprite3d->setPosition3D(Vec3(0, 0, 80));
	sprite3d->setRotation3D(Vec3(-90, 0, 0));
	return sprite3d;
}

void Archer::ArcherlAttackCallback(int audioID, std::string filePath)
{
	experimental::AudioEngine::play2d(Archerproperty.attack2, false, 1);
}

void Archer::playDyingEffects()
{
	experimental::AudioEngine::play2d(Archerproperty.dead, false, 1);
}

void Archer::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(Archerproperty.wounded, false, 1);
}

void Archer::normalAttack()
{
	ArcherNormalAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack, this);
	experimental::AudioEngine::play2d(Archerproperty.normalAttackShout, false, 1);
	AUDIO_ID.ARCHERATTACK = experimental::AudioEngine::play2d(Archerproperty.attack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
}

void Archer::specialAttack()
{
	_specialAttackChance = ArcherValues._specialAttackChance;
	_angry = ActorCommonValues._angry;

	struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry, _angryMax };
	MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, this);
	log("Archer Special Attack %f,%f",_angry, _angryMax);

	experimental::AudioEngine::play2d(Archerproperty.specialAttackShout, false, 1);
	AUDIO_ID.ARCHERATTACK = experimental::AudioEngine::play2d(Archerproperty.attack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);

	auto attack = _specialAttack;
	attack.knock = 80;
	auto pos1 = getPosTable(this);
	pos1 = ccpRotateByAngle(pos1, _myPos, _curFacing);
	auto pos2 = pos1;
	auto pos3 = pos2;
	ArcherSpecialAttack::CreateWithPos(pos1, _curFacing, attack, this);
	auto spike2 = [&]() {
		ArcherSpecialAttack::CreateWithPos(pos2, _curFacing, attack, this);
		AUDIO_ID.ARCHERATTACK = experimental::AudioEngine::play2d(Archerproperty.attack1, false, 1);
		experimental::AudioEngine::setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
	};
	auto spike3 = [&]() {
		ArcherSpecialAttack::CreateWithPos(pos3, _curFacing, attack, this);
		AUDIO_ID.ARCHERATTACK = experimental::AudioEngine::play2d(Archerproperty.attack1, false, 1);
		experimental::AudioEngine::setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
	};
	auto wait2 = DelayTime::create(0.2);
	this->runAction(Sequence::create(wait2, CallFunc::create(spike2), NULL));
	auto wait3 = DelayTime::create(0.4);
	this->runAction(Sequence::create(wait3, CallFunc::create(spike3), NULL));
}

void Archer::init3D()
{
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(1.6);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
	initShadow();
}

void Archer::initActions()
{
	_action.insert("idle", createAnimation(file, 208, 253, 0.7));
	_action.insert("walk", createAnimation(file, 110, 130, 0.7));
	_action.insert("attack1", createAnimation(file, 0, 12, 0.7));
	_action.insert("attack2", createAnimation(file, 12, 24, 0.7));
	_action.insert("specialattack1", createAnimation(file, 30, 43, 0.2));
	_action.insert("specialattack2", createAnimation(file, 44, 56, 0.2));
	_action.insert("defend", createAnimation(file, 70, 95, 0.7));
	_action.insert("knocked", createAnimation(file, 135, 145, 0.7));
	_action.insert("dead", createAnimation(file, 150, 196, 0.7));
}

//set default equipments
void Archer::setDefaultEqt()
{
	updateWeapon();
	updateHelmet();
	updateArmour();
	showOrHideArrow(false, 0);
}

void Archer::updateWeapon()
{
	if (_useWeaponId == 0) {
		auto weapon = _sprite3d->getMeshByName("gongjianshou_gong01");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("gongjianshou_gong02");
		weapon->setVisible(false);
	}
	else {
		auto weapon = _sprite3d->getMeshByName("gongjianshou_gong02");
		weapon->setVisible(true);
		weapon = _sprite3d->getMeshByName("gongjianshou_gong01");
		weapon->setVisible(false);
	}
}

void Archer::updateHelmet()
{
	if (_useHelmetId == 0) {
		auto helmet = _sprite3d->getMeshByName("gongjianshou_tou01");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("gonajingshou_tou02");
		helmet->setVisible(false);
	}
	else {
		auto helmet = _sprite3d->getMeshByName("gonajingshou_tou02");
		helmet->setVisible(true);
		helmet = _sprite3d->getMeshByName("gongjianshou_tou01");
		helmet->setVisible(false);
	}
}

void Archer::updateArmour()
{
	if (_useArmourId == 0) {
		auto armour = _sprite3d->getMeshByName("gongjianshou_shenti01");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("gonjianshou_shenti02");
		armour->setVisible(false);
	}
	else {
		auto armour = _sprite3d->getMeshByName("gonjianshou_shenti02");
		armour->setVisible(true);
		armour = _sprite3d->getMeshByName("gongjianshou_shenti01");
		armour->setVisible(false);
	}
}

//switch weapon
void Archer::switchWeapon()
{
	_useWeaponId++;
	if (_useWeaponId > 1)
		_useWeaponId = 0;
	updateWeapon();
}

//switch helmet
void Archer::switchHelmet()
{
	_useHelmetId++;
	if (_useHelmetId > 1)
		_useHelmetId = 0;
	updateHelmet();
}

//switch armour
void Archer::switchArmour()
{
	_useArmourId++;
	if (_useArmourId > 1)
		_useArmourId = 0;
	updateArmour();
}

//show or hide arrow
//isShow true:Show,  false:Hide
//type 0:show/hide all, 1:show /hide 1,  2:show/hide 2
void Archer::showOrHideArrow(bool isShow, int arrowType)
{
	if (arrowType == 0) {
		auto arrow = _sprite3d->getMeshByName("gongjiashou_jian01");
		arrow->setVisible(isShow);
		arrow = _sprite3d->getMeshByName("gongjianshou_jian02");
		arrow->setVisible(isShow);
	}
	else if (arrowType == 1) {
		auto arrow = _sprite3d->getMeshByName("gongjiashou_jian01");
		arrow->setVisible(isShow);
	}
	else if (arrowType == 2) {
		auto arrow = _sprite3d->getMeshByName("gongjianshou_jian02");
		arrow->setVisible(isShow);
	};
}

//get weapon id
int Archer::getWeaponID()
{
	return _useWeaponId;
}

//get armour id
int Archer::getArmourID()
{
	return _useArmourId;
}

//get helmet id
int Archer::getHelmetID()
{
	return _useHelmetId;
}

float Archer::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (_isalive) {
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

		struct MESSAGE_BLOOD_MINUS bloodMinus = { _name, _maxhp, _hp, _bloodBar, _bloodBarClone, _avatar };
		MessageDispatchCenter::getInstance()->dispatchMessage(BLOOD_MINUS, this);
		struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry, _angryMax };
		MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, this);
		log("Archer hurt %f,%f", _angry, _angryMax);
		_angry += damage;
		return damage;
	}
	return 0;
}
