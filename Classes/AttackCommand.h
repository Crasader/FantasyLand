#pragma once

#include <list>
#include <numeric>
#include <algorithm>
#include "cocos2d.h"
#include "Actor.h"
#include "Helper.h"
#include "Manager.h"
#include "GlobalVariables.h"
#include "Archer.h"

USING_NS_CC;

class Actor;

class BasicCollider : public Node
{
public:
	BasicCollider();
	static BasicCollider* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo);
	CREATE_FUNC(BasicCollider);
	virtual bool init();
	void onTimeOut();
	void playHitAudio();
	void hurtEffect(Actor* target);
	void onCollide(Actor* target);
	void onUpdate();
	void initData(Vec2 pos, int facing, struct attack_d attackInfo);

	//set & get
	int getDamage();
	void setDamage(int damage);
	int getKnock();
	void setKnock(int knock);
	float getCriticalChance();
	void setCriticalChance(float criticalChance);
	int getFacing();
	void setFacing(int facing);
	int getMask();
	int getMaxRange();
	int getMinRange();
	float getAngle();
	float getDuration();
	float getCurDuration();
	void setCurDuration(float curDuration);

protected:
	int _minRange;	//the min radius of the fan
	int _maxRange;	//the max radius of the fan
	float _angle;	//arc of attack, in radians
	int _knock;	//default knock;
	int _mask;	//1 is Heroes, 2 is enemy, 3 ??
	int _damage;
	int _facing;	//this is radians
	int _curFacing;
	float _duration;
	float _curDuration;
	int _speed;	//traveling speed;
	float _criticalChance;
	float _curDOTTime;
	float _DOTTimer;
	bool _DOTApplied;
};

class KnightNormalAttack : public BasicCollider
{
public:
	KnightNormalAttack();
	static KnightNormalAttack* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo, Actor* knight);
	CREATE_FUNC(KnightNormalAttack);
	virtual bool init();
	void onTimeOut();

private:
	Actor* _owner;
};

class MageNormalAttack : public BasicCollider
{
public:
	MageNormalAttack();
	static MageNormalAttack* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo, Actor* target, Actor* owner);
	CREATE_FUNC(MageNormalAttack);
	virtual bool init();
	void onTimeOut();
	void playHitAudio();
	void onCollide(Actor* target);
	void onUpdate(float dt);
private:
	Actor* _owner;
	Actor* _target;
	ParticleSystemQuad* _part1;
	ParticleSystemQuad* _part2;
	BillBoard* _sp;
};

class MageIceSpikes : public BasicCollider
{
public:
    MageIceSpikes();
	static MageIceSpikes* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(MageIceSpikes);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner;
	Sprite* _sp;
	Actor* _target;
	Node* _spikes;
};

class ArcherNormalAttack : public BasicCollider
{
public:
	ArcherNormalAttack();
	static ArcherNormalAttack* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(ArcherNormalAttack);
	virtual bool init();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner;
	Sprite* _sp;
};

class ArcherSpecialAttack : public BasicCollider
{
public:
	ArcherSpecialAttack();
	static ArcherSpecialAttack* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo, Actor* owner);
	CREATE_FUNC(ArcherSpecialAttack);
	virtual bool init();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner;
};

class Nova : public BasicCollider
{
public:
	Nova();
	static Nova* CreateWithPos(Vec2 pos, int facing);
	CREATE_FUNC(Nova);
	virtual bool init();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp;
};

class DragonAttack : public BasicCollider
{
public:
	DragonAttack();
	static DragonAttack* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo);
	CREATE_FUNC(DragonAttack);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp;
};

class BossNormal : public BasicCollider
{
public:
	BossNormal();
	static BossNormal* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo);
	CREATE_FUNC(BossNormal);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp;
};

class BossSuper : public BasicCollider
{
public:
    BossSuper();
	static BossSuper* CreateWithPos(Vec2 pos, int facing, struct attack_d attackInfo);
	CREATE_FUNC(BossSuper);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Sprite* _sp;
};

void solveAttacks(float dt);

