#include "Actor.h"
#include "BattleFieldUI.h"
#include "ParticleManager.h"
#include "Helper.h"
#include "Manager.h"
#include "HPCounter.h"
#include "MessageDispatchCenter.h"

bool Actor::init() 
{
	Node::init();
	this->setCascadeColorEnabled(true);

	//reset Actor
	_action.clear();
	copyData();

	//load HPCounter
	_hpCounter = HPCounter::create();
	addChild(_hpCounter);

	//load effectNode
	_effectNode = Node::create();
	_monsterHeight = 70;
	_heroHeight = 150;

	if (uiLayer != nullptr)
		currentLayer->addChild(_effectNode);
	return true;
}

void Actor::copyData()
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

	//Actor Default Values
	_racetype = EnumRaceType::HERO;
	_statetype = EnumStateType::IDLE;
	_radius = 50;
	_mass = 100;
	_shadowSize = 70;
	_maxhp = 1000;
	_defense = 100;
	_specialAttackChance = 0;
	_recoverTime = 0.8;
	_speed = 500;
	_turnSpeed = DEGREES_TO_RADIANS(225);
	_acceleration = 750;
	_decceleration = 750 * 1.7;
	_AIFrequency = 1.0;
	_attackFrequency = 0.01;
	_searchDistance = 5000;
	_attackRange = 100;
	_normalAttack = ActorDefaultValues._normalAttack;
}

void Actor::addEffect(Node* effect)
{
	//Play effect when being hurted
	effect->setPosition(ccpAdd(getPosTable(this), getPosTable(effect)));
	if (_racetype != EnumRaceType::MONSTER)
		effect->setPositionZ(this->getPositionZ() + _heroHeight);
	else
		effect->setPositionZ(this->getPositionZ() + _monsterHeight + effect->getPositionZ());
	effect->setCameraMask(2);
	currentLayer->addChild(effect);
}

void Actor::initShadow()
{
	_circle = Sprite::createWithSpriteFrameName("shadow.png");
	this->addChild(_circle);
	_circle->setScale(_shadowSize / 16);
	_circle->setOpacity(255 * 0.7);
	_sprite3d->setGlobalZOrder(0.01);
}

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
}

//getter & setter

float Actor::getHP()
{
	return _hp;
}

float Actor::getMaxHP()
{
	return _maxhp;
}

std::string Actor::getname()
{
	return _name;
}

ProgressTimer* Actor::getBloodBar()
{
	return _bloodBar;
}

ProgressTimer* Actor::getBloodBarClone()
{
	return _bloodBarClone;
}

Sprite* Actor::getAvatar()
{
	return _avatar;
}

void Actor::setname(std::string name)
{
	_name = name;
}

EnumRaceType Actor::getRaceType()
{
	return _racetype;
}

void Actor::setRaceType(EnumRaceType type)
{
	_racetype = type;
}

float Actor::getRadius() 
{
	return _radius;
}

float Actor::getMass() {
	return _mass;
}

EnumStateType Actor::getStateType()
{
	return _statetype;
}

void Actor::setStateType(EnumStateType type)
{
	_statetype = type;
}

void Actor::setTarget(Actor* target)
{
	if (_target != target)
		_target = target;
}

//rotate the actor
void Actor::setFacing(float degrees)
{
	_curFacing = DEGREES_TO_RADIANS(degrees);
	_targetFacing = _curFacing;
	this->setRotation(degrees);
}

bool Actor::getAIEnabled()
{
	return _AIEnabled;
}

//turn on/off AI machine
void Actor::setAIEnabled(bool enable)
{
	_AIEnabled = enable;
}

void Actor::setAngry(float angry) {
	_angry = angry;
}

float Actor::getAngry() {
	return _angry;
}

int Actor::getWeaponID()
{
	return _useWeaponId;
}

int Actor::getArmourID()
{
	return _useArmourId;
}

int Actor::getHelmetID()
{
	return _useHelmetId;
}

float Actor::getAngryMax() {
	return _angryMax;
}

bool Actor::isAlive() {
	return _isalive;
}

Actor* Actor::getTarget() {
	return _target;
}

