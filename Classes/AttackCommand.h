#pragma once

#include <list>
#include <numeric>
#include <algorithm>
#include "cocos2d.h"
#include "Actor.h"
#include "Helper.h"
#include "Manager.h"
#include "GlobalVariables.h"


USING_NS_CC;

class Actor;

class BasicCollider : public Node
{
public:
	BasicCollider();
	BasicCollider(Vec3 pos, int facing, std::string attackInfo);
	CREATE_FUNC(BasicCollider);
	virtual bool init();
	void onTimeOut();
	void playHitAudio();
	void hurtEffect(Actor* target);
	void onCollide(Actor* target);
	void onUpdate();
	void initData(Vec3 pos, int facing, std::string attackInfo);

protected:
	int minRange;	//the min radius of the fan
	int maxRange;	//the max radius of the fan
	float angle;	//arc of attack, in radians
	int knock;	//default knock;
	int mask;	//1 is Heroes, 2 is enemy, 3 ??
	int damage;
	float facing;	//this is radians
	float duration;
	float curDuration;
	int speed;	//traveling speed;
	int criticalChance;
};

class KnightNormalAttack : public BasicCollider
{
public:
	KnightNormalAttack();
	KnightNormalAttack(Vec3 pos, int facing, std::string attackInfo, Actor* knight);
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
	MageNormalAttack(Vec3 pos, int facing, std::string attackInfo, Actor* target, Actor* owner);
	CREATE_FUNC(MageNormalAttack);
	virtual bool init();
	void onTimeOut();
	void playHitAudio();
	void onCollide(Actor* target);
	void onUpdate(float dt);
private:
	Actor* _owner;
	Actor* _target;
};

class MageIceSpikes : public BasicCollider
{
public:
    MageIceSpikes();
	MageIceSpikes(Vec3 pos, int facing, std::string attackInfo, Actor* owner);
	CREATE_FUNC(MageIceSpikes);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onUpdate(float dt);

private:
	Actor* _owner;
};

class ArcherNormalAttack : public BasicCollider
{
public:
	ArcherNormalAttack();
	ArcherNormalAttack(Vec3 pos, int facing, std::string attackInfo, Actor* owner);
	CREATE_FUNC(ArcherNormalAttack);
	virtual bool init();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);

private:
	Actor* _owner;
};

class ArcherSpecialAttack : public BasicCollider
{
public:
	ArcherSpecialAttack();
	ArcherSpecialAttack(Vec3 pos, int facing, std::string attackInfo, Actor* owner);
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
	Nova(Vec3 pos, int facing);
	CREATE_FUNC(Nova);
	virtual bool init();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);
};

class DragonAttack : public BasicCollider
{
public:
	DragonAttack();
	DragonAttack(Vec3 pos, int facing, std::string attackInfo);
	CREATE_FUNC(DragonAttack);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);
};

class BossNormal : public BasicCollider
{
public:
	BossNormal();
	BossNormal(Vec3 pos, int facing, std::string attackInfo);
	CREATE_FUNC(BossNormal);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);
};

class BossSuper : public BasicCollider
{
public:
    BossSuper();
	BossSuper(Vec3 pos, int facing, std::string attackInfo);
	CREATE_FUNC(BossSuper);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);
};

std::list<BasicCollider*> AttackManager;

void solveAttacks(float dt);

