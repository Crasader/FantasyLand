#include "AttackCommand.h"

std::list<BasicCollider*> AttackManager;

void solveAttacks(float dt)
{

};

BasicCollider::BasicCollider()
{

};

void BasicCollider::CreateWithPos(Vec3 pos, int facing, std::string attackInfo)
{

};

bool BasicCollider::init()
{

};

void BasicCollider::onTimeOut()
{

};

void BasicCollider::playHitAudio()
{

};

void BasicCollider::hurtEffect(Actor* target)
{

};

void BasicCollider::onCollide(Actor* target)
{

};

void BasicCollider::onUpdate()
{

};

void BasicCollider::initData(Vec3 pos, int facing, std::string attackInfo)
{

};

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

KnightNormalAttack::KnightNormalAttack()
{

};

void KnightNormalAttack::CreateWithPos(Vec3 pos, int facing, std::string attackInfo, Actor* knight)
{

};

bool KnightNormalAttack::init()
{

};

void KnightNormalAttack::onTimeOut()
{

};

MageNormalAttack::MageNormalAttack()
{

};

void MageNormalAttack::CreateWithPos(Vec3 pos, int facing, std::string attackInfo, Actor* target, Actor* owner)
{

};

bool MageNormalAttack::init()
{

};

void MageNormalAttack::onTimeOut()
{

};

void MageNormalAttack::playHitAudio()
{

};

void MageNormalAttack::onCollide(Actor* target)
{

};

void MageNormalAttack::onUpdate(float dt)
{

};

MageIceSpikes::MageIceSpikes()
{

};

void MageIceSpikes::CreateWithPos(Vec3 pos, int facing, std::string attackInfo, Actor* owner)
{

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