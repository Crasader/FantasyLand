#include "Actor.h"

extern Layer* uiLayer;
extern Layer* currentLayer;
extern int FXZorder;

bool Actor::init() 
{
	this->setCascadeColorEnabled(true);
	_action.clear();
	copyTable(ActorDefaultValues, this);
	copyTable(ActorCommonValues, this);

	//dropblood
	_hpCounter = HPCounter::create();
	addChild(_hpCounter);
	_effectNode = Node::create();
	_monsterHeight = 70;
	_heroHeight = 150;
	if (uiLayer != NULL)
		currentLayer->addChild(_effectNode);
	
	return true;
};

void Actor::addEffect(Sprite* effect)
{
	effect->setPosition(ccpAdd(getPosTable(this), getPosTable(effect)));
	if (_racetype != EnumRaceType::MONSTER)
		effect->setPositionZ(this->getPositionZ() + _heroHeight);
	else
		effect->setPositionZ(this->getPositionZ() + _heroHeight);
	currentLayer->addChild(effect);
};

void Actor::initPuff()
{
	auto puff = ParticleSystem::create(ParticleManager::getInstance()->getPlistData("walkpuff"));
	//ParticleSystem should be BillboardParticleSystem;
	auto puffFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("walkingPuff.png");
	puff->setTexture(puffFrame->getTexture());
	puff->setScale(1.5);
	puff->setGlobalZOrder(-getPositionZ() + FXZorder);
	puff->setPositionZ(10);
	_puff = puff;
	_effectNode->addChild(puff);
};

void Actor::initShadow()
{
	_circle = Sprite::createWithSpriteFrameName("shadow.png");
	//use Shadow size for aesthetic, use radius to see collision size
	_circle->setScale(_shadowSize / 16);
	_circle->setOpacity(255 * 0.7);
	this->addChild(_circle);
};

void Actor::playAnimation(std::string name, bool loop) 
{
	if (_curAnimation != name) 
	{
		_sprite3d->stopAllActions();
		if (loop)
			_curAnimation3d = RepeatForever::create(_action.at(name)->clone());
		else
			_curAnimation3d = _action.at(name)->clone();
		_sprite3d->runAction(_curAnimation3d);
		_curAnimation = name;
	}
};

//getter & setter
EnumRaceType Actor::getRaceType()
{
	return _racetype;
};

void Actor::setRaceType(EnumRaceType type)
{
	_racetype = type;
};

EnumStateType Actor::getStateType()
{
	return _statetype;
};

void Actor::setStateType(EnumStateType type)
{
	_statetype = type;
	//add puff particle
	if (_puff) {
		if (type == EnumStateType::WALKING)
			_puff->setEmissionRate(5);
		else
			_puff->setEmissionRate(0);
	}
};

void Actor::setTarget(Actor* target)
{
	if (_target != target)
		_target = target;
};

void Actor::setFacing(float degrees)
{
	_curFacing = DEGREES_TO_RADIANS(degrees);
	_targetFacing = _curFacing;
	this->setRotation(degrees);
};

bool Actor::getAIEnabled()
{
	return _AIEnabled;
};

void Actor::setAIEnabled(bool enable)
{
	_AIEnabled = enable;
};

int Actor::hurt(BasicCollider* collider, bool dirKnockMode)
{
    if (_isalive == true) {
		//TODO add sound effect
		float damage = collider->getDamage();
		bool critical = false;
		int knock = collider->getKnock();
		if (CCRANDOM_0_1() < collider->getCriticalChance()) {
			damage *= 1.5;
			critical = true;
			knock *= 2;
		}
		damage = damage + damage * CCRANDOM_MINUS1_1() * 0.15;
		damage -= _defense;
		damage = floor(damage);
		if (damage <= 0)
			damage = 1;

		_hp -= damage;
		if (_hp > 0) {
			if (collider->getKnock() && damage != 1) {
				knockMode(collider, dirKnockMode);
				hurtSoundEffects();
			}
			else
				hurtSoundEffects();
		}
		else {
			_hp = 0;
			_isalive = false;
			dyingMode(getPosTable(collider), knock);
		}
		auto blood = _hpCounter->showBloodLossNum(damage, this, critical);
		addEffect(blood);
		return damage;
	}
	return 0;
};

void Actor::hurtSoundEffects()
{
	//to override	
};

void Actor::normalAttackSoundEffects()
{
	//to override	
};

void Actor::specialAttackSoundEffects()
{
	//to override	
};

void Actor::playDyingEffects()
{
	//to override	
};


//attacking collision check
void Actor::normalAttack()
{
	BasicCollider::CreateWithPos(_myPos, _curFacing, _normalAttack);

};

void Actor::specialAttack()
{

};


//State Machine switching functions
void Actor::idleMode()
{

};

void Actor::walkMode()
{

};

void Actor::attackMode()
{

};

void Actor::knockMode(BasicCollider* collider, bool dirKnockMode)
{

};

void Actor::dyingMode(Actor* knockSource, int knockAmount)
{

};


//Base Update Functions
void Actor::stateMachineUpdate(float dt)
{

};

Actor* Actor::_findEnemy(EnumRaceType HeroOrMonster, bool &allDead)
{

};

bool Actor::_inRange() 
{

};


//AI function does not run every tick
void Actor::AI()
{

};

void Actor::baseUpdate(float dt)
{

};

void Actor::knockingUpdate(float dt)
{

};

void Actor::attackUpdate(float dt)
{

};

void Actor::walkUpdate(float dt) 
{

};

void Actor::movementUpdate(float dt)
{

};
