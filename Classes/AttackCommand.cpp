#include "AttackCommand.h"
#include "Actor.h"
#include "ParticleManager.h"
#include "Manager.h"
#include "AudioEngine.h"
#include "Archer.h"
#include "MessageDispatchCenter.h"

std::vector<BasicCollider*> AttackManager;

void solveAttacks(float dt)
{
	//for (auto val = AttackManager.begin(); val != AttackManager.end() && AttackManager.size() != 0; ++val) {
	for (int i = AttackManager.size() - 1; i >= 0; --i) {
		//if (AttackManager[i] == nullptr) continue;
		auto attack = AttackManager[i];
		auto apos = getPosTable(attack);
		if (attack->getMask() == EnumRaceType::HERO) {
			//if heroes attack, then lets check monsters
			int mmSize = MonsterManager.size();
			if (mmSize >= 1)
			for (int j = mmSize - 1; j >= 0; --j) {
			//for (auto mkey = MonsterManager.rbegin(); mkey != MonsterManager.rend(); ++mkey) {
				//check distance first
				auto monster = MonsterManager[j];
				Vec2 mpos = monster->getMyPos();
				auto dist = ccpDistance(apos, mpos);
				if (dist < (attack->getMaxRange() + monster->getRadius()) && (dist > attack->getMinRange())) {
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
			int hmSize = HeroManager.size();
			if (hmSize >= 1)
			for (int k = hmSize - 1; k >= 0; --k) {
			//for (auto hkey = HeroManager.end(); hkey != HeroManager.begin(); --hkey) {
				//check distance first
				auto hero = HeroManager[k];
				Vec2 hpos = hero->getMyPos();
				auto dist = ccpDistance(getPosTable(attack), hpos);
				if (dist < (attack->getMaxRange() + hero->getRadius()) && (dist > attack->getMinRange())) {
					//range test passed, now angle test
					auto angle = radNormalize(ccpToAngle(ccpSub(hpos, getPosTable(attack))));
					auto afacing = radNormalize(attack->getFacing());
					if (afacing + attack->getAngle() / 2 > angle && angle > afacing - attack->getAngle() / 2)
						attack->onCollide(hero);
				}
			}
		}
		attack->setCurDuration(attack->getCurDuration() + dt);
		if (attack->getCurDuration() > attack->getDuration()) {
			attack->onTimeOut();
			//AttackManager.erase(val);
			AttackManager.erase(AttackManager.begin() + i);
		}
		else
			attack->onUpdate(dt);
	}
}

BasicCollider::BasicCollider()
{
	_minRange = 0;	//the min radius of the fan
	_maxRange = 150;	//the max radius of the fan
	_angle = 120;	//arc of attack, in radians
	_knock = 150;	//default knock, knocks 150 units
	_mask = 1;	//1 is Heroes, 2 is enemy, 3 ? ?
	_damage = 100;
	_facing = 0;	//this is radians
	_duration = 0;
	_curDuration = 0;
	_speed = 0;	//travel speed
	_criticalChance = 0;

	
}

BasicCollider* BasicCollider::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo)
{
	BasicCollider* newBasicCollider = BasicCollider::create();
	//newBasicCollider->_minRange = 0;	//the min radius of the fan
	//newBasicCollider->_maxRange = 150;	//the max radius of the fan
	//newBasicCollider->_angle = 120;	//arc of attack, in radians
	//newBasicCollider->_knock = 150;	//default knock, knocks 150 units
	//newBasicCollider->_mask = 1;	//1 is Heroes, 2 is enemy, 3 ? ?
	//newBasicCollider->_damage = 100;
	//newBasicCollider->_facing = 0;	//this is radians
	//newBasicCollider->_duration = 0;
	//newBasicCollider->_curDuration = 0;
	//newBasicCollider->_speed = 0;	//travel speed
	//newBasicCollider->_criticalChance = 0;
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
	hurtEffect->runAction(Sequence::create(hurtAction, RemoveSelf::create(), NULL));
	hurtEffect->setPosition3D(Vec3(0, 0, 50));
	//hurtEffect->setCameraMask(2);
	target->addChild(hurtEffect);
	log("Animation played");
}

void BasicCollider::onCollide(Actor* target)
{
	hurtEffect(target);
	playHitAudio();
	target->hurt(this);
}

void BasicCollider::onUpdate(float dt)
{
	//implement this function if this is a projectile
}

void BasicCollider::initData(Vec2 pos, float facing, struct attack_d attackInfo)
{
	setCascadeColorEnabled(true);
	_minRange = attackInfo.minRange;
	_maxRange = attackInfo.maxRange;
	_angle = attackInfo.angle;
	_knock = attackInfo.knock;
	_damage = attackInfo.damage;
	_mask = attackInfo.mask;
	_duration = attackInfo.duration;
	_speed = attackInfo.speed;
	_criticalChance = attackInfo.criticalChance;
	_DOTTimer = attackInfo.DOTTimer;
	_curDOTTime = attackInfo.curDOTTime;
	_DOTApplied = attackInfo.DOTApplied;
	if (facing != 0)
		_facing = facing;
	AttackManager.push_back(this);	
	setPosition(pos);
    currentLayer->addChild(this, 100);
	this->setGlobalZOrder(100);

	//_spritey = Sprite::create("img.jpg");
	//currentLayer->addChild(this);
	//this->addChild(_spritey);
	//_spritey->setCameraMask(2);
	//_spritey->setPosition3D(Vec3(0,0,0));
}

void BasicCollider::setDamage(float damage) {
	_damage = damage;
}

float BasicCollider::getDamage() {
	return _damage;
}

void BasicCollider::setKnock(float knock) {
	_knock = knock;
}

float BasicCollider::getKnock() {
	return _knock;
}

void BasicCollider::setCriticalChance(float criticalChance) {
	_criticalChance = criticalChance;
}

float BasicCollider::getCriticalChance() {
	return _criticalChance;
}

void BasicCollider::setFacing(float facing) {
	_facing = facing;
}

float BasicCollider::getFacing() {
	return _facing;
}

int BasicCollider::getMask() {
	return _mask;
}

float BasicCollider::getMaxRange() {
	return _maxRange;
}

float BasicCollider::getMinRange() {
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

KnightNormalAttack* KnightNormalAttack::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* knight)
{
	auto newKnightNormalAttack = KnightNormalAttack::create();
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

MageNormalAttack* MageNormalAttack::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* target, Actor* owner)
{
	auto newMageNormalAttack = MageNormalAttack::create();
	newMageNormalAttack->initData(pos, facing, attackInfo);
	newMageNormalAttack->_target = target;
	newMageNormalAttack->_owner = owner;
	newMageNormalAttack->_sp = BillBoard::create("FX/FX.png", RECTS.iceBolt);
	newMageNormalAttack->_sp->setCameraMask(2);
	//owner->addChild(newMageNormalAttack);	
	newMageNormalAttack->_sp->setPosition3D(Vec3(0, 0, 50));
	newMageNormalAttack->_sp->setScale(2);
	newMageNormalAttack->addChild(newMageNormalAttack->_sp);



	auto pm = ParticleManager::getInstance()->getPlistData("iceTrail");
	auto smoke = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("puff.png");
	smoke->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	smoke->setScale(2);
	//smoke->setCameraMask(996);
	newMageNormalAttack->addChild(smoke);
	smoke->setRotation3D(Vec3(90, 0, 0));
	smoke->setGlobalZOrder(-newMageNormalAttack->getPositionY() * 2 + FXZorder);
	smoke->setPositionZ(50);

	auto pmf = ParticleManager::getInstance()->getPlistData("pixi");
	auto pixi = ParticleSystemQuad::create(pmf);
	auto pixif = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	pixi->setTextureWithRect(pixif->getTexture(), pixif->getRect());
	pixi->setScale(2);
	pixi->addChild(smoke);
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
	runAction(Sequence::create(DelayTime::create(1), RemoveSelf::create(), NULL));
	auto pm = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	magic->setScale(1.5);
	magic->setRotation3D(Vec3(90, 0, 0));
	addChild(magic);
	magic->setGlobalZOrder(-getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);

	_sp->setTextureRect(RECTS.iceSpike);
	//_sp->setCameraMask(943);
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
	struct MESSAGE_ANGRY_CHANGE angryChange = { MageValues._name, _owner->getAngry(), _owner->getAngryMax() };
	MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, _owner);
	//    _owner->MDC->dispatchMessage(MessageType::ANGRY_CHANGE, angryChange);
		//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration++;
}

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
	setPosition(nextPos);
}

