﻿#include "AttackCommand.h"

std::vector<BasicCollider*> AttackManager;

void solveAttacks(float dt)
{
	for (auto val = AttackManager.rend(); val != AttackManager.rbegin(); ++val) {
		BasicCollider* attack = AttackManager(val);
		Vec2 apos = getPosTable(attack);
		if (attack->getMask() == EnumRaceType::HERO) {
			//if heroes attack, then lets check monsters
			for (auto mkey = MonsterManager.rend(), MonsterManager.rbegin(), ++mkey) {
				//check distance first
				Actor* monster = MonsterManager(mkey);
				Vec2 mpos = monster->_myPos;
				auto dist = ccpDistance(apos, mpos);
				if (dist < (attack->getMaxRange() + monster->getRadius) && (dist > attack->getMinRange())) {
					//range test passed, now angle test
					auto angle = radNormalize(ccpToAngle(ccpSub(mpos, apos)));
					auto afacing = radNormalize(attack->getFacing());
					if (afacing + attack->getAngle() / 2 > angle && angle > afacing - attack->getAngle() / 2)
						attack->onCollide(monster);
				}
			}
		}
		else if (attack->getMask() == EnumRaceType::MONSTER) {
			//if heroes attack, then lets check monsters
			for (auto hkey = HeroManager.rend(), HeroManager.rbegin(), ++hkey) {
				//check distance first
				Actor* hero = HeroManager(hkey);
				Vec2 hpos = hero->_myPos;
				auto dist = ccpDistance(getPosTable(attack), hpos);
				if (dist < (attack->getMaxRange() + hero->getRadius) && (dist > attack->getMinRange())) {
					//range test passed, now angle test
					auto angle = radNormalize(ccpToAngle(ccpSub(hpos, getPosTable(attack)));
					auto afacing = radNormalize(attack->getFacing());
					if (afacing + attack->getAngle() / 2 > angle && angle > afacing - attack->getAngle() / 2)
						attack->onCollide(hero);
				}
			}
		}
		attack->setCurDuration(attack->getDuration() + dt);
		if (attack->getCurDuration > attack->getDuration()) {
			attack->onTimeOut();
			AttackManager.erase(val);
		}
		else attack->onUpdate();
	}
}

BasicCollider::BasicCollider()
{
	setCascadeColorEnabled(true);
}

BasicCollider* BasicCollider::CreateWithPos(Vec2 pos, int facing, struct attackInfo)
{
	BasicCollider* newBasicCollider = BasicCollider::create();
	newBasicCollider->_minRange = 0;	//the min radius of the fan
	newBasicCollider->_maxRange = 150;	//the max radius of the fan
	newBasicCollider->_angle = 120;	//arc of attack, in radians
	newBasicCollider->_knock = 150;	//default knock, knocks 150 units
	newBasicCollider->_mask = 1;	//1 is Heroes, 2 is enemy, 3 ? ?
	newBasicCollider->_damage = 100;
	newBasicCollider->_facing = 0;	//this is radians
	newBasicCollider->_duration = 0;
	newBasicCollider->_curDuration = 0;
	newBasicCollider->_speed = 0;	//travel speed
	newBasicCollider->_criticalChance = 0;
	newBasicCollider->initData(pos, facing, attackInfo);
	return newBasicCollider;
}

//callback when the collider has being solved by the attack manager,
//make sure you delete it from node tree
//if say you have an effect attached to the collider node.
bool BasicCollider::init()
{
	return true;
}

void BasicCollider::onTimeOut()
{
    this->removeFromParent();
}

void BasicCollider::playHitAudio()
{
	experimental::AudioEngine::play2d(CommonAudios.hit, false, 0.7);
}

void BasicCollider::hurtEffect(Actor* target)
{
	auto hurtAction = Animate::create(animationCache->getAnimation("hurtAnimation"));
	auto hurtEffect = BillBoard::create();
	hurtEffect->setScale(1.5);
	hurtEffect->runAction(Sequence::create(hurtAction, RemoveSelf::create()));
	hurtEffect->setPosition3D(Vec3(0, 0, 50));
	target->addChild(hurtEffect);
}

void BasicCollider::onCollide(Actor* target)
{
	hurtEffect(target);
	playHitAudio();
	target->hurt(this);
}

void BasicCollider::onUpdate()
{
	//implement this function if this is a projectile
}

void BasicCollider::initData(Vec2 pos, int facing, std::string attackInfo)
{
	copyTable(attackInfo, this);
    
	_facing = facing | _facing;
	setPosition(pos);
	AttackManager.insert(AttackManager.end(), this);
	currentLayer->addChild(this, -10);
}

void BasicCollider::setDamage(int damage) {
	_damage = damage;
}

int BasicCollider::getDamage() {
	return _damage;
}

void BasicCollider::setKnock(int knock) {
	_knock = knock;
}

int BasicCollider::getKnock() {
	return _knock;
}

void BasicCollider::setCriticalChance(float criticalChance) {
	_criticalChance = criticalChance;
}

float BasicCollider::getCriticalChance() {
	return _criticalChance;
}

void BasicCollider::setFacing(int facing) {
	_facing = facing;
}

int BasicCollider::getFacing() {
	return _facing;
}

int BasicCollider::getMask() {
	return _mask;
}

int BasicCollider::getMaxRange() {
	return _maxRange;
}

int BasicCollider::getMinRange() {
	return _minRange;
}

float BasicCollider::getAngle() {
	return _angle;
}

float BasicCollider::getDuration() {
	return _duration;
}

float BasicCollider::getCurDuration() {
	return _curDuration;
}

void BasicCollider::setCurDuration(float curDuration) {
	_curDuration = curDuration;
	
}

KnightNormalAttack::KnightNormalAttack()
{

}

KnightNormalAttack* KnightNormalAttack::CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* knight)
{
	KnightNormalAttack* newKnightNormalAttack = KnightNormalAttack::create();
    newKnightNormalAttack->initData(pos, facing, attackInfo);
	newKnightNormalAttack->_owner = knight;
	return newKnightNormalAttack;
};

