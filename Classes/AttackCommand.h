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
	static void CreateWithPos(Vec2 pos, int facing, struct attackInfo);
	CREATE_FUNC(BasicCollider);
	virtual bool init();
	void onTimeOut();
	void playHitAudio();
	void hurtEffect(Actor* target);
	void onCollide(Actor* target);
	void onUpdate();
	void initData(Vec3 pos, int facing, std::string attackInfo);

	//set & get
	int getDamage();
	void setDamage(int damage);
	int getKnock();
	void setKnock(int knock);
	float getCriticalChance();
	void setCriticalChance(float criticalChance);
	float getFacing();
	void setFacing(float facing);

protected:
	int _minRange;	//the min radius of the fan
	int _maxRange;	//the max radius of the fan
	float _angle;	//arc of attack, in radians
	int _knock;	//default knock;
	int _mask;	//1 is Heroes, 2 is enemy, 3 ??
	int _damage;
	float _facing;	//this is radians
	float _duration;
	float _curDuration;
	int _speed;	//traveling speed;
	float _criticalChance;
};

class KnightNormalAttack : public BasicCollider
{
public:
	KnightNormalAttack();
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* knight);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* target, Actor* owner);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* owner);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* owner);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo, Actor* owner);
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
	static void CreateWithPos(Vec2 pos, int facing);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo);
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
	static void CreateWithPos(Vec2 pos, int facing, std::string attackInfo);
	CREATE_FUNC(BossSuper);
	virtual bool init();
	void playHitAudio();
	void onTimeOut();
	void onCollide(Actor* target);
	void onUpdate(float dt);
};

void solveAttacks(float dt);