Vec2 Actor::getMyPos() {
	return _myPos;
}

void Actor::setMyPos(Vec2 pos)
{
	_myPos = pos;
}

bool Actor::getGoRight()
{
	return _goRight;
}

void Actor::setGoRight(bool goRight)
{
	_goRight = goRight;
}


Node* Actor::getEffectNode() {
	return _effectNode;
}

float Actor::getSpecialAttackChance()
{
	return _specialAttackChance;
}

void Actor::setSpecialAttackChance(float chance)
{
	_specialAttackChance = 1;
}

//call the function when being hurted
float Actor::hurt(BasicCollider* collider, bool dirKnockMode)
{
	if (_isalive == true) {
		auto damage = collider->getDamage();
		auto critical = false;
		auto knock = collider->getKnock();

		//randomly generated critical attack
		if (CCRANDOM_0_1() < collider->getCriticalChance()) {
			damage *= 1.5;
			critical = true;
			knock *= 2;
		}

		//calculate the damage
		damage = damage + damage * CCRANDOM_MINUS1_1() * 0.15;
		damage -= _defense;
		damage = floor(damage);
		if (damage <= 0)
			damage = 1;
		_hp -= damage;

		if (_hp > 0) {	//if ailive
			if (collider->getKnock() && damage != 1) {
				knockMode(collider, dirKnockMode);
				hurtSoundEffects();
			}
			else
				hurtSoundEffects();
		}
		else {	// if dead
			_hp = 0;
			_isalive = false;
			dyingMode(getPosTable(collider), knock);
		}

		//add blood-loss effect
		auto blood = _hpCounter->showBloodLossNum(damage, this, critical);
		blood->setCameraMask(2);
		addEffect(blood);

		return damage;
	}
	return 0;
}

void Actor::hurtSoundEffects()
{
	//to override	
}

void Actor::normalAttackSoundEffects()
{
	//to override	
}

void Actor::specialAttackSoundEffects()
{
	//to override	
}

void Actor::playDyingEffects()
{
	//to override	
}


//attacking collision check
void Actor::normalAttack()
{
	BasicCollider::CreateWithPos(_myPos, _curFacing, _normalAttack);
	normalAttackSoundEffects();
}

void Actor::specialAttack()
{
	BasicCollider::CreateWithPos(_myPos, _curFacing, _specialAttack);
	specialAttackSoundEffects();
}


//state machine switching functions

//switch into idle mode
void Actor::idleMode()	
{
	setStateType(EnumStateType::IDLE);
	playAnimation("idle", true);
}

//switch into walk mode
void Actor::walkMode()
{
	setStateType(EnumStateType::WALKING);
	playAnimation("walk", true);
}

//switch into walk mode
void Actor::attackMode()	
{
	setStateType(EnumStateType::ATTACKING);
	playAnimation("idle", true);
	_attackTimer = _attackFrequency * 3 / 4;
}

//switch into knock mode
void Actor::knockMode(BasicCollider* collider, bool dirKnockMode)
{
	setStateType(EnumStateType::KNOCKING);
	playAnimation("knocked", false);
	_timeKnocked = _aliveTime;
	auto p = _myPos;
	auto angle = dirKnockMode?collider->getFacing():ccpToAngle(ccpSub(p, getPosTable(collider)));
	auto newPos = ccpRotateByAngle(ccpAdd(Vec2(collider->getKnock(), 0), p), p, angle);
	runAction(EaseCubicActionOut::create(MoveTo::create(_action.at("knocked")->getDuration() * 3, newPos)));
}