bool KnightNormalAttack::init()
{
	return true;
}

void KnightNormalAttack::onTimeOut()
{
	removeFromParent();
}

MageNormalAttack::MageNormalAttack()
{

}

MageNormalAttack* MageNormalAttack::CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* target, Actor* owner)
{
	MageNormalAttack* newMageNormalAttack = MageNormalAttack::create();
	newMageNormalAttack->initData(pos, facing, attackInfo);
	newMageNormalAttack->_target = target;
	newMageNormalAttack->_owner = owner;
	newMageNormalAttack->_sp = BillBoard::create("FX/FX.png", RECTS::iceBolt, 0);
	
	newMageNormalAttack->setPosition3D(Vec3(0, 0, 50));
	newMageNormalAttack->setScale(2);
	newMageNormalAttack->addChild(newMageNormalAttack->_sp);

	auto smoke = ParticleSystemQuad::create(ParticleManager::getInstance()->getPlistData("iceTrail"));
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("puff.png");
	smoke->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	smoke->setScale(2);
	newMageNormalAttack->addChild(smoke);
	smoke->setRotation3D(Vec3(90, 0, 0));
	smoke->setGlobalZOrder(-newMageNormalAttack->getPositionY() * 2 + FXZorder);
	smoke->setPositionZ(50);

	auto pixi = ParticleSystemQuad::create(ParticleManager::getInstance()->getPlistData("pixi"));
	auto pixif = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	pixi->setTextureWithRect(pixif->getTexture(), pixif->getRect());
	pixi->setScale(2);
	newMageNormalAttack->addChild(pixi);
	pixi->setRotation3D(Vec3(90, 0, 0));
	pixi->setGlobalZOrder(-newMageNormalAttack->getPositionY() * 2 + FXZorder);
	pixi->setPositionZ(50);

	newMageNormalAttack->_part1 = smoke;
	newMageNormalAttack->_part2 = pixi;
	return newMageNormalAttack;
}

bool MageNormalAttack::init()
{
	return true;
}

void MageNormalAttack::onTimeOut()
{
	_part1->stopSystem();
	_part2->stopSystem();
	runAction(Sequence::create(DelayTime::create(1), RemoveSelf::create()));

	auto magic = ParticleSystemQuad::create(ParticleManager::getInstance()->getPlistData("magic"));
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	magic->setScale(1.5);
	magic->setRotation3D(Vec3(90, 0, 0));
	addChild(magic);
	magic->setGlobalZOrder(-getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);

	_sp->getTextureRect(RECTS::iceSpike);
	_sp->runAction(FadeOut::create(1));
	_sp->setScale(4);
}

void MageNormalAttack::playHitAudio()
{
	experimental::AudioEngine::play2d(MageProperty.ice_normalAttackHit, false, 1);

}

void MageNormalAttack::onCollide(Actor* target)
{
	hurtEffect(target);
	playHitAudio();
	_owner->setAngry(_owner->getAngry() + target->hurt(this) * 0.3);
	auto anaryChange = (MageValues._name, _owner->getAngry(), _owner->getAngryMax());
    MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, anaryChange);
	//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration++;
};