MageIceSpikes::MageIceSpikes()
{

}

MageIceSpikes* MageIceSpikes::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner)
{
	auto ret = MageIceSpikes::create();
	ret->initData(pos, facing, attackInfo);
	ret->_owner = owner;
	ret->_sp = Sprite::createWithSpriteFrameName("shadow.png");
	ret->_sp->setGlobalZOrder(-ret->getPositionY() + FXZorder);
	ret->_sp->setOpacity(100);
	ret->_sp->setCameraMask(2);
	ret->_sp->setPosition3D(Vec3(0, 0, 1));
	ret->_sp->setScale(ret->getMaxRange() / 12);
	ret->addChild(ret->_sp);

	//create 3 spikes
	auto x = Node::create();
	ret->_spikes = x;
	ret->addChild(x);
	for (int var = 0; var <= 10; var++) {
		int rand = CCRANDOM_0_1() * 3 + 1;
		std::string spriteFrameName = Value("iceSpike").asString() + Value(rand).asString() + Value(".png").asString();
		auto spike = Sprite::createWithSpriteFrameName(spriteFrameName);
		spike->setAnchorPoint(Vec2(0.5, 0));
		spike->setRotation3D(Vec3(90, 0, 0));
		x->addChild(spike);
		if (rand == 3)
			spike->setScale(1.5);
		else
			spike->setScale(2);
		spike->setOpacity(165);
		spike->setFlippedX(!(floor(CCRANDOM_0_1() * 2)));
		spike->setPosition3D(Vec3(CCRANDOM_MINUS1_1()*ret->getMaxRange() / 1.5,
			CCRANDOM_MINUS1_1()*ret->getMaxRange() / 1.5, 1));
		spike->setGlobalZOrder(-ret->getPositionY() - spike->getPositionY() + FXZorder);
		x->setScale(0);
		x->setPositionZ(-210);
	}
	x->runAction(EaseBackOut::create(MoveBy::create(0.3, Vec3(0, 0, 200))));
	x->runAction(EaseBounceOut::create(ScaleTo::create(0.4, 1)));
	auto pm = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	//magic->setCameraMask(943);
	magic->setScale(1.5);
	ret->addChild(magic);
	magic->setGlobalZOrder(-ret->getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);

	return ret;
}

