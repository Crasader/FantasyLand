#pragma once
#include "cocos2d.h"
#include "GlobalVariables.h"
#include "Manager.h"
#include "GameMaster.h"
#include "AttackCommand.h"

USING_NS_CC;

class MessageDispatchCenter;
class BasicCollider;
class HPCounter;

class Actor : public Node
{
public:	
	CREATE_FUNC(Actor);
	virtual bool init();
	void addEffect(Node* effect);
	void copyData();
	void initPuff();
	void initShadow();
	void playAnimation(std::string name, bool loop = false);

	//getter & setter
	EnumRaceType getRaceType();
	void setRaceType(EnumRaceType type);
	EnumStateType getStateType();
	void setStateType(EnumStateType type);
	void setTarget(Actor* target);
	void setFacing(float degrees);
	bool getAIEnabled();
	void setAIEnabled(bool enable);
	float getRadius();
	float getMass();
	float getAngry();
	Actor* getTarget();
	void setAngry(float angry);
	float getAngryMax();
	bool isAlive();
	Vec2 getMyPos();
	void setMyPos(Vec2 pos);
	void setGoRight(bool goRight);
	bool getGoRight();
	Node* getEffectNode();
	ParticleSystem* getPuff();

	virtual float hurt(BasicCollider* collider, bool dirKnockMode = false);
	virtual void hurtSoundEffects();
	virtual void normalAttackSoundEffects();
	virtual void specialAttackSoundEffects();
	virtual void playDyingEffects();
	
	//attacking collision check
	virtual void normalAttack();
	virtual void specialAttack();

	//State Machine switching functions
	virtual void idleMode();	//switch into idle mode
	virtual void walkMode();	//switch into walk mode
	virtual void attackMode();	//switch into attack mode
	virtual void knockMode(BasicCollider* collider, bool dirKnockMode = false);
	virtual void dyingMode(Vec2 knockSource, int knockAmount);

	//Base Update Functions
	void stateMachineUpdate(float dt);
	Actor* _findEnemy(EnumRaceType HeroOrMonster, bool &allDead);
	bool _inRange();

	//AI function does not run every tick
	void AI();
	void baseUpdate(float dt);
	void knockingUpdate(float dt);
	void attackUpdate(float dt);
	void walkUpdate(float dt);
	void movementUpdate(float dt);

	MessageDispatchCenter * MDC;

protected:
	float _aliveTime;	//time the actor is alive in seconds
	float _curSpeed;	//current speed the actor is traveling in units/seconds
	std::string _curAnimation;
	Action* _curAnimation3d;

	std::string _name;

	//runtime modified values
	float _curFacing;	//current direction the actor is facing, in radians, 0 is to the right
	bool _isalive;
	float _AITimer;	//accumulated timer before AI will execute, in seconds
	bool _AIEnabled; //if false, AI will not run
	float _attackTimer;	//accumulated timer to decide when to attack, in seconds
	float _timeKnocked;	//accumulated timer to recover from knock, in seconds
	bool _cooldown;	//if its true, then you are currently playing attacking animation
	float _hp = 1000;	//current hit point
	bool _goRight;
	
	//target variables
	float _targetFacing;//direction the actor Wants to turn to
	Actor* _target;	//the enemy actor;
	Vec2 _myPos;
	float _angry;
	float _angryMax;

	//other variables
	HPCounter* _hpCounter;
	Node* _effectNode;
	int _monsterHeight;
	int _heroHeight;
	ParticleSystem* _puff = nullptr;
	Sprite* _circle;
	Map<std::string, ActionInterval*> _action;

	int _useWeaponId;
	int _useArmourId;
	int _useHelmetId;
	ProgressTimer* _bloodBar;
	ProgressTimer* _bloodBarClone;
	Sprite* _avatar;

	//
	enum EnumRaceType _racetype;	//type of the actor
	enum EnumStateType _statetype;	//AI state machine
	Sprite* _sprite;
    Sprite3D* _sprite3d;	//place to hold 3d model

    float _radius;	//actor collider size
	float _shadowSize;	//weight of the role, it affects collision
	float _mass;	//the size of the shadow under the actor

	float _maxhp;
	float _defense;
	float _specialAttackChance;
	float _specialSlowTime;
	float _recoverTime;	//time takes to recover from knock, in seconds

	float _speed; //actor maximum movement speed in units/seconds
	float _turnSpeed;	//actor turning speed in radians/seconds
	float _acceleration;	//actor movement acceleration, in units/seconds
	float _decceleration;	//actor movement decceleration, in units/seconds

	float _AIFrequency;	//how often AI executes in seconds
	float _attackFrequency;	//an attack move every few seconds
	float _searchDistance;	//distance which enemy can be found

	float _attackRange;	//distance the actor will stop and commence attack
	//attack collider info, it can be customized
	struct attack_d _normalAttack;
};

struct ActorCommonValues;
struct ActorDefaultValues;