void Actor::dyingMode(Vec2 knockSource, int knockAmount)
{
	setStateType(EnumStateType::DEAD);
	playAnimation("dead", false);
	playDyingEffects();

	if (_racetype == EnumRaceType::HERO) {
		uiLayer->heroDead(this);

		//Erase the hero from HeroManager
		std::vector<Actor *>::iterator it = std::find(HeroManager.begin(), HeroManager.end(), this);
		HeroManager.erase(it);

		runAction(Sequence::create(DelayTime::create(3), 
			MoveBy::create(1.0, Vec3(0, 0, -50)), 
			RemoveSelf::create(), NULL));

		_angry = 0;
		struct MESSAGE_ANGRY_CHANGE angryChange = { _name, _angry, _angryMax };
		MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, this);		
	}
	else 
	{
		//Erase the hero from MonsterManager
		std::vector<Actor *>::iterator it = std::find(MonsterManager.begin(), MonsterManager.end(), this);
	    MonsterManager.erase(it);

		auto recycle = [&]() {
			setVisible(false);
			getPoolByName(_name).push_back(this);	
		};
		auto recycleShadow = [&]()
		{
			_circle->setVisible(false);
		};
		runAction(Sequence::create(DelayTime::create(3),
			CallFunc::create(recycleShadow),
			MoveBy::create(1.0, Vec3(0, 0, -50)),
			CallFunc::create(recycle), NULL));
	}

	if (knockAmount) {
		auto p = _myPos;
		auto angle = ccpToAngle(ccpSub(p, knockSource));
		auto newPos = ccpRotateByAngle(ccpAdd(Vec2(knockAmount, 0), p), p, angle);
		runAction(EaseCubicActionOut::create(MoveTo::create(_action.at("knocked")->getDuration() * 3, newPos)));
	}
	_AIEnabled = false;
}


//Base Update Functions
void Actor::stateMachineUpdate(float dt)
{
	auto state = getStateType();
	if (state == EnumStateType::WALKING)
		walkUpdate(dt);
	else if (state == EnumStateType::IDLE)
		;	//do nothing
	else if (state == EnumStateType::ATTACKING)
		attackUpdate(dt);
	else if (state == EnumStateType::DEFENDING)
		;	//trying to defend from an attack, so I need to finish my defending animation
	else if (state == EnumStateType::KNOCKING)
		knockingUpdate(dt);	//being knocked from an attack, so I need time to recover
	else if (state == EnumStateType::DYING)
		;	//I am dying.. Can you help me do something???

}

//find the closest enemy actor
Actor* Actor::findEnemy(EnumRaceType HeroOrMonster, bool &allDead)
{
	auto shortest = _searchDistance;
	allDead = true;
	Actor* target = nullptr;
	std::vector<Actor*>* manager;
	if (HeroOrMonster == EnumRaceType::MONSTER)
		manager = &HeroManager;
	else
		manager = &MonsterManager;
	for (auto val = manager->begin(); val != manager->end(); ++val) {
		auto temp = *val;
		auto dis = ccpDistance(_myPos, temp->_myPos);
		if (temp->_isalive) {
			if (dis < shortest) {
				shortest = dis;
				target = temp;
			}
			allDead = false;
		}
	}
	return target;
}

bool Actor::_inRange() 
{
	if (!_target)
		return false;
	else if (_target->_isalive) {
		auto attackDistance = _attackRange + _target->_radius - 1;
		auto p1 = _myPos;
		auto p2 = _target->_myPos;
		return (ccpDistance(p1, p2) < attackDistance);
	}
	return false;
}

//AI function(a FSM)
void Actor::AI()
{
	if (_isalive) {
		auto state = getStateType();
		bool allDead;
		_target = findEnemy(_racetype, allDead);

		//if I can find a target
		if (_target) {
			auto p1 = _myPos;
			auto p2 = _target->_myPos;
			_targetFacing = ccpToAngle(ccpSub(p2, p1));
			auto isInRange = _inRange();

			//if I'm (not attacking, or not walking) and my target is not in range
			if ((!_cooldown || state != EnumStateType::WALKING) && !isInRange) {
				walkMode();
				return;
			}
			//if I'm able to attack the enemy, why not attack him at once?
			else if (isInRange&&state != EnumStateType::ATTACKING) {
				attackMode();
				return;
			}
		}
        //I did not find a target, and I'm not attacking or not already idle
		else if (_statetype != EnumStateType::WALKING && _goRight == true) {
			walkMode();
			return;	
		}
		//So the only thing I can do is waiting...
		else if (!_cooldown || state != EnumStateType::IDLE) {
			idleMode();
			return;
		}
	}
}