bool MageIceSpikes::init()
{

	return true;
}

void MageIceSpikes::onTimeOut()
{
	_spikes->setVisible(false);
	auto pm = ParticleManager::getInstance()->getPlistData("puffRing");
	auto puff = ParticleSystemQuad::create(pm);
	// puff = ParticleSystemQuad : create("FX/puffRing.plist")
	auto puffFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("puff.png");
	puff->setTextureWithRect(puffFrame->getTexture(), puffFrame->getRect());
	puff->setCameraMask(2);
	puff->setScale(3);
	addChild(puff);
	puff->setGlobalZOrder(-getPositionY() + FXZorder);
	puff->setPositionZ(20);

	auto pmf = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pmf);
	// puff = ParticleSystemQuad : create("FX/puffRing.plist")
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	magic->setCameraMask(2);
	//magic->setCamera(camera);
	magic->setScale(1.5);
	addChild(magic);
	puff->setGlobalZOrder(-getPositionY() + FXZorder);
	puff->setPositionZ(0);
}

void MageIceSpikes::playHitAudio()
{

}

void MageIceSpikes::onCollide(Actor* target)
{
	if (_curDOTTime >= _DOTTimer) {
		hurtEffect(target);
		playHitAudio();
		//	_owner->setAngry(_owner->getAngry() + target->hurt(this, true) * 0.3);
		struct MESSAGE_ANGRY_CHANGE  angryChange = { ArcherValues._name, _owner->getAngry(), _owner->getAngryMax() };
		MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, _owner);
		//		_owner->MDC->dispatchMessage(MessageType::ANGRY_CHANGE, angryChange);
		_DOTApplied = true;
	}
}

void MageIceSpikes::onUpdate(float dt)
{
	//implement this function if this is a projectile
	_curDOTTime += dt;
	if (_DOTApplied) {
		_DOTApplied = false;
		_curDOTTime = 0;
	}
}

ArcherNormalAttack::ArcherNormalAttack()
{

}

ArcherNormalAttack* ArcherNormalAttack::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner)
{
	auto ret = ArcherNormalAttack::create();
	ret->initData(pos, facing, attackInfo);
	ret->_owner = owner;
	ret->_sp = Archer::createArrow();
	
	ret->addChild(ret->_sp);
	ret->_sp->setRotation(RADIANS_TO_DEGREES(-facing) - 90);
	ret->_sp->setCameraMask(2);

	return ret;
}