void MageNormalAttack::onUpdate(float dt)
{
	Vec2 nextPos;
	if (_target && _target->isAlive()) {
		Vec2 selfPos = getPosTable(this);
		Vec2 tpos = _target->getMyPos();
		float angle = ccpToAngle(ccpSub(tpos, selfPos));
		nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, angle);
	}
	else {
		Vec2 selfPos = getPosTable(this);
		nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	}
};

MageIceSpikes::MageIceSpikes()
{
};

void MageIceSpikes::CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* owner)
{
	MageIceSpikes* ret = MageIceSpikes::create();
	ret->initData(pos, facing, attackInfo);
	ret->_owner = owner;
	ret->_sp = Sprite::createWithSpriteFrameName("shadow.png");
	ret->_sp->setGlobalZOrder(-ret->getPositionY() + FXZorder);
	ret->_sp->setOpacity(100);
	ret->setPosition3D(Vec3(0, 0, 1));
	ret->setScale(ret->getMaxRange() / 12);
	ret->addChild(ret->_sp);

	//create 3 spikes
	auto x = Node::create();
	ret->_spikes = x;
	ret->addChild(x);
	for (int var = 0; var <= 10; var++) {
		int rand = CCRANDOM_0_1() * 3;
		auto spike = Sprite::createWithSpriteFrameName("iceSpike" + Value(rand).asString() + ".png");
		spike->setAnchorPoint(Vec2(0.5, 0));
		spike->setRotation3D(Vec3(90, 0, 0));
		x->addChild(spike);
		if (rand == 3)
			spike->setScale(1.5);
		else
			spike->setScale(2);
		spike->setOpacity(165);
		spike->setFlippedX(!(floor(CCRANDOM_0_1() * 2)));




	}
};

bool MageIceSpikes::init()
{

};

void MageIceSpikes::onTimeOut()
{

};

void MageIceSpikes::playHitAudio()
{

};

void MageIceSpikes::onUpdate(float dt)
{

};

ArcherNormalAttack::ArcherNormalAttack()
{

};

void ArcherNormalAttack::CreateWithPos(Vec3 pos, int facing, std::string attackInfo, Actor* owner)
{

};

bool ArcherNormalAttack::init()
{

};

void ArcherNormalAttack::onTimeOut()
{

};

void ArcherNormalAttack::onCollide(Actor* target)
{

};

void ArcherNormalAttack::onUpdate(float dt)
{

};

ArcherSpecialAttack::ArcherSpecialAttack()
{

};

void ArcherSpecialAttack::CreateWithPos(Vec3 pos, int facing, std::string attackInfo, Actor* owner)
{

};

bool ArcherSpecialAttack::init()
{

};

void ArcherSpecialAttack::onTimeOut()
{

};

void ArcherSpecialAttack::onCollide(Actor* target)
{

};

void ArcherSpecialAttack::onUpdate(float dt)
{

};

Nova::Nova()
{

}; 

void Nova::CreateWithPos(Vec3 pos, int facing)
{

};

bool Nova::init()
{

};

void Nova::onTimeOut()
{

};

void Nova::onCollide(Actor* target)
{

};

void Nova::onUpdate(float dt)
{

};

DragonAttack::DragonAttack()
{

};

void DragonAttack::CreateWithPos(Vec3 pos, int facing, std::string attackInfo)
{

};

bool DragonAttack::init()
{

};

void DragonAttack::onTimeOut()
{

};

void DragonAttack::playHitAudio()
{

};

void DragonAttack::onCollide(Actor* target)
{

};

void DragonAttack::onUpdate(float dt)
{

};

BossNormal::BossNormal()
{

};

void BossNormal::CreateWithPos(Vec3 pos, int facing, std::string attackInfo)
{

};

bool BossNormal::init()
{

};

void BossNormal::onTimeOut()
{

};

void BossNormal::playHitAudio()
{

};

void BossNormal::onCollide(Actor* target)
{

};

void BossNormal::onUpdate(float dt)
{

};

BossSuper::BossSuper()
{

};

void BossSuper::CreateWithPos(Vec3 pos, int facing, std::string attackInfo)
{

};

bool BossSuper::init()
{

};

void BossSuper::onTimeOut()
{

};

void BossSuper::playHitAudio()
{

};

void BossSuper::onCollide(Actor* target)
{

};

void BossSuper::onUpdate(float dt)
{

};