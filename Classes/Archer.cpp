#include "Archer.h"

struct ArcherValues;

Archer::Archer()
{
	idleMode();
	_AIEnabled = true;
	//this update do not do AI
	scheduleUpdate();
	
	auto specialAttack = [&]() {
		if (_specialAttackChance == 1)
			return;
		_specialAttackChance = 1;
	};
	MessageDispatchCenter::registerMessage(MessageDispatchCenter::MessageType::SPECIAL_ARCHER, specialAttack);
};

bool Archer::init()
{
	//_useWeaponId = ReSkin.archer.weapon;
	//_useArmourId = ReSkin.archer.armour;
	//_useHelmetId = ReSkin.archer.helmet;
	//copyTable(ActorCommonValues, self);
	//copyTable(ArcherValues, self);
	if (uiLayer != NULL) {
		_bloodBar = uiLayer->ArcherBlood;
		_bloodBarClone = uiLayer->ArcherBloodClone;
		_avatar = uiLayer->ArcherPng;
	}

	init3D();
	initActions();
};

void Archer::update(float dt)
{
	baseUpdate(dt);
	stateMachineUpdate(dt);
	movementUpdate(dt);
};

Sprite3D* Archer::createArrow()
{
	auto sprite3d = Sprite3D::create("model/archer/arrow.obj");
	sprite3d->setTexture("model/archer/hunter01_tex_head.jpg");
	sprite3d->setScale(2);
	sprite3d->setPosition3D(Vec3(0, 0, 50));
	sprite3d->setRotation3D(Vec3(-90, 0, 0));
	return sprite3d;
};

void Archer::ArcherlAttackCallback(int audioID, std::string filePath)
{
	experimental::AudioEngine::play2d(Archerproperty.attack2, false, 1);
};

void Archer::playDyingEffects()
{
	experimental::AudioEngine::play2d(Archerproperty.dead, false, 1);
};

void Archer::hurtSoundEffects()
{
	experimental::AudioEngine::play2d(Archerproperty.wounded, false, 1);
};

void Archer::normalAttack()
{
	ArcherNormalAttack::CreateWithPos(getPosTable(this), _curFacing, _normalAttack, this);
	experimental::AudioEngine::play2d(Archerproperty.normalAttackShout, false, 1);
	AUDIO_ID.ARCHERATTACK = experimental::AudioEngine::play2d(Archerproperty.attack1, false, 1);
	experimental::AudioEngine::setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
};

void Archer::specialAttack()
{
	_specialAttackChance = ArcherValues._specialAttackChance;
	_angry = ActorCommonValues._angry;
	auto angryChange = { _name, _angry, _angryMax };
	MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, angryChange);

	experimental::AudioEngine::play2d(Archerproperty.specialAttackShout, false, 1);
	AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false, 1);
	ccexp.AudioEngine : setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);

	auto attack = _specialAttack;
	attack.knock = 80;

	auto pos1 = getPosTable(this);
	pos1 = ccpRotateByAngle(pos1, _myPos, _curFacing);
	auto pos2 = pos1;
	auto pos3 = pos2;
	ArcherSpecialAttack::create(pos1, _curFacing, attack, this);
	auto spike2 = [&]() {
		ArcherSpecialAttack::create(pos2, _curFacing, attack, this);
		AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false, 1);
		ccexp.AudioEngine : setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
	}
	auto spike3 = [&]() {
		ArcherSpecialAttack::create(pos3, _curFacing, attack, this);
		AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false, 1);
		ccexp.AudioEngine : setFinishCallback(AUDIO_ID.ARCHERATTACK, ArcherlAttackCallback);
	}
	delayExecute(this, spike2, 0.2);
	delayExecute(this, spike3, 0.4);

};

void Archer::init3D()
{
	initShadow();
	initPuff();
	_sprite3d = Sprite3D::create(file);
	_sprite3d->setScale(1.6);
	_sprite3d->addEffect(Vec3(0, 0, 0), CelLine, -1);
	addChild(_sprite3d);
	_sprite3d->setRotation3D(Vec3(90, 0, 0));
	_sprite3d->setRotation(-90);
	setDefaultEqt();
};

void Archer::initActions()
{

};

//set default equipments
void Archer::setDefaultEqt()
{

};

void Archer::updataWeapon()
{

};

void Archer::updateHelmet()
{

};

void Archer::updateArmour()
{

};

//switth weapon
void Archer::switchWeapon()
{

};

//switch helmet
void Archer::switchHelmet()
{

};

//switch armour
void Archer::switchArmour()
{

};

//show/hide arrow
//isShow: true : Show false : Hide
//type: 0 : show / hide all 1 : show / hide 1 2 : show / hide 2
void Archer::showOrHideArrow(bool isShow, int arrowType)
{

};

//get weapon id
int Archer::getWeaponID()
{

};

//get armour id
int Archer::getArmourID()
{

};

//get helmet id
int Archer::getHelmetID()
{

};

int Archer::hurt(Actor* collider, bool dirKnockMode)
{

};