bool ArcherNormalAttack::init()
{
	return true;
}

void ArcherNormalAttack::onTimeOut()
{
	runAction(RemoveSelf::create());
}

void ArcherNormalAttack::onCollide(Actor* target)
{
	hurtEffect(target);
	playHitAudio();
	_owner->setAngry(_owner->getAngry() + target->hurt(this, true) * 0.3);
	struct MESSAGE_ANGRY_CHANGE angryChange = { ArcherValues._name, _owner->getAngry(),  _owner->getAngryMax() };
	MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, _owner);

	//	_owner->MDC->dispatchMessage(MessageType::ANGRY_CHANGE, angryChange);
		//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration = _duration + 1;
}

void ArcherNormalAttack::onUpdate(float dt)
{
	auto selfPos = getPosTable(this);
	auto nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	setPosition(nextPos);
}

ArcherSpecialAttack::ArcherSpecialAttack()
{
}

ArcherSpecialAttack* ArcherSpecialAttack::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner)
{
	auto ret = ArcherSpecialAttack::create();
	ret->initData(pos, facing, attackInfo);
	ret->_owner = owner;
	ret->_sp = Archer::createArrow();
	ret->_sp->setRotation(RADIANS_TO_DEGREES(-facing) - 90);
	ret->_sp->setCameraMask(2);
	ret->addChild(ret->_sp);
	return ret;
}

bool ArcherSpecialAttack::init()
{
	return true;
}

void ArcherSpecialAttack::onTimeOut()
{
	runAction(RemoveSelf::create());
}

void ArcherSpecialAttack::onCollide(Actor* target)
{
	if (_curDOTTime >= _DOTTimer) {
		hurtEffect(target);
		playHitAudio();
		_owner->setAngry(_owner->getAngry() + target->hurt(this, true) * 0.3);
		struct MESSAGE_ANGRY_CHANGE angryChange = { ArcherValues._name, _owner->getAngry(), _owner->getAngryMax() };
		MessageDispatchCenter::getInstance()->dispatchMessage(ANGRY_CHANGE, _owner);

		//MessageDispatchCenter::dispatchMessage(MessageDispatchCenter::MessageType::ANGRY_CHANGE, angryChange);*/
		_DOTApplied = true;
	}
}

void ArcherSpecialAttack::onUpdate(float dt)
{
	auto selfPos = getPosTable(this);
	auto nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	setPosition(nextPos);
	_curDOTTime += dt;
	if (_DOTApplied) {
		_DOTApplied = false;
		_curDOTTime = 0;
	}
}

Nova::Nova()
{

}

Nova* Nova::CreateWithPos(Vec2 pos, float facing)
{
	auto ret = Nova::create();
	ret->initData(pos, facing, BossValues.nova);
	ret->_sp = Sprite::createWithSpriteFrameName("nova1.png");
	ret->_sp->setGlobalZOrder(-ret->getPositionY() + FXZorder);
	ret->_sp->setPosition3D(Vec3(0, 0, 1));
	ret->addChild(ret->_sp);
	ret->_sp->setScale(0);
	ret->_sp->setCameraMask(2);
	ret->_sp->runAction(EaseCircleActionOut::create(ScaleTo::create(0.3, 3)));
	ret->_sp->runAction(FadeOut::create(0.7));
	return ret;
}

bool Nova::init()
{

	return true;
}

void Nova::onTimeOut()
{
	runAction(Sequence::create(DelayTime::create(1), RemoveSelf::create(), NULL));
}

void Nova::onCollide(Actor* target)
{
	if (_curDOTTime >= _DOTTimer) {
		hurtEffect(target);
		playHitAudio();
		_DOTApplied = true;
		target->hurt(this);
	}
}

void Nova::onUpdate(float dt)
{
	//implement this function if this is a projectile
	if (_DOTApplied) {
		_DOTApplied = false;
		_curDOTTime = 0;
	}
}

DragonAttack::DragonAttack()
{

}

DragonAttack* DragonAttack::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo)
{
	auto ret = DragonAttack::create();
	ret->initData(pos, facing, attackInfo);
	ret->_sp = BillBoard::create("FX/FX.png", RECTS.fireBall);
    ret->_sp->setPosition3D(Vec3(0, 0, 48));
	ret->addChild(ret->_sp);
	ret->_sp->setCameraMask(2);
	ret->_sp->setScale(1.7);
	return ret;
}

bool DragonAttack::init()
{
	return true;
}