void Actor::baseUpdate(float dt)
{
	_myPos = getPosTable(this);
	_aliveTime += dt;
	if (_AIEnabled) {
		_AITimer += dt;
		if (_AITimer > _AIFrequency) {
			_AITimer -= _AIFrequency;
			AI();
		}
	}
}

void Actor::knockingUpdate(float dt)
{
	if (_aliveTime - _timeKnocked > _recoverTime) {
		//I've recovered from a knock
		_timeKnocked = NULL;
		if (_inRange())
			attackMode();
		else
			walkMode();
	}
}

void Actor::attackUpdate(float dt)
{
	_attackTimer += dt;
	if (_attackTimer > _attackFrequency) {
		_attackTimer -= _attackFrequency;
		auto playIdle = [&]() {
			playAnimation("idle", true);
			_cooldown = false;
		};
		//time for an attack, which attack should I do ?
		float random_special = CCRANDOM_0_1();
		
		//Just create a normal attack
		if (random_special > _specialAttackChance) {
			auto createCol = [&]() {
				normalAttack();
			};
			auto attackAction = Sequence::create(_action.at("attack1")->clone(),
				CallFunc::create(createCol), _action.at("attack2")->clone(),
				CallFunc::create(playIdle), NULL);
			_sprite3d->stopAction(_curAnimation3d);
			_sprite3d->runAction(attackAction);
			_curAnimation = "attack1";
			_cooldown = true;
		}
		//create a special attack
		else {
			setCascadeColorEnabled(false);
			auto createCol = [&]() {
				specialAttack();
			};
			struct MESSAGE_SPECIAL_PERSPECTIVE messageParam = {0.2, _myPos, _specialSlowTime, this};
			MessageDispatchCenter::getInstance()->dispatchMessage(SPECIAL_PERSPECTIVE, this);
			auto attackAction = Sequence::create(_action.at("attack1")->clone(),
				CallFunc::create(createCol), _action.at("attack2")->clone(),
				CallFunc::create(playIdle), NULL);
			_sprite3d->stopAction(_curAnimation3d);
			_sprite3d->runAction(attackAction);
			_curAnimation = "specialAttack1";
			_cooldown = true;	
		}
	}
}

void Actor::walkUpdate(float dt) 
{
	//Walking state, switch to attack state when target in range
	if (_target && _target->_isalive) 
	{
		auto attackDistance = _attackRange + _target->_radius - 1;
		auto p1 = _myPos;
		auto p2 = _target->_myPos;
		_targetFacing = ccpToAngle(ccpSub(p2, p1));
		if (ccpDistance(p1, p2) < attackDistance)
			attackMode();
	}
	else {
		auto cur = this->getPosition();
		if (_goRight)
			_targetFacing = 0;
		else
			idleMode();
	}
}

void Actor::movementUpdate(float dt)
{
	//If my facing is incorrent, then rotate myself
	if (_curFacing != _targetFacing) {
		auto angleDt = _curFacing - _targetFacing;
		angleDt = angleDt - int(angleDt / (MATH_PIOVER2 * 4)) * (MATH_PIOVER2 * 4);
		auto turnleft = (angleDt - MATH_PIOVER2 * 2) < 0;
		auto turnby = _turnSpeed * dt;

		if (turnby > angleDt)
			_curFacing = _targetFacing;
		else if (turnleft)	//trun left
			_curFacing -= turnby;
		else //turn right
			_curFacing += turnby;
		setRotation(-RADIANS_TO_DEGREES(_curFacing));
	}

	//position update
	if (getStateType() != EnumStateType::WALKING)
		//If I am not walking, I need to slow down;
		_curSpeed = clampf(_curSpeed - _decceleration * dt, 0, _speed);
	else if (_curSpeed < _speed)
		//I am in walk mode, if I can speed up, then speed up
		_curSpeed = clampf(_curSpeed + _decceleration * dt, 0, _speed);
	if (_curSpeed > 0) {
		auto p1 = _myPos;
		auto targetPosition = ccpRotateByAngle(ccpAdd(Vec2(_curSpeed * dt, 0), p1), p1, _curFacing);
		setPosition(targetPosition);
	}
}
