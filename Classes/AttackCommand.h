#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Actor;
class BasicCollider : public Node
{
public:
	BasicCollider();
	static BasicCollider* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo);
	void initData(Vec2 pos, float facing, struct attack_d attackInfo);
	CREATE_FUNC(BasicCollider);
	virtual bool init();

	virtual void onTimeOut();	//hit missed
	virtual void playHitAudio();
	virtual void hurtEffect(Actor* target);	//play hurt effect
	virtual void onCollide(Actor* target);	//hit enemy successfully
	virtual void onUpdate(float dt);	//move the attack
	

	//seter & geter
	float getDamage();
	void setDamage(float damage);
	float getKnock();
	void setKnock(float knock);
	float getCriticalChance();
	void setCriticalChance(float criticalChance);
	float getFacing();
	void setFacing(float facing);
	int getMask();
	float getMaxRange();
	float getMinRange();
	float getAngle();
	float getDuration();
	float getCurDuration();
	void setCurDuration(float curDuration);

protected:
	float _minRange;	//the min radius of the attack
	float _maxRange;	//the max radius of the attack
	float _angle;	//arc of attack, in rads
	float _knock;
	int _mask;	//1 is heroes, 2 is enemy
	float _damage;
	float _facing;	//the enemy direction, in rads
	float _curFacing;	//the current attack movement direction at the moment, in rads
	float _duration;	//the attack max duration
	float _curDuration;
	float _speed;	//traveling speed;
	float _criticalChance;
	float _curDOTTime;
	float _DOTTimer;
	bool _DOTApplied;
};

class KnightNormalAttack : public BasicCollider
{
public:
	KnightNormalAttack();
	static KnightNormalAttack* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* knight);
	CREATE_FUNC(KnightNormalAttack);
	virtual bool init();
	void onTimeOut();

private:
	Actor* _owner = nullptr;
};

class MageNormalAttack : public BasicCollider
{
public:
	MageNormalAttack();
	static MageNormalAttack* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* target, Actor* owner);
	CREATE_FUNC(MageNormalAttack);
	virtual bool init();

	void onTimeOut();
	void playHitAudio();
	void onCollide(Actor* target);
	void onUpdate(float dt);
private:
	Actor* _owner = nullptr;
	Actor* _target = nullptr;
	ParticleSystemQuad* _part1 = nullptr;
	ParticleSystemQuad* _part2 = nullptr;
	Sprite* _sp = nullptr;
};

class MageIceSpikes : public BasicCollider
{
public:
    MageIceSpikes();
	static MageIceSpikes* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(MageIceSpikes);
	virtual bool init();

	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner = nullptr;
	Sprite* _sp = nullptr;
	Actor* _target = nullptr;
	Node* _spikes = nullptr;
};

class ArcherNormalAttack : public BasicCollider
{
public:
	ArcherNormalAttack();
	static ArcherNormalAttack* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(ArcherNormalAttack);
	virtual bool init();

	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner = nullptr;
	Sprite3D* _sp = nullptr;
};

class ArcherSpecialAttack : public BasicCollider
{
public:
	ArcherSpecialAttack();
	static ArcherSpecialAttack* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(ArcherSpecialAttack);
	virtual bool init();

	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner = nullptr;
	Sprite3D* _sp = nullptr;
};

class Nova : public BasicCollider
{
public:
	Nova();
	static Nova* CreateWithPos(Vec2 pos, float facing);
	CREATE_FUNC(Nova);
	virtual bool init();

	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp = nullptr;
};

class DragonAttack : public BasicCollider
{
public:
	DragonAttack();
	static DragonAttack* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo);
	CREATE_FUNC(DragonAttack);
	virtual bool init();

	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp = nullptr;
};

class BossNormal : public BasicCollider
{
public:
	BossNormal();
	static BossNormal* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo);
	CREATE_FUNC(BossNormal);
	virtual bool init();

	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp = nullptr;
};

class BossSuper : public BasicCollider
{
public:
    BossSuper();
	static BossSuper* CreateWithPos(Vec2 pos, float facing, struct attack_d attackInfo);
	CREATE_FUNC(BossSuper);
	virtual bool init();

	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp = nullptr;
};

void solveAttacks(float dt);

extern std::vector<BasicCollider*> AttackManager;