void DragonAttack::onTimeOut()
{
	runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), NULL));
	auto pm = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	magic->setScale(1.5);
	magic->setRotation3D(Vec3(90, 0, 0));
	addChild(magic);
	magic->setGlobalZOrder(-getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);
	magic->setEndColor(ccc4f(255, 128, 0, 255));

	auto fireballAction = Animate::create(AnimationCache::getInstance()->getAnimation("fireBallAnim"));
	_sp->setCameraMask(2);
	_sp->runAction(fireballAction);
	_sp->setScale(2);
}

void DragonAttack::playHitAudio()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.fireHit, false, 0.6);
}

void DragonAttack::onCollide(Actor* target)
{
	hurtEffect(target);
	playHitAudio();
	target->hurt(this);
	//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration = _duration + 1;
}

void DragonAttack::onUpdate(float dt)
{
	auto selfPos = getPosTable(this);
	auto nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	setPosition(nextPos);
}

BossNormal::BossNormal()
{

}

BossNormal* BossNormal::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo)
{
	auto ret = BossNormal::create();
	ret->initData(pos, facing, attackInfo);
	ret->_sp = BillBoard::create("FX/FX.png", RECTS.fireBall);
	ret->_sp->setPosition3D(Vec3(0, 0, 48));
	ret->addChild(ret->_sp);
	ret->_sp->setScale(1.7);
	ret->_sp->setCameraMask(2);
	return ret;
}

bool BossNormal::init()
{
	return true;
}

void BossNormal::onTimeOut()
{
	runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), NULL));
	auto pm = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	magic->setScale(1.5);
	magic->setRotation3D(Vec3(90, 0, 0));
	addChild(magic);
	magic->setGlobalZOrder(-getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);
	magic->setEndColor(ccc4f(255, 128, 0, 255));

	auto fireballAction = Animate::create(AnimationCache::getInstance()->getAnimation("fireBallAnim"));
	_sp->runAction(fireballAction);
	_sp->setScale(2);
	Nova::CreateWithPos(getPosTable(this), _curFacing);
}

void BossNormal::playHitAudio()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.fireHit, false, 0.6);
}

void BossNormal::onCollide(Actor* target)
{
	//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration = _duration + 1;
}

void BossNormal::onUpdate(float dt)
{
	auto selfPos = getPosTable(this);
	auto nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	setPosition(nextPos);
}

BossSuper::BossSuper()
{

}

BossSuper* BossSuper::CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo)
{
	auto ret = BossSuper::create();
	ret->initData(pos, facing, attackInfo);
	ret->_sp = BillBoard::create("FX/FX.png", RECTS.fireBall);
	ret->_sp->setPosition3D(Vec3(0, 0, 48));
	ret->addChild(ret->_sp);
	ret->_sp->setScale(1.7);
	ret->_sp->setCameraMask(2);
	return ret;
}

bool BossSuper::init()
{
	return true;
}

void BossSuper::onTimeOut()
{
	runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf::create(), NULL));
	auto pm = ParticleManager::getInstance()->getPlistData("magic");
	auto magic = ParticleSystemQuad::create(pm);
	auto magicf = SpriteFrameCache::getInstance()->getSpriteFrameByName("particle.png");
	magic->setTextureWithRect(magicf->getTexture(), magicf->getRect());
	//magic->setCameraMask(943);
	magic->setScale(1.5);
	magic->setRotation3D(Vec3(90, 0, 0));
	addChild(magic);
	magic->setGlobalZOrder(-getPositionY() * 2 + FXZorder);
	magic->setPositionZ(0);
	magic->setEndColor(ccc4f(255, 128, 0, 255));

	auto fireballAction = Animate::create(AnimationCache::getInstance()->getAnimation("fireBallAnim"));
	_sp->runAction(fireballAction);
	_sp->setScale(2);
	Nova::CreateWithPos(getPosTable(this), _curFacing);
}

void BossSuper::playHitAudio()
{
	experimental::AudioEngine::play2d(MonsterDragonValues.fireHit, false, 0.6);
}

void BossSuper::onCollide(Actor* target)
{
	//set cur duration to its max duration, so it will be removed when checking time out
	_curDuration = _duration + 1;
}

void BossSuper::onUpdate(float dt)
{
	auto selfPos = getPosTable(this);
	auto nextPos = ccpRotateByAngle(ccpAdd(Vec2(_speed*dt, 0), selfPos), selfPos, _facing);
	setPosition(nextPos);
};