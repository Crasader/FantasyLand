#include "Actor.h"

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
}

void Actor::addEffect(Sprite* effect)
{
	effect->setPosition(ccpAdd(getPosTable(this), getPosTable(effect)));
	if (_racetype != EnumRaceType::MONSTER)
		effect->setPositionZ(this->getPositionZ() + _heroHeight);
	else
		effect->setPositionZ(this->getPositionZ() + _heroHeight);
	currentLayer->addChild(effect);
}

void Actor::initPuff()
{
	auto puff = ParticleSystemQuad::create(ParticleManager::getInstance()->getPlistData("walkpuff"));
	//*** create(a string)

	//ParticleSystem should be BillboardParticleSystem;
	auto puffFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("walkingPuff.png");
	puff->setTextureWithRect(puffFrame->getTexture(), puffFrame->getRect());
	puff->setScale(1.5);
	puff->setGlobalZOrder(-getPositionZ() + FXZorder);
	puff->setPositionZ(10);
	_puff = puff;
	_effectNode->addChild(puff);
}

void Actor::initShadow()
{
	_circle = Sprite::createWithSpriteFrameName("shadow.png");
	//use Shadow size for aesthetic, use radius to see collision size
	_circle->setScale(_shadowSize / 16);
	_circle->setOpacity(255 * 0.7);
	this->addChild(_circle);
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
EnumRaceType Actor::getRaceType()
{
	return _racetype;
}

void Actor::setRaceType(EnumRaceType type)
{
	_racetype = type;
}

int Actor::getRadius() 
{
	return _radius;
}

EnumStateType Actor::getStateType()
{
	return _statetype;
}

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
}

void Actor::setTarget(Actor* target)
{
	if (_target != target)
		_target = target;
}

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

void Actor::setAIEnabled(bool enable)
{
	_AIEnabled = enable;
}

void Actor::setAngry(int angry) {
	_angry = angry;
}

int Actor::getAngry() {
	return _angry;
}

int Actor::getAngryMax() {
	return _angryMax;
}

bool Actor::isAlive() {
	return _isalive;
}

Vec2 Actor::getMyPos() {
	return _myPos;
}

int Actor::hurt(BasicCollider* collider, bool dirKnockMode = false)
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


//State Machine switching functions
void Actor::idleMode()
{
	setStateType(EnumStateType::IDLE);
	playAnimation("idle", true);
}

void Actor::walkMode()
{
	setStateType(EnumStateType::WALKING);
	playAnimation("walk", true);
}

void Actor::attackMode()
{
	setStateType(EnumStateType::ATTACKING);
	playAnimation("idle", true);
	_attackTimer = _attackFrequency * 3 / 4;
}

void Actor::knockMode(BasicCollider* collider, bool dirKnockMode)
{
	setStateType(EnumStateType::KNOCKING);
	playAnimation("knocked", false);
	_timeKnocked = _aliveTime;
	auto p = _myPos;
	float angel = dirKnockMode ? collider->getFacing() : ccpToAngle(ccpSub(p, getPosTable(collider)));
	//****** getPosTable should return a Vec2 type.
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
		//自己修改的Erase，下面还有一个
		std::vector<Actor*>::iterator it = std::find(HeroManager.begin(), HeroManager.end(), this);
		HeroManager.erase(it);

		runAction(Sequence::create(DelayTime::create(3), 
			MoveBy::create(1.0, Vec3(0, 0, -50)), 
			RemoveSelf::create(), NULL));
		_angry = 0;

		//AUTO???!!!
		auto angryChange = { _name, _angry, _angryMax };
		MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, angryChange);
    //CallFunc::create(recycle)
	}
	else {
		std::vector<Actor*>::iterator it = std::find(HeroManager.begin(), HeroManager.end(), this);
		HeroManager.erase(it);

		auto recycle = [&]() {
			setVisible(false);
			getPoolByName(_name).push_back(this);
			//List.pushlast(getPoolByName(_name), self);
			
		};
		runAction(Sequence::create(DelayTime::create(3),
			MoveBy::create(1.0, Vec3(0, 0, -50)),
			CallFunc::create(recycle), NULL));
	}

	if (knockAmount) {
		auto p = _myPos;
		auto angle = ccpToAngle(ccpSub(p, knockSource));
		auto newPos = ccpRotateByAngle(ccpAdd(Vec2(knockAmount, 0), p), p, angle);
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
		;
	//do nothing
	else if (state == EnumStateType::ATTACKING)
		//I am attacking someone, I probably has a target
		attackUpdate(dt);
	else if (state == EnumStateType::DEFENDING)
		;
		//I am trying to defend form an attack, I need to finish my defending animation
		//TODO: update for defending
	else if (state == EnumStateType::KNOCKING)
		knockingUpdate(dt);
	//I got knocked from an attack, I need time to recover
	else if (state == EnumStateType::DYING)
		;
		//I am dying.. there is not much I can do right?

}

Actor* Actor::_findEnemy(EnumRaceType HeroOrMonster, bool &allDead)
{
	auto shortest = _searchDistance;
	allDead = true;
	Actor* target = NULL;
	std::list<Actor*>* manager;
	//error in delaration in Manager.h
	//if (HeroOrMonster == EnumRaceType::MONSTER)
		//manager = &HeroManager;
	//else
		//manager = &MonsterManager;
	for (auto val = manager->begin(); val != manager->end(); val++) {
		auto temp = *val;
		float dis = ccpDistance(_myPos, temp->_myPos);
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
}


//AI function does not run every tick
void Actor::AI()
{
	if (_isalive) {
		auto state = getStateType();
		bool allDead;
		_target = _findEnemy(_racetype, &allDead);
		//if I can find a target
		if (_target) {
			auto p1 = _myPos;
			auto p2 = _target->_myPos;
			_targetFacing = ccpAngle(ccpSub(p2, p1));
			auto isInRange = _inRange();
			//if I'm (not attacking, or not walking) and my target is not in range
			if ((!_cooldown || state != EnumStateType::WALKING) && !isInRange) {
				walkMode();
				return;
			}
			else if (isInRange&&state != EnumStateType::ATTACKING) {
				attackMode();
				return;
				//else
				//Since im attacking, i cant just switch to another mode immediately
				//print(self._name, "says : what should I do?", self._statetype)	
			}
		}
		else if (_statetype != EnumStateType::WALKING && _goRight == true) {
			walkMode();
			return;
			//I did not find a target, and I'm not attacking or not already idle
		}
		else if (!_cooldown || state != EnumStateType::IDLE) {
			idleMode();
			return;
		}
	}
	else
		;//logic when I'm dead
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
		if (random_special > _specialAttackChance) {
			auto createCol = [&]() {
				normalAttack();
			};
			auto attackAction =Sequence::create(_action.at("attack1")->clone(), 
				CallFunc::create(createCol), _action.at("attack2")->clone(),
				CallFunc::create(playIdle), NULL);
			_sprite3d->stopAction(_curAnimation3d);
			_sprite3d->runAction(attackAction);
			_curAnimation = attackAction;
			_cooldown = true;
		}
		else {
			setCascadeColorEnabled(false);
			auto createCol = [&]() {
				specialAttack();
			};
			auto messageParam = {0.2, _myPos, _specialSlowTime, this};
			//speed = 0.2, pos = self._myPos, dur= self._specialSlowTime , target=self
			MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::SPECIAL_PERSPECTIVE, messageParam);
			auto attackAction = Sequence::create(_action.at("specialattack1")->clone(),
				CallFunc::create(createCol), _action.at("specialattack2")->clone(),
				CallFunc::create(playIdle), NULL);
			_sprite3d->stopAction(_curAnimation3d);
			_sprite3d->runAction(attackAction);
			_curAnimation = attackAction;
			_cooldown = true;	
		}
	}
}

void Actor::walkUpdate(float dt) 
{
	//Walking state, switch to attack state when target in range
	if (_target&&_target->_isalive) {
		auto attackDistance = _attackRange + _target->_radius - 1;
		auto p1 = _myPos;
		auto p2 = _target->_myPos;
		_targetFacing = ccpToAngle(ccpSub(p2, p1));
		if (ccpDistance(p1, p2) < attackDistance)
			attackMode();
	}
	else {
		Vec2 cur = this->getPosition();
		if (_goRight)
			_targetFacing = 0;
		else
			idleMode();
	}
}

void Actor::movementUpdate(float dt)
{
	if (_curFacing != _targetFacing) {
		auto angleDt = _curFacing - _targetFacing;
		angleDt = angleDt - int(angleDt / (MATH_PIOVER2 * 4)) * (MATH_PIOVER2 * 4);
		bool turnleft = (angleDt - MATH_PIOVER2 * 2) < 0;
		float turnby = _turnSpeed*dt;

		//right
		if (turnby > angleDt)
			_curFacing = _targetFacing;
		else if (turnleft)
			_curFacing -= turnby;
		else //left
			_curFacing += turnby;
	}
	//position update
	if (getStateType() != EnumStateType::WALKING)
		//If I am not walking, I need to slow down;
		_curSpeed = clampf(_curSpeed - _decceleration*dt, 0, _speed);
	else if (_curSpeed < _speed)
		//I am in walk mode, if I can speed up, then speed up
		_curSpeed = clampf(_curSpeed + _decceleration*dt, 0, _speed);
	if (_curSpeed > 0) {
		Vec2 p1 = _myPos;
		Vec2 targetPosition = ccpRotateByAngle(ccpAdd(Vec2(_curSpeed*dt, 0), p1), p1, _curFacing);
		setPosition(targetPosition);
	}
}